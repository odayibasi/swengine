#include "SWServicesIn.h"


//-------------------------------------------------------------------------------------------
DllExport void swPhysModelExplosion(swVec2 position, float Radious, float force,void(*explosionListen)(swExplosionEffect*)){


	//Conversion
	b2Vec2 pos;
	pos.Set(swPhysUtilConvert(position.x), swPhysUtilConvert(position.y));
	float radious=swPhysUtilConvert(Radious);

	b2AABB Sector;
	Sector.lowerBound.Set(pos.x-radious, pos.y-radious);
	Sector.upperBound.Set(pos.x+radious, pos.y+radious);
	const int32 k_bufferSize = 512;
	b2Shape *buffer[k_bufferSize];
	int32 count = swPhysWorldGet()->Query(Sector, buffer, k_bufferSize);
	b2Body* Body;
	b2Vec2 HitVector;
	b2Vec2 BodyPos;
	float HitForce;
	float Distance;
	for (int32 i = 0; i < count; ++i)
	{
		Body = buffer[i]->GetBody();
		BodyPos = Body->GetWorldCenter();
		HitVector = (BodyPos-pos);
		Distance = HitVector.Normalize(); //Makes a 1 unit length vector from HitVector, while getting the length.
		if ((Body->IsDynamic()) & (Distance<=radious))
		{
			HitForce=(radious-Distance)*force; //TODO: This is linear, but that's not realistic.
			Body->ApplyImpulse(HitForce * HitVector, Body->GetWorldCenter());
			if(explosionListen!=NULL){
				    swExplosionEffect eff;
					eff.userData=Body->GetUserData();
					eff.dist=swPhysUtilReConvert(Distance);
					(*explosionListen)(&eff);
			}
		};
	}

};