#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "cbLog.h"
#include "cbDefines.h"
#include "MemMgr.h"

#define PROC_NAME_LEN 128
#define MAX_TIME_STR 32

char *g_cbLogFileName = NULL;
static int g_cbLogLevel;
static FILE *g_logFP = NULL;

static const char *getpname(void)
{
	static char pProcPath[PROC_NAME_LEN] = "";
	static const char *pProcName = NULL;

	if (!pProcName)
	{
		/* Check the value one more time; it might have been set by another thread while we were waiting for the lock */
		if (!pProcName)
		{
			FILE *fCmdline = fopen("/proc/self/cmdline", "r");
			fgets(pProcPath, PROC_NAME_LEN, fCmdline);
			fclose(fCmdline);

			/* Strip any leading path info */
			char *pLastSlash;
			if ((pLastSlash = strrchr(pProcPath, '/')))
				pProcName = pLastSlash + 1;
			else
				pProcName = pProcPath;
		}
	}
	return pProcName;
}

char* cbLog_LogLevelFileName()
{
	/* Log level indicator file will be stored under the user's home directory */
	char *logLevelFileName = MEM_XMALLOC(MAX_LEN);
	if(logLevelFileName != NULL)
		snprintf(logLevelFileName, MAX_LEN, "%s/.cbLogLevel", getenv("HOME"));

	return logLevelFileName;
}

void cbLog_SetLevel(int logLevel)
{
	struct stat logBuf;
	int logLevelInFile;
	if(stat(CB_LOG_LEVEL_FILE, &logBuf) == 0)
	{
		FILE *fp = fopen(CB_LOG_LEVEL_FILE, "r");
		if(fp)
		{
			char buf[2] = {0};
			fread(buf, 1, 2, fp);
			logLevelInFile = atoi(buf); /* Get the current log level */
		}
	}

	char cmd[MAX_CMD_LEN] = {'\0'};
	snprintf(cmd, MAX_CMD_LEN, "echo %d > %s", logLevel, CB_LOG_LEVEL_FILE);
	system(cmd);
	g_cbLogLevel = logLevel;

	if(logLevelInFile != logLevel) /* Switch the log level and write approopriate log switch message only if different */
	{
		switch(logLevel)
		{
			case 0:
				CBLogDebug("Log level set to %s", cbLog_LevelToString(logLevel));
				break;
			case 1:
				CBLogInfo("Log level set to %s", cbLog_LevelToString(logLevel));
				break;
			case 2:
				CBLogNotice("Log level set to %s", cbLog_LevelToString(logLevel));
				break;
			case 3:
				CBLogWarn("Log level set to %s", cbLog_LevelToString(logLevel));
				break;
			case 4:
				CBLogError("Log level set to %s", cbLog_LevelToString(logLevel));
				break;
		}
	}
}

int cbLog_GetLevel(void)
{
	return g_cbLogLevel;
}

int cbLog_ClearLogs()
{
	char cmd[MAX_CMD_LEN] = {'\0'};
	snprintf(cmd, MAX_CMD_LEN, "cat /dev/null > %s/%s", getenv("HOME"), CB_LOG_NAME); /* Clear out CB logs */
	system(cmd);

	fprintf(stdout, "All CloudBrew logs cleared\n");
	return EXIT_SUCCESS;
}

char *cbLog_LogFileName(void)
{
	return (g_cbLogFileName ? strdup(g_cbLogFileName) : NULL);
}

const char * cbLog_LevelToString(CB_LOG_LEVEL cbLogLevel)
{
	switch (cbLogLevel)
	{
		case CB_LOG_DEBUG:
			return "Debug";
		case CB_LOG_INFO:
			return "Info";
		case CB_LOG_NOTICE:
			return "Notice";
		case CB_LOG_WARN:
			return "Warning";
		case CB_LOG_ERROR:
			return "Error";
		default:/* Invalid input */
			return NULL;
	}
}

void enableDebugLogging(int debugMode)
{
	if(debugMode == 1)
	{
		g_cbLogLevel = CB_LOG_DEBUG;
	}
}

#define MAX_COUNTER 20
#define MAX_LOG_FILE_SIZE 0x20000000 /* 512 MB */

