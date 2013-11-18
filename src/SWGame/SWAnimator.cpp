#include "SWGameIn.h"

typedef struct{
	int   id;
	int   index;
	int   count;
	float delay;
	float lastTime;
	swAnimatorExecMode mode;
}Animator;


int animatorList;
int animatorCounter=0;


//-------------------------------------------------------------
DllExport void  swAnimatorInit(){
	animatorList=swLinkedListCreate();
}


//-------------------------------------------------------------
DllExport void  swAnimatorDeInit(){
	Animator *anim=(Animator*)swLinkedListGetFirst(animatorList);
	while(anim!=NULL){
		free(anim);
		anim=(Animator*)swLinkedListGetNext(animatorList);
	}
	swLinkedListDestroy(animatorList);
}


//-------------------------------------------------------------
DllExport int swAnimatorCreate(int count, float delay){
	Animator *anim=(Animator *)malloc(sizeof(Animator));
	anim->count=count;
	anim->index=0;
	anim->mode=SW_ANIMATOR_EXEC_STOP;
	anim->delay=delay;
	anim->lastTime=0;
	anim->id=animatorCounter++;
	swLinkedListAdd(animatorList,anim);
	return anim->id;
}


//-------------------------------------------------------------
Animator* swAnimatorGet(int id){
	Animator *anim=(Animator*)swLinkedListGetFirst(animatorList);
	while(anim!=NULL){
		if(anim->id==id)
			return anim;
		anim=(Animator*)swLinkedListGetNext(animatorList);
	}
	return NULL;
}


//-------------------------------------------------------------
DllExport void  swAnimatorDestroy(int animatorID){
	Animator *anim=swAnimatorGet(animatorID);
	swLinkedListDel(animatorList,anim);
	free(anim);
}


//-------------------------------------------------------------
DllExport void  swAnimatorSetIndex(int animatorID,int imgIndex){
	Animator *anim=swAnimatorGet(animatorID);
	anim->index=imgIndex;
}


//-------------------------------------------------------------
DllExport void  swAnimatorSetDelay(int animatorID,float delay){
	Animator *anim=swAnimatorGet(animatorID);
	anim->delay=delay;
}


//-------------------------------------------------------------
DllExport void swAnimatorSetExecutionMode(int animatorID, swAnimatorExecMode mode){
	Animator *anim=swAnimatorGet(animatorID);
	anim->mode=mode;
}


//-------------------------------------------------------------
DllExport int  swAnimatorGetIndex(int animatorID){
	Animator *anim=swAnimatorGet(animatorID);
	float currentTime=swSystemGetElapsedSeconds();

	if(currentTime-anim->lastTime<anim->delay){
		return anim->index;
	}
		
	switch(anim->mode){
		case SW_ANIMATOR_EXEC_STOP:
			break;

		case SW_ANIMATOR_EXEC_BACKWARD:
			--anim->index;
			if(anim->index<0)
				anim->index=0;
			break;

		case SW_ANIMATOR_EXEC_BACKWARD_LOOP:
			--anim->index;
			if(anim->index<0)
				anim->index=anim->count-1;
			break;

		case SW_ANIMATOR_EXEC_FORWARD:
			++anim->index;
			anim->index=swMathClampInt(anim->index,0,anim->count-1);
			break;

		case SW_ANIMATOR_EXEC_FORWARD_LOOP:
			++anim->index;
			anim->index=anim->index%(anim->count-1);			
			break; 

		default:
			break;
	}


	anim->lastTime=currentTime;
	return anim->index;
}

//-------------------------------------------------------------
DllExport bool swAnimatorIsLastFrameActive(int animatorID){
	Animator *anim=swAnimatorGet(animatorID);
	return anim->index==anim->count-1;
}

//-------------------------------------------------------------
DllExport bool swAnimatorIsFirstFrameActive(int animatorID){
	Animator *anim=swAnimatorGet(animatorID);
	return anim->index==0;
}

