#include "XenDemoApp.h"

int exploreInterp1;
extern int bgMusicBufferID;
extern int bgMusicSourceID;


//-------------------------------------------------------------------------------------------
void scenePlayInit(){
	clawSetHangingOnAir(true);
	hudSetBombType(BOMB_TYPE_SHARAPNEL);
	hudSetTransparent(true);
	clawSetEnabledInteraction(true);
	scnMngrSetMode(SCENE_DEMO_LVL_PLAY_RUN);
}


//-------------------------------------------------------------------------------------------
void scenePlayRun(){
	//todo level esc, game over, pause etc..
}


//-------------------------------------------------------------------------------------------
void scenePlayRestart(){
	swDestroyManagerExecute();
	scnMngrSetMode(SCENE_DEMO_LVL_GENERATE);		
}


//-------------------------------------------------------------------------------------------
void scenePlayExit(){
	swDestroyManagerExecute();
	scnMngrSetMode(SCENE_EXIT_INTRO_INIT);		
}



//-------------------------------------------------------------------------------------------
void sceneIntroInit(){
	//Total 8 Seconds..
	exploreInterp1=swInterpolaterCreate(32,350,4); 	
	swInterpolaterStart(exploreInterp1);
	scnMngrSetMode(SCENE_DEMO_LVL_INTRO_RUN);		
}



//-------------------------------------------------------------------------------------------
void sceneIntroRun(){
	 float val=swInterpolaterGetValue(exploreInterp1);
	 clawSetPos(200,val);
	 clawSetTargetPos(450,val+32);
	 if(swInterpolaterIsFinished(exploreInterp1)){
		 scnMngrSetMode(SCENE_DEMO_LVL_INTRO_DEINIT);		
	 }
}


//-------------------------------------------------------------------------------------------
void sceneIntroDeInit(){
	swInterpolaterDestroy(exploreInterp1); 	
	scnMngrSetMode(SCENE_DEMO_LVL_PLAY_INIT);
}


//-------------------------------------------------------------------------------------------
void sceneGenerate(){ 
	dslExecuterParseFolder("Levels/Hangar/");
	dslExecuterExecuteLevel("Demo.lvl");
	scnMngrSetMode(SCENE_DEMO_LVL_INTRO_INIT);
	swAudioPlaySource(bgMusicSourceID);

}