static int isMaxFileSizeExceeded(int maxSize)
{
	static int counter = MAX_COUNTER;
	static int maxFileSizeExceeded = 0;

	if(maxFileSizeExceeded == 1)
		return maxFileSizeExceeded; /* If max file size is already reached, do nothing */
	
	if(!g_cbLogFileName)
		return EXIT_FAIL; /* Should never happen - return 1 to be safe - don't log if file was not created */
	
	if(counter <= 0)
	{
		counter = MAX_COUNTER; /* Reset counter */
		struct stat buf;

		if(maxFileSizeExceeded == 0)
		{
			fprintf(g_logFP, "Checking log size ...\n");
		}

		
		if(stat(g_cbLogFileName, &buf) >= 0)
		{
			if(buf.st_size >= maxSize)
			{
				maxFileSizeExceeded = 1; /* Turn OFF debug logging until rotation */
				fprintf(g_logFP, "Max log file size exceeded (0X%x bytes). Logging will be disabled\n", maxSize); fflush(g_logFP);
			}
			else
			{
				maxFileSizeExceeded = 0;
			}
		}
		else
		{
			fprintf(g_logFP, "Checking log size failed: %s\n", strerror(errno));
		}
	}
	else
	{
		counter--;
	}

	return maxFileSizeExceeded;
}

int cbLog_IsDebugLoggingEnabled(void)
{
	return  ((g_cbLogLevel == CB_LOG_DEBUG) || (g_cbLogLevel == CB_LOG_INFO));
}

static void getCurrentTime4Log(char * timeBuffer)
{
	time_t currTime;
	struct tm splitTime, *pSplitTime = NULL;

	currTime = time(&currTime);
	pSplitTime = gmtime_r(&currTime, &splitTime);

	if(pSplitTime)
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);

		sprintf(timeBuffer, "\"%4d-%02d-%02d %02d:%02d:%02d.%03lu\"", pSplitTime->tm_year+1900, pSplitTime->tm_mon+1, pSplitTime->tm_mday, pSplitTime->tm_hour, pSplitTime->tm_min, pSplitTime->tm_sec, tv.tv_usec/1000);
	}
}

void cbLog(int loglevel, const char *fmt, ...)
{
	va_list ap;
	if(g_logFP == NULL)
	{
		asprintf(&g_cbLogFileName, "%s/%s", getenv("HOME"), CB_LOG_NAME);
		
		if((g_logFP = fopen(g_cbLogFileName, "a")) == NULL)
		{
			fprintf(stderr, "Unable to open log file:%s", g_cbLogFileName);
			return;
		}
	}

	struct stat logBuf;
	if(stat(CB_LOG_LEVEL_FILE, &logBuf) != 0) /* If log level file does not exist, set to Notice */
	{
		char cmd[MAX_CMD_LEN] = {'\0'};
		snprintf(cmd, MAX_CMD_LEN, "echo %d > %s", CB_LOG_NOTICE, CB_LOG_LEVEL_FILE);
		system(cmd);
		g_cbLogLevel = CB_LOG_NOTICE;
	}
	else /* Read from file and set level accordingly */
	{
		FILE *mcLogLevelFile;
		mcLogLevelFile = fopen(CB_LOG_LEVEL_FILE, "r");
		if(mcLogLevelFile)
		{
			char logLevel[SHORT_LEN];
			fgets(logLevel, 2, mcLogLevelFile);
			g_cbLogLevel = atoi((const char*)logLevel);
			fclose(mcLogLevelFile);
		}
	}

	if(g_cbLogLevel > loglevel)
		return;

	if(isMaxFileSizeExceeded(MAX_LOG_FILE_SIZE) == 1)
	{
		return;
	}

	/* Get the timestamp in UTC */
	char localTimeBuf[MAX_TIME_STR]	= {0};	
	localTimeBuf[0] = '\0';
	getCurrentTime4Log(localTimeBuf);
	fprintf(g_logFP, "%s:", localTimeBuf);

	fprintf(g_logFP, "%s:", cbLog_LevelToString(loglevel));

	const char *pProcName = getpname();
	if (pProcName)
		fprintf(g_logFP, "%s ", pProcName);

	fprintf(g_logFP, "%d: ", getpid());

	va_start(ap, fmt);
	vfprintf(g_logFP,  fmt, ap);
	va_end(ap);

	fprintf(g_logFP, "\n");		

	fflush(g_logFP);

	fclose(g_logFP);
	g_logFP = NULL;

	return;
}
