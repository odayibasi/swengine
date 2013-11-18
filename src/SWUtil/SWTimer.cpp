#include "SWUtilIn.h"


typedef struct _Timer{
	int   id;
	void  *obj;
	float  delaySeconds;
	float  lastSeconds;
	void  (*callBack)(void *);
	bool  status;  //0 Pause  1/Run;
}Timer;



int   swTimer_ListID=-1;
float swTimer_Tick=0;
int   swTimer_IdCounter=0;


//--------------------------------------------------------------------------------
DllExport void swTimerInit(){
	swTimer_ListID=swLinkedListCreate();
}

//--------------------------------------------------------------------------------
DllExport void swTimerDeInit(){
	swLinkedListDestroy(swTimer_ListID);
}

//--------------------------------------------------------------------------------
Timer *swTimerGet(int id){
Timer *timer=(Timer*)swLinkedListGetFirst(swTimer_ListID);
	while(timer!=NULL){
		if(timer->id==id)
			return timer;
		timer=(Timer*)swLinkedListGetNext(swTimer_ListID);
	}
	assert(FALSE);
	return NULL;
}


//--------------------------------------------------------------------------------
void swTimerExecutes(void *obj){
void(*callBack)(void *);
Timer *timer=(Timer*)obj;
	if(timer->status){
		if(swTimer_Tick-timer->lastSeconds>=timer->delaySeconds){
			timer->lastSeconds=swTimer_Tick;
			callBack=timer->callBack;
			(*callBack)(timer->obj);
		}
	}
}

//--------------------------------------------------------------------------------
DllExport void swTimerTick(float seconds){
	swTimer_Tick=seconds;
	swLinkedListIterate(swTimer_ListID,swTimerExecutes);
}


//--------------------------------------------------------------------------------
DllExport int swTimerCreate(float delaySeconds,void *obj,void(*callBack)(void*)){
	Timer *timer=(Timer*)malloc(sizeof(Timer));
	timer->id=swTimer_IdCounter++;
	timer->obj=obj;
	timer->status=true;
	timer->callBack=callBack;
	timer->lastSeconds=0;
	timer->delaySeconds=delaySeconds;
	swLinkedListAdd(swTimer_ListID,timer);
	return timer->id;
}

//--------------------------------------------------------------------------------
DllExport void swTimerDestroy(int timerID){
Timer *timer=swTimerGet(timerID);	
	swLinkedListDel(swTimer_ListID,timer);
	free(timer);
}

//--------------------------------------------------------------------------------
DllExport void swTimerStart(int timerID){
	swTimerGet(timerID)->status=true;
}

//--------------------------------------------------------------------------------
DllExport void swTimerStop(int timerID){
	swTimerGet(timerID)->status=false;
}


//--------------------------------------------------------------------------------
DllExport bool swTimerIsRunning(int timerID){
	return swTimerGet(timerID)->status;
}

//--------------------------------------------------------------------------------
DllExport void swTimerUpdateDelaySeconds(int timerID,float delaySeconds){
	swTimerGet(timerID)->delaySeconds=delaySeconds;
}
