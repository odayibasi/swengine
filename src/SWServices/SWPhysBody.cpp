#include "SWServicesIn.h"



int swBodyList=-1;
int bodyCounter=0;
b2World *bodyWorld;


extern BodyBuffer  bodyBuffer;

//-------------------------------------------------------------------------------------------
void  swPhysBodyInit(){
	swBodyList=swLinkedListCreate();
	swPhysBodyDefReset();
}

//-------------------------------------------------------------------------------------------
void  swPhysBodyDeInit(){
	swLinkedListDestroy(swBodyList);
}


//-------------------------------------------------------------------------------------------
void  swPhysBodyUpdate(){
	PhysBody *b=(PhysBody *)swLinkedListGetFirst(swBodyList);
	while(b!=NULL){
		if(b->xListener!=NULL)
			(*b->xListener)=swPhysUtilReConvert(b->body->GetPosition().x);

		if(b->yListener!=NULL)
			(*b->yListener)=swPhysUtilReConvert(b->body->GetPosition().y);

		if(b->angleListener!=NULL)
			(*b->angleListener)=swMathRadianToDegree(b->body->GetAngle());


		if(b->cxListener!=NULL)
			(*b->cxListener)=swPhysUtilReConvert(b->body->GetWorldCenter().x);

		if(b->cyListener!=NULL)
			(*b->cyListener)=swPhysUtilReConvert(b->body->GetWorldCenter().y);


		b=(PhysBody *)swLinkedListGetNext(swBodyList);
	}
}


//-------------------------------------------------------------------------------------------
PhysBody* swPhysBodyGet(int id){
	PhysBody *body=(PhysBody*)swLinkedListGetFirst(swBodyList);
	while(body!=NULL){
		if(body->id==id){
			return body;
		}
		body=(PhysBody*)swLinkedListGetNext(swBodyList);	
	}
	return NULL;
}




//-------------------------------------------------------------------------------------------
void swPhysBodyCreateRectShape(b2Body *body){
	swRect *rP=&bodyBuffer.shapeRect;
	b2Vec2 pCenter;
	float b2X=rP->x;
	float b2Y=rP->y;
	float b2W=rP->w;
	float b2H=rP->h;
	float b2Degree=swMathDegreeToRadian(0.0f);
	pCenter.Set(b2X+b2W/2,b2Y+b2H/2);

	b2PolygonDef pDef;
	pDef.SetAsBox(b2W/2,b2H/2,pCenter,b2Degree);
	pDef.density=bodyBuffer.density;
	pDef.restitution=bodyBuffer.restitution;
	pDef.friction=bodyBuffer.friction;
	
	pDef.filter.categoryBits=bodyBuffer.filterCategoryBits;
	pDef.filter.maskBits=bodyBuffer.filterMaskBits;
	pDef.filter.groupIndex=bodyBuffer.filterGroupIndex;

	body->CreateShape(&pDef);
}


//-------------------------------------------------------------------------------------------
void swPhysBodyCreateCircleShape(b2Body *body){

	swRect *rC=&bodyBuffer.shapeRect;
	float b2CX=rC->x;
	float b2CY=rC->y;
	float b2CR=rC->w;


	b2CircleDef cDef;
	cDef.localPosition.Set(b2CX,b2CY);
	cDef.radius=b2CR;
	cDef.density=bodyBuffer.density;
	cDef.restitution=bodyBuffer.restitution;
	cDef.friction=bodyBuffer.friction;
	body->CreateShape(&cDef);
}

