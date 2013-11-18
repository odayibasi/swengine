#include "SWGameIn.h"

typedef struct{
	int   id;
	bool isFinished;
	bool bigger;
	float   initVal;
	float   endVal;
	float   speed;
	float   startTime;
}Interpolater;


int interpolaterList;
int interpolaterCounter=0;



//-------------------------------------------------------------
DllExport void  swInterpolaterInit(){
	interpolaterList=swLinkedListCreate();
}


//-------------------------------------------------------------
DllExport void  swInterpolaterDeInit(){
	Interpolater *interp=(Interpolater*)swLinkedListGetFirst(interpolaterList);
	while(interp!=NULL){
		free(interp);
		interp=(Interpolater*)swLinkedListGetNext(interpolaterList);
	}
	swLinkedListDestroy(interpolaterList);
}


//-------------------------------------------------------------
DllExport int swInterpolaterCreate(float initVal,float endVal,float totalTime){
	Interpolater *interp=(Interpolater *)malloc(sizeof(Interpolater));
	interp->id=interpolaterCounter++;
	interp->initVal=initVal;
	interp->endVal=endVal;
	interp->bigger=swMathSign(endVal-initVal)==1?true:false;
	interp->speed=(endVal-initVal)/totalTime;
	swLinkedListAdd(interpolaterList,interp);
	return interp->id;
}


//-------------------------------------------------------------
Interpolater* swInterpolaterGet(int id){
	Interpolater *interp=(Interpolater*)swLinkedListGetFirst(interpolaterList);
	while(interp!=NULL){
		if(interp->id==id)
			return interp;
		interp=(Interpolater*)swLinkedListGetNext(interpolaterList);
	}
	return NULL;
}


//-------------------------------------------------------------
DllExport void  swInterpolaterDestroy(int interpolaterID){
	Interpolater *interp=swInterpolaterGet(interpolaterID);
	swLinkedListDel(interpolaterList,interp);
	free(interp);
}


//-------------------------------------------------------------
DllExport float swInterpolaterGetValue(int interpolaterID){
	Interpolater *interp=swInterpolaterGet(interpolaterID);
	float currentTime=swSystemGetElapsedSeconds();
	float dTime=currentTime-interp->startTime;
	float value=interp->initVal+dTime*interp->speed;
	if(interp->bigger && value>=interp->endVal){
		interp->isFinished=true;
		return interp->endVal;
	}

	if(!interp->bigger && value<=interp->endVal){
		interp->isFinished=true;
		return interp->endVal;
	}

	return value;
}


//-------------------------------------------------------------
DllExport void swInterpolaterStart(int interpolaterID){
	Interpolater *interp=swInterpolaterGet(interpolaterID);
	interp->startTime=swSystemGetElapsedSeconds();
	interp->isFinished=false;
}


//-------------------------------------------------------------
DllExport bool swInterpolaterIsFinished(int interpolaterID){
	Interpolater *interp=swInterpolaterGet(interpolaterID);
	return interp->isFinished;
}
