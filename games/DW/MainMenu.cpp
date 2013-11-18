#include "Stages.h"

#include "../../include/SWEngine.h"
#include "DWApp.h"

typedef struct Button{
	int animID;
	int index;
	swRect target;
}Button;

extern swMouseState		mousState;
extern int				clawTargetImgID;

extern int sprWakeupBtnMOverImgID;
extern int sprSleepBtnMOverImgID;
extern int imgmainMenuBgID;
extern int sprWakeupItself;
extern int sprSleepItself;

extern void (*activeFunc)(void);

Button *animsleep, *animwakeup, *sleep, *wakeup;
swRect mainMenuTarget  = {0,128,1024,512};

extern int horrBufferID;
extern int alarmBufferID;
extern int soundSourceID;

extern int bgSoundSourceID;
extern int menuBgBufferID;
extern int gameBgBufferID;


boolean zzzPressed=false;
boolean alarmPressed=false;



//-------------------------------------------------------------------------------------------
void stageMainGuiInit(){
	animsleep  = new Button();
	animwakeup = new Button();
	sleep      = new Button();
	wakeup     = new Button();

	animsleep->animID = swAnimatorCreate(swGraphicsGetCountOfImgInSprite(sprSleepBtnMOverImgID),0.1);
	swAnimatorSetExecutionMode(animsleep->animID,SW_ANIMATOR_EXEC_FORWARD);

	animwakeup->animID = swAnimatorCreate(swGraphicsGetCountOfImgInSprite(sprWakeupBtnMOverImgID),0.1);
	swAnimatorSetExecutionMode(animwakeup->animID,SW_ANIMATOR_EXEC_FORWARD);

	sleep->animID = swAnimatorCreate(swGraphicsGetCountOfImgInSprite(sprSleepItself),0.1);
	swAnimatorSetExecutionMode(sleep->animID,SW_ANIMATOR_EXEC_FORWARD);

	wakeup->animID = swAnimatorCreate(swGraphicsGetCountOfImgInSprite(sprWakeupItself),0.1);
	swAnimatorSetExecutionMode(wakeup->animID,SW_ANIMATOR_EXEC_FORWARD);

	swRectSet(&sleep->target,816,200+128,128,64);
	swRectSet(&animsleep->target,910,264+128,128,256);

	swRectSet(&wakeup->target,825,109+128,128,64);	
	swRectSet(&animwakeup->target,690,109+128,128,64);
	
	swAudioSetSourceGain(bgSoundSourceID,5);
	swAudioSetSourceLoop(bgSoundSourceID,true);
	swAudioBindSourceAndBuffer(bgSoundSourceID,menuBgBufferID);
	swAudioPlaySource(bgSoundSourceID);



	activeFunc    = stageMainGuiExecute;
}

//-------------------------------------------------------------------------------------------
void stageMainGuiExecute(){

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);

	swGraphicsRenderImg0(imgmainMenuBgID,&mainMenuTarget);

	bool bMOver;

	//Play
	swGraphicsRenderImg0(sprSleepItself,&sleep->target);

	if(bMOver=swIntersectionRectAndPoint2(&sleep->target,mousState.x,mousState.y))
	{
		if(!zzzPressed){	
			swAudioSetSourceGain(soundSourceID,5);
			swAudioSetSourceLoop(soundSourceID,true);
			swAudioBindSourceAndBuffer(soundSourceID,horrBufferID);
			swAudioPlaySource(soundSourceID);
			zzzPressed=true;
		}

		swGraphicsRenderSprite0(sprSleepBtnMOverImgID,swAnimatorGetIndex(animsleep->animID),&animsleep->target);
		swGraphicsRenderSprite0(sprSleepItself,swAnimatorGetIndex(sleep->animID),&sleep->target);

	}
	else
	{
		if(zzzPressed){
			zzzPressed=false;
			swAudioStopSource(soundSourceID);
		}
		
		swAnimatorSetIndex(animsleep->animID,0);
		swAnimatorSetIndex(sleep->animID,0);
	}

	if(bMOver && mousState.btnLEFT){
		swAudioStopSource(soundSourceID);
		swAudioStopSource(bgSoundSourceID);
		swAudioBindSourceAndBuffer(bgSoundSourceID,gameBgBufferID);
		swAudioPlaySource(bgSoundSourceID);
		activeFunc = stageLightInit;
	}


	//Exit
	swGraphicsRenderImg0(sprWakeupItself,&wakeup->target);

	if(bMOver=swIntersectionRectAndPoint2(&wakeup->target,mousState.x,mousState.y))
	{
		swGraphicsRenderSprite0(sprWakeupBtnMOverImgID,swAnimatorGetIndex(animwakeup->animID),&animwakeup->target);
		swGraphicsRenderSprite0(sprWakeupItself,swAnimatorGetIndex(wakeup->animID),&wakeup->target);
		if(!alarmPressed){	
			swAudioSetSourceGain(soundSourceID,5);
			swAudioSetSourceLoop(soundSourceID,true);
			swAudioBindSourceAndBuffer(soundSourceID,alarmBufferID);
			swAudioPlaySource(soundSourceID);
			alarmPressed=true;
		}
	
	}
	else		
	{
		if(alarmPressed){
			alarmPressed=false;
			swAudioStopSource(soundSourceID);
		}

		swAnimatorSetIndex(animwakeup->animID,0);
		swAnimatorSetIndex(wakeup->animID,0);
	}

	if(bMOver && mousState.btnLEFT){
		swAudioStopSource(soundSourceID);
		exit(0);
	}
}





