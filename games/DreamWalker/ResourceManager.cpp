#include "../../include/SWEngine.h"


//Lights
int sprPlatformID       = -1;
int imgStageLightsBgID  = -1;  
int imgsGreenPlatformID[3];
int imgsYellowPlatformID[3];
int imgsRedPlatformID[3];
int sprActorID = -1;

//Colors
int imgColorIDS[3];

//Crossing
int imgCrossPlatformID=-1;
int imgStageCrossingBgID=-1; 
int imgStageCrossingBgLayoutID=-1; 

//Sleep
int sprSleepBtnMOverImgID = -1;
int sprSleepItself        = -1;

//WakeUp
int sprWakeupBtnMOverImgID = -1;
int sprWakeupItself		   = -1;

//MainMenu
int imgmainMenuBgID = -1;

//Sound
int soundSourceID=-1;
int horrBufferID=-1;
int alarmBufferID=-1;
int dropBufferID=-1;

int bgSoundSourceID=-1;
int menuBgBufferID=-1;
int gameBgBufferID=-1;

int endOfSceneSourceID=-1;
int endOfSceneBufferID=-1;


//End of Scene
int imgYouDiedID=-1;
int imgEndOfSceneBgID=-1;
int imgEndOfSceneExitID=-1;


//Common
int fontID=-1;
int mouseID=-1;
int score=0;
int highscore=0;





//---------------------------------------------------------------------------------
void resourceManagerInit(){
	imgStageLightsBgID = swGraphicsCreateImg("stagelights\\bg.tga");
	sprPlatformID=swGraphicsCreateSprite("stagelights\\platform\\");

	imgsGreenPlatformID[0]=swGraphicsCreateImg("stagelights\\rgb\\green\\yellow.tga");
	imgsGreenPlatformID[1]=swGraphicsCreateImg("stagelights\\rgb\\green\\red.tga");
	imgsGreenPlatformID[2]=swGraphicsCreateImg("stagelights\\rgb\\green\\green.tga");

	imgsYellowPlatformID[0]=swGraphicsCreateImg("stagelights\\rgb\\yellow\\red.tga");
	imgsYellowPlatformID[1]=swGraphicsCreateImg("stagelights\\rgb\\yellow\\green.tga");
	imgsYellowPlatformID[2]=swGraphicsCreateImg("stagelights\\rgb\\yellow\\yellow.tga");

	imgsRedPlatformID[0]=swGraphicsCreateImg("stagelights\\rgb\\red\\green.tga");
	imgsRedPlatformID[1]=swGraphicsCreateImg("stagelights\\rgb\\red\\yellow.tga");
	imgsRedPlatformID[2]=swGraphicsCreateImg("stagelights\\rgb\\red\\red.tga");

	imgCrossPlatformID=swGraphicsCreateImg("crossing\\crossplatform.tga");
	imgStageCrossingBgID=swGraphicsCreateImg("crossing\\bg.tga");
	imgStageCrossingBgLayoutID=swGraphicsCreateImg("crossing\\bgLayout.tga");

	sprActorID = swGraphicsCreateSprite("stagelights\\actor\\");


	imgYouDiedID=swGraphicsCreateImg("endofScene\\youdied.tga");
	imgEndOfSceneBgID=swGraphicsCreateImg("endofScene\\finalBg.tga");
	imgEndOfSceneExitID=swGraphicsCreateImg("endofScene\\exit.tga");

	imgmainMenuBgID = swGraphicsCreateImg("mainmenu\\mainmenu.tga");
	sprSleepItself  = swGraphicsCreateSprite("mainmenu\\sleep\\");
	sprWakeupItself = swGraphicsCreateSprite("mainmenu\\WakeUp\\");

	soundSourceID=swAudioCreateSource();
	horrBufferID=swAudioCreateBuffer("Audio\\Horr.wav",SW_AUDIO_BUFFER_TYPE_WAV);
	alarmBufferID=swAudioCreateBuffer("Audio\\Alarm.wav",SW_AUDIO_BUFFER_TYPE_WAV);
	dropBufferID=swAudioCreateBuffer("Audio\\Drop.wav",SW_AUDIO_BUFFER_TYPE_WAV);

	bgSoundSourceID=swAudioCreateSource();
	menuBgBufferID=swAudioCreateBuffer("Audio\\MenuBg.ogg",SW_AUDIO_BUFFER_TYPE_OGG);
	gameBgBufferID=swAudioCreateBuffer("Audio\\GameBg.ogg",SW_AUDIO_BUFFER_TYPE_OGG);

	endOfSceneSourceID=swAudioCreateSource();
	endOfSceneBufferID=swAudioCreateBuffer("Audio\\YouDied.ogg",SW_AUDIO_BUFFER_TYPE_OGG);

    sprSleepBtnMOverImgID = swGraphicsCreateSprite("mainmenu\\zzz\\");
	sprWakeupBtnMOverImgID = swGraphicsCreateSprite("mainmenu\\donot\\");

	fontID=swGraphicsCreateFont("common\\font.tga");
	mouseID=swGraphicsCreateImg("common\\mouseicon.tga");

	imgColorIDS[0]=swGraphicsCreateImg("common\\alpha\\green.tga");
	imgColorIDS[1]=swGraphicsCreateImg("common\\alpha\\yellow.tga");
	imgColorIDS[2]=swGraphicsCreateImg("common\\alpha\\red.tga");


}

//---------------------------------------------------------------------------------
void resourceManagerDeInit(){

}

