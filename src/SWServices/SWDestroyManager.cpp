#include "SWServicesIn.h"


typedef struct{
	void  *obj;
	void (*destroyFunc)(void*);
}DestroyObj;

int iGameDestroyList=-1;

//-------------------------------------------------------------------------------------------
DllExport void swDestroyManagerInit(){
	iGameDestroyList=swLinkedListCreate();
}

//-------------------------------------------------------------------------------------------
DllExport void swDestroyManagerDeInit(){
	swLinkedListDestroy(iGameDestroyList);
}

//-------------------------------------------------------------------------------------------
DllExport void swDestroyManagerExecute(){
	void  (*pDestroy)(void *);
	DestroyObj* pO=(DestroyObj*)swLinkedListGetFirst(iGameDestroyList);
	while(pO!=NULL){
		pDestroy=pO->destroyFunc;
		(*pDestroy)(pO->obj);
		pO=(DestroyObj*)swLinkedListGetNext(iGameDestroyList);
	}
	swLinkedListClear(iGameDestroyList);
}



//-------------------------------------------------------------------------------------------
DllExport void swDestroyManagerAdd(void(*destroyFunc)(void*), void *obj){
	DestroyObj *pO=(DestroyObj*)malloc(sizeof(DestroyObj));
	pO->destroyFunc=destroyFunc;
	pO->obj=obj;
	swLinkedListAdd(iGameDestroyList,pO);
}

