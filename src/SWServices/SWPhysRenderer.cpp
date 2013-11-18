#include "SWServicesIn.h"

DebugDraw debugDraw;
uint32    flagsOfDebugDraw = 0;
bool   bStatisticsOfDebugDraw=false;
int32	  m_textLine=0;


bool bContactPointsOfDebugDraw=false;
bool bContactNormalsOfDebugDraw=false;
bool bContactForcesOfDebugDraw=false;
bool bContactFrictionOfDebugDraw=false;


//-------------------------------------------------------------------------------------------
void swPhysRendererInit(){
	swPhysWorldGet()->SetDebugDraw(&debugDraw);
}

//-------------------------------------------------------------------------------------------
DllExport void swPhysRendererSetEnabled(swPhysRenderedItemEnum type, bool bVisible){
	int val=0;
	switch(type){
		case SW_PHYS_RENDERED_SHAPE:
			val=b2DebugDraw::e_shapeBit;
			break;
		case SW_PHYS_RENDERED_JOINTS:
			val=b2DebugDraw::e_jointBit;
			break;
		case SW_PHYS_RENDERED_CORESHAPES:
			val=b2DebugDraw::e_coreShapeBit;
			break;
		case SW_PHYS_RENDERED_AABBs:
			val=b2DebugDraw::e_aabbBit;
			break;
		case SW_PHYS_RENDERED_OBBs:
			val=b2DebugDraw::e_obbBit;
			break;
		case SW_PHYS_RENDERED_PAIRS:
			val=b2DebugDraw::e_pairBit;
			break;
		case SW_PHYS_RENDERED_CENTEROFMASSES:
			val=b2DebugDraw::e_centerOfMassBit;
			break;
		case SW_PHYS_RENDERED_STATISTICS:
			bStatisticsOfDebugDraw=bVisible;
			break;
		default:
			break;
	}

	if(bVisible)
		flagsOfDebugDraw+=val;
	else
		flagsOfDebugDraw-=val;
		
	debugDraw.SetFlags(flagsOfDebugDraw);
}

//-------------------------------------------------------------------------------------------
void swPhysRendererDrawStatistics(){

	if (!bStatisticsOfDebugDraw) 
		return;

	b2World *m_world=swPhysWorldGet();
	DrawString(5, m_textLine, "proxies(max) = %d(%d), pairs(max) = %d(%d)",
		m_world->GetProxyCount(), b2_maxProxies,
		m_world->GetPairCount(), b2_maxPairs);
	m_textLine += 15;

	DrawString(5, m_textLine, "bodies/contacts/joints = %d/%d/%d",
		m_world->GetBodyCount(), m_world->GetContactCount(), m_world->GetJointCount());
	m_textLine += 15;

	DrawString(5, m_textLine, "heap bytes = %d", b2_byteCount);
	m_textLine += 15;
}


//-------------------------------------------------------------------------------------------
void swPhysRendererContacts(){
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysRendererExecute(){
	swPhysWorldGet()->DrawDebugData();	
	swPhysRendererDrawStatistics();


}
