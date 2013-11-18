#ifndef SWSERVICES_IN_H
#define SWSERVICES_IN_H


#pragma comment (lib,"../../lib/SWTypes.lib")   
#pragma comment (lib,"../../lib/SWUtil.lib")   
#pragma comment (lib,"../../lib/SWCore.lib")   


#include "../../include/SWServices.h"
#include "Box2D/Include/Box2D.h"
#include "Box2D/Framework/Render.h"

typedef enum _ShapeEnum{
	BODY_SHAPE_NULL,
	BODY_SHAPE_RECT,
	BODY_SHAPE_CIRCLE,
}ShapeEnum;


typedef struct _BodyBuffer{
	ShapeEnum	 shapeType;
	swRect		 shapeRect;
	void         *userData;
	swPoint		 pos;
	float		 angle;
	float        density;
	float        friction;
	float        restitution;
	float		 linearDamping;
	int          filterCategoryBits;
	int          filterMaskBits;
	int          filterGroupIndex;
	bool         fixedRotation;
	bool         isBullet;
	float		 *xListener;
	float		 *yListener;
	float		 *rListener; 
	float        *cxListener;
	float        *cyListener;
}BodyBuffer;

void swPhysBodyDefReset();

typedef struct _PhysBody{
	int		  id;
	b2Body	  *body;
	float	  *xListener;
	float	  *yListener;
	float	  *angleListener;
	float     *cxListener;
	float     *cyListener;
}PhysBody;

//Renderer
void swPhysRendererInit();

//Body
void	swPhysBodyInit();
void	swPhysBodyUpdate();
void	swPhysBodyDeInit();
PhysBody* swPhysBodyGet(int id);


//World
b2World * swPhysWorldGet();
void swPhysWorldCreate(swRect *AABB, swVec2 *gravity,bool doSleep);
void swPhysWorldUpdate();
void swPhysWorldDestroy();

//PhysUtil
void  swPhysUtilMeterOfPixelRatio(float ratio);
float swPhysUtilConvert(float pixel);
float swPhysUtilReConvert(float meter);
void  swPhysUtilConvertRect(swRect *rPixel,swRect *rMeter);

//Contact
void  swPhysContactInit();
void  swPhysContactDeInit();
void  swPhysContactUpdate();


//Joints
typedef struct _PhysJoint{
	int		   id;
	b2Joint	  *joint;
}PhysJoint;


void swPhysJointInit();
void swPhysJointDeInit();

#endif