//-------------------------------------------------------------------------------------------
DllExport int swPhysBodyCreate(){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=(PhysBody*)malloc(sizeof(PhysBody));
	swLinkedListAdd(swBodyList,physBody);
	
	physBody->xListener=bodyBuffer.xListener;
	physBody->yListener=bodyBuffer.yListener;
	physBody->angleListener=bodyBuffer.rListener;
	physBody->cxListener=bodyBuffer.cxListener;
	physBody->cyListener=bodyBuffer.cyListener;

	b2BodyDef def;
	def.angle=bodyBuffer.angle;
	def.position.x=bodyBuffer.pos.x;
	def.position.y=bodyBuffer.pos.y;
	def.linearDamping=bodyBuffer.linearDamping;
	def.massData.center.SetZero();
	def.fixedRotation=bodyBuffer.fixedRotation;
	def.isBullet=bodyBuffer.isBullet;
	def.userData=bodyBuffer.userData;
	physBody->body=world->CreateBody(&def);

	if(bodyBuffer.shapeType==BODY_SHAPE_RECT){
		swPhysBodyCreateRectShape(physBody->body);
	}else if(bodyBuffer.shapeType==BODY_SHAPE_CIRCLE){
		swPhysBodyCreateCircleShape(physBody->body);	
	}

	swPhysBodyDefReset();
	physBody->body->SetMassFromShapes();
	physBody->id=bodyCounter++;
	return physBody->id;
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyDestroy(int bodyID){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	world->DestroyBody(physBody->body);
	swLinkedListDel(swBodyList,physBody);
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyApplyForce(int bodyID, swVec2 force,swPoint pos){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	b2Vec2 v2Force,v2Pos;
	v2Force.Set(force.x,force.y);
	v2Pos.Set(swPhysUtilConvert(pos.x),swPhysUtilConvert(pos.y));
	physBody->body->ApplyForce(v2Force,v2Pos);
}



//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyApplyForce1(int bodyID, float fx, float fy,float x,float y){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	b2Vec2 v2Force,v2Pos;
	v2Force.Set(fx,fy);
	v2Pos.Set(swPhysUtilConvert(x),swPhysUtilConvert(y));
	physBody->body->ApplyForce(v2Force,v2Pos);
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodySetLinearVelocity(int bodyID, swVec2 vel){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	b2Vec2 v2Vel;
	v2Vel.Set(vel.x,vel.y);
	physBody->body->SetLinearVelocity(v2Vel);
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodySetLinearVelocity1(int bodyID, float x, float y){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	b2Vec2 v2Vel;
	v2Vel.Set(x,y);
	physBody->body->SetLinearVelocity(v2Vel);
}

//-------------------------------------------------------------------------------------------
DllExport void swPhysBodySetLinearVelocityX(int bodyID, float x){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	b2Vec2 v2Vel;
	v2Vel.Set(x,physBody->body->GetLinearVelocity().y);
	physBody->body->SetLinearVelocity(v2Vel);
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodySetLinearVelocityY(int bodyID, float y){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	b2Vec2 v2Vel;
	v2Vel.Set(physBody->body->GetLinearVelocity().x,y);
	physBody->body->SetLinearVelocity(v2Vel);
}



//-------------------------------------------------------------------------------------------
DllExport void swPhysBodySetXForm(int bodyID, swVec2 pos,float rot){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	b2Vec2 v2Pos;
	v2Pos.Set(swPhysUtilConvert(pos.x),swPhysUtilConvert(pos.y));
	rot=swMathDegreeToRadian(rot);
	physBody->body->SetXForm(v2Pos,rot);
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodySetUserData(int bodyID, void *userData){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	physBody->body->SetUserData(userData);

}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodySetXForm1(int bodyID, float x, float y,float rot){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	b2Vec2 v2Pos;
	v2Pos.Set(swPhysUtilConvert(x),swPhysUtilConvert(y));
	rot=swMathDegreeToRadian(rot);
	physBody->body->SetXForm(v2Pos,rot);
}

//-------------------------------------------------------------------------------------------
DllExport void swPhysBodySetBullet(int bodyID,bool isBullet){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	physBody->body->SetBullet(isBullet);

}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyWakeUp(int bodyID){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	physBody->body->WakeUp();
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysBodyPutToSleep(int bodyID){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	physBody->body->PutToSleep();
}



//-------------------------------------------------------------------------------------------
DllExport float swPhysBodyGetMass(int bodyID){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	return physBody->body->GetMass();
}

//-------------------------------------------------------------------------------------------
DllExport bool  swPhysBodyIsBullet(int bodyID){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	return physBody->body->IsBullet();
}


//-------------------------------------------------------------------------------------------
DllExport bool  swPhysBodyIsStatic(int bodyID){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	return physBody->body->IsStatic();
}


//-------------------------------------------------------------------------------------------
DllExport bool  swPhysBodyIsDynamic(int bodyID){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	return physBody->body->IsDynamic();
}

//-------------------------------------------------------------------------------------------
DllExport bool  swPhysBodyIsFrozen(int bodyID){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	return physBody->body->IsFrozen();
}

//-------------------------------------------------------------------------------------------
DllExport bool  swPhysBodyIsSleeping(int bodyID){
	b2World *world=swPhysWorldGet();
	PhysBody* physBody=swPhysBodyGet(bodyID);
	return physBody->body->IsSleeping();
}




