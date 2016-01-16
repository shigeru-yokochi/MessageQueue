#include <stdio.h>
#include <string.h>
#include <time.h>
#define MILLI_SEC 1000000



void SpeekTime(int nHour, int nMin,char *cpWavFileName);	//指定時間にしゃべる
void TimeRepeat(char *pStr);								//一定期間繰り返す
/*******************************************************************
* メイン
*******************************************************************/
void main(void)
{
	struct timespec req = {0, 500*MILLI_SEC};

	for(;;){
		SpeekTime(16,24,"ozv_asakai.wav");		//全体朝会
		SpeekTime(16,25,"system_asakai.wav");	//制作チーム朝会
		SpeekTime(16,26,"system_yukai.wav");		//制作チーム夕会

		nanosleep(&req, NULL);

//    	printf("%04d/%02d/%02d %02d:%02d:%02d\n",pNow->tm_year+1900,pNow->tm_mon+1,pNow->tm_mday,pNow->tm_hour,pNow->tm_min,pNow->tm_sec);
	}
}
/*******************************************************************
* 指定時間にしゃべる
*******************************************************************/
void SpeekTime(int nHour, int nMin,char *cpWavFileName)
{
    time_t timer;
    struct tm *pNow;
	char zStr[256];

    timer = time(NULL);
   	pNow = localtime(&timer);

	if(pNow->tm_hour == nHour && pNow->tm_min == nMin && pNow->tm_sec < 1){
		sprintf(zStr,"aplay -q /root/AquesTalk/aquestalkpi/wav/%s",cpWavFileName);
		TimeRepeat(zStr);
	}
}
/*******************************************************************
* 一定期間繰り返す
*******************************************************************/
void TimeRepeat(char *pStr)
{
	time_t start_time;
	
	start_time = time(NULL);
	for(;;){
		system(pStr);
		if(difftime(time(NULL), start_time) > 20.)break;		//20sec
	}
}


/*******************************************************************
* memo(wavファイル作成方法)
*******************************************************************/
// /root/AquesTalk/aquestalkpi/AquesTalkPi -b "全体あさかい始めますよー" -o /root/AquesTalk/aquestalkpi/wav/ozv_asakai.wav
// /root/AquesTalk/aquestalkpi/AquesTalkPi -b "制作チームのあさかいですよー" -o /root/AquesTalk/aquestalkpi/wav/system_asakai.wav
// /root/AquesTalk/aquestalkpi/AquesTalkPi -b "ゆうかいの時間ですよー" -o /root/AquesTalk/aquestalkpi/wav/system_yukai.wav


