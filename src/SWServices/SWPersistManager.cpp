#include "SWServicesIn.h"


typedef struct{
	int   id;
	void  *obj;
	void (*saveFunc)(FILE*,void*);
}PersistObj;

int iGameSaverList=-1;
int iGameSaverCount=0;

//-------------------------------------------------------------------------------------------
DllExport void swPersistManagerInit(){
	iGameSaverList=swLinkedListCreate();
}

//-------------------------------------------------------------------------------------------
DllExport void swPersistManagerDeInit(){
	swLinkedListDestroy(iGameSaverList);
}

//-------------------------------------------------------------------------------------------
DllExport void swPersistManagerExecute(FILE *file){
	void  (*pSaver)(FILE *,void *);
	PersistObj* pO=(PersistObj*)swLinkedListGetFirst(iGameSaverList);
	while(pO!=NULL){
		pSaver=pO->saveFunc;
		(*pSaver)(file,pO->obj);
		pO=(PersistObj*)swLinkedListGetNext(iGameSaverList);
	}
}


//-------------------------------------------------------------------------------------------
PersistObj* swPersistManagerGet(int id){
	PersistObj* pO=(PersistObj*)swLinkedListGetFirst(iGameSaverList);
	while(pO!=NULL){
		if(pO->id==id){
			return pO;
		}
		pO=(PersistObj*)swLinkedListGetNext(iGameSaverList);
	}
	return NULL;
}


//-------------------------------------------------------------------------------------------
DllExport int swPersistManagerAdd(void(*saveFunc)(FILE *,void*), void *obj){
	PersistObj *pO=(PersistObj*)malloc(sizeof(PersistObj));
	pO->id=iGameSaverCount;
	pO->saveFunc=saveFunc;
	pO->obj=obj;
	iGameSaverCount++;
	swLinkedListAdd(iGameSaverList,pO);
	return pO->id;
}

//-------------------------------------------------------------------------------------------
DllExport void  swPersistManageDel(int id){
	PersistObj *pO=swPersistManagerGet(id);
	swLinkedListDel(iGameSaverList,pO);
}
