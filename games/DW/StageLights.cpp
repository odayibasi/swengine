#include "Stages.h"

#define MAX_CHANGE_SPEED 2
#define MIN_CHANGE_SPEED 0.5



typedef enum _PlatformColors{
	PLT_GREEN,
	PLT_YELLOW,
	PLT_RED,
}PlatformColors;

extern int sprPlatformID;
extern int imgStageLightsBgID; 

Platform *firstPlt, *secondPlt, *thirdPlt;
Actor *actor; 
swRect rectBgLights={0,128,1024,512};

PlatformColors colorsOfPlatform[3];
bool clickRegion[3];

extern int imgsGreenPlatformID[3];
extern int imgsYellowPlatformID[3];
extern int imgsRedPlatformID[3];

extern void (*activeFunc)(void);
extern swMouseState mousState;
extern int sprActorID;

void displayWriting(int index, PlatformColors color, int mode);

float lightsLastRandomUpdateTime = 0;
float lightsActorLastUpdateTime  = 0;
int writerand = 0 ;
float speedofChange = MAX_CHANGE_SPEED;
float deltaofSpeedChange = 0.1;
bool  activateAfterFirstClick=false;
bool  selectionPerformed=false;
int   animatorIndex = 0;

swMousBehaviourListener stageLightsMBListener;

extern int fontID;
extern int score;
extern int highscore;


extern int dropBufferID;
extern int soundSourceID;




//---------------------------------------------------------------------------------
void bindActorToPlatform(Actor* act, Platform* plt){
	act->target.x = plt->target.x;
	act->target.y = swRectYPlusH(&plt->target);
}


//---------------------------------------------------------------------------------
void stageLightsMBPressed(float x, float y){
	activateAfterFirstClick=true;

	clickRegion[0]=(firstPlt->target.x <= mousState.x && swRectXPlusW(&firstPlt->target)> mousState.x);
	clickRegion[1]=(secondPlt->target.x <= mousState.x && swRectXPlusW(&secondPlt->target)> mousState.x);
	clickRegion[2]=(thirdPlt->target.x <= mousState.x && swRectXPlusW(&thirdPlt->target)> mousState.x);

	if(clickRegion[0]) bindActorToPlatform(actor,firstPlt);
	else if(clickRegion[1]) bindActorToPlatform(actor, secondPlt);
	else if(clickRegion[2]) bindActorToPlatform(actor, thirdPlt);

}

//---------------------------------------------------------------------------------
void stageLightsMBReleased(float x, float y){
	//Something to Remember
}


//---------------------------------------------------------------------------------
void stageLightInit(){

	firstPlt  = new Platform();
	secondPlt = new Platform();
	thirdPlt  = new Platform();
	actor     = new Actor();

	actor->target.w = 64;
	actor->target.h = 64;
	actor->rot=0;

	firstPlt->animID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(sprPlatformID),0.1);
	swAnimatorSetExecutionMode(firstPlt->animID,SW_ANIMATOR_EXEC_FORWARD_LOOP);

	secondPlt->animID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(sprPlatformID),0.1);
	swAnimatorSetIndex(secondPlt->animID,3);
	swAnimatorSetExecutionMode(secondPlt->animID,SW_ANIMATOR_EXEC_FORWARD_LOOP);

	thirdPlt->animID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(sprPlatformID),0.1);
	swAnimatorSetIndex(thirdPlt->animID,6);
	swAnimatorSetExecutionMode(thirdPlt->animID,SW_ANIMATOR_EXEC_FORWARD_LOOP);

	swRectSet(&firstPlt->target,704,215,64,32);
	swRectSet(&secondPlt->target,799,215,64,32);
	swRectSet(&thirdPlt->target,892,215,64,32);

	colorsOfPlatform[0]=PLT_GREEN;
	colorsOfPlatform[1]=PLT_YELLOW;
	colorsOfPlatform[2]=PLT_RED;

	bindActorToPlatform(actor,firstPlt);

	activateAfterFirstClick = false;
	selectionPerformed      = false;

	stageLightsMBListener.dragging = NULL;
	stageLightsMBListener.moving   = NULL;
	stageLightsMBListener.pressed  = stageLightsMBPressed;
	stageLightsMBListener.released = stageLightsMBReleased;
	
	swMousBehaviourAdd(&stageLightsMBListener);
	activeFunc=stageLightExecute;
}

