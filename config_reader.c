#include"config.h"
#include"config_reader.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

static const char* strPixFormat[] = {
    "PIX_FMT_YUV420P",   ///< Planar YUV 4:2:0 (1 Cr & Cb sample per 2x2 Y samples) (I420)
    "PIX_FMT_NV12",      ///< Packed YUV 4:2:0 (separate Y plane, interleaved Cb & Cr planes)
    "PIX_FMT_NV21",      ///< Packed YUV 4:2:0 (separate Y plane, interleaved Cb & Cr planes)
    "PIX_FMT_YVU420P",   ///< Planar YUV 4:2:0 (1 Cb & Cr sample per 2x2 Y samples) (YV12)
    "PIX_FMT_YUV422",    ///< Packed pixel, Y0 Cb Y1 Cr
    "PIX_FMT_RGB24",     ///< Packed pixel, 3 bytes per pixel, RGBRGB...
    "PIX_FMT_BGR24",     ///< Packed pixel, 3 bytes per pixel, BGRBGR...
    "PIX_FMT_YUV422P",   ///< Planar YUV 4:2:2 (1 Cr & Cb sample per 2x1 Y samples)
    "PIX_FMT_YUV444P",   ///< Planar YUV 4:4:4 (1 Cr & Cb sample per 1x1 Y samples)
    "PIX_FMT_RGBA32",    ///< Packed pixel, 4 bytes per pixel, BGRABGRA..., stored in cpu endianness
    "PIX_FMT_BGRA32",    ///< Packed pixel, 4 bytes per pixel, ARGBARGB...
    "PIX_FMT_ARGB32",    ///< Packed pixel, 4 bytes per pixel, ABGRABGR..., stored in cpu endianness
    "PIX_FMT_ABGR32",    ///< Packed pixel, 4 bytes per pixel, RGBARGBA...
    "PIX_FMT_RGB32",     ///< Packed pixel, 4 bytes per pixel, BGRxBGRx..., stored in cpu endianness
    "PIX_FMT_xRGB32",    ///< Packed pixel, 4 bytes per pixel, xBGRxBGR..., stored in cpu endianness
    "PIX_FMT_BGR32",     ///< Packed pixel, 4 bytes per pixel, xRGBxRGB...
    "PIX_FMT_BGRx32",    ///< Packed pixel, 4 bytes per pixel, RGBxRGBx...
    "PIX_FMT_YUV410P",   ///< Planar YUV 4:1:0 (1 Cr & Cb sample per 4x4 Y samples)
    "PIX_FMT_YVU410P",   ///< Planar YVU 4:1:0 (1 Cr & Cb sample per 4x4 Y samples)
    "PIX_FMT_YUV411P",   ///< Planar YUV 4:1:1 (1 Cr & Cb sample per 4x1 Y samples)
    "PIX_FMT_Y800",      ///< 8 bit Y plane (range [16-235])
    "PIX_FMT_Y16",       ///< 16 bit Y plane (little endian)
    "PIX_FMT_RGB565",    ///< always stored in cpu endianness
    "PIX_FMT_RGB555",    ///< always stored in cpu endianness, most significant bit to 1
    "PIX_FMT_GRAY8",
    "PIX_FMT_GRAY16_L",
    "PIX_FMT_GRAY16_B",
    "PIX_FMT_MONOWHITE", ///< 0 is white
    "PIX_FMT_MONOBLACK", ///< 0 is black
    "PIX_FMT_PAL8",      ///< 8 bit with RGBA palette
    "PIX_FMT_YUVJ420P",  ///< Planar YUV 4:2:0 full scale (jpeg)
    "PIX_FMT_YUVJ422P",  ///< Planar YUV 4:2:2 full scale (jpeg)
    "PIX_FMT_YUVJ444P",  ///< Planar YUV 4:4:4 full scale (jpeg)
    "PIX_FMT_XVMC_MPEG2_MC",///< XVideo Motion Acceleration via common packet passing(xvmc_render.h)
    "PIX_FMT_XVMC_MPEG2_IDCT",
    "PIX_FMT_UYVY422",   ///< Packed pixel, Cb Y0 Cr Y1
    "PIX_FMT_YVYU422",   ///< Packed pixel, Y0 Cr Y1 Cb
    "PIX_FMT_UYVY411",   ///< Packed pixel, Cb Y0 Y1 Cr Y2 Y3
    "PIX_FMT_V308",      ///< Packed pixel, Y0 Cb Cr

    "PIX_FMT_AYUV4444",  ///< Packed pixel, A0 Y0 Cb Cr
    "PIX_FMT_YUVA420P",   ///< Planar YUV 4:4:2:0 (1 Cr & Cb sample per 2x2 Y & A samples) (A420)
    "PIX_FMT_NB"
};

