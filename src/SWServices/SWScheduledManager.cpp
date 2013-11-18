#include "SWServicesIn.h"


typedef struct{
	void  *obj;
	float triggerTime;
	void (*scheduledFunc)(void*);
}ScheduledObj;

#define SCHEDULED_DELETION_MAX 100
void  swScheduledManagerExecute(void *obj);;

int scheduledList=-1;
int scheduledTimerID=-1;



//-------------------------------------------------------------------------------------------
DllExport void  swScheduledManagerInit(){
	scheduledList=swLinkedListCreate();
	scheduledTimerID=swTimerCreate(0.2f,NULL,swScheduledManagerExecute);
	swTimerStart(scheduledTimerID);
}


//-------------------------------------------------------------------------------------------
DllExport void  swScheduledManagerDeInit(){
	ScheduledObj *obj=(ScheduledObj*)swLinkedListGetFirst(scheduledList);
	while(obj!=NULL){
		free(obj);
		obj=(ScheduledObj*)swLinkedListGetNext(scheduledList);
	}
	swTimerStop(scheduledTimerID);
	swTimerDestroy(scheduledTimerID);
	swLinkedListDestroy(scheduledList);
}


//-------------------------------------------------------------------------------------------
DllExport void swScheduledManagerAdd0(void(*scheduledFunc)(void*), void *obj,float triggerTime){
	ScheduledObj *scheduledObj=(ScheduledObj*)malloc(sizeof(ScheduledObj));
	scheduledObj->obj=obj;
	scheduledObj->scheduledFunc=scheduledFunc;
	scheduledObj->triggerTime=triggerTime;
	swLinkedListAdd(scheduledList,scheduledObj);
}


//-------------------------------------------------------------------------------------------
DllExport void swScheduledManagerAdd1(void(*scheduledFunc)(void*), void *obj,float waitingTime){
	float elapsedSeconds=swSystemGetElapsedSeconds();
	swScheduledManagerAdd0(scheduledFunc,obj,elapsedSeconds+waitingTime);
}


//-------------------------------------------------------------------------------------------
void  swScheduledManagerExecute(void *objNothing){
	int countDel=0;
	void *delArray[SCHEDULED_DELETION_MAX];

	void(*scheduledFunc)(void *);
	float elapsedSeconds=swSystemGetElapsedSeconds();

	ScheduledObj *obj=(ScheduledObj*)swLinkedListGetFirst(scheduledList);
	while(obj!=NULL){
		if(obj->triggerTime<=elapsedSeconds){
			scheduledFunc=obj->scheduledFunc;
			(*scheduledFunc)(obj->obj);
			delArray[countDel]=obj;
			countDel++;
			if(countDel>SCHEDULED_DELETION_MAX)
				assert(FALSE);
		}
		obj=(ScheduledObj*)swLinkedListGetNext(scheduledList);
	}

	for(int i=0;i<countDel;i++){
		swLinkedListDel(scheduledList,delArray[i]);
	}
}

