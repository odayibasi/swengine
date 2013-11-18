#include "Hud.h"


void xenInVehicleGUIAddTextToLogScreen(char *Log);
void xenInVehicleGUIClearLogScreen();
void xenInVehicleGUIRestartLogScreen();


int	 HUDLayer=10;
bool HUDActive=true;
bool HUDEnd=false;
bool hudTransparent=false;

int  HUDDispID=-1;


extern int  hudEngineStartLedID,hudDangerLedID;
extern int  hudHealthID,hudArmorID;
extern int  hudWeaponID,hudWeaponBtnID,hudWeaponTxtID;
extern int  hudBombPanelShadowID, hudLayoutID, hudCockpitGlowID;
extern int  hudBombBarID,hudAmmoBarID;
extern int  hudCockpitCrashID,hudCockpitStillID,huCockpitExplodeID;
extern int  hudBombID;



swRect rectHUDEngineStartLed, rectHUDDangerLed;
swRect rectHUDHealth,rectHUDArmor,rectHUDHealthSource,rectHUDArmorSource;
swRect rectHUDWeapon,rectHUDWeaponBtn,rectHUDWeaponTxt;
swRect rectHUDLayout;
swRect rectHUDBombBar,rectHUDAmmoBar,rectHUDBombType;
swRect rectHUDCockpit;
swRect rectVehicleScore;
swRect rectVehicleBombCount,rectVehicleAmmoCount,rectVehicleScoreCount;

int  m_iScore,m_iBombCount,m_iAmmoCount;
int  m_iBombType,m_iWeaponType;
bool m_bHUDDangerLed=true;
bool m_bHUDEngineLed=true;



typedef enum _ElectricalBarState{
	ELECTRICAL_BAR_STATE_CLOSE,
	ELECTRICAL_BAR_STATE_OPEN,
	ELECTRICAL_BAR_STATE_CLOSING,
	ELECTRICAL_BAR_STATE_OPENING,
}ElectricalBarState;





int hudAmmoBarAnimID,hudBombBarAnimID,hudCockpitAnimID;	
ElectricalBarState stateAmmoBar,stateBombBar;
eCockpitMode m_iCockpitMode=COCKPIT_TYPE_NORMAL;

#define MAX_USABLE_WPN_COUNT 4
#define MAX_USABLE_BOMB_COUNT 4

int usableWpnS[MAX_USABLE_WPN_COUNT];
int usableBombS[MAX_USABLE_BOMB_COUNT];

extern int fontID;


typedef struct _CockpitMonitorText{
	char name[200];
}CockpitMonitorText;

typedef struct _CockpitLogText{
	CockpitMonitorText log;
	int iPassingKey;
	struct _CockpitLogText *prev,*next;
}CockpitLogText;

typedef struct _CockpitLogMonitor{
	float fElapsedTime,fWaitingTime;
	float fYElapsedTime,fYWaitingTime;
	float fDX,fDY;
	float fFontSize;
	float fPassingLog;
	swPoint pos;
	int		logText;
}CockpitLogMonitor;

CockpitLogMonitor logMonitor;

extern int camID;


//------------------------------------------------------------------------------------------
void hudDisplayLayout(){
		swGraphicsRenderImg0(hudLayoutID,&rectHUDLayout);
}


//------------------------------------------------------------------------------------------
void hudDisplayLeds(){
	if(m_bHUDEngineLed) swGraphicsRenderImg0(hudEngineStartLedID,&rectHUDEngineStartLed);
	if(m_bHUDDangerLed) swGraphicsRenderImg0(hudDangerLedID,&rectHUDDangerLed);
}


//------------------------------------------------------------------------------------------
void hudDisplaysHealthAndShield(){
	swGraphicsRenderImg2(hudHealthID,&rectHUDHealth,&rectHUDHealthSource);
	swGraphicsRenderImg2(hudArmorID,&rectHUDArmor,&rectHUDArmorSource);
}


