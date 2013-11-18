#include "XenDemoApp.h"


swApplication xenDemoApp;
void (*activeFunc)(void);

swDimension extern	winSize;
swKeyboardState		keybState;
swMouseState		mousState;

int rendTargID=-1;
int fullScreenImgID=-1;
int gameLoopTimerID=0;


#ifdef DEBUG
bool   xenIsFullScreen=false;
#else
bool   xenIsFullScreen=true;
#endif



swRect fullScreenRect={0,0,1024,768};
swRect windScreenRect={0,0,1024,736};
int    camID;
bool   xenShadowActive=true;


extern int fontID;

extern int shdGrayscaled;
void xenDemoLoop(void *obj);
int bgMusicSourceID;
extern int bgMusicBufferID;


//-------------------------------------------------------------------------------------------
bool  xenDemoIsSupportPostProcessing(){
 	return swGraphicsIsSupportGLSL() && swGraphicsIsSupportFBOSupport();
}

//-------------------------------------------------------------------------------------------
bool  graphicsCardIsNvidia(){
	char *vendor=swSystemGetGraphicsCardVendor();
	return (strncmp(vendor,"NVIDIA",6) == 0);
}




//-------------------------------------------------------------------------------------------
void xenDemoInit(){ 

	//Init My Application
	swDispManagerSetCullRegion(0,0,1024,768);
	swDispManagerSetLayerCount(10);
	camID=swGraphicsCreateCam();

	//Manager Init
	resourceInit();
	physInit();
	soundInit();
	moleculerDecomposeInit();
	explosionInit();
	objParticleInit();
	clawWeaponInit();
	enemyWeaponInit();
	dslInit();
	

	//Entitiy Init
	laserGateInit();
	//clawCreate();




	if(xenDemoIsSupportPostProcessing() && graphicsCardIsNvidia()){
		rendTargID=swGraphicsCreateRenderingTarget(1024,512,3); //Define New RenderingTarget 
		fullScreenImgID=swGraphicsRenderingTargetGetImgID(rendTargID); //Get ImgID  
		swGraphicsActiveGLSLShader(SW_DISABLED_SHADER_ID);
	}
		

	bgMusicSourceID=swAudioCreateSource();
	swAudioBindSourceAndBuffer(bgMusicSourceID,bgMusicBufferID);
	swAudioSetSourceGain(bgMusicSourceID,5.0);

	
	#ifdef DEBUG	
	//sceneGenerate();
	scnMngrSetMode(SCENE_MAINGUI_MAINPAGE);
	#else
	//scnMngrSetMode(SCENE_MAINGUI_MAINPAGE);
	introInit();
	#endif
	gameLoopTimerID=swTimerCreate(0.016,NULL,xenDemoLoop);
}


//-------------------------------------------------------------------------------------------
void xenDemoSetGameSpeed(float delaySeconds){ 
	swTimerUpdateDelaySeconds(gameLoopTimerID,delaySeconds);
}

//-------------------------------------------------------------------------------------------
void xenDemoSetPaused(bool bPaused){ 
	if(bPaused){
		swTimerStop(gameLoopTimerID);
	}else{
		swTimerStart(gameLoopTimerID);
	}
}



//-------------------------------------------------------------------------------------------
void xenDemoAppSetActiveFunc(void (*activeFuncPointer)(void)){ 
	activeFunc=activeFuncPointer;
}

//-------------------------------------------------------------------------------------------
void xenDemoRenderWithPostProcessing(){
	//Default Rendering
	swGraphicsSetRenderingTarget(rendTargID);
	swGraphicsClearRenderingTarget();
	swGraphicsActiveCam(camID);
	if(activeFunc!=NULL) (*activeFunc)();
	swDispManagerExecute();
	swPhysRendererExecute();

	//FullScreenFX
	swGraphicsSetRenderingTarget(SW_RENDERING_TARGET_DEFAULT);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
	swGraphicsActiveCam(SW_CAM_DEFAULT);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	swGraphicsActiveGLSLShader(fullSceenFXGetActive());
	fullSceenFXUpdateVariables();
	if(xenIsFullScreen){
		swGraphicsRenderImg0(fullScreenImgID,&fullScreenRect);
	}else{
		swGraphicsRenderImg0(fullScreenImgID,&windScreenRect);
	}			

	swGraphicsActiveGLSLShader(SW_DISABLED_SHADER_ID);
}


//-------------------------------------------------------------------------------------------
void xenDemoRenderWithoutPostProcessing(){
	swGraphicsActiveCam(camID);
	if(activeFunc!=NULL) (*activeFunc)();
	swDispManagerExecute();
	swPhysRendererExecute();
}





//-------------------------------------------------------------------------------------------
void xenDemoLoop(void *obj){ 
	swInteractionManagerExecute(&keybState,&mousState);
	swPhysWorldUpdate();
	swExecManagerExecute();
	swGraphicsBeginScene();
	if(xenDemoIsSupportPostProcessing()){
		xenDemoRenderWithPostProcessing();
	}else{
		xenDemoRenderWithoutPostProcessing();
	}
	swGraphicsEndScene();
	if(keybState.keyESCAPE){
		swDestroyManagerExecute();
		swGraphicsSetCamPos(camID,0,0);
		scnMngrSetMode(SCENE_MAINGUI_MAINPAGE);
		swAudioStopSource(bgMusicSourceID);
	}

	if(keybState.keyR){
		scnMngrSetMode(SCENE_DEMO_LVL_PLAY_RESTART);
	}			
}


//-------------------------------------------------------------------------------------------
void xenDemoAppLoop(){
	swInputListenKeyboard(&keybState);
	swInputListenMouse(&mousState);
	swKeybBehaviourExecute(&keybState); 
}



//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	//Application Settings
	xenDemoApp.hInstance=hInstance;
	xenDemoApp.fullScreen=xenIsFullScreen;
	xenDemoApp.cursor=!xenIsFullScreen;
	xenDemoApp.width=winSize.w;
	xenDemoApp.height=winSize.h;
	xenDemoApp.title="Xen Demo";
	xenDemoApp.path="\\rsc\\XenDemo\\";
	xenDemoApp.appRun=xenDemoAppLoop;

	//Application Execution
	swEngineInit(&xenDemoApp);
	xenDemoInit();
	swEngineRun();
	swEngineExit();

	return 0;
}