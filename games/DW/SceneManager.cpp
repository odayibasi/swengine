#include "SceneManager.h"
#include "Scenes.h"
#include "DWCommon.h"

int currentMode=SCENE_GAME_NONE;

//---------------------------------------------------------------------------------
void scnMngrSetModeFunc(int mode){


	switch(mode){
		case SCENE_GAME_STAGE_LIGHTS_INIT:
			
			break;

		case SCENE_GAME_PLAY_INIT:
			//xenDemoAppSetActiveFunc(sceneGamePlayInit);
			break;

		case SCENE_GAME_PLAY_RUN:
			//xenDemoAppSetActiveFunc(sceneGamePlayRun);
			break;

		case SCENE_GAME_PLAY_RESTART:
			//xenDemoAppSetActiveFunc(sceneGamePlayRestart);
			break;

		case SCENE_GAME_PLAY_EXIT:
			//xenDemoAppSetActiveFunc(sceneGamePlayExit);
			break;

		case SCENE_GAME_MAINMENU:
			//xenDemoAppSetActiveFunc(Game_MainMenuDisplay);
			break;

		default:
			break;
	}

	currentMode=mode;
}



//---------------------------------------------------------------------------------
void scnMngrSetMode(int mode){
     scnMngrSetModeFunc(mode);
}