//------------------------------------------------------------------------------------------
void hudDisplaysAmmoBar(){
	switch(stateAmmoBar){
			case ELECTRICAL_BAR_STATE_CLOSE:
				break;
			case ELECTRICAL_BAR_STATE_OPEN:
				break;
			case ELECTRICAL_BAR_STATE_CLOSING:
				if(swAnimatorIsFirstFrameActive(hudAmmoBarAnimID)) stateAmmoBar=ELECTRICAL_BAR_STATE_CLOSE;
				break;
			case ELECTRICAL_BAR_STATE_OPENING:
				if(swAnimatorIsLastFrameActive(hudAmmoBarAnimID)) stateAmmoBar=ELECTRICAL_BAR_STATE_OPEN;
				break;
			default:
				break;
	}

	int index=swAnimatorGetIndex(hudAmmoBarAnimID);
	swGraphicsRenderSprite0(hudAmmoBarID,index,&rectHUDAmmoBar);
}



//------------------------------------------------------------------------------------------
void hudDisplaysBombBar(){
	switch(stateBombBar){
			case ELECTRICAL_BAR_STATE_CLOSE:
				break;
			case ELECTRICAL_BAR_STATE_OPEN:
				break;
			case ELECTRICAL_BAR_STATE_CLOSING:
				if(swAnimatorIsFirstFrameActive(hudBombBarAnimID)) stateBombBar=ELECTRICAL_BAR_STATE_CLOSE;
				break;
			case ELECTRICAL_BAR_STATE_OPENING:
				if(swAnimatorIsLastFrameActive(hudBombBarAnimID)) stateBombBar=ELECTRICAL_BAR_STATE_OPEN;
				break;
			default:
				break;
	}

	int index=swAnimatorGetIndex(hudBombBarAnimID);
	swGraphicsRenderSprite0(hudBombBarID,index,&rectHUDBombBar);
}

//------------------------------------------------------------------------------------------
void hudDisplayWeapon(){
	if(m_iWeaponType!=0){
		swGraphicsRenderSprite0(hudWeaponID,m_iWeaponType-1,&rectHUDWeapon);
		swGraphicsRenderSprite0(hudWeaponTxtID,m_iWeaponType-1,&rectHUDWeaponTxt);
		swGraphicsRenderSprite0(hudWeaponBtnID,m_iWeaponType-1,&rectHUDWeaponBtn);
	}
}

//------------------------------------------------------------------------------------------
void hudDisplayBomb(){
	swGraphicsRenderSprite0(hudBombID,m_iBombType,&rectHUDBombType);
	swGraphicsRenderImg0(hudBombPanelShadowID,&rectHUDBombType);
}


//------------------------------------------------------------------------------------------
void hudDisplayCockpit(){
	int index=swAnimatorGetIndex(hudCockpitAnimID);
	swGraphicsRenderSprite0(hudCockpitStillID,index,&rectHUDCockpit);
	swGraphicsRenderImg0(hudCockpitGlowID,&rectHUDCockpit);
}

//------------------------------------------------------------------------------------------
void hudDisplayScore(){
	char temp[10];
	swStringFormatInt(8,temp,m_iScore);  
	swGraphicsRenderText(fontID,0,15,rectVehicleScoreCount.x,rectVehicleScoreCount.y,0,temp);
}


//------------------------------------------------------------------------------------------
void hudDisplayLog(){

	float dx=700;
	float dy=60;
	swGraphicsRenderText(fontID,0,12,dx,dy,0,"Welcome 7D8");
	swGraphicsRenderText(fontID,0,12,dx+2,dy-15*1,0,"XenDemo by");
	swGraphicsRenderText(fontID,0,12,dx+5,dy-15*2,0,"Darklight");
	swGraphicsRenderText(fontID,0,12,dx+10,dy-15*3,0,"Takashi");
}

//------------------------------------------------------------------------------------------
void hudDisplayAmmoCount(){
char temp[8];
	if(stateAmmoBar==ELECTRICAL_BAR_STATE_OPEN){
		swStringFormatInt(3,temp,usableWpnS[m_iWeaponType]);  
		swGraphicsRenderText(fontID,0,12,rectVehicleAmmoCount.x,rectVehicleAmmoCount.y,0,temp);
	}
}

