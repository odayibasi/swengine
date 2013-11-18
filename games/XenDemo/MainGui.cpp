#include "../../include/SWEngine.h"
#include "XenDemoApp.h"


extern swMouseState		mousState;
extern int				clawTargetImgID;

//MainPage
extern int xenLogoImgID;
extern int xenLogoImgID;
extern int playBtnImgID;
extern int playBtnMOverImgID;
extern int exitBtnImgID;
extern int exitBtnMOverImgID;
extern int creditsBtnImgID;
extern int creditsBtnMOverImgID;
extern int storyBtnImgID;
extern int storyBtnMOverImgID;
extern int hScoreBtnImgID;
extern int hScoreBtnMOverImgID;
extern int helpBtnImgID;
extern int helpBtnMOverImgID;
extern int backBtnImgID;
extern int backBtnMOverImgID;
extern int continueBtnImgID;
extern int continueBtnMOverImgID;


swRect     xenLogoTarget={384,400,256,256};
swRect     playBtnTarget={450,350,128,32};
swRect     storyBtnTarget={450,300,128,32};
swRect     helpBtnTarget={450,250,128,32};
swRect     hScoreBtnTarget={450,200,128,32};
swRect     creditsBtnTarget={450,150,128,32};
swRect     exitBtnTarget={450,100,128,32};


//LevelSelection_Page
extern int fontID;
extern int xenLvlLayoutImgID;
extern int xenLvlLayoutCogImgID;
extern int xenLvlLayoutValidImgID;
swRect xenLvlLayout={0,128,2048,512};
swRect cogTargetL={0,128,50,50};
swRect cogTargetR={976,590,50,50};
float  cogRotL=0;
float  cogRotR=0;
float  cogRotLastTime=0;
swRect hangarTarget={144,385,20,20};
swRect backBtnTarget={10,20,128,32};
swRect nextBtnTarget={890,20,128,32};


extern int camID;


//-------------------------------------------------------------------------------------------
void mainGui_LevelSelectionDisplay(){
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg0(xenLvlLayoutImgID,&xenLvlLayout);

		
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	
	bool bMOver;
	float lastTime=swSystemGetElapsedSeconds(); 	



	//Left Move
	bMOver=swIntersectionRectAndPoint2(&cogTargetL,mousState.x,mousState.y);
	if(bMOver) 	swGraphicsSetColor0(0.0,0.0,0.0,0.8);
	else swGraphicsSetColor0(0.2,0.2,0.2,0.5);
	swGraphicsRenderImg1(xenLvlLayoutCogImgID,&cogTargetL,cogRotL);
	if(bMOver && mousState.btnLEFT && xenLvlLayout.x<0 && lastTime-cogRotLastTime>0.01){
		cogRotL+=5;
		cogRotR+=5;
		xenLvlLayout.x+=3;
		hangarTarget.x+=3;
		cogRotLastTime=lastTime;
	}

	//Right Move
	bMOver=swIntersectionRectAndPoint2(&cogTargetR,mousState.x,mousState.y);
	if(bMOver) 	swGraphicsSetColor0(0.0,0.0,0.0,0.8);
	else swGraphicsSetColor0(0.2,0.2,0.2,0.5);
	swGraphicsRenderImg1(xenLvlLayoutCogImgID,&cogTargetR,cogRotR);
	if(bMOver && mousState.btnLEFT && xenLvlLayout.x>-400 && lastTime-cogRotLastTime>0.01){
		cogRotL-=5;
		cogRotR-=5;
		xenLvlLayout.x-=3;
		hangarTarget.x-=3;
		cogRotLastTime=lastTime;
	}


	//Hangar Level Load
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg0(xenLvlLayoutValidImgID,&hangarTarget);


	//Contine
	bMOver=swIntersectionRectAndPoint2(&nextBtnTarget,mousState.x,mousState.y);
	if(bMOver) swGraphicsRenderImg0(continueBtnMOverImgID,&nextBtnTarget);
	else swGraphicsRenderImg0(continueBtnImgID,&nextBtnTarget);

	if(bMOver && mousState.btnLEFT){
		scnMngrSetMode(SCENE_DEMO_LVL_GENERATE);				
	}


	//Back
	bMOver=swIntersectionRectAndPoint2(&backBtnTarget,mousState.x,mousState.y);
	if(bMOver) swGraphicsRenderImg0(backBtnMOverImgID,&backBtnTarget);
	else swGraphicsRenderImg0(backBtnImgID,&backBtnTarget);

	if(bMOver && mousState.btnLEFT){
		scnMngrSetMode(SCENE_MAINGUI_MAINPAGE);
	}



	//Mouse Icon Icon
	swRect iconTarget;
	swRectSet(&iconTarget,mousState.x-16,mousState.y-16,32,32);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg0(clawTargetImgID,&iconTarget);


}

//-------------------------------------------------------------------------------------------
void mainGui_MainPageDisplay(){

	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsRenderImg0(xenLogoImgID,&xenLogoTarget);
	
	bool bMOver;
	
	//Play
	bMOver=swIntersectionRectAndPoint2(&playBtnTarget,mousState.x,mousState.y);
	if(bMOver) swGraphicsRenderImg0(playBtnMOverImgID,&playBtnTarget);
	else swGraphicsRenderImg0(playBtnImgID,&playBtnTarget);
	
	if(bMOver && mousState.btnLEFT){
		xenLvlLayout.x=0;
		hangarTarget.x=144;
		cogTargetL.x=0;
		cogTargetR.x=976;
		scnMngrSetMode(SCENE_MAINGUI_LEVELSELECTION);				
	}

	//Story
	bMOver=swIntersectionRectAndPoint2(&storyBtnTarget,mousState.x,mousState.y);
	if(bMOver) swGraphicsRenderImg0(storyBtnMOverImgID,&storyBtnTarget);
	else swGraphicsRenderImg0(storyBtnImgID,&storyBtnTarget);


	//Help
	bMOver=swIntersectionRectAndPoint2(&helpBtnTarget,mousState.x,mousState.y);
	if(bMOver) swGraphicsRenderImg0(helpBtnMOverImgID,&helpBtnTarget);
	else swGraphicsRenderImg0(helpBtnImgID,&helpBtnTarget);

	//HScore
	bMOver=swIntersectionRectAndPoint2(&hScoreBtnTarget,mousState.x,mousState.y);
	if(bMOver) swGraphicsRenderImg0(hScoreBtnMOverImgID,&hScoreBtnTarget);
	else swGraphicsRenderImg0(hScoreBtnImgID,&hScoreBtnTarget);

	//Credits
	bMOver=swIntersectionRectAndPoint2(&creditsBtnTarget,mousState.x,mousState.y);
	if(bMOver) swGraphicsRenderImg0(creditsBtnMOverImgID,&creditsBtnTarget);
	else swGraphicsRenderImg0(creditsBtnImgID,&creditsBtnTarget);

	//Exit
	bMOver=swIntersectionRectAndPoint2(&exitBtnTarget,mousState.x,mousState.y);
	if(bMOver) swGraphicsRenderImg0(exitBtnMOverImgID,&exitBtnTarget);
	else swGraphicsRenderImg0(exitBtnImgID,&exitBtnTarget);

	if(bMOver && mousState.btnLEFT){
		scnMngrSetMode(SCENE_EXIT_INTRO_INIT);		
	}


	//Mouse Icon Icon
	swRect iconTarget;
	swRectSet(&iconTarget,mousState.x-16,mousState.y-16,32,32);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsRenderImg0(clawTargetImgID,&iconTarget);


}





