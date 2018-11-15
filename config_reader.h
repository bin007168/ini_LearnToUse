#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#ifdef __cplusplus
//extern "C"{
#endif
int openConfig(const char * confFileName);
unsigned int getu32Value(const char * grpName, const char * entryName);
int getIntValue(const char * grpName, const char * entryName);
unsigned char getu8Value(const char * grpName, const char * entryName) ;
double getdoubleValue(const char * grpName, const char * entryName);
char* getStrValue(const char * grpName, const char * entryName, char * entryBuf, int entryBufSize);
int getEnumValue(const char * grpName, const char * entryName);
float getFloatValue(const char * grpName, const char * entryName);

int setStrValue(const char * grpName, const char * entryName, char* buf, int bufSize);
int setValue(const char * grpName, const char * entryName, unsigned long val);
int setFourccValue(const char * grpName, const char * entryName, unsigned int val);
int setCodecValue(const char * grpName, const char * entryName, unsigned int val);

int saveConfig();
int closeConfig();
#ifdef __cplusplus
//}
#endif

#endif
