#include "SWGameIn.h"

typedef struct{
	int   id;
	swPoint* parent;
	swPoint* child;
}Linker;


int linkerList;
int linkerCounter=0;


//-------------------------------------------------------------
DllExport void  swLinkerInit(){
	linkerList=swLinkedListCreate();
}


//-------------------------------------------------------------
DllExport void  swLinkerDeInit(){
	Linker *linker=(Linker*)swLinkedListGetFirst(linkerList);
	while(linker!=NULL){
		free(linker);
		linker=(Linker*)swLinkedListGetNext(linkerList);
	}
	swLinkedListDestroy(linkerList);
}


//-------------------------------------------------------------
DllExport int swLinkerCreate(swPoint *parent,swPoint *child){
	Linker *linker=(Linker *)malloc(sizeof(Linker));
	linker->parent=parent;
	linker->child=child;
	linker->id=linkerCounter++;
	swLinkedListAdd(linkerList,linker);
	return linker->id;
}


//-------------------------------------------------------------
Linker* swLinkerGet(int id){
	Linker *linker=(Linker*)swLinkedListGetFirst(linkerList);
	while(linker!=NULL){
		if(linker->id==id)
			return linker;
		linker=(Linker*)swLinkedListGetNext(linkerList);
	}
	return NULL;
}


//-------------------------------------------------------------
DllExport void  swLinkerDestroy(int linkerID){
	Linker *linker=swLinkerGet(linkerID);
	swLinkedListDel(linkerList,linker);
	free(linker);
}


//-------------------------------------------------------------------
DllExport void swLinkerBind0(int linkerID,swRect *parent,swRect *child){
	swPoint pPos,cPos;
	Linker *linker=swLinkerGet(linkerID);
	pPos.x=parent->x+(parent->w*linker->parent->x);
	pPos.y=parent->y+(parent->h*linker->parent->y);

	cPos.x=child->x+(child->w*linker->child->x);
	cPos.y=child->y+(child->h*linker->child->y);

	child->x+=pPos.x-cPos.x; 
	child->y+=pPos.y-cPos.y; 
}

//-------------------------------------------------------------------
DllExport void swLinkerBind1(int linkerID,int linkerCID,swRect *parent,int indexParent,swRect *child,int indexChild){
	swPoint pPos,cPos;
	Linker  *linker=swLinkerGet(linkerID);

	swPoint *pBind=&linker->parent[indexParent];
	swPoint *cBind=&linker->child[indexChild];

	pPos.x=parent->x+(parent->w*pBind->x);
	pPos.y=parent->y+(parent->h*pBind->y);

	cPos.x=child->x+(child->w*cBind->x);
	cPos.y=child->y+(child->h*cBind->y);

	child->x+=(pPos.x-cPos.x); 
	child->y+=(pPos.y-cPos.y); 
}



//-------------------------------------------------------------------
DllExport void swLinkerBind2(int linkerID,swRect *sourceParent,swRect *targetParent,swPoint *wpParent,float rotParent,int indexParent,swRect *sourceChild,swRect *targetChild,swPoint *wpChild,float rotChild,int indexChild){
	swPoint pPos,cPos;

	Linker  *linker=swLinkerGet(linkerID);

	swPoint *pBind=&linker->parent[indexParent];
	swPoint *cBind=&linker->child[indexChild];

	swMathSource2Target(pBind,&pPos,targetParent,sourceParent,rotParent,wpParent);
	swMathSource2Target(cBind,&cPos,targetChild,sourceChild,rotChild,wpChild);

	targetChild->x+=(pPos.x-cPos.x); 
	targetChild->y+=(pPos.y-cPos.y); 


}

