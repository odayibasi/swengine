#ifndef XEN_POSTPROCESSING_FX_H
#define XEN_POSTPROCESSING_FX_H

#include "../../include/SWEngine.h"




//FullScreenFX
typedef enum _FullSreenFXType{
	FULLSCREEN_FX_NONE,
	FULLSCREEN_FX_GRAYSCALED,
	FULLSCREEN_FX_SHARPEN,
	FULLSCREEN_FX_DIOGNALBLUR,
	FULLSCREEN_FX_INVERTED,
	FULLSCREEN_FX_EMBOSSS,
	FULLSCREEN_FX_MULTIPLIER,
	FULLSCREEN_FX_SHOCKWAVE,
}xenFullSreenFXType;


void fullSceenFXSetActive(xenFullSreenFXType fxType);
int  fullSceenFXGetActive();
void fullSceenFXUpdateVariables();


//SlowMotion
void slowMotionEnter();


//ShockWave
void shockWaveEditorInit();
void shockWaveEnter(float x,float y);
void shockWaveGLSLVariablesUpdate();

//LasarCollision
void laserCollisionEnter();




#endif
