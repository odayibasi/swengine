#include "SWServicesIn.h"


int mousBLList=-1;
boolean prevMousPressed=false;


//-------------------------------------------------------------------------------------------
DllExport void  swMousBehaviourInit(){
	mousBLList=swLinkedListCreate();
}


//-------------------------------------------------------------------------------------------
DllExport void  swMousBehaviourDeInit(){
	swLinkedListDestroy(mousBLList);
}


//-------------------------------------------------------------------------------------------
DllExport void  swMousBehaviourAdd(swMousBehaviourListener *listener){
	swLinkedListAdd(mousBLList,listener);
}


//-------------------------------------------------------------------------------------------
DllExport void  swMousBehaviourDel(swMousBehaviourListener *listener){
	swLinkedListDel(mousBLList,listener);
}


//-------------------------------------------------------------------------------------------
void  swMousBehaviourFirePressed(swMouseState *mState){
void(*pressedFunc)(float,float);
	
	swMousBehaviourListener *obj=(swMousBehaviourListener*)swLinkedListGetFirst(mousBLList);
	while(obj!=NULL){
		if(obj->pressed!=NULL){
			pressedFunc=obj->pressed;
			(*pressedFunc)(mState->x,mState->y);
		}
		obj=(swMousBehaviourListener*)swLinkedListGetNext(mousBLList);
	}
}

//-------------------------------------------------------------------------------------------
void  swMousBehaviourFireReleased(swMouseState *mState){
void(*releasedFunc)(float,float);

	swMousBehaviourListener *obj=(swMousBehaviourListener*)swLinkedListGetFirst(mousBLList);
	while(obj!=NULL){
		if(obj->released!=NULL){
			releasedFunc=obj->released;
			(*releasedFunc)(mState->x,mState->y);
		}
		obj=(swMousBehaviourListener*)swLinkedListGetNext(mousBLList);
	}
}


//-------------------------------------------------------------------------------------------
void  swMousBehaviourFireMoving(swMouseState *mState){
void(*movingFunc)(float,float);

	swMousBehaviourListener *obj=(swMousBehaviourListener*)swLinkedListGetFirst(mousBLList);
	while(obj!=NULL){
		if(obj->moving!=NULL){
			movingFunc=obj->moving;
			(*movingFunc)(mState->x,mState->y);
		}
		obj=(swMousBehaviourListener*)swLinkedListGetNext(mousBLList);
	}
}


//-------------------------------------------------------------------------------------------
void  swMousBehaviourFireDragging(swMouseState *mState){
void(*draggingFunc)(float,float);

	swMousBehaviourListener *obj=(swMousBehaviourListener*)swLinkedListGetFirst(mousBLList);
	while(obj!=NULL){
		if(obj->dragging!=NULL){
			draggingFunc=obj->dragging;
			(*draggingFunc)(mState->x,mState->y);
		}
		obj=(swMousBehaviourListener*)swLinkedListGetNext(mousBLList);
	}
}


//-------------------------------------------------------------------------------------------
DllExport void  swMousBehaviourExecute(swMouseState *mousState){
	if(mousState->btnLEFT && !prevMousPressed){
		swMousBehaviourFirePressed(mousState);
	}
	
	else if(!mousState->btnLEFT && prevMousPressed){
		swMousBehaviourFireReleased(mousState);
	}

	else if(mousState->btnLEFT && prevMousPressed){
		swMousBehaviourFireDragging(mousState);
	}

	else if(!mousState->btnLEFT && !prevMousPressed){
		swMousBehaviourFireMoving(mousState);
	}

	prevMousPressed=mousState->btnLEFT;

}