static const char *strCodecID[] = {
    "CODEC_ID_NONE",

    /* video codecs */
    "CODEC_ID_RAWVIDEO",

    "CODEC_ID_H263",
    "CODEC_ID_MPEG4",
    "CODEC_ID_MSV1",
    "CODEC_ID_H264",
    "CODEC_ID_FFH264",
    "CODEC_ID_AMV",
    "CODEC_ID_MJPEG",

	/* various PCM "codecs" */
    "CODEC_ID_PCM_S16LE",//= 0x10000
    "CODEC_ID_PCM_S16BE",
    "CODEC_ID_PCM_U16LE",
    "CODEC_ID_PCM_U16BE",
    "CODEC_ID_PCM_S8",
    "CODEC_ID_PCM_U8",
    "CODEC_ID_PCM_MULAW",
    "CODEC_ID_PCM_ALAW",
    "CODEC_ID_PCM_S32LE",
    "CODEC_ID_PCM_S32BE",
    "CODEC_ID_PCM_U32LE",
    "CODEC_ID_PCM_U32BE",
    "CODEC_ID_PCM_S24LE",
    "CODEC_ID_PCM_S24BE",
    "CODEC_ID_PCM_U24LE",
    "CODEC_ID_PCM_U24BE",
    "CODEC_ID_PCM_S24DAUD",
    "CODEC_ID_PCM_ZORK",
    "CODEC_ID_PCM_S16LE_PLANAR",
    "CODEC_ID_PCM_DVD",
    "CODEC_ID_PCM_F32BE",
    "CODEC_ID_PCM_F32LE",
    "CODEC_ID_PCM_F64BE",
    "CODEC_ID_PCM_F64LE",
    "CODEC_ID_PCM_BLURAY",
	/* various ADPCM codecs */
    "CODEC_ID_ADPCM_IMA_QT",//= 0x11000
    "CODEC_ID_ADPCM_IMA_WAV",
    "CODEC_ID_ADPCM_IMA_DK3",
    "CODEC_ID_ADPCM_IMA_DK4",
    "CODEC_ID_ADPCM_IMA_WS",
    "CODEC_ID_ADPCM_IMA_SMJPEG",
    "CODEC_ID_ADPCM_MS",
    "CODEC_ID_ADPCM_4XM",
    "CODEC_ID_ADPCM_XA",
    "CODEC_ID_ADPCM_ADX",
    "CODEC_ID_ADPCM_EA",
    "CODEC_ID_ADPCM_G726",
    "CODEC_ID_ADPCM_CT",
    "CODEC_ID_ADPCM_SWF",
    "CODEC_ID_ADPCM_YAMAHA",
    "CODEC_ID_ADPCM_SBPRO_4",
    "CODEC_ID_ADPCM_SBPRO_3",
    "CODEC_ID_ADPCM_SBPRO_2",
    "CODEC_ID_ADPCM_THP",
    "CODEC_ID_ADPCM_IMA_AMV",
    "CODEC_ID_ADPCM_EA_R1",
    "CODEC_ID_ADPCM_EA_R3",
    "CODEC_ID_ADPCM_EA_R2",
    "CODEC_ID_ADPCM_IMA_EA_SEAD",
    "CODEC_ID_ADPCM_IMA_EA_EACS",
    "CODEC_ID_ADPCM_EA_XAS",
    "CODEC_ID_ADPCM_EA_MAXIS_XA",
    "CODEC_ID_ADPCM_IMA_ISS",
	/* AMR */
	"CODEC_ID_AMR_NB",//= 0x12000
	"CODEC_ID_AMR_WB",

	/* various DPCM codecs */
	"CODEC_ID_ROQ_DPCM",//0x14000
	"CODEC_ID_INTERPLAY_DPCM",
	"CODEC_ID_XAN_DPCM",
	"CODEC_ID_SOL_DPCM",

	/* audio codecs */
	"CODEC_ID_MP2",//0x15000
	"CODEC_ID_MP3", ///< preferred ID for decoding MPEG audio layer 1, 2 or 3
	"CODEC_ID_AAC",

	/* subtitle codecs */
	"CODEC_ID_DVD_SUBTITLE",//0x17000
	"CODEC_ID_DVB_SUBTITLE",
	"CODEC_ID_TEXT",	///< raw UTF-8 text
	"CODEC_ID_XSUB",
	"CODEC_ID_SSA"

};
#define PCM_START_POS 9
#define ADPCM_START_POS 34
#define AMR_START_POS 62
#define DPCM_START_POS 64
#define AUDIO_START_POS 68
#define SUBTITLE_START_POS 71

