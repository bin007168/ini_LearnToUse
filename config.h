/*
 *  libConfig.h
 *
 *  General list structure
 *
 *  Author:  IAN
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#ifndef _LIBCONFIG_HEADER
#define _LIBCONFIG_HEADER

#include "list.h"

#define MAX_LEN_CFG 128
#define MAX_LEN_GROUP_NAME 32
#define MAX_LEN_ENTRY_NAME 32
#define MAX_LEN_ENTRY_VALUE 256
//!
#define MAX_LEN_ENTRY_COMMENT 256
/*
typedef struct _tagConfigEntry {
	char name[MAX_LEN_ENTRY_NAME];
	int nameLen;
	char value[MAX_LEN_ENTRY_VALUE];
	int valueLen;
	List  listEntry;
} ConfigEntry, *pConfigEntry;

typedef struct _tagConfigGroup {
	char name[MAX_LEN_GROUP_NAME];
	List  listGroup;
	int   numEntry;
	ConfigEntry listConfigEntry;
} ConfigGroup, *pConfigGroup;

int setCurConfigGroup(char * grpName);
int addConfigGroup(char * grpName);
int parseConfigFile();

int initConfigs();
int freeConfigs();
*/
#ifdef __cplusplus
extern "C"{
#endif

int openConfigFile(const char * confFileName);
int getConfigEntry(const char * grpName, const char * entryName, char * entryBuf, int entryBufSize);
int setConfigEntry(const char * grpName, const char * entryName, char * entryBuf, int entryBufSize);
int saveConfigFile();
int closeConfigFile();

int dumpConfigs();
#ifdef __cplusplus
}
#endif

#endif

