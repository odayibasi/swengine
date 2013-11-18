#include "Stages.h"

extern int imgStageLightsBgID; 
extern int imgStageCrossingBgLayoutID;
extern swRect rectBgLights;
extern Actor *actor; 
extern int sprActorID;
extern void (*activeFunc)(void);
extern int camID;
float  camLastUpdateTime=0;
float  camSpeed=0.2;

float layoutSpeed=0.02;

float  litFadeColor=1; 
swPoint wP={0.0,0.0};
extern int fontID;

float transitionMinY   =-2550;
float transitionDeltaY =-10;

#define MAX_BEHIND_LINES 50
swRect behindLines[MAX_BEHIND_LINES];
swRect layout={0,0,1024,768};
swRect otherlayout={550,-1000,1024,762};
swRect otherlayout1={-600,-1700,1024,768};
swRect otherlayout2={800,-2572,1024,512};


//---------------------------------------------------------------------------------
void updateLinesBehindActor(){
	for(int i=0;i<MAX_BEHIND_LINES;i++){
		if(swIntersectionRectAndPoint2(&layout,behindLines[i].x, behindLines[i].y)){
			behindLines[i].y+=20;
		}else{
			behindLines[i].x=rand()%1025;
			behindLines[i].y=rand()%769;
			behindLines[i].w=0;
			behindLines[i].h=-(rand()%51+50);
		}
	}
}

//---------------------------------------------------------------------------------
void createLinesBehindActor(){
	activeFunc=stageTransitionLightToCrossingExecute;
}


//---------------------------------------------------------------------------------
void stageTransitionLightToCrossingInit(){
	activeFunc=stageTransitionLightToCrossingExecute;
}




//---------------------------------------------------------------------------------
void stageTransitionLightToCrossingExecute(){

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor0(litFadeColor,litFadeColor,litFadeColor,litFadeColor);
	swGraphicsRenderImg0(imgStageLightsBgID,&rectBgLights);
	swGraphicsRenderImg0(imgStageCrossingBgLayoutID,&otherlayout);
	swGraphicsRenderImg0(imgStageCrossingBgLayoutID,&otherlayout1);
	swGraphicsRenderImg0(imgStageCrossingBgLayoutID,&otherlayout2);


	swGraphicsActiveCam(SW_CAM_DEFAULT);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	for(int i=0;i<MAX_BEHIND_LINES;i++){
		swGraphicsRenderLine0(behindLines[i].x,behindLines[i].y,behindLines[i].x+behindLines[i].w, behindLines[i].y+behindLines[i].h,2);
	}
	swGraphicsActiveCam(camID);

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderSprite1(sprActorID,0,&actor->target,actor->rot);

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor1(&SWCOLOR_RED);

	//swGraphicsActiveCam(SW_CAM_DEFAULT);
	//swGraphicsRenderText(fontID,1,32,200,200,0,"%f",actor->target.y);
	//swGraphicsActiveCam(camID);


	float currentTime=swSystemGetElapsedSeconds();
	if(currentTime-camLastUpdateTime>camSpeed){
		//Fade out
		litFadeColor-=0.02;
		if(litFadeColor<=0){
			litFadeColor=1;
		}

		
		if(swGraphicsGetCamPosY(camID)> transitionMinY){
			swGraphicsAddCamPosY(camID,  transitionDeltaY);
			actor->target.y+=transitionDeltaY;
		}else{
			actor->rot=0;
			activeFunc=stageTransitionCrossingLayoutCentered;
		}


		//Rotate
		if(actor->rot<180){
			actor->rot+=3;
			actor->target.x=800;
		}

       updateLinesBehindActor();


	}

}




//---------------------------------------------------------------------------------
void stageTransitionCrossingLayoutCentered(){
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg0(imgStageCrossingBgLayoutID,&otherlayout2);
	swGraphicsRenderSprite1(sprActorID,0,&actor->target,actor->rot);


	float currentTime=swSystemGetElapsedSeconds();
	if(currentTime-camLastUpdateTime>layoutSpeed){


		boolean isYExist=otherlayout2.y>=-2450;
		boolean isXExist=otherlayout2.x<=0;

		if(isXExist && isYExist){
			otherlayout2.x=0;
			otherlayout2.y=128;
			swGraphicsSetCamPos(camID,0,0);
			activeFunc=stageCrossingInit;
			
		}

		if(!isXExist) {
			otherlayout2.x-=10;
			actor->target.x-=10;
		}
		
		if(!isYExist){
			otherlayout2.y+=10;
			actor->target.y+=10;	
		}

		camLastUpdateTime=currentTime;

	}

}







//---------------------------------------------------------------------------------
void stageTransitionLightToCrossingDeInit(){



}
