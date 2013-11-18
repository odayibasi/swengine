#ifndef SWSERVICES_H
#define SWSERVICES_H


#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include "SWTypes.h"
#include "SWUtil.h"
#include "SWCore.h"




#ifndef DllExport
#define DllExport extern "C" __declspec(dllexport)
#endif


//==================================================================================================
//                 PHYSICS MANAGER on Box2D
//                 -->WORLD 
//				   -->SHAPE
//                 -->BODY 
//                 -->JOINTS
//                 -->CONTACTS
//=================================================================================================


//World
DllExport void swPhysWorldSetMeterOfPixelRatio(float ratio);
DllExport void swPhysWorldCreate(swRect *AABB, swVec2 *gravity,bool doSleep);
DllExport void swPhysWorldDestroy();
DllExport void swPhysWorldUpdate();
DllExport void swPhysWorldSetGravity(swVec2 *gravity);


//Renderer
typedef enum _swPhysRenderedItemEnum{
  SW_PHYS_RENDERED_SHAPE,
  SW_PHYS_RENDERED_JOINTS,
  SW_PHYS_RENDERED_CORESHAPES,
  SW_PHYS_RENDERED_AABBs,
  SW_PHYS_RENDERED_OBBs,
  SW_PHYS_RENDERED_PAIRS,
  SW_PHYS_RENDERED_CONTACTPOINTS,
  SW_PHYS_RENDERED_CONTACTNORMALS,
  SW_PHYS_RENDERED_CONTACTFORCES,
  SW_PHYS_RENDERED_FRICTIONFORCES,
  SW_PHYS_RENDERED_CENTEROFMASSES,
  SW_PHYS_RENDERED_STATISTICS,
}swPhysRenderedItemEnum;

DllExport void swPhysRendererSetEnabled(swPhysRenderedItemEnum type, bool bVisible);
DllExport void swPhysRendererExecute();



//BodyDef Func
DllExport void  swPhysBodyDefSetUserData(void *userData);
DllExport void  swPhysBodyDefSetPos(float x,float y);
DllExport void  swPhysBodyDefSetAngle(float angle);
DllExport void  swPhysBodyDefSetRectShapeType(float w,float h);
DllExport void  swPhysBodyDefSetCircleShapeType(float radious);
DllExport void  swPhysBodyDefSetLinearDamping(float damping);
DllExport void  swPhysBodyDefSetDensity(float density);
DllExport void  swPhysBodyDefSetFriction(float friction);
DllExport void  swPhysBodyDefSetRestitution(float restitution);
DllExport void  swPhysBodyDefSetFixedRotation(bool bfixedRot);
DllExport void  swPhysBodyDefSetBullet(bool isBullet);
DllExport void  swPhysBodyDefSetFilterGroupIndex(int index);
DllExport void  swPhysBodyDefSetFilterCategoryBits(int bits);
DllExport void  swPhysBodyDefSetFilterMaskBits(int bits);
DllExport void  swPhysBodyDefSetPosListener(float *xListener,float *yListener);
DllExport void  swPhysBodyDefSetCenterListener(float *cxListener,float *cyListener);
DllExport void  swPhysBodyDefSetAngleListener(float *angleListener);



//Body Manage Func
DllExport int   swPhysBodyCreate();
DllExport void  swPhysBodyDestroy(int bodyID);
DllExport void  swPhysBodySetUserData(int bodyID, void *userData);
DllExport void  swPhysBodyApplyForce(int bodyID, swVec2 force,swPoint pos);
DllExport void  swPhysBodyApplyForce1(int bodyID, float fx, float fy,float x,float y);
DllExport void  swPhysBodySetLinearVelocity(int bodyID, swVec2 vel);
DllExport void  swPhysBodySetLinearVelocity1(int bodyID, float x, float y);
DllExport void  swPhysBodySetLinearVelocityY(int bodyID, float y);
DllExport void  swPhysBodySetLinearVelocityX(int bodyID, float x);
DllExport void  swPhysBodySetXForm(int bodyID, swVec2 pos,float rot);
DllExport void  swPhysBodySetXForm1(int bodyID, float x, float y,float rot);
DllExport void  swPhysBodySetBullet(int bodyID,bool isBullet);
DllExport void  swPhysBodyWakeUp(int bodyID);
DllExport void  swPhysBodyPutToSleep(int bodyID);


//Body Query Func
DllExport float swPhysBodyGetMass(int bodyID);
DllExport bool  swPhysBodyIsBullet(int bodyID);
DllExport bool  swPhysBodyIsStatic(int bodyID);
DllExport bool  swPhysBodyIsDynamic(int bodyID);
DllExport bool  swPhysBodyIsFrozen(int bodyID);
DllExport bool  swPhysBodyIsSleeping(int bodyID);

//Joint Funcs
DllExport int swPhysDistJointCreate(int bodyID1,swPoint anchor1,float bodyID2,swPoint anchor2,bool collideConneted);
DllExport int swPhysRevoJointCreate(int bodyID1,float bodyID2,swPoint anchor,float lowerAngle, float upperAngle, bool enableLimit, float maxMotorTorque, float motorSpeed, bool enableMotor);
DllExport int swPhysPrisJointCreate(int bodyID1,float bodyID2,swPoint anchor,swPoint axis,float lowerTrans, float upperTrans, bool enableLimit, float maxMotorForce, float motorSpeed, bool enableMotor);
DllExport int swPhysPullJointCreate(int bodyID1,float bodyID2,swPoint gAnchor1,swPoint gAnchor2,swPoint anchor1,swPoint anchor2, float ratio,float maxLength1, float maxLength2);
DllExport int  swPhysGearJointCreate(int bodyID1,float bodyID2,int joint1,int joint2,float ratio);
DllExport void swPhysJointDestroy(int jointID);

