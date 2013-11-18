#include "../../include/SWEngine.h"
#include "XenCommon.h"
#include "Hud.h"
#include "XenCommon.h"
#include "SceneManager.h"
#include "PostProcessingFX.h"
extern  int gameLoopTimerID;



#define VIEWX  -2000


extern int	camID;
extern int	fontID;
extern int	xenRunID;
int			xenRunAnimID;
swRect		xenRunTarget={400+VIEWX,500,150,150};
float		time=0;


typedef struct _aboutStr{
	char str[128];
	swPoint pos;
	float size;
}aboutStr;


#define ABOUT_STR_MAX 8
aboutStr aboutStrS[ABOUT_STR_MAX];


//-------------------------------------------------------------------------------------------
void aboutDeInit(){ 
	xenDemoAppSetActiveFunc(NULL);
	swEngineExit();
}


//-------------------------------------------------------------------------------------------
void aboutSetDeInitMode(void *obj){ 
	scnMngrSetMode(SCENE_EXIT_INTRO_DEINIT);	
}


//-------------------------------------------------------------------------------------------
void aboutRun(){ 

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	int index=swAnimatorGetIndex(xenRunAnimID);
	swGraphicsRenderSprite0(xenRunID,index,&xenRunTarget);	

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	for(int i=0;i<ABOUT_STR_MAX;i++){
		swGraphicsRenderText(fontID,1,aboutStrS[i].size,aboutStrS[i].pos.x,aboutStrS[i].pos.y,0,aboutStrS[i].str);
	}
}


//-------------------------------------------------------------------------------------------
void aboutInit(){ 

	aboutStr* str=NULL;

	float x=400;
	float y=400;
	float dLY=25;
	float dHY=45;

	float bSize=20;
	float sSize=16;

	//-----
	str=&aboutStrS[0];
	str->pos.x=x-5+VIEWX; str->pos.y=y; str->size=bSize; swStringCopy(str->str,"CODE & DESIGN");

	str=&aboutStrS[1];
	str->pos.x=x+30+VIEWX; str->pos.y=y-dLY; str->size=sSize; swStringCopy(str->str,"darklight");

	//-----

	str=&aboutStrS[2];
	str->pos.x=x+25+VIEWX; str->pos.y=y-(dLY+dHY); str->size=bSize; swStringCopy(str->str,"GRAPHIC");

	str=&aboutStrS[3];
	str->pos.x=x+35+VIEWX; str->pos.y=y-(dLY*2+dHY); str->size=sSize; swStringCopy(str->str,"takashi");


	//-----
	str=&aboutStrS[4];
	str->pos.x=x+35+VIEWX; str->pos.y=y-(2*dLY+2*dHY); str->size=bSize; swStringCopy(str->str,"MUSIC");

	str=&aboutStrS[5];
	str->pos.x=x+42+VIEWX; str->pos.y=y-(3*dLY+2*dHY); str->size=sSize; swStringCopy(str->str,"utku");


	//-----
	str=&aboutStrS[6];
	str->pos.x=x+38+VIEWX; str->pos.y=y-(3*dLY+3*dHY); str->size=bSize; swStringCopy(str->str,"TEST");

	str=&aboutStrS[7];
	str->pos.x=x+48+VIEWX; str->pos.y=y-(4*dLY+3*dHY); str->size=sSize; swStringCopy(str->str,"scg");


	hudEnd();

	swTimerUpdateDelaySeconds(gameLoopTimerID,0.016f);
	fullSceenFXSetActive(FULLSCREEN_FX_NONE);


	swGraphicsSetCamPos(camID,VIEWX,0);
	xenRunAnimID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(xenRunID),0.02f);
    swAnimatorSetExecutionMode(xenRunAnimID,SW_ANIMATOR_EXEC_FORWARD_LOOP);
	swScheduledManagerAdd1(aboutSetDeInitMode,NULL,3);
	scnMngrSetMode(SCENE_EXIT_INTRO_RUN);	
}


