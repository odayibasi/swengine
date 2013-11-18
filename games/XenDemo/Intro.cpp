#include "../../include/SWEngine.h"
#include "XenCommon.h"
#include "SceneManager.h"

swColor introColor;
float   introLastTime;
float   fadeOutMultiplier=0.02;

swRect  rectLogo={0,0,80,160};
char    webAdressTemp[20]="";
char    webAdress[20]="www.skywar.org";

extern  int logoID;
extern  int fontID;
extern  swDimension winSize;



//-------------------------------------------------------------------------------------------
void executeIntro(void *obj){ 
	float lastTime=swSystemGetElapsedSeconds();

	//Exit Function
	if(introColor.a<=0){
		scnMngrSetMode(SCENE_SW_INTRO_DEINIT);
	}

	//Fade Out Animation
	if(lastTime-introLastTime>0.15 && swStringEquals(webAdress,webAdressTemp)){
		fadeOutMultiplier+=0.005;
		introColor.a-=fadeOutMultiplier;
		introColor.r=introColor.g=introColor.b=introColor.a;
		introLastTime=lastTime;
	}

	//Writing Animation
	if(lastTime-introLastTime>0.15 && !swStringEquals(webAdress,webAdressTemp)){
		int len=swStringGetLength(webAdressTemp);
		swStringCopyEx(webAdressTemp,webAdress,0,len+1);
		introLastTime=lastTime;
	}

}


//-------------------------------------------------------------------------------------------
void displayIntro(void *obj){ 

	swGraphicsSetColor1(&introColor);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
	swGraphicsRenderImg0(logoID,&rectLogo);	

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsRenderText(fontID,1,16,440,300,0,webAdressTemp);
}




//-------------------------------------------------------------------------------------------
void introRun(){
 executeIntro(NULL);
 displayIntro(NULL);
}


//-------------------------------------------------------------------------------------------
void introInit(){ 
	swColorSet(&introColor,1,1,1,1);
	introLastTime=0;
	fadeOutMultiplier=0.02f;
	swStringCopy(webAdressTemp,"");
	rectLogo.x=winSize.w/2-rectLogo.w/2;
	rectLogo.y=winSize.h/2-rectLogo.h/2;
	scnMngrSetMode(SCENE_SW_INTRO_RUN);
}

//-------------------------------------------------------------------------------------------
void introDeInit(){ 
	scnMngrSetMode(SCENE_MAINGUI_MAINPAGE);
}