//string to unique value
int str2enum(const char* str)
{
	int fooEnum = -1;
	int i;

	if(strncmp(str,strPixFormat[0],strlen("PIX_FMT"))==0)
	{
		int count = sizeof (strPixFormat) / sizeof (strPixFormat[0]);

		for ( i = 0; i < count; ++i)
		{
			if (strcmp (str, strPixFormat[i])==0)
			{
				fooEnum = i;
				break ;
			}
		}
	}
	else if(strncmp(str,strCodecID[0],strlen("CODEC_ID"))==0)
	{
		int count = sizeof (strCodecID) / sizeof (strCodecID[0]);
		if(strncmp(str,strCodecID[PCM_START_POS],strlen("CODEC_ID_PCM"))==0)//CODEC_ID_PCM
			i = PCM_START_POS;
		else if(strncmp(str,strCodecID[PCM_START_POS],strlen("CODEC_ID_ADPCM"))==0)//CODEC_ID_ADPCM
			i = ADPCM_START_POS;
		else i= 0;
		for (; i < count; ++i)
		{
			if (strcmp (str, strCodecID[i])==0)
			{
				fooEnum = i;
				break ;
			}
		}
		if(fooEnum >= SUBTITLE_START_POS)fooEnum=fooEnum-SUBTITLE_START_POS+0x17000;
		else if(fooEnum >= AUDIO_START_POS)fooEnum=fooEnum-AUDIO_START_POS+0x15000;
		else if(fooEnum >= DPCM_START_POS)fooEnum=fooEnum-DPCM_START_POS+0x14000;
		else if(fooEnum >= AMR_START_POS)fooEnum=fooEnum-AMR_START_POS+0x12000;
		else if(fooEnum >= ADPCM_START_POS)fooEnum=fooEnum-ADPCM_START_POS+0x11000;
		else if(fooEnum >= PCM_START_POS)fooEnum=fooEnum-PCM_START_POS+0x10000;
	}
	return fooEnum;
}
//enum value to unique string
const char* enum2str_pix(unsigned int enumval)
{
	return strPixFormat[enumval];
}

const char* enum2str_codec(unsigned int enumval)
{
	if(enumval >= 0x17000)enumval=enumval-0x17000+SUBTITLE_START_POS;
	else if(enumval >= 0x15000)enumval=enumval-0x15000+AUDIO_START_POS;
	else if(enumval >= 0x14000)enumval=enumval-0x14000+DPCM_START_POS;
	else if(enumval >= 0x12000)enumval=enumval-0x12000+AMR_START_POS;
	else if(enumval >= 0x11000)enumval=enumval-0x11000+ADPCM_START_POS;
	else if(enumval >= 0x10000)enumval=enumval-0x10000+PCM_START_POS;
	return strCodecID[enumval];
}



