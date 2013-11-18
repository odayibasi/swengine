#include "SWServicesIn.h"


class swContactListener : public b2ContactListener
{
public:
	void Add(const b2ContactPoint* point);
	void Persist(const b2ContactPoint* point);
	void Remove(const b2ContactPoint* point);
};


const int32 k_maxContactPoints = 2048;
swContactPoint m_points[k_maxContactPoints];
int32 m_pointCount=0;
swContactListener m_contactListener;
void(*contactCallBack)(swContactPoint*)=NULL;


//-------------------------------------------------------------------------------------------
void swPhysContactInit(){
	swPhysWorldGet()->SetContactListener(&m_contactListener);
}


//-------------------------------------------------------------------------------------------
void swPhysContactDeInit(){
	swPhysWorldGet()->SetContactListener(NULL);
}

//-------------------------------------------------------------------------------------------
void swContactListener::Add(const b2ContactPoint* point){
	if (m_pointCount == k_maxContactPoints)
		return;

	swContactPoint* cp = &m_points[m_pointCount];
	cp->userData1 = point->shape1->GetBody()->GetUserData();
	cp->userData2 = point->shape2->GetBody()->GetUserData();
	cp->state = SW_CONTACT_ADDED;
	++m_pointCount;
}

//-------------------------------------------------------------------------------------------
void swContactListener::Persist(const b2ContactPoint* point){
	if (m_pointCount == k_maxContactPoints)
		return;

	swContactPoint* cp = &m_points[m_pointCount];
	cp->userData1 = point->shape1->GetBody()->GetUserData();
	cp->userData2 = point->shape2->GetBody()->GetUserData();
	cp->state = SW_CONTACT_PERSIST;
	++m_pointCount;
}

//-------------------------------------------------------------------------------------------
void swContactListener::Remove(const b2ContactPoint* point){
	if (m_pointCount == k_maxContactPoints)
		return;
	
	swContactPoint* cp = &m_points[m_pointCount];
	cp->userData1 = point->shape1->GetBody()->GetUserData();
	cp->userData2 = point->shape2->GetBody()->GetUserData();
	cp->state = SW_CONTACT_REMOVED;
	++m_pointCount;
}

//-------------------------------------------------------------------------------------------
void  swPhysContactUpdate(){
	if(contactCallBack==NULL)
			return;

	for(int32 i=0;i<m_pointCount;i++){
		(*contactCallBack)(&m_points[i]);
	}
	m_pointCount=0;
}

//-------------------------------------------------------------------------------------------
DllExport void  swPhysContactSetListener(void(*contactListen)(swContactPoint*)){
	contactCallBack=contactListen;
}
