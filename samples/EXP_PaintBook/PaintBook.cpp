#include "../../include/SWEngine.h"
#include <math.h>

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")  



typedef enum _pbColorIndex{
  PB_COLOR_INDEX_RED,
  PB_COLOR_INDEX_GREEN,
  PB_COLOR_INDEX_BLUE,
  PB_COLOR_INDEX_WHITE,
  PB_COLOR_INDEX_BLACK,
}pbColorIndex;


#define IMG_POSX 244
#define IMG_POSY 100
#define IMG_WIDTH  312
#define IMG_HEIGHT 400





swMouseState  mousState;
swKeyboardState keybState;
swApplication paintBookApp;
pbColorIndex  colorBuffer[IMG_WIDTH][IMG_HEIGHT];
pbColorIndex  fillColor=PB_COLOR_INDEX_GREEN;

//-------------------------------------------------------------------------------------------
swColor* convertColorIndex2Color(pbColorIndex index){
	switch(index){
		case PB_COLOR_INDEX_BLACK:
			return &SWCOLOR_BLACK;
		case PB_COLOR_INDEX_BLUE:
			return &SWCOLOR_BLUE;
		case PB_COLOR_INDEX_GREEN:
			return &SWCOLOR_GREEN;
		case PB_COLOR_INDEX_WHITE:
			return &SWCOLOR_WHITE;
		case PB_COLOR_INDEX_RED:
			return &SWCOLOR_RED;
	}
	return NULL;
} 


//-------------------------------------------------------------------------------------------
pbColorIndex getPixel(int x,int y){
	return colorBuffer[x][y];
}

//-------------------------------------------------------------------------------------------
void setPixel(int x,int y,pbColorIndex index){
	colorBuffer[x][y]=index;
}

//-------------------------------------------------------------------------------------------
void boundaryFill(int x,int y,pbColorIndex fill,pbColorIndex boundary){

	pbColorIndex current=getPixel(x,y);
	if(current!=boundary && current!=fill){
		setPixel(x,y,fill);
		boundaryFill(x+1,y,  fill,boundary);
		boundaryFill(x-1,y,  fill,boundary);
		boundaryFill(x  ,y+1,fill,boundary);
		boundaryFill(x  ,y-1,fill,boundary);
	}
}


//-------------------------------------------------------------------------------------------
void GameLoop(){ //This function triggered when 1 frame process end Independent Time

	swInputListenKeyboard(&keybState);
	swInputListenMouse(&mousState);
	swInteractionManagerExecute(&keybState,&mousState);


	//Select Fill Color	
	if(keybState.key1){
		fillColor=PB_COLOR_INDEX_RED;
	}else if(keybState.key2){	
		fillColor=PB_COLOR_INDEX_GREEN;
	}else if(keybState.key3){	
		fillColor=PB_COLOR_INDEX_BLUE;
	}


	if(mousState.btnLEFT){
		float mX=mousState.x-IMG_POSX;
		float mY=mousState.y-IMG_POSY;
		if(mX>0 && mX<IMG_WIDTH &&
			mY>0 && mY<IMG_HEIGHT){
			boundaryFill(mX,mY,fillColor,PB_COLOR_INDEX_BLACK);
		}
	}

	//Display Scene	
	swGraphicsBeginScene();

		swGraphicsSetBgColor2(&SWCOLOR_WHITE);
		for(int x=0;x<IMG_WIDTH;x++){
			for(int y=0;y<IMG_HEIGHT;y++){
				pbColorIndex index=getPixel(x,y);
				swGraphicsSetColor1(convertColorIndex2Color(index));	
				swGraphicsRenderPoint0(x+IMG_POSX,y+IMG_POSY,1);
			}
		}

  swGraphicsEndScene();
}



//-------------------------------------------------------------------------------------------
void GameInit(){
	swImgBufferLoad("Sample.tga",SW_IMGTYPE_TGA);
	int width=swImgBufferGetWidth();
	int height=swImgBufferGetHeight();
	swColor currPixel;

	for(int x=0;x<width;x++){
		for(int y=0;y<height;y++){
			swImgBufferGetPixel(x,y,&currPixel);
			if(currPixel.r>0.9)
				setPixel(x,y,PB_COLOR_INDEX_WHITE);
			else
				setPixel(x,y,PB_COLOR_INDEX_BLACK);
		}
	}

}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 

	//Application Settings
	paintBookApp.hInstance=hInstance;
	paintBookApp.fullScreen=false;
	paintBookApp.cursor=true;
	paintBookApp.width=800;
	paintBookApp.height=600;
	paintBookApp.title="Paint Book";
	paintBookApp.path="\\rsc\\PaintBook\\";
	paintBookApp.appRun=GameLoop;

	//Application Execution
	//Init SWEngine
	swEngineInit(&paintBookApp);
	GameInit();
	swEngineRun();
	swEngineExit();

	return 0;
}