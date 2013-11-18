#include "SWServicesIn.h"

typedef struct{
 int	 id;
 void    *obj;
 void(*dispFunc)(void*);
 swRect  *rect;
 bool *bEnabled;
 int     *layer;
}DispObj;

int dispList=-1;
int dispObjCounter=0;
int maxLayer=1;

#define MAX_DISP_COUNT 1000
DispObj* dispArray[MAX_DISP_COUNT];
int dispArraySize=0;
swRect dispView={0,0,800,600};


//-------------------------------------------------------------------------------------------
DllExport void  swDispManagerInit(){
   dispList=swLinkedListCreate();
}


//-------------------------------------------------------------------------------------------
DllExport void  swDispManagerDeInit(){
	DispObj *obj=(DispObj*)swLinkedListGetFirst(dispList);
	while(obj!=NULL){
	   free(obj);
	   obj=(DispObj*)swLinkedListGetNext(dispList);
	}
	swLinkedListDestroy(dispList);
}


//-------------------------------------------------------------------------------------------
DllExport int swDispManagerAdd(void(*dispFunc)(void*), void *obj,bool *bEnabled,swRect *rect,int *layer){
	DispObj *dispObj=(DispObj*)malloc(sizeof(DispObj));
	dispObj->id=dispObjCounter++;
	dispObj->bEnabled=bEnabled;
	dispObj->dispFunc=dispFunc;
	dispObj->layer=layer;
	dispObj->obj=obj;
	dispObj->rect=rect;
	swLinkedListAdd(dispList,dispObj);
	return dispObj->id;
}

//-------------------------------------------------------------------------------------------
DllExport void swDispManagerSetLayerCount(int count){
	maxLayer=count;
}


//-------------------------------------------------------------------------------------------
DispObj* swDispManagerGet(int id){
	DispObj *obj=(DispObj*)swLinkedListGetFirst(dispList);
	while(obj!=NULL){
		if(obj->id==id)
			return obj;
		obj=(DispObj*)swLinkedListGetNext(dispList);
	}
	return NULL;
}


//-------------------------------------------------------------------------------------------
bool swDispIsVisible(DispObj *obj,swRect *view){
	if(obj->bEnabled!=NULL && (*obj->bEnabled)==false)
		return false;

	if(obj->rect!=NULL && swIntersectionRectAndRect(view,obj->rect)==false)
		return false;

	return true;
}


//-------------------------------------------------------------------------------------------
DllExport void  swDispManagerExecute(){
void(*dispFunc)(void *);
	dispArraySize=0;
	
	DispObj *obj=(DispObj*)swLinkedListGetFirst(dispList);
	while(obj!=NULL){
		if(swDispIsVisible(obj,&dispView)){
			dispArray[dispArraySize]=obj;
			dispArraySize++;
		}
		obj=(DispObj*)swLinkedListGetNext(dispList);
	}


	for(int i=0;i<maxLayer+1;i++){		
		for(int j=0;j<dispArraySize;j++){
			obj=(DispObj*)dispArray[j];
			if(obj->layer!=NULL && (*obj->layer)!=i){
				continue;
			}
			dispFunc=obj->dispFunc;
		   (*dispFunc)(obj->obj);
		}
	}
}


//-------------------------------------------------------------------------------------------
DllExport int  swDispManagerSizeOfAll(){
   return swLinkedListSize(dispList);
}


//-------------------------------------------------------------------------------------------
DllExport int swDispManagerSizeOfRendered(){
   return dispArraySize;
}


//-------------------------------------------------------------------------------------------
DllExport void  swDispManagerSetCullRegionPos(float x,float y){
	dispView.x=x;
	dispView.y=y;
}

//-------------------------------------------------------------------------------------------
DllExport void  swDispManagerSetCullRegion(float x,float y,float w,float h){
	swRectSet(&dispView,x,y,w,h);
}


//-------------------------------------------------------------------------------------------
DllExport void  swDispManagerDel(int id){
	DispObj *obj=swDispManagerGet(id);
	if(obj!=NULL){
		swLinkedListDel(dispList,obj);	
	}
}