//---------------------------------------------------------------------------------
void checkLastMouseSelectionIsCorrected(){
	 bool flagFirst= clickRegion[0] && colorsOfPlatform[0]==PLT_GREEN;
	 bool flagSecond=clickRegion[1] && colorsOfPlatform[1]==PLT_GREEN;
	 bool flagThird= clickRegion[2] && colorsOfPlatform[2]==PLT_GREEN;

	 if(flagFirst|| flagSecond|| flagThird){
	   score+=1000;
	 }else{
	   score-=3000;
	 }

	 if(score>highscore) highscore=score;
	


	 if(score<=0){
		 swAudioSetSourceGain(soundSourceID,5);
		 swAudioBindSourceAndBuffer(soundSourceID,dropBufferID);
		 swAudioSetSourceLoop(soundSourceID,false);
		 swAudioPlaySource(soundSourceID);
		 activeFunc=stageTransitionLightToCrossingInit;
		 score=highscore+1000;
		 
	 }
		

}

//---------------------------------------------------------------------------------
void stageLightExecute(){

  swRect rect;


  swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
  swGraphicsSetColor1(&SWCOLOR_WHITE);
  swGraphicsRenderImg0(imgStageLightsBgID,&rectBgLights);

  swGraphicsRenderSprite0(sprPlatformID,swAnimatorGetIndex(firstPlt->animID),&firstPlt->target);
  swGraphicsRenderSprite0(sprPlatformID,swAnimatorGetIndex(secondPlt->animID),&secondPlt->target);
  swGraphicsRenderSprite0(sprPlatformID,swAnimatorGetIndex(thirdPlt->animID),&thirdPlt->target);

  float currentTime=swSystemGetElapsedSeconds();

  //Change Platform 
  if(activateAfterFirstClick && currentTime-lightsLastRandomUpdateTime >speedofChange){
	  
      checkLastMouseSelectionIsCorrected();

	  if(speedofChange > MIN_CHANGE_SPEED)
		 speedofChange -=deltaofSpeedChange;
	  else{
		  //todo
	  }
			
		int lightsRandom = rand() % 3;
		writerand++;
		lightsLastRandomUpdateTime=currentTime;

		colorsOfPlatform[lightsRandom%3]     = PLT_GREEN;
		colorsOfPlatform[(lightsRandom+1)%3] = PLT_RED;
		colorsOfPlatform[(lightsRandom+2) %3]= PLT_YELLOW;
  
  }
	
	displayWriting(0,colorsOfPlatform[0],writerand%3);
	displayWriting(1,colorsOfPlatform[1],writerand%3);
	displayWriting(2,colorsOfPlatform[2],writerand%3);

	swGraphicsRenderSprite0(sprActorID,actor->animIndex,&actor->target);

	if(currentTime - lightsActorLastUpdateTime > 0.75){
		if(!actor->animIndex){
			actor->animIndex++;
		}
		else{
			actor->animIndex--;
		}

		lightsActorLastUpdateTime = currentTime;
	}


	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor0(1,1,0,1);
	swGraphicsRenderText(false,1,32,650,650,0,"Score %i",score);


	if(!activateAfterFirstClick){
		swGraphicsSetColor0(0,1,0,1);
		swGraphicsRenderText(false,0,40,260,80,0,"Click To Green Color");

	}
}

//---------------------------------------------------------------------------------
void displayWriting(int index, PlatformColors color, int mode){

	swRect rect;
	Platform *plt;

	if(index==0) plt=firstPlt;
	if(index==1) plt=secondPlt;
	if(index==2) plt=thirdPlt;

	swRectCopy(&rect,&plt->target);
	rect.y-=16;



	switch(color){
		case PLT_GREEN:
			swGraphicsRenderImg0(imgsGreenPlatformID[mode],&rect);
			break;

		case PLT_YELLOW:
			swGraphicsRenderImg0(imgsYellowPlatformID[mode],&rect);
			break;

		case PLT_RED:
			swGraphicsRenderImg0(imgsRedPlatformID[mode],&rect);
			break;

		default:
			break;
  
	}

}

//---------------------------------------------------------------------------------
void stageLightDeInit(){
	//
}