//------------------------------------------------------------------------------------------
void hudDisplayBombCount(){
	char temp[8];
	if(stateBombBar==ELECTRICAL_BAR_STATE_OPEN){
		swStringFormatInt(3,temp,usableBombS[m_iBombType]);  
		swGraphicsRenderText(fontID,0,12,rectVehicleBombCount.x,rectVehicleBombCount.y,0,temp);
	}
}



//------------------------------------------------------------------------------------------
void hudDisplay(void *obj){

	if(HUDEnd) return;

	swGraphicsActiveCam(SW_CAM_DEFAULT);	
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
		if(hudTransparent)  swGraphicsSetColor0(1,1,1,0.3);
		else swGraphicsSetColor0(1,1,1,1);

		hudDisplayLayout();
		hudDisplaysHealthAndShield();
		hudDisplayLeds();
		hudDisplaysAmmoBar();
		hudDisplaysBombBar();
		hudDisplayWeapon();
		hudDisplayBomb();
		hudDisplayCockpit();

		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		hudDisplayScore();
		hudDisplayLog();
		hudDisplayAmmoCount();
		hudDisplayBombCount();




	swGraphicsActiveCam(camID);
}


//------------------------------------------------------------------------------------------
void hudDestroy(void *obj){
	swDispManagerDel(HUDDispID);
	swAnimatorDestroy(hudAmmoBarAnimID);
	swAnimatorDestroy(hudBombBarAnimID);
	swAnimatorDestroy(hudCockpitAnimID);
}



//------------------------------------------------------------------------------------------
void hudCreate(){

	//Setting
	float dx=112;
	float dy=0;
	swRectSet(&rectHUDLayout,0+dx,0,800,98);

	//Count
	swRectSet(&rectVehicleScore,300+dx,dy+300,30,30);
	swRectSet(&rectVehicleBombCount,516+dx,dy+56,300,39);
	swRectSet(&rectVehicleAmmoCount,260+dx,dy+56,30,30);
	swRectSet(&rectVehicleScoreCount,364+dx,dy+48,30,30);

	//Health & Shield		
	swRectSet(&rectHUDHealth,47+dx,dy+11,66,69);
	swRectSet(&rectHUDHealthSource,0,0,1,1);
	swRectSet(&rectHUDArmor,124+dx,dy+11,66,69);
	swRectSet(&rectHUDArmorSource,0,0,1,1);

	//Led
	swRectSet(&rectHUDDangerLed,32+dx,dy+43,30,30);
	swRectSet(&rectHUDEngineStartLed,1+dx,dy+23,30,30);


	//Weapon
	swRectSet(&rectHUDWeapon,107+dx,dy+29,30,30);
	swRectSet(&rectHUDWeaponTxt,106+dx,dy+18,30,8);
	swRectSet(&rectHUDWeaponBtn,190+dx,dy+30,32,16);

	//BombType
	swRectSet(&rectHUDBombType,249+dx,dy-3,306,40);

	//Ammo & Bomb Bar
	swRectSet(&rectHUDAmmoBar,237+dx,18,dy+60,65);
	swRectSet(&rectHUDBombBar,507+dx,18,dy+57,65);

	//Cockpit
	swRectSet(&rectHUDCockpit,713+dx,dy+11,66,66);


	//Animator Setting
	hudAmmoBarAnimID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(hudAmmoBarID),0.05);
	hudBombBarAnimID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(hudBombBarID),0.05);
	hudCockpitAnimID=swAnimatorCreate(swGraphicsGetCountOfImgInSprite(hudCockpitStillID),0.2);
	swAnimatorSetExecutionMode(hudCockpitAnimID,SW_ANIMATOR_EXEC_FORWARD_LOOP);

	HUDDispID=swDispManagerAdd(hudDisplay,NULL,&HUDActive,NULL,&HUDLayer);


	m_iScore=0;

	//Wpn & Bomb List
	for(int i=0;i<MAX_USABLE_WPN_COUNT;i++) usableWpnS[i]=0;
	for(int i=0;i<MAX_USABLE_BOMB_COUNT;i++)usableBombS[i]=0;

	//State Setting
	stateAmmoBar=ELECTRICAL_BAR_STATE_CLOSE;
	stateBombBar=ELECTRICAL_BAR_STATE_CLOSE;

	m_iWeaponType=WPN_TYPE_NONE;
	m_iBombType=BOMB_TYPE_NONE;

	swDestroyManagerAdd(hudDestroy,NULL);

}


