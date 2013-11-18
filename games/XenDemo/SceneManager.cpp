#include "SceneManager.h"
#include "Scenes.h"
#include "XenCommon.h"

int currentMode=SCENE_SW_NONE;

//---------------------------------------------------------------------------------
void scnMngrSetModeFunc(int mode){


	switch(mode){
		case SCENE_SW_INTRO_INIT:
			xenDemoAppSetActiveFunc(introInit);
			break;
		
		case SCENE_SW_INTRO_RUN:
			xenDemoAppSetActiveFunc(introRun);
			break;

		case SCENE_SW_INTRO_DEINIT:
			xenDemoAppSetActiveFunc(introDeInit);
			break;

		case SCENE_DEMO_LVL_GENERATE:
			xenDemoAppSetActiveFunc(sceneGenerate);
			break;

		case SCENE_DEMO_LVL_INTRO_INIT:
			xenDemoAppSetActiveFunc(sceneIntroInit);
			break;

		case SCENE_DEMO_LVL_INTRO_RUN:
			xenDemoAppSetActiveFunc(sceneIntroRun);
			break;

		case SCENE_DEMO_LVL_INTRO_DEINIT:
			xenDemoAppSetActiveFunc(sceneIntroDeInit);
			break;

		case SCENE_DEMO_LVL_PLAY_INIT:
			xenDemoAppSetActiveFunc(scenePlayInit);
			break;

		case SCENE_DEMO_LVL_PLAY_RUN:
			xenDemoAppSetActiveFunc(scenePlayRun);
			break;

		case SCENE_DEMO_LVL_PLAY_RESTART:
			xenDemoAppSetActiveFunc(scenePlayRestart);
			break;

		case SCENE_DEMO_LVL_PLAY_EXIT:
			xenDemoAppSetActiveFunc(scenePlayExit);
			break;

		case SCENE_EXIT_INTRO_INIT:
			xenDemoAppSetActiveFunc(aboutInit);
			break;

		case SCENE_EXIT_INTRO_RUN:
			xenDemoAppSetActiveFunc(aboutRun);
			break;

		case SCENE_EXIT_INTRO_DEINIT:
			xenDemoAppSetActiveFunc(aboutDeInit);
			break;

		case SCENE_MAINGUI_MAINPAGE:
			xenDemoAppSetActiveFunc(mainGui_MainPageDisplay);
			break;

		case SCENE_MAINGUI_LEVELSELECTION:
			xenDemoAppSetActiveFunc(mainGui_LevelSelectionDisplay);
			break;



		default:
			break;
	}

	currentMode=mode;
}

//---------------------------------------------------------------------------------
bool scnMngrIsModeTransitionValid(int mode){
	if(mode==SCENE_DEMO_LVL_PLAY_EXIT && currentMode!=SCENE_DEMO_LVL_PLAY_RUN){
		return false;
	}

	if(mode==SCENE_DEMO_LVL_PLAY_RESTART && currentMode!=SCENE_DEMO_LVL_PLAY_RUN){
		return false;
	}


	return true;
}



//---------------------------------------------------------------------------------
void scnMngrSetMode(int mode){
	if(scnMngrIsModeTransitionValid(mode)){
		scnMngrSetModeFunc(mode);
	}
}