//Contact
typedef enum _swContactState{
	SW_CONTACT_ADDED,
	SW_CONTACT_PERSIST,
	SW_CONTACT_REMOVED,
}swContactState;

struct swContactPoint
{
	void *userData1;
	void *userData2;
	swContactState state;
};


DllExport void  swPhysContactSetListener(void(*contactListen)(swContactPoint*));

//Model
struct swExplosionEffect
{
	float  dist;
	void  *userData;
};
DllExport void swPhysModelExplosion(swVec2 pos, float radious, float force,void(*explosionListen)(swExplosionEffect*));



//==================================================================================================
//                 DESTROY MANAGER
//=================================================================================================
DllExport void swDestroyManagerInit();
DllExport void swDestroyManagerDeInit();
DllExport void swDestroyManagerExecute();
DllExport void swDestroyManagerAdd(void(*destroyFunc)(void*), void *obj);


//==================================================================================================
//                 DISPLAY MANAGER
//=================================================================================================
DllExport void  swDispManagerInit();
DllExport void  swDispManagerDeInit();
DllExport int   swDispManagerAdd(void(*dispFunc)(void*), void *obj,bool *bEnabled,swRect *rect,int *layer);
DllExport void  swDispManagerDel(int id);
DllExport void  swDispManagerSetLayerCount(int count);
DllExport void  swDispManagerSetCullRegionPos(float x,float y);
DllExport void  swDispManagerSetCullRegion(float x,float y,float w,float h);
DllExport void  swDispManagerExecute();
DllExport int   swDispManagerSizeOfAll();
DllExport int   swDispManagerSizeOfRendered();


//==================================================================================================
//                 EXECUTE MANAGER
//=================================================================================================
DllExport void  swExecManagerInit();
DllExport void  swExecManagerDeInit();
DllExport int   swExecManagerAdd(void(*execFunc)(void*), void *obj,bool *bEnabled);
DllExport void  swExecManagerDel(int id);
DllExport void  swExecManagerExecute();


//==================================================================================================
//                  PERSIST MANAGER
//=================================================================================================

DllExport void  swPersistManagerInit();
DllExport void  swPersistManagerDeInit();
DllExport int   swPersistManagerAdd(void(*saveFunc)(FILE *,void*), void *obj);
DllExport void  swPersistManageDel(int id);
DllExport void  swPersistManagerExecute(FILE *file);



//==================================================================================================
//                  INTERACTION MANAGER
//=================================================================================================

DllExport void  swInteractionManagerInit();
DllExport void  swInteractionManagerDeInit();
DllExport int   swInteractionManagerAdd(void(*intrFunc)(void*,swKeyboardState *,swMouseState *), void *obj,bool *bEnabled);
DllExport void  swInteractionManagerExecute(swKeyboardState *keybState,swMouseState *mousState);
DllExport void  swInteractionManagerDel(int id);


//==================================================================================================
//                  SCHEDULED MANAGER
//=================================================================================================
DllExport void  swScheduledManagerInit();
DllExport void  swScheduledManagerDeInit();
DllExport void  swScheduledManagerAdd1(void(*scheduledFunc)(void*), void *obj,float waitingTime);
DllExport void  swScheduledManagerAdd0(void(*scheduledFunc)(void*), void *obj,float triggerTime);


//==================================================================================================
//                  MOUSE BEHAVIOUR
//=================================================================================================

typedef struct _swMousBehaviourListener{
  void (*pressed)(float,float);
  void (*released)(float,float);
  void (*dragging)(float,float);
  void (*moving)(float,float);
}swMousBehaviourListener;


DllExport void  swMousBehaviourInit();
DllExport void  swMousBehaviourDeInit();
DllExport void  swMousBehaviourAdd(swMousBehaviourListener *listener);
DllExport void  swMousBehaviourDel(swMousBehaviourListener *listener);
DllExport void  swMousBehaviourExecute(swMouseState *mousState);



//==================================================================================================
//                  KEY BEHAVIOUR
//=================================================================================================

typedef struct _swKeybBehaviourListener{
	void (*typed)(char c);
	void (*pressed)(swKeyEnum key);
	void (*released)(swKeyEnum key);
}swKeybBehaviourListener;


DllExport void  swKeybBehaviourInit();
DllExport void  swKeybBehaviourDeInit();
DllExport void	swKeybBehaviourSetTypedSleepTime(float dTime);
DllExport void  swKeybBehaviourAdd(swKeybBehaviourListener *listener);
DllExport void  swKeybBehaviourDel(swKeybBehaviourListener *listener);
DllExport void  swKeybBehaviourExecute(swKeyboardState *keybState);



//==================================================================================================
//                DSL (DOMAIN SPESIFIC LANGUAGE)
//=================================================================================================
#define MAX_CHAR_DLS_CMD 64

DllExport void  swDSLInit();
DllExport void  swDSLDeInit();
DllExport void  swDSLRegisterCommand(void(*cmdFunc)(int,swArg *cArgs),char *cmdName,int count,swArg *cArgs);
DllExport bool  swDSLExecuteCommand(char *fullCmd);
DllExport bool  swDSLIsValidCommand(char *fullCmd);









#endif
