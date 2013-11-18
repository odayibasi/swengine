#include "PostProcessingFX.h"
#include "XenCommon.h"
#include <math.h>

int activeShaderID=SW_DISABLED_SHADER_ID;


extern int shdGrayscaled;
extern int shdSharpen;
extern int shdDiognalBlur;
extern int shdInverted;
extern int shdEmboss;
extern int shdMultiplier;
extern int shdShockWave;


extern bool xenShadowActive;

//-------------------------------------------------------------------------------------------
void fullSceenFXSetActive(xenFullSreenFXType fxType){
	xenShadowActive=false;
	switch(fxType){
		case FULLSCREEN_FX_GRAYSCALED:
			activeShaderID=shdGrayscaled;
			break;

		case FULLSCREEN_FX_SHARPEN:
			activeShaderID=shdSharpen;
			break;

		case FULLSCREEN_FX_DIOGNALBLUR:
			activeShaderID=shdDiognalBlur;
			break;

		case FULLSCREEN_FX_INVERTED:
			activeShaderID=shdInverted;
			break;

		case FULLSCREEN_FX_EMBOSSS:
			activeShaderID=shdEmboss;
			break;

		case FULLSCREEN_FX_MULTIPLIER:
			activeShaderID=shdMultiplier;
			break;

		case FULLSCREEN_FX_SHOCKWAVE:
			activeShaderID=shdShockWave;
			break;


		default:
			activeShaderID=SW_DISABLED_SHADER_ID;
			xenShadowActive=true;
			break;

	}//end of switch	
}


//-------------------------------------------------------------------------------------------
int fullSceenFXGetActive(){
	return activeShaderID;
}


//-------------------------------------------------------------------------------------------
void fullSceenFXUpdateVariables(){
	if(xenDemoIsSupportPostProcessing()){
		if(activeShaderID==shdShockWave){
			shockWaveGLSLVariablesUpdate();
		}
	}
}
