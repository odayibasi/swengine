#include "ObjParticle.h"

typedef struct objParticle{
	bool   bLive;
	float  rot;
	float  posSpeed;
	float  scaleSpeed;
	float  rotSpeed;
	int    imgID;
	int    imgIndex;
	swRect target;
	swRect source;
	swVec2 direction;

};

#define MAX_OBJ_PARTICLE 1000
objParticle objParticleS[MAX_OBJ_PARTICLE];

int objParticleLayer=6;

//-------------------------------------------------------------------------------------------
objParticle* objParticleGet(){
	for(int i=0;i<MAX_OBJ_PARTICLE;i++){
		if(!objParticleS[i].bLive)
			return &objParticleS[i];
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------
void objParticleGenerate(swRect *target,int wSlice,int hSlice,int imgID,int index,float rot,float posSpeed,float scaleSpeed,float rotSpeed){

		for(int i=0;i<hSlice;i++){
			for(int j=0;j<wSlice;j++){
				objParticle *p=objParticleGet();
				if(p==NULL) 
					return;

				p->bLive=true;
				p->rot=rot;
				p->posSpeed=posSpeed;
				p->scaleSpeed=scaleSpeed;
				p->rotSpeed=rotSpeed;

				p->imgID=imgID;
				p->imgIndex=index;

				p->target.x=target->x+(target->w/wSlice*j);
				p->target.y=target->y+(target->h/hSlice*i);
				p->target.w=target->w/wSlice;
				p->target.h=target->h/hSlice;

				p->source.x=(1.0f/wSlice*j);
				p->source.y=(1.0f/hSlice*i);
				p->source.w=(1.0f/wSlice);
				p->source.h=(1.0f/hSlice);
				float sx=j-(wSlice/2);
				float sy=i-(hSlice/2);
				if(sx==0) sx=0.9;
				if(sy==0) sy=0.9;
				p->direction.x=1.0f/sx;
				p->direction.y=1.0f/sy;

			}//end of for
		}//end of for
}


//-------------------------------------------------------------------------------------------
void objParticleExecute(objParticle *p){

	p->target.x+=(p->direction.x)*p->posSpeed;
	p->target.y+=(p->direction.y)*p->posSpeed;
	p->target.w-=p->scaleSpeed;
	p->target.h-=p->scaleSpeed;
	if(p->target.w<0 || p->target.h<0){
		p->bLive=false;
	}
	p->rot+=p->rotSpeed;
}



//-------------------------------------------------------------------------------------------
void objParticleExecuteManager(void *obj){
	for(int i=0;i<MAX_OBJ_PARTICLE;i++){
		if(objParticleS[i].bLive)
			objParticleExecute(&objParticleS[i]);
	}
}





//-------------------------------------------------------------------------------------------
void objParticleDisplay(objParticle *p){
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);
	if(p->imgIndex==-1){
		swGraphicsRenderImg3(p->imgID,&p->target,&p->source,p->rot);
	}else{
		swGraphicsRenderSprite3(p->imgID,p->imgIndex,&p->target,&p->source,p->rot);
	}
}


//-------------------------------------------------------------------------------------------
void objParticleDisplayManager(void *obj){
	for(int i=0;i<MAX_OBJ_PARTICLE;i++){
		if(objParticleS[i].bLive)
			objParticleDisplay(&objParticleS[i]);
	}
}





//-------------------------------------------------------------------------------------------
void objParticleInit(){
	
	swDispManagerAdd(objParticleDisplayManager,NULL,NULL,NULL,&objParticleLayer);
	swExecManagerAdd(objParticleExecuteManager,NULL,NULL);	

	for(int i=0;i<MAX_OBJ_PARTICLE;i++){
		objParticleS[i].bLive=false;
	}
}





