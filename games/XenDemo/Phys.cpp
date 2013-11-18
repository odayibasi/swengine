#include "../../include/SWEngine.h"
#include "Contacts.h"



//-------------------------------------------------------------------------------------------
void physInit(){

	//Physics
	swRect  aabb={0,0,1000000,100000};
	swVec2  grav={0,-2.0f};
	bool    sleep=true;

	//World
	swPhysWorldSetMeterOfPixelRatio(100);
	swPhysWorldCreate(&aabb,&grav,sleep);;
	//Configure Phys Renderer
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_SHAPE,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_JOINTS,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_CORESHAPES,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_AABBs,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_OBBs,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_CENTEROFMASSES,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_PAIRS,true);
	//swPhysRendererSetEnabled(SW_PHYS_RENDERED_STATISTICS,true);

	swPhysContactSetListener(xenContactListener);
}



