#include "SWServicesIn.h"

typedef struct{
	int	  id;
	void *obj;
	void(*execFunc)(void *);
	bool *bEnabled;
}ExecObj;

int execList=-1;
int execObjCounter=0;



//-------------------------------------------------------------------------------------------
DllExport void  swExecManagerInit(){
	execList=swLinkedListCreate();
}


//-------------------------------------------------------------------------------------------
DllExport void  swExecManagerDeInit(){
	ExecObj *obj=(ExecObj*)swLinkedListGetFirst(execList);
	while(obj!=NULL){
		free(obj);
		obj=(ExecObj*)swLinkedListGetNext(execList);
	}
	swLinkedListDestroy(execList);
}


//-------------------------------------------------------------------------------------------
DllExport int swExecManagerAdd(void(*execFunc)(void*), void *obj,bool *bEnabled){
	ExecObj* execObj=(ExecObj*)malloc(sizeof(ExecObj));
	execObj->id=execObjCounter++;
	execObj->bEnabled=bEnabled;
	execObj->execFunc=execFunc;
	execObj->obj=obj;
	swLinkedListAdd(execList,execObj);
	return execObj->id;
}

//-------------------------------------------------------------------------------------------
ExecObj* swExecManagerGet(int id){
	ExecObj *obj=(ExecObj*)swLinkedListGetFirst(execList);
	while(obj!=NULL){
		if(obj->id==id)
			return obj;
		obj=(ExecObj*)swLinkedListGetNext(execList);
	}
	return NULL;
}


//-------------------------------------------------------------------------------------------
bool swExecIsEnabled(ExecObj *obj){
	if(obj->bEnabled!=NULL && (*obj->bEnabled)==false)
		return false;
	return true;
}


//-------------------------------------------------------------------------------------------
DllExport void  swExecManagerExecute(){
	void(*execFunc)(void *);
	ExecObj *obj=(ExecObj*)swLinkedListGetFirst(execList);
	while(obj!=NULL){
		if(swExecIsEnabled(obj)){
			execFunc=obj->execFunc;
			(*execFunc)(obj->obj);
		}
		obj=(ExecObj*)swLinkedListGetNext(execList);
	}
}

//-------------------------------------------------------------------------------------------
DllExport void  swExecManagerDel(int id){
	ExecObj *obj=swExecManagerGet(id);
	if(obj!=NULL){
		swLinkedListDel(execList,obj);	
	}
}