int openConfig(const char * confFileName)
{
	return openConfigFile(confFileName);
}
//get
unsigned long getulongValue(const char * grpName,const char * entryName)
{
	if(grpName == NULL || entryName == NULL){return 0;}
	int bufSize=32;
	char ulongBuf[bufSize];

	if(getConfigEntry(grpName,entryName,ulongBuf,bufSize-1) != 0)
	{return 0;}

	unsigned long retVal=strtoul(ulongBuf,NULL,10);
	return retVal;
}

unsigned int getu32Value(const char * grpName,const char * entryName)
{//it may cut off the value,but that caused by users..
	return (unsigned int)getulongValue(grpName,entryName);
}

int getIntValue(const char * grpName,const char * entryName)
{
	return (int)getulongValue(grpName,entryName);
}

unsigned char getu8Value(const char * grpName,const char * entryName)
{
	return (unsigned char)getulongValue(grpName,entryName);
}

char* getStrValue(const char * grpName,const char * entryName, char * entryBuf, int entryBufSize)
{
	if(grpName == NULL || entryName == NULL || entryBuf == NULL || entryBufSize <= 0)return NULL;
	if(getConfigEntry(grpName,entryName,entryBuf,entryBufSize) != 0)
		return NULL;
	return entryBuf;
}

int getEnumValue(const char * grpName,const char * entryName)
{
	if(grpName == NULL || entryName == NULL){return 0;}
	int bufSize=128;
	char StrBuf[bufSize];

	if(getConfigEntry(grpName,entryName,StrBuf,bufSize-1) != 0)
	{return 0;}

	int retVal = str2enum(StrBuf);
	return retVal;
}

double getdoubleValue(const char * grpName,const char * entryName)
{
	if(grpName == NULL || entryName == NULL){return 0;}
	int bufSize=sizeof(double)*8 + 1;
	char doubleBuf[bufSize];

	if(getConfigEntry(grpName,entryName,doubleBuf,bufSize-1) != 0)
	{return 0;}

	double retVal=strtod(doubleBuf,NULL);
	return retVal;
}

float getFloatValue(const char * grpName,const char * entryName)
{
	if(grpName == NULL || entryName == NULL){return 0;}
	int bufSize=128;
	char floatBuf[bufSize];
	float data;
	if(getConfigEntry(grpName,entryName,floatBuf,bufSize-1) != 0)
	{return 0;}
	sscanf(floatBuf,"%f",&data);

	return data;
}

//set
int setValue(const char * grpName,const char * entryName,unsigned long val)
{//int or u32 or u8 may use this version..
	if(grpName == NULL || entryName == NULL){return 0;}
	int bufSize=32;
	char ulongBuf[bufSize];

	sprintf(ulongBuf,"%lu",val);

	return setConfigEntry(grpName,entryName,ulongBuf,bufSize-1);
}
int setStrValue(const char * grpName,const char * entryName,char* buf,int bufSize)
{//int or u32 or u8 may use this version..
	if(grpName == NULL || entryName == NULL){return 0;}

	return setConfigEntry(grpName,entryName,buf,bufSize-1);
}

//specified
int setFourccValue(const char * grpName,const char * entryName,unsigned int val)
{
	if(grpName == NULL || entryName == NULL){return 0;}
	int bufSize=128;
	char buf[bufSize];

	strcpy(buf,enum2str_pix(val));

	return setConfigEntry(grpName,entryName,buf,bufSize-1);
}
int setCodecValue(const char * grpName,const char * entryName,unsigned int val)
{
	if(grpName == NULL || entryName == NULL){return 0;}
	int bufSize=128;
	char buf[bufSize];

	strcpy(buf,enum2str_codec(val));

	return setConfigEntry(grpName,entryName,buf,bufSize-1);
}



int saveConfig()
{
	return saveConfigFile();
}
int closeConfig()
{
	return closeConfigFile();
}




