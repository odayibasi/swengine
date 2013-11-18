#include "SWServicesIn.h"

BodyBuffer  bodyBuffer;

//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyDefSetPos(float x,float y){
	float b2X=swPhysUtilConvert(x);
	float b2Y=swPhysUtilConvert(y);
	swPointSet(&bodyBuffer.pos,b2X,b2Y);
}


//-------------------------------------------------------------------------------------------
DllExport void  swPhysBodyDefSetAngle(float angle){
	float angleRad=swMathDegreeToRadian(angle);
	bodyBuffer.angle=angleRad;
}


//-------------------------------------------------------------------------------------------
DllExport void  swPhysBodyDefSetRectShapeType(float w,float h){
	bodyBuffer.shapeType=BODY_SHAPE_RECT;
	swRectSet(&bodyBuffer.shapeRect,0,0,swPhysUtilConvert(w),swPhysUtilConvert(h));
}

//-------------------------------------------------------------------------------------------
DllExport void  swPhysBodyDefSetCircleShapeType(float radious){
	bodyBuffer.shapeType=BODY_SHAPE_CIRCLE;
	swRectSet(&bodyBuffer.shapeRect,0,0,swPhysUtilConvert(radious),0);
}


//-------------------------------------------------------------------------------------------
DllExport void  swPhysBodyDefSetDensity(float density){
	bodyBuffer.density=density;
}


//-------------------------------------------------------------------------------------------
DllExport void  swPhysBodyDefSetUserData(void *userData){
	bodyBuffer.userData=userData;
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyDefSetFixedRotation(bool bfixedRot){
	bodyBuffer.fixedRotation=bfixedRot;
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyDefSetFriction(float friction){
	bodyBuffer.friction=friction;
}

//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyDefSetRestitution(float restitution){
	bodyBuffer.restitution=restitution;
}

//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyDefSetBullet(bool isBullet){
	bodyBuffer.isBullet=isBullet;
}


//-------------------------------------------------------------------------------------------
DllExport void  swPhysBodyDefSetLinearDamping(float damping){
	bodyBuffer.linearDamping=damping;
}

//-------------------------------------------------------------------------------------------
DllExport void  swPhysBodyDefSetFilterGroupIndex(int index){
	bodyBuffer.filterGroupIndex=index;
}


//-------------------------------------------------------------------------------------------
DllExport void  swPhysBodyDefSetFilterCategoryBits(int bits){
	bodyBuffer.filterCategoryBits=bits;
}

//-------------------------------------------------------------------------------------------
DllExport void  swPhysBodyDefSetFilterMaskBits(int bits){
	bodyBuffer.filterMaskBits=bits;
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyDefSetPosListener(float *xListener,float *yListener){
	bodyBuffer.xListener=xListener;
	bodyBuffer.yListener=yListener;
}

//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyDefSetAngleListener(float *angleListener){
	bodyBuffer.rListener=angleListener;
}

//-------------------------------------------------------------------------------------------
DllExport void  swPhysBodyDefSetCenterListener(float *cxListener,float *cyListener){
	bodyBuffer.cxListener=cxListener;
	bodyBuffer.cyListener=cyListener;
	
}

//-------------------------------------------------------------------------------------------
void swPhysBodyDefReset(){
	b2ShapeDef def;
	b2BodyDef  bDef;
	bodyBuffer.xListener=NULL;
	bodyBuffer.yListener=NULL;
	bodyBuffer.rListener=NULL;
	bodyBuffer.cxListener=NULL;
	bodyBuffer.cyListener=NULL;

	bodyBuffer.userData=def.userData;

	bodyBuffer.density=def.density;
	bodyBuffer.restitution=def.restitution;
	bodyBuffer.friction=def.friction;
	bodyBuffer.shapeType=BODY_SHAPE_NULL;


	bodyBuffer.linearDamping=bDef.linearDamping;
	bodyBuffer.fixedRotation=false;
	bodyBuffer.isBullet=false;

	bodyBuffer.pos.x=bDef.position.x;
	bodyBuffer.pos.y=bDef.position.y;
	bodyBuffer.angle=bDef.angle;

	bodyBuffer.filterGroupIndex=def.filter.groupIndex;
	bodyBuffer.filterMaskBits=def.filter.maskBits;
	bodyBuffer.filterCategoryBits=def.filter.categoryBits;
}

