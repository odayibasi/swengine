#ifndef SWGAME_H
#define SWGAME_H


#include "SWTypes.h"
#include "SWUtil.h"
#include "SWCore.h"



#ifndef DllExport
#define DllExport extern "C" __declspec(dllexport)
#endif


//==================================================================================================
//                ANIMATOR MANAGER
//=================================================================================================

typedef enum {
	SW_ANIMATOR_EXEC_STOP,
	SW_ANIMATOR_EXEC_FORWARD,
	SW_ANIMATOR_EXEC_BACKWARD,
	SW_ANIMATOR_EXEC_BACKWARD_LOOP,
	SW_ANIMATOR_EXEC_FORWARD_LOOP,
}swAnimatorExecMode;

DllExport void  swAnimatorInit();
DllExport void  swAnimatorDeInit();
DllExport int   swAnimatorCreate(int count, float delay);
DllExport void  swAnimatorDestroy(int animatorID);
DllExport void  swAnimatorSetIndex(int animatorID,int imgIndex);
DllExport int   swAnimatorGetIndex(int animatorID);
DllExport void  swAnimatorSetDelay(int animatorID,float delay);
DllExport void  swAnimatorSetExecutionMode(int animatorID, swAnimatorExecMode mode);
DllExport bool  swAnimatorIsLastFrameActive(int animatorID);
DllExport bool  swAnimatorIsFirstFrameActive(int animatorID);


//==================================================================================================
//                LINKER
//=================================================================================================

DllExport void  swLinkerInit();
DllExport void  swLinkerDeInit();
DllExport int	swLinkerCreate(swPoint *parent,swPoint *child);
DllExport void	swLinkerDestroy(int linkerID);
DllExport void	swLinkerBind0(int linkerID,swRect *parent,swRect *child);
DllExport void	swLinkerBind1(int linkerID,int linkerCID,swRect *parent,int indexParent,swRect *child,int indexChild);
DllExport void	swLinkerBind2(int linkerID,swRect *sourceParent,swRect *targetParent,swPoint *wpParent,float rotParent,int indexParent,swRect *sourceChild,swRect *targetChild,swPoint *wpChild,float rotChild,int indexChild);

//==================================================================================================
//                INTERPOLATER MANAGER
//=================================================================================================

DllExport void     swInterpolaterInit();
DllExport void     swInterpolaterDeInit();
DllExport int      swInterpolaterCreate(float initVal,float endVal,float totalTime);
DllExport void     swInterpolaterDestroy(int id);
DllExport bool	   swInterpolaterIsFinished(int interpolaterID);
DllExport void     swInterpolaterStart(int interpolaterID);
DllExport float    swInterpolaterGetValue(int interpolaterID);


//==================================================================================================
//                VALUE MODIFIER
//=================================================================================================

typedef enum{
	SW_VALUE_MODIFIER_01_LOOP,
	SW_VALUE_MODIFIER_10_LOOP,
	SW_VALUE_MODIFIER_010_LOOP,
}swValueModifierMode;

DllExport void     swValueModifierInit();
DllExport void     swValueModifierDeInit();
DllExport int      swValueModifierCreate(swValueModifierMode mode,float *val,float begin,float end,float velocity,float acceleration);
DllExport void     swValueModifierDestroy(int modID);
DllExport void	   swValueModifierExecute(int id,float dTime);





//==================================================================================================
//                  BEZIERPATH API
//=================================================================================================




//==================================================================================================
//                  TEXTUREFX API
//==================================================================================================








#endif
