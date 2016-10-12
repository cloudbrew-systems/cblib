
/*******************************************************
**	CloudBrew - Software Defined Distributed Public Cloud Storage	**
**	Sample file Hash capture to SQLite							**

**	File:		cbSqlite.c											**
**	Author: 	Runcy Oommen									**
**	Date:	02/22/2016										**

**	Copyright 2016 CloudBrew Systems. All rights reserved.			**
*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "cbSqlite.h"
#include "dbSqlite.h"
#include "cbDefines.h"
#include "MemMgr.h"

int cb_sqlite(char *param)
{
	if(strncmp(param, STR_SETUP, strlen(STR_SETUP)) == 0)
		cbHashDbUpdateSchema(DBH_CBHASH);

	return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	/* To be executed as ./cbSqlite argv[1] */
	/* argv[1] = setup */

	/* .cbSqlite setup needs to be run while bringing up a new environment or if there are any DB schema changes on existing environment */

	if(argc > 1)
	{
		if(strncmp(argv[1], STR_SETUP, strlen(STR_SETUP)) == 0)
		{
			cb_sqlite(argv[1]);
		}
		return EXIT_SUCCESS;
	}
	else
	{
		fprintf(stdout, "Something is definitely not looking right!\n");
		return EXIT_FAIL;
	}
}

