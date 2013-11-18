#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    
swApplication propertyWinApp;


int windowID=-1;
int windowTexID=-1;
swRect window={0,0,800,600};

typedef enum _eBoundaryStyle{
    BOUNDARY_POINT,
	BOUNDARY_LINE,
}eBoundaryStyle;

//Boundary
int boundaryStyle=BOUNDARY_LINE;
swColor boundaryColor={1,0,0,0};
float   boundarySize=5;

//Inner
swColor innerColor={0,1,0,0};

//Elips
swPoint elipsPos={400,300};
swDimension elipsDim={250,150};
int elipsSmoothness=60;

swKeyboardState keybState;
swMouseState    mousState;

char lineName[5]="line";
char pointName[6]="point";


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swInputListenKeyboard(&keybState);
	swInputListenMouse(&mousState);

	swInteractionManagerExecute(&keybState,&mousState);
	swGraphicsBeginScene();
		
		swGraphicsSetBgColor1(0,0,0,0);

		//Fill Elips
		swGraphicsSetColor1(&innerColor);
		swGraphicsRenderSolidElips1(&elipsPos,&elipsDim,elipsSmoothness);

		//Draw Elips Boundary
		swGraphicsSetColor1(&boundaryColor);
		if(boundaryStyle==BOUNDARY_POINT){
			swGraphicsRenderPointElips1(&elipsPos,&elipsDim,elipsSmoothness,boundarySize);
		}else if(boundaryStyle==BOUNDARY_LINE){
			swGraphicsRenderLineElips1(&elipsPos,&elipsDim,elipsSmoothness,boundarySize);
		}

		//Manage GUI System 
		
		swDispManagerExecute();

		//Display Cursor
		//swGraphicsSetColor1(&SWCOLOR_BLUE);
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
	propertyWinApp.hInstance=hInstance;
	propertyWinApp.fullScreen=false;
	propertyWinApp.cursor=true;
	propertyWinApp.width=800;
	propertyWinApp.height=600;
	propertyWinApp.title="PropertyWin";
	propertyWinApp.path="\\rsc\\PropertyWin\\";
	propertyWinApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&propertyWinApp);


	//Set Resource Path (Logo, Font, IconSet)
    swNumPropWinSetPath("NumPropWinRsc\\");



	//CreateEnumList
	int enumList=swLinkedListCreate();
	swLinkedListAdd(enumList,lineName);
	swLinkedListAdd(enumList,pointName);

	//Create Windows
	int winID=swNumPropWinCreate("Elips Property",200,200,300,4);
	int winElipsPosID=swNumPropPointWinCreate("Center",300,300,&elipsPos);
	int winElipsDimID=swNumPropDimWinCreate("Size",300,300,&elipsDim);
	int winInnerColorID=swNumPropColorWinCreate("Fill Color",300,300,&innerColor);
	int winBoundaryColorID=swNumPropColorWinCreate("Boundary Color",300,300,&boundaryColor);
	

	//Add Property To WinID(Elips Property Win)
	swNumPropWinAddInt(winID,"Smooth",&elipsSmoothness,3,100,1);
	swNumPropWinAddEnum(winID,"BoundaryType",&boundaryStyle,enumList);	
	swNumPropWinAddFloat(winID,"BoundarySize",&boundarySize,0.0f,10.0f,1.0f);	
	swNumPropWinAddSubWin(winID,winElipsPosID);
	swNumPropWinAddSubWin(winID,winElipsDimID);
	swNumPropWinAddSubWin(winID,winInnerColorID);
	swNumPropWinAddSubWin(winID,winBoundaryColorID);
	swNumPropWinSetVisible(winID,true);

	swEngineRun();
	swEngineExit();

	return 0;
}


