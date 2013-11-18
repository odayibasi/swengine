#include "PostProcessingFX.h"

extern int shdShockWave;
extern int camID;
swPoint    shockWavePos={0.5,0.5};
float      alphaFrame=0;
float      elapsedTime=0.016;
float      widthMultiplier=0.85f;


//-------------------------------------------------------------------------------------------
void shockWaveEditorInit(){
	int winID=swNumPropWinCreate("ShockWave",200,200,300,3);
	swNumPropWinAddFloat(winID,"elapsedTime",&elapsedTime,0.000f,0.030f,0.001);	
	swNumPropWinAddFloat(winID,"alphaFrame",&alphaFrame,0.0f,1.0f,0.01f);	
	swNumPropWinAddFloat(winID,"widthMultiplier",&widthMultiplier,0.50f,1.0f,0.01f);
	swNumPropWinSetVisible(winID,true);
}


//-------------------------------------------------------------------------------------------
void shockWaveExit(){
	fullSceenFXSetActive(FULLSCREEN_FX_NONE);
}


//-------------------------------------------------------------------------------------------
void shockWaveEnter(float x,float y){
	float dX=swGraphicsGetCamPosX(camID);
	swPointSet(&shockWavePos,(x-dX)/1024.0f,y/800.0f);
	alphaFrame = 0.0f;
	elapsedTime=0;
	fullSceenFXSetActive(FULLSCREEN_FX_SHOCKWAVE);	
}


//-------------------------------------------------------------------------------------------
void shockWaveGLSLVariablesUpdate(){

	elapsedTime+=0.0008;
	//if(elapsedTime>0.0080) //wait
		alphaFrame +=elapsedTime*2;
	
	if (alphaFrame > 1.0f){
		elapsedTime=0.016;
		shockWaveExit();
	} 

	swPoint pos;
	swPointSet(&pos,0.5,0.5);
	float width=alphaFrame * widthMultiplier;
	float mag=1.0f -alphaFrame;

	swGraphicsSetGLSLShaderPointAttrb(shdShockWave,"center",shockWavePos);
	swGraphicsSetGLSLShaderFloatAttrb(shdShockWave,"mag",mag);
	swGraphicsSetGLSLShaderFloatAttrb(shdShockWave,"width",width);
}



