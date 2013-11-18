#include "XenDemoApp.h"
#include "Sound.h"




//-------------------------------------------------------------------------------------------
void xenProcessClawWeaponAndBarrelCollision(xenUserData *barrelData,xenUserData *clawWeaponData){
	xenBarrel *barrel=(xenBarrel *)barrelData->obj;
	barrel->hitCount++;
	soundPlay(SOUND_OF_CLAW_WEAPON_BULLET_COLLIDE);
}

//-------------------------------------------------------------------------------------------
void xenProcessClawWeaponAndDefenderCollision(xenUserData *defenderData, xenUserData *clawWeaponData){
	xenDefender *defender=(xenDefender *)defenderData->obj;
	defender->hitCount++;
	clawWeapon *wpn=(clawWeapon *)clawWeaponData->obj;
	wpn->bDieOperation=true;
}

//-------------------------------------------------------------------------------------------
void xenProcessClawWeaponAndTurretCollision(xenUserData *turretData, xenUserData *clawWeaponData){
	xenTurret *turret=(xenTurret *)turretData->obj;
	turret->hitCount++;
	clawWeapon *wpn=(clawWeapon *)clawWeaponData->obj;
	wpn->bDieOperation=true;
}



//-------------------------------------------------------------------------------------------
void xenProcessEnemyWeaponAndClawCollision(xenUserData *clawDataX,xenUserData *enemyWeaponData){
	enemyWeapon *wpn=(enemyWeapon *)enemyWeaponData->obj;
	wpn->bDieOperation=true;

	clawData *claw=(clawData *)clawDataX->obj;
	if(claw->shield>0){
		claw->shield--;
	}else if(claw->health>0){
		claw->health--;
	}
}

//-------------------------------------------------------------------------------------------
void xenCheckBulletAndBarrelIsCollide(xenUserData *userData1, xenUserData *userData2){
	
	//WPN_BARREL
	bool isCollide=false;
	isCollide=userData1->type==XEN_BARREL && userData2->type==XEN_CLAW_WPN_BULLET;
	if(isCollide) 
		xenProcessClawWeaponAndBarrelCollision(userData1,userData2);
	
	isCollide=userData1->type==XEN_CLAW_WPN_BULLET && userData2->type==XEN_BARREL;
	if(isCollide) 
		xenProcessClawWeaponAndBarrelCollision(userData2,userData1);

}



//-------------------------------------------------------------------------------------------
void xenCheckBulletAndDefenderIsCollide(xenUserData *userData1, xenUserData *userData2){

	//WPN_BARREL
	bool isCollide=false;
	isCollide=userData1->type==XEN_DEFENDER && userData2->type==XEN_CLAW_WPN_BULLET;
	if(isCollide)
		xenProcessClawWeaponAndDefenderCollision(userData1,userData2);
	

	isCollide=userData1->type==XEN_CLAW_WPN_BULLET && userData2->type==XEN_DEFENDER;
	if(isCollide)
		xenProcessClawWeaponAndDefenderCollision(userData2,userData1);
	
}


//-------------------------------------------------------------------------------------------
void xenCheckBulletAndTurretIsCollide(xenUserData *userData1, xenUserData *userData2){

	//WPN_BARREL
	bool isCollide=false;
	isCollide=userData1->type==XEN_TURRET && userData2->type==XEN_CLAW_WPN_BULLET;
	if(isCollide)
		xenProcessClawWeaponAndTurretCollision(userData1,userData2);


	isCollide=userData1->type==XEN_CLAW_WPN_BULLET && userData2->type==XEN_TURRET;
	if(isCollide)
		xenProcessClawWeaponAndTurretCollision(userData2,userData1);

}


//-------------------------------------------------------------------------------------------
void xenCheckClawAndEnemyBulletIsCollide(xenUserData *userData1, xenUserData *userData2){

	//WPN_BARREL
	bool isCollide=false;
	isCollide=userData1->type==XEN_ENEMY_WPN_BULLET && userData2->type==XEN_CLAW;
	if(isCollide)
		xenProcessEnemyWeaponAndClawCollision(userData2,userData1);
	

	isCollide=userData1->type==XEN_CLAW && userData2->type==XEN_ENEMY_WPN_BULLET;
	if(isCollide)
		xenProcessEnemyWeaponAndClawCollision(userData1,userData2);
	
}






//-------------------------------------------------------------------------------------------
void xenContactListener(swContactPoint *cp){
	
	//Barrel 
	if(cp->userData1!=NULL && cp->userData2!=NULL){
		xenUserData *userData1=(xenUserData *)cp->userData1;
		xenUserData *userData2=(xenUserData *)cp->userData2;
		
		if(cp->state==SW_CONTACT_ADDED){
			xenCheckBulletAndBarrelIsCollide(userData1,userData2);
			xenCheckBulletAndDefenderIsCollide(userData1,userData2);
			xenCheckClawAndEnemyBulletIsCollide(userData1,userData2);
			xenCheckBulletAndTurretIsCollide(userData1,userData2);
		}
	}

		

}




