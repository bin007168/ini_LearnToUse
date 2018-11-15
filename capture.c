/******************************************************
** File Name   : capture.c
** The author  : hzbin
** E-mail      : hzbin@stonkam.com
** Created Time: 2018年11月15日 星期四 09时36分55秒
*******************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "config.h"
#include "list.h"
#include "config_reader.h"

#define u32 unsigned int
#define u8  unsigned char

#define CAPTURE_INI_PATH "./cap.ini"

#define FILE_PATH_LEN 128

typedef struct VidCapParm
{
	char fourcc[FILE_PATH_LEN];
	u32 width;
	u32 height;
	u8 fps;
}VidCapParm;

VidCapParm gVideoCapParm;

int main(int argc,char *argv[])
{
	int exitCode=0;
	if((exitCode=openConfig(CAPTURE_INI_PATH)) != 0){
		printf("no found the ./cap.ini file\n");
		return 0;
	}
	
   	gVideoCapParm.width=getu32Value((char*)"VidCapParm",(char*)"width");
	gVideoCapParm.height=getu32Value((char*)"VidCapParm",(char*)"height");
	getStrValue("VidCapParm","fourcc",gVideoCapParm.fourcc,FILE_PATH_LEN);
//	gVideoCapParm.fourcc=(u32)getEnumValue((char*)"VidCapParm",(char*)"fourcc");
	gVideoCapParm.fps=getu8Value((char*)"VidCapParm",(char*)"fps");

	printf("gVideoCapParm.width is %d\n",gVideoCapParm.width);
	printf("gVideoCapParm.height is %d\n",gVideoCapParm.height);
	printf("gVideoCapParm.fourcc is %s\n",gVideoCapParm.fourcc);
	printf("gVideoCapParm.fps is %d\n",gVideoCapParm.fps);
   
   return 0;



}




















