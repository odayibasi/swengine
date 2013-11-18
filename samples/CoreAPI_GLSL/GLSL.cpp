#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    


swApplication glslApp;
swKeyboardState keybState;
int imgID=-1;
int fontID=-1;
swRect rect={0,0,512,512};
int diognalblur=SW_DISABLED_SHADER_ID;
int edgedetection=SW_DISABLED_SHADER_ID;
int emboss=SW_DISABLED_SHADER_ID;
int inverted=SW_DISABLED_SHADER_ID;
int bloom=SW_DISABLED_SHADER_ID;
int sharpen=SW_DISABLED_SHADER_ID;
int multiplier=SW_DISABLED_SHADER_ID;
int samplingCoord=SW_DISABLED_SHADER_ID;
int samplingCoordexp=SW_DISABLED_SHADER_ID;
int activeShaderID=SW_DISABLED_SHADER_ID;


//-------------------------------------------------------------------------------------------
void GameLoop(){ 


	//Input Handling
	swInputListenKeyboard(&keybState);
	if(keybState.keyESCAPE){
		swEngineExit();
	}

	if(keybState.key0)
		activeShaderID=SW_DISABLED_SHADER_ID;

	if(keybState.key1)
		activeShaderID=diognalblur;

	if(keybState.key2)
		activeShaderID=edgedetection;

	if(keybState.key3)
		activeShaderID=emboss;

	if(keybState.key4)
		activeShaderID=inverted;

	if(keybState.key5)
		activeShaderID=bloom;

	if(keybState.key6)
		activeShaderID=sharpen;

	if(keybState.key7)
		activeShaderID=multiplier;

	if(keybState.key8)
		activeShaderID=samplingCoord;

	if(keybState.key9)
		activeShaderID=samplingCoordexp;


    
	swGraphicsBeginScene();

	    //Background
		swGraphicsSetBgColor0(0.6f,0.6f,0.6f);

		//Img Rendering
		swGraphicsActiveGLSLShader(activeShaderID);
		swGraphicsSetColor0(1,1,1,1);
		swGraphicsRenderImg0(imgID,&rect);

		//Info Rendering
		swGraphicsActiveGLSLShader(SW_DISABLED_SHADER_ID);
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		swGraphicsRenderText(fontID,0,16,515,450,0,"Key0=Disabled Shader");
		swGraphicsRenderText(fontID,0,16,515,430,0,"Key1=Diognal Blur");
		swGraphicsRenderText(fontID,0,16,515,410,0,"Key2=Edge Detection");
		swGraphicsRenderText(fontID,0,16,515,390,0,"Key3=Emboss");
		swGraphicsRenderText(fontID,0,16,515,370,0,"Key4=Inverted");
		swGraphicsRenderText(fontID,0,16,515,350,0,"Key5=Bloom");
		swGraphicsRenderText(fontID,0,16,515,330,0,"Key6=Sharpen");
		swGraphicsRenderText(fontID,0,16,515,310,0,"Key7=Multiplier");
		swGraphicsRenderText(fontID,0,16,515,290,0,"Key8=Sampling Coord");
		swGraphicsRenderText(fontID,0,16,515,270,0,"Key9=Sampling CoordEx");
	swGraphicsEndScene();
}





//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	glslApp.hInstance=hInstance;
	glslApp.fullScreen=false;
	glslApp.cursor=true;
	glslApp.width=800;
	glslApp.height=600;
	glslApp.title="GLSL";
	glslApp.path="\\rsc\\GLSL\\";
	glslApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&glslApp);

	if(!swGraphicsIsSupportGLSL()){
		swEngineExit();
		return 0; //exit
	}

	//InitApp
	imgID=swGraphicsCreateImg("fruits.tga");
	fontID=swGraphicsCreateFont("font.tga");
	diognalblur=swGraphicsCreateGLSLShader("fixed.vert","diognalblur.frag");
	edgedetection=swGraphicsCreateGLSLShader("fixed.vert","edgedetection.frag");
	emboss=swGraphicsCreateGLSLShader("fixed.vert","emboss.frag");
	inverted=swGraphicsCreateGLSLShader("fixed.vert","inverted.frag");
	bloom=swGraphicsCreateGLSLShader("fixed.vert","bloom.frag");
	sharpen=swGraphicsCreateGLSLShader("fixed.vert","sharpen.frag");
	multiplier=swGraphicsCreateGLSLShader("fixed.vert","multiplier.frag");
	samplingCoord=swGraphicsCreateGLSLShader("fixed.vert","samplingcoord.frag");
	samplingCoordexp=swGraphicsCreateGLSLShader("fixed.vert","samplingcoordexp.frag");
	activeShaderID=SW_DISABLED_SHADER_ID;
	
	swEngineRun();
	swEngineExit();

	return 0;
}