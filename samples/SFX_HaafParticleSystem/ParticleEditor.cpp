#include "Base.h"
#include "ParticleSystemManager.h"
#include "ParticleSystem.h"
#include "ParticleSystemInfo.h"
#include "Particle.h"
#include "Vec2.h"


swApplication particleEditorApp;
ParticleSystem *pS;



swKeyboardState keybState;
swMouseState    mousState;


//=============================================================================================
void particleEditorInitDefaultPS(){

	particleSystemManagerInit();
	pS=particleSystemManagerCreate();

	pS->info.sprite=swGraphicsCreateImg("LightMap2.tga");

	pS->vecLocation.index[0]=600;
	pS->vecLocation.index[1]=450;


	pS->info.nEmission=500;
	pS->info.fLifetime=-1;

	pS->info.fParticleLifeMin=1;
	pS->info.fParticleLifeMax=3;


	swColorSet(&pS->info.colColorStart,0.2f,1.0f,1.1f,0.3f);
	swColorSet(&pS->info.colColorEnd,0.5f,1.0f,1.0f,1.0f);
	pS->info.fColorVar=0;
	pS->info.fAlphaVar=2;

	pS->info.fSizeStart=1;
	pS->info.fSizeEnd=19;
	pS->info.fSizeVar=3;


	pS->info.fGravityMin=0;
	pS->info.fGravityMax=0;
	pS->info.fDirection=20;

	pS->info.fRadialAccelMax=3;
	pS->info.fRadialAccelMin=1;

	pS->info.fTangentialAccelMin=1;
	pS->info.fTangentialAccelMax=5;


	pS->info.fSpinVar=2;
	pS->info.fSpinStart=10;
	pS->info.fSpinEnd=30;

	pS->info.fSpread=10;
	pS->info.fSpeedMin=1;
	pS->info.fSpeedMax=2;

}

//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swInputListenKeyboard(&keybState);
	swInputListenMouse(&mousState);
	swInteractionManagerExecute(&keybState,&mousState);

	swGraphicsBeginScene();
		swGraphicsSetBgColor1(0,0,0,0);
		particleSystemManagerExecute();
		particleSystemManagerDisplay();
		swDispManagerExecute();
		
		//Display Cursor
		//swGraphicsSetColor1(&SWCOLOR_WHITE);
		//swGraphicsRenderPoint0(mousState.x,mousState.y,10);
	swGraphicsEndScene();

	if(keybState.keyESCAPE){
		swEngineExit();
	}
}

//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	//Application Settings
	particleEditorApp.hInstance=hInstance;
	particleEditorApp.fullScreen=false;
	particleEditorApp.cursor=true;
	particleEditorApp.width=1024;
	particleEditorApp.height=768;
	particleEditorApp.title="Particle Editor";
	particleEditorApp.path="\\rsc\\ParticleEditor\\";
	particleEditorApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&particleEditorApp);
	particleEditorInitDefaultPS();
	swNumPropWinSetPath("NumPropWinRsc\\");		


	int winID=swNumPropWinCreate("ParticleSystem Parameters",200,200,300,14);

	//Location
	int locationWinID=swNumPropWinCreate("Location",300,300,250,2);
	swNumPropWinAddFloat(locationWinID,"PosX",&pS->vecLocation.index[0],FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(locationWinID,"PosY",&pS->vecLocation.index[1],FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddSubWin(winID,locationWinID);

	//Emission
	swNumPropWinAddInt(winID,"Emission",&pS->info.nEmission,0,1000,1);

	//ParticleLife 
	int particleLifeWinID=swNumPropWinCreate("Particle Life",300,300,250,2);
	swNumPropWinAddFloat(particleLifeWinID,"Min",&pS->info.fParticleLifeMin,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(particleLifeWinID,"Max",&pS->info.fParticleLifeMax,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddSubWin(winID,particleLifeWinID);


	//ColorStart
	int colorStartWinID=swNumPropColorWinCreate("Color Start",300,300,&pS->info.colColorStart);
	swNumPropWinAddSubWin(winID,colorStartWinID);

	//ColorEnd
	int colorEndWinID=swNumPropColorWinCreate("Color End",300,300,&pS->info.colColorEnd);
	swNumPropWinAddSubWin(winID,colorEndWinID);

	swNumPropWinAddFloat(winID,"Color Var",&pS->info.fColorVar,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(winID,"Alpha Var",&pS->info.fAlphaVar,FLT_MIN,FLT_MAX,1.0f);

	//ParticleSize	
	int particleSizeWinID=swNumPropWinCreate("Size",300,300,250,3);
	swNumPropWinAddFloat(particleSizeWinID,"Start",&pS->info.fSizeStart,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(particleSizeWinID,"End",&pS->info.fSizeEnd,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(particleSizeWinID,"Var",&pS->info.fSizeVar,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddSubWin(winID,particleSizeWinID);

	//ParticleSpin	
	int particleSpinWinID=swNumPropWinCreate("Spin",300,300,250,3);
	swNumPropWinAddFloat(particleSpinWinID,"Start",&pS->info.fSpinStart,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(particleSpinWinID,"End",&pS->info.fSpinEnd,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(particleSpinWinID,"Var",&pS->info.fSpinVar,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddSubWin(winID,particleSpinWinID);


	//Gravity	
	int gravityWinID=swNumPropWinCreate("Gravity",300,300,250,3);
	swNumPropWinAddFloat(gravityWinID,"Min",&pS->info.fGravityMin,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(gravityWinID,"Max",&pS->info.fGravityMax,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(gravityWinID,"Direction",&pS->info.fDirection,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddSubWin(winID,gravityWinID);


	//Speed	
	int speedWinID=swNumPropWinCreate("Speed",300,300,250,3);
	swNumPropWinAddFloat(speedWinID,"Min",&pS->info.fSpeedMin,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(speedWinID,"Max",&pS->info.fSpeedMax,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddFloat(speedWinID,"Spread",&pS->info.fSpread,FLT_MIN,FLT_MAX,1.0f);
	swNumPropWinAddSubWin(winID,speedWinID);


	//RadialAcc 
	int radialAccWinID=swNumPropWinCreate("Radial Accelaration",300,300,250,2);
	swNumPropWinAddFloat(radialAccWinID,"Min",&pS->info.fRadialAccelMin,FLT_MIN,FLT_MAX,0.5f);
	swNumPropWinAddFloat(radialAccWinID,"Max",&pS->info.fRadialAccelMax,FLT_MIN,FLT_MAX,0.5f);
	swNumPropWinAddSubWin(winID,radialAccWinID);


	//TangantAcc 
	int tangentAccWinID=swNumPropWinCreate("Tangent Accelaration",300,300,250,2);
	swNumPropWinAddFloat(tangentAccWinID,"Min",&pS->info.fTangentialAccelMin,FLT_MIN,FLT_MAX,0.5f);
	swNumPropWinAddFloat(tangentAccWinID,"Max",&pS->info.fTangentialAccelMax,FLT_MIN,FLT_MAX,0.5f);
	swNumPropWinAddSubWin(winID,tangentAccWinID);


	swNumPropWinSetVisible(winID,true);
	swEngineRun();
	swEngineExit();

	return 0;
}


