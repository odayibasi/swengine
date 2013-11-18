#include "SWServicesIn.h"


int swJointList=-1;
int jointCounter=0;

//-------------------------------------------------------------------------------------------
void swPhysJointInit(){
	swJointList=swLinkedListCreate();
}

//-------------------------------------------------------------------------------------------
void swPhysJointDeInit(){
	swLinkedListDestroy(swJointList);
}


//-------------------------------------------------------------------------------------------
PhysJoint* swPhysJointGet(int id){
	PhysJoint *joint=(PhysJoint*)swLinkedListGetFirst(swJointList);
	while(joint!=NULL){
		if(joint->id==id){
			return joint;
		}
		joint=(PhysJoint*)swLinkedListGetNext(swJointList);	
	}
	return NULL;
}


//-------------------------------------------------------------------------------------------
DllExport void swPhysJointDestroy(int jointID){
	b2World *world=swPhysWorldGet();
	PhysJoint* physJoint=swPhysJointGet(jointID);
	world->DestroyJoint(physJoint->joint);
	swLinkedListDel(swJointList,physJoint);
}



//-------------------------------------------------------------------------------------------
DllExport int swPhysDistJointCreate(int bodyID1,swPoint anchor1,float bodyID2,swPoint anchor2,bool collideConneted){
	b2DistanceJointDef b2JDef;
	b2Vec2 pos1,pos2;
	pos1.Set(swPhysUtilConvert(anchor1.x),swPhysUtilConvert(anchor1.y));
	pos2.Set(swPhysUtilConvert(anchor2.x),swPhysUtilConvert(anchor2.y));
	b2JDef.Initialize(swPhysBodyGet(bodyID1)->body,swPhysBodyGet(bodyID2)->body,pos1,pos2);
	b2JDef.collideConnected=collideConneted;


	PhysJoint* joint=(PhysJoint*)malloc(sizeof(PhysJoint));
	swLinkedListAdd(swJointList,joint);
	joint->joint=swPhysWorldGet()->CreateJoint(&b2JDef);
	joint->id=jointCounter++;
	return joint->id;
}



//-------------------------------------------------------------------------------------------
DllExport int swPhysRevoJointCreate(int bodyID1,float bodyID2,swPoint anchor,float lowerAngle, float upperAngle, bool enableLimit, float maxMotorTorque, float motorSpeed, bool enableMotor){
	b2RevoluteJointDef b2JDef;
	b2Vec2 pos;
	pos.Set(swPhysUtilConvert(anchor.x),swPhysUtilConvert(anchor.y));
	b2JDef.Initialize(swPhysBodyGet(bodyID1)->body,swPhysBodyGet(bodyID2)->body,pos);
	b2JDef.lowerAngle=swMathDegreeToRadian(lowerAngle);
	b2JDef.upperAngle=swMathDegreeToRadian(upperAngle);
	b2JDef.enableLimit=enableLimit;
	b2JDef.maxMotorTorque=maxMotorTorque;
	b2JDef.motorSpeed=motorSpeed;
	b2JDef.enableMotor=enableMotor;


	PhysJoint* joint=(PhysJoint*)malloc(sizeof(PhysJoint));
	swLinkedListAdd(swJointList,joint);
	joint->joint=swPhysWorldGet()->CreateJoint(&b2JDef);
	joint->id=jointCounter++;
	return joint->id;

}


//-------------------------------------------------------------------------------------------
DllExport int swPhysPrisJointCreate(int bodyID1,float bodyID2,swPoint anchor,swPoint axis,float lowerTrans, float upperTrans, bool enableLimit, float maxMotorForce, float motorSpeed, bool enableMotor){
	b2PrismaticJointDef b2JDef;
	b2Vec2 pos,ax;

	pos.Set(swPhysUtilConvert(anchor.x),swPhysUtilConvert(anchor.y));
	ax.Set(axis.x,axis.y);

	b2JDef.Initialize(swPhysBodyGet(bodyID1)->body,swPhysBodyGet(bodyID2)->body,pos,ax);
	b2JDef.lowerTranslation=swPhysUtilConvert(lowerTrans);
	b2JDef.upperTranslation=swPhysUtilConvert(upperTrans);
	b2JDef.enableLimit=enableLimit;
	b2JDef.maxMotorForce=maxMotorForce;
	b2JDef.motorSpeed=motorSpeed;
	b2JDef.enableMotor=enableMotor;

	PhysJoint* joint=(PhysJoint*)malloc(sizeof(PhysJoint));
	swLinkedListAdd(swJointList,joint);
	joint->joint=swPhysWorldGet()->CreateJoint(&b2JDef);
	joint->id=jointCounter++;
	return joint->id;

}




//-------------------------------------------------------------------------------------------
DllExport int swPhysPullJointCreate(int bodyID1,float bodyID2,swPoint gAnchor1,swPoint gAnchor2,swPoint anchor1,swPoint anchor2, float ratio,float maxLength1, float maxLength2){
	b2PulleyJointDef b2JDef;
	b2Vec2 gP1,gP2,aP1,aP2;
	gP1.Set(swPhysUtilConvert(gAnchor1.x),swPhysUtilConvert(gAnchor1.y));
	gP2.Set(swPhysUtilConvert(gAnchor2.x),swPhysUtilConvert(gAnchor2.y));
	aP1.Set(swPhysUtilConvert(anchor1.x),swPhysUtilConvert(anchor1.y));
	aP2.Set(swPhysUtilConvert(anchor2.x),swPhysUtilConvert(anchor2.y));
	
	

	b2JDef.Initialize(swPhysBodyGet(bodyID1)->body,swPhysBodyGet(bodyID2)->body,gP1,gP2,aP1,aP2,ratio);
	b2JDef.maxLength1=swPhysUtilConvert(maxLength1);
	b2JDef.maxLength2=swPhysUtilConvert(maxLength2);

	PhysJoint* joint=(PhysJoint*)malloc(sizeof(PhysJoint));
	swLinkedListAdd(swJointList,joint);
	joint->joint=swPhysWorldGet()->CreateJoint(&b2JDef);
	joint->id=jointCounter++;
	return joint->id;

}



//-------------------------------------------------------------------------------------------
DllExport int swPhysGearJointCreate(int bodyID1,float bodyID2,int joint1,int joint2,float ratio){
	b2GearJointDef b2JDef;
	b2JDef.body1=swPhysBodyGet(bodyID1)->body;
	b2JDef.body2=swPhysBodyGet(bodyID2)->body;
	b2JDef.joint1=swPhysJointGet(joint1)->joint;
	b2JDef.joint2=swPhysJointGet(joint2)->joint;
	b2JDef.ratio=ratio;

	PhysJoint* joint=(PhysJoint*)malloc(sizeof(PhysJoint));
	swLinkedListAdd(swJointList,joint);
	joint->joint=swPhysWorldGet()->CreateJoint(&b2JDef);
	joint->id=jointCounter++;
	return joint->id;

}


