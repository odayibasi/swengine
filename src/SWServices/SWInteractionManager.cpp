#include "SWServicesIn.h"

typedef struct{
	int	  id;
	void *obj;
	void(*intrFunc)(void *,swKeyboardState *,swMouseState *);
	bool *bEnabled;
}IntrObj;

int intrList=-1;
int intrObjCounter=0;



//-------------------------------------------------------------------------------------------
DllExport void  swInteractionManagerInit(){
	intrList=swLinkedListCreate();
}


//-------------------------------------------------------------------------------------------
DllExport void  swInteractionManagerDeInit(){
	IntrObj *obj=(IntrObj*)swLinkedListGetFirst(intrList);
	while(obj!=NULL){
		free(obj);
		obj=(IntrObj*)swLinkedListGetNext(intrList);
	}
	swLinkedListDestroy(intrList);
}


//-------------------------------------------------------------------------------------------
DllExport int swInteractionManagerAdd(void(*intrFunc)(void*,swKeyboardState *,swMouseState *), void *obj,bool *bEnabled){
	IntrObj *intrObj=(IntrObj*)malloc(sizeof(IntrObj));
	intrObj->id=intrObjCounter++;
	intrObj->bEnabled=bEnabled;
	intrObj->intrFunc=intrFunc;
	intrObj->obj=obj;
	swLinkedListAdd(intrList,intrObj);
	return intrObj->id;
}

//-------------------------------------------------------------------------------------------
IntrObj* swInteractionManagerGet(int id){
	IntrObj *obj=(IntrObj*)swLinkedListGetFirst(intrList);
	while(obj!=NULL){
		if(obj->id==id)
			return obj;
		obj=(IntrObj*)swLinkedListGetNext(intrList);
	}
	return NULL;
}


//-------------------------------------------------------------------------------------------
bool swIntrIsEnabled(IntrObj *obj){
	if(obj->bEnabled!=NULL && (*obj->bEnabled)==false)
		return false;
	return true;
}


//-------------------------------------------------------------------------------------------
DllExport void  swInteractionManagerExecute(swKeyboardState *keybState,swMouseState *mousState){
	void(*intrFunc)(void *,swKeyboardState *,swMouseState *);
	IntrObj *obj=(IntrObj*)swLinkedListGetFirst(intrList);
	while(obj!=NULL){
		if(swIntrIsEnabled(obj)){
			intrFunc=obj->intrFunc;
			(*intrFunc)(obj->obj,keybState,mousState);
		}
		obj=(IntrObj*)swLinkedListGetNext(intrList);
	}
}

//-------------------------------------------------------------------------------------------
DllExport void  swInteractionManagerDel(int id){
	IntrObj *obj=swInteractionManagerGet(id);
	if(obj!=NULL){
		swLinkedListDel(intrList,obj);	
	}
}


