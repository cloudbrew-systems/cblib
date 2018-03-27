
#ifdef __cplusplus
extern "C" {
#endif

#ifndef CB_LOG_H
#define CB_LOG_H

#define CB_LOG_NAME ".cb.log"
#define CB_LOG_LEVEL_FILE cbLog_LogLevelFileName()

typedef enum cb_log_level_t{
	CB_LOG_DEBUG = 0,/* Highest - max logs */
	CB_LOG_INFO,
	CB_LOG_NOTICE, /* Default - optimal logs */
	CB_LOG_WARN,
	CB_LOG_ERROR /* Lowest - min logs */
}CB_LOG_LEVEL;

extern void cbLog(int loglevel, const char *fmt, ...);

#define CBLogError(...) cbLog(CB_LOG_ERROR, __VA_ARGS__)
#define CBLogWarn(...) cbLog(CB_LOG_WARN, __VA_ARGS__)
#define CBLogNotice(...) cbLog(CB_LOG_NOTICE, __VA_ARGS__)
#define CBLogInfo(...) cbLog(CB_LOG_INFO, __VA_ARGS__)
#define CBLogDebug(...) cbLog(CB_LOG_DEBUG, __VA_ARGS__)

void cbLog_SetLevel(int logLevel);
int  cbLog_GetLevel(void);
int cbLog_ClearLogs(void);
char *cbLog_LogFileName(void);
const char * cbLog_LevelToString(CB_LOG_LEVEL cbLogLevel);
int  cbLog_IsDebugLoggingEnabled(void);
char *cbLog_LogLevelFileName(void);

#endif /* CB_LOG_H */

#ifdef __cplusplus
}
#endif

