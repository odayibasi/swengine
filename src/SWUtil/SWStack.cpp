#include "SWUtilIn.h"


//--------------------------------------------------------------------------------
DllExport int swStackCreate(){
   return swLinkedListCreate();
}


//--------------------------------------------------------------------------------
DllExport void   swStackDestroy(int stackID){
	swLinkedListDestroy(stackID);
}



//--------------------------------------------------------------------------------
DllExport void   swStackPush(int stackID, void *obj){
	swLinkedListAdd(stackID,obj);
}

//--------------------------------------------------------------------------------
DllExport void*  swStackPop(int stackID){
	void* obj=swLinkedListGetLast(stackID);
	swLinkedListDel(stackID,obj);
	return obj;
}

//--------------------------------------------------------------------------------
DllExport void*  swStackPeek(int stackID){
	void* obj=swLinkedListGetLast(stackID);
	return obj;
}


//--------------------------------------------------------------------------------
DllExport bool  swStackIsEmpty(int stackID){
	return swLinkedListSize(stackID)==0;
}

//--------------------------------------------------------------------------------
DllExport int  swStackSize(int stackID){
	return swLinkedListSize(stackID);
}