//------------------------------------------------------------------------------------------
void hudSetHealth(int Health){ 
	rectHUDHealthSource.h=0.01f*Health;
	rectHUDHealth.h=69*0.01f*Health;
}

//------------------------------------------------------------------------------------------
void hudSetShield(int Shield){ 
	rectHUDArmorSource.h=0.01f*Shield;
	rectHUDArmor.h=69*0.01f*Shield;
}

//------------------------------------------------------------------------------------------
void hudSetScore(int Score){ 
	m_iScore=Score;
}

//------------------------------------------------------------------------------------------
void hudAddScore(int Score){ 
	m_iScore+=Score;
}

//------------------------------------------------------------------------------------------
void hudSetDangerLED(BOOL bOn){ 
	m_bHUDDangerLed=bOn;
}

//------------------------------------------------------------------------------------------
void hudSetEngineLED(BOOL bOn){ 
	m_bHUDEngineLed=bOn;
}


//------------------------------------------------------------------------------------------
void hudSetBombType(eBombType BombType){ 


	if(BombType==BOMB_TYPE_NONE && m_iBombType!=BombType){
		stateBombBar=ELECTRICAL_BAR_STATE_CLOSING;
		swAnimatorSetExecutionMode(hudBombBarAnimID,SW_ANIMATOR_EXEC_BACKWARD);
	}

	if(m_iBombType==BOMB_TYPE_NONE && m_iBombType!=BombType){
		stateBombBar=ELECTRICAL_BAR_STATE_OPENING;
		swAnimatorSetExecutionMode(hudBombBarAnimID,SW_ANIMATOR_EXEC_FORWARD);
	}
	m_iBombType=BombType;
}



//------------------------------------------------------------------------------------------
void hudSetWeaponType(eWpnType WpnType){ 

	if(WpnType==WPN_TYPE_NONE && m_iWeaponType!=WpnType){
		stateAmmoBar=ELECTRICAL_BAR_STATE_CLOSING;
		swAnimatorSetExecutionMode(hudAmmoBarAnimID,SW_ANIMATOR_EXEC_BACKWARD);
	}

	if(m_iWeaponType==WPN_TYPE_NONE && m_iWeaponType!=WpnType){
		stateAmmoBar=ELECTRICAL_BAR_STATE_OPENING;
		swAnimatorSetExecutionMode(hudAmmoBarAnimID,SW_ANIMATOR_EXEC_FORWARD);
	}

	m_iWeaponType=WpnType;	
}


//------------------------------------------------------------------------------------------
void hudXenCockpitMode(eCockpitMode CockpitMode){ 
	if(m_iCockpitMode!=CockpitMode){
		m_iCockpitMode=CockpitMode;
		swAnimatorSetIndex(hudCockpitAnimID,0);
	}

}

//------------------------------------------------------------------------------------------
void hudSetWeaponCount(eWpnType wpnType,int count){ 
	usableWpnS[wpnType]=count;
}


//------------------------------------------------------------------------------------------
void hudSetBombCount(eBombType bombType,int count){ 
	usableBombS[bombType]=count;	
}


//------------------------------------------------------------------------------------------
void hudSetEnabled(bool bActive){ 
	HUDActive=bActive;
}

//------------------------------------------------------------------------------------------
void hudEnd(){ 
	HUDEnd=true;
}


//------------------------------------------------------------------------------------------
void hudSetTransparent(bool bEnabled){ 
	hudTransparent=bEnabled;
}
