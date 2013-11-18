#ifndef XEN_COMMON_H
#define XEN_COMMON_H



typedef enum _xenUserDataType{
	XEN_CLAW,
	XEN_CLAW_WPN_BULLET,
	XEN_ENEMY_WPN_BULLET,
	XEN_BARREL,
	XEN_EXPLOSION_PARTICLE,
	XEN_TURRET,
	XEN_DEFENDER,
}xenUserDataType;

typedef struct _xenUserData{
	xenUserDataType type;
	void *obj;
}xenUserData;



//Scenes
#define SCENE_SW_NONE			-1


#define SCENE_SW_INTRO_INIT					0
#define SCENE_SW_INTRO_RUN					1
#define SCENE_SW_INTRO_DEINIT				2




#define SCENE_DEMO_LVL_GENERATE				3
#define SCENE_DEMO_LVL_INTRO_INIT			4
#define SCENE_DEMO_LVL_INTRO_RUN			5
#define SCENE_DEMO_LVL_INTRO_DEINIT			6
#define SCENE_DEMO_LVL_PLAY_INIT			7
#define SCENE_DEMO_LVL_PLAY_RUN				8
#define SCENE_DEMO_LVL_PLAY_GAMEOVER		9
#define SCENE_DEMO_LVL_PLAY_RESTART			10
#define SCENE_DEMO_LVL_PLAY_EXIT			11


#define SCENE_EXIT_INTRO_INIT			12
#define SCENE_EXIT_INTRO_RUN			13
#define SCENE_EXIT_INTRO_DEINIT			14


#define SCENE_MAINGUI_MAINPAGE			20
#define SCENE_MAINGUI_LEVELSELECTION	21





void	xenDemoAppSetActiveFunc(void (*activeFuncPointer)(void));
void	xenDemoSetGameSpeed(float delaySeconds);
void	xenDemoSetPaused(bool bPaused);
bool	xenDemoIsSupportPostProcessing();


#endif