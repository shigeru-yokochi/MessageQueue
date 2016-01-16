#include <stdio.h>
#include <string.h>
#include <time.h>
#define MILLI_SEC 1000000



void SpeekTime(int nHour, int nMin,char *cpWavFileName);	//指定時間にしゃべる
void TimeRepeat(char *pStr);								//一定期間繰り返す
void SpeekCurrentTime(void);								//現在時刻をしゃべる
/*******************************************************************
* メイン
*******************************************************************/
void main(void)
{
	struct timespec req = {0, 500*MILLI_SEC};

	for(;;){
		SpeekTime(10,0,"ozv_asakai.wav");		//全体朝会
		SpeekTime(10,40,"system_asakai.wav");	//制作チーム朝会
		SpeekTime(18,48,"system_yukai.wav");	//制作チーム夕会
		SpeekCurrentTime();						//現在時刻をしゃべる
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
* 現在時刻をしゃべる
*******************************************************************/
void SpeekCurrentTime(void)
{
    time_t timer;
    struct tm *pNow;
	char zStr[256];

    timer = time(NULL);
   	pNow = localtime(&timer);

	if(pNow->tm_sec > 0)return;

	sprintf(zStr,"aplay -q /root/AquesTalk/aquestalkpi/wav/time/%02dhour.wav",pNow->tm_hour);
	system(zStr);

	if(pNow->tm_min%10 == 0){
		sprintf(zStr,"aplay -q /root/AquesTalk/aquestalkpi/wav/time/%02dmin.wav",pNow->tm_min);
		system(zStr);
	}
	else{
		if(pNow->tm_min/10 != 0){
			sprintf(zStr,"aplay -q /root/AquesTalk/aquestalkpi/wav/time/%dXmin.wav",pNow->tm_min/10);
			system(zStr);
		}
		sprintf(zStr,"aplay -q /root/AquesTalk/aquestalkpi/wav/time/%02dmin.wav",pNow->tm_min%10);
		system(zStr);
	}

	strcpy(zStr,"aplay -q /root/AquesTalk/aquestalkpi/wav/desu.wav");
	system(zStr);

	sleep(1);

}
/*******************************************************************
* memo(wavファイル作成方法)
*******************************************************************/
/*
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "全体あさかい始めますよー" -o /root/AquesTalk/aquestalkpi/wav/ozv_asakai.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "制作チームのあさかいですよー" -o /root/AquesTalk/aquestalkpi/wav/system_asakai.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "ゆうかいの時間ですよー" -o /root/AquesTalk/aquestalkpi/wav/system_yukai.wav

/root/AquesTalk/aquestalkpi/AquesTalkPi -b "ちょうど" -o /root/AquesTalk/aquestalkpi/wav/time/00min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅっぷん" -o /root/AquesTalk/aquestalkpi/wav/time/10min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "にじゅっぷん" -o /root/AquesTalk/aquestalkpi/wav/time/20min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "さんじゅっぷん" -o /root/AquesTalk/aquestalkpi/wav/time/30min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "よんじゅっぷん" -o /root/AquesTalk/aquestalkpi/wav/time/40min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "ごじゅっぷん" -o /root/AquesTalk/aquestalkpi/wav/time/50min.wav


/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅう" -o /root/AquesTalk/aquestalkpi/wav/time/1Xmin.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "にじゅう" -o /root/AquesTalk/aquestalkpi/wav/time/2Xmin.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "さんじゅう" -o /root/AquesTalk/aquestalkpi/wav/time/3Xmin.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "よんじゅう" -o /root/AquesTalk/aquestalkpi/wav/time/4Xmin.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "ごじゅう" -o /root/AquesTalk/aquestalkpi/wav/time/5Xmin.wav


/root/AquesTalk/aquestalkpi/AquesTalkPi -b "いっぷん" -o /root/AquesTalk/aquestalkpi/wav/time/01min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "にふん" -o /root/AquesTalk/aquestalkpi/wav/time/02min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "さんぷん" -o /root/AquesTalk/aquestalkpi/wav/time/03min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "よんふん" -o /root/AquesTalk/aquestalkpi/wav/time/04min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "ごふん" -o /root/AquesTalk/aquestalkpi/wav/time/05min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "ろっぷん" -o /root/AquesTalk/aquestalkpi/wav/time/06min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "ななふん" -o /root/AquesTalk/aquestalkpi/wav/time/07min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "はっぷん" -o /root/AquesTalk/aquestalkpi/wav/time/08min.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "きゅうふん" -o /root/AquesTalk/aquestalkpi/wav/time/09min.wav

/root/AquesTalk/aquestalkpi/AquesTalkPi -b "れいじ" -o /root/AquesTalk/aquestalkpi/wav/time/00hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "いちじ" -o /root/AquesTalk/aquestalkpi/wav/time/01hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "にじ" -o /root/AquesTalk/aquestalkpi/wav/time/02hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "さんじ" -o /root/AquesTalk/aquestalkpi/wav/time/03hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "よじ" -o /root/AquesTalk/aquestalkpi/wav/time/04hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "ごじ" -o /root/AquesTalk/aquestalkpi/wav/time/05hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "ろくじ" -o /root/AquesTalk/aquestalkpi/wav/time/06hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "しちじ" -o /root/AquesTalk/aquestalkpi/wav/time/07hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "はちじ" -o /root/AquesTalk/aquestalkpi/wav/time/08hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "くじ" -o /root/AquesTalk/aquestalkpi/wav/time/09hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅうじ" -o /root/AquesTalk/aquestalkpi/wav/time/10hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅういちじ" -o /root/AquesTalk/aquestalkpi/wav/time/11hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅうにじ" -o /root/AquesTalk/aquestalkpi/wav/time/12hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅうさんじ" -o /root/AquesTalk/aquestalkpi/wav/time/13hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅうよじ" -o /root/AquesTalk/aquestalkpi/wav/time/14hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅうごじ" -o /root/AquesTalk/aquestalkpi/wav/time/15hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅうろくじ" -o /root/AquesTalk/aquestalkpi/wav/time/16hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅうしちじ" -o /root/AquesTalk/aquestalkpi/wav/time/17hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅうはちじ" -o /root/AquesTalk/aquestalkpi/wav/time/18hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "じゅうくじ" -o /root/AquesTalk/aquestalkpi/wav/time/19hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "にじゅうじ" -o /root/AquesTalk/aquestalkpi/wav/time/20hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "にじゅういちじ" -o /root/AquesTalk/aquestalkpi/wav/time/21hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "にじゅうにじ" -o /root/AquesTalk/aquestalkpi/wav/time/22hour.wav
/root/AquesTalk/aquestalkpi/AquesTalkPi -b "にじゅうさんじ" -o /root/AquesTalk/aquestalkpi/wav/time/23hour.wav

/root/AquesTalk/aquestalkpi/AquesTalkPi -b "です。" -o /root/AquesTalk/aquestalkpi/wav/desu.wav

*/

