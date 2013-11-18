#include "SWServicesIn.h"

b2Vec2 phys_Gravity(0.0f, -1000.0f);
b2World *swWorld;

//-------------------------------------------------------------------------------------------
b2World * swPhysWorldGet(){
	return swWorld;
}

//-------------------------------------------------------------------------------------------
DllExport void swPhysWorldSetMeterOfPixelRatio(float ratio){
	swPhysUtilMeterOfPixelRatio(ratio);
}

//-------------------------------------------------------------------------------------------
DllExport void swPhysWorldCreate(swRect *AABB, swVec2 *gravity,bool doSleep){
	// Define the size of the world. Simulation will still work
	// if bodies reach the end of the world, but it will be slower.
	
	swRect rAABB;
	swPhysUtilConvertRect(AABB,&rAABB);
	

	b2AABB worldAABB;
	worldAABB.lowerBound.Set(rAABB.x, rAABB.y);
	worldAABB.upperBound.Set(rAABB.x+rAABB.w,rAABB.y+rAABB.h);

	phys_Gravity.x=gravity->x;
	phys_Gravity.y=gravity->y;

	// Construct a world object, which will hold and simulate the rigid bodies.
	swWorld=new b2World(worldAABB, phys_Gravity, doSleep);

	swPhysRendererInit();
	swPhysBodyInit();
	swPhysJointInit();
	swPhysContactInit();
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysWorldSetGravity(swVec2 *gravity){

	phys_Gravity.x=gravity->x;
	phys_Gravity.y=gravity->y;

	swWorld->SetGravity(phys_Gravity);
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysWorldDestroy(){
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysWorldUpdate(){
	float32 timeStep = 1.0f / 60.0f;
	int32 iterations = 10;	
	swWorld->Step(timeStep, iterations);

	swPhysBodyUpdate();
	swPhysContactUpdate();
}



