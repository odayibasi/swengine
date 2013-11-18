#include "SWUtilIn.h"


typedef struct _LinkListNode{
	void    *pObj;
	struct _LinkListNode *prev,*next,*end,*selected;
}LinkListNode;


typedef struct _LinkList{
	int id;
	int size;
	LinkListNode nodeS; 
	struct _LinkList *prev,*next,*end;
}LinkList;



LinkList linkListS;
LinkList *activeLinkList=NULL;
bool bLinkListInit=false;

#define INVALID_LINKED_LIST_ID -1


//--------------------------------------------------------------------------------
void  LinkedListInit(){

	if (!bLinkListInit){
		linkListS.size=0;
		linkListS.next=linkListS.prev=NULL;
		linkListS.end=&linkListS;
		bLinkListInit=true;
	}
}

//--------------------------------------------------------------------------------
void  LinkListActivate(int listID){
	LinkList *pLinkList;
	pLinkList=linkListS.next;
	while(pLinkList!=NULL){
		if(pLinkList->id==listID) {
			activeLinkList=pLinkList; 
			return;
		}
		pLinkList=pLinkList->next;
	}//end of while

}

//--------------------------------------------------------------------------------
DllExport void  swLinkedListClear(int listID){
	LinkListActivate(listID);
	LinkListNode *pLinkListNode=activeLinkList->nodeS.next;
	while(pLinkListNode!=NULL){
		LinkListNode *pLinkListNodeNext=pLinkListNode->next;
		free(pLinkListNode); 
		pLinkListNode=pLinkListNodeNext;  
	}

	activeLinkList->size=0;
	activeLinkList->nodeS.next=activeLinkList->nodeS.prev=NULL;
	activeLinkList->nodeS.end=&activeLinkList->nodeS;
}






//--------------------------------------------------------------------------------
DllExport int swLinkedListCreate(){      
static int linkListUID=0;
LinkList *pLinkList,*pLinkListEnd;
	LinkedListInit();
	pLinkList=(LinkList*)malloc(sizeof(LinkList)); //Allocation & Linking
	pLinkListEnd=linkListS.end;
	pLinkListEnd->next=pLinkList;
	pLinkList->prev=pLinkListEnd;
	linkListS.end=pLinkList;
	pLinkList->next=NULL;
	linkListS.size++;
    linkListUID++;

	pLinkList->id=linkListUID;
	pLinkList->size=0;
	pLinkList->nodeS.next=pLinkList->nodeS.prev=NULL;
	pLinkList->nodeS.end=&pLinkList->nodeS;
	return pLinkList->id;
}


//--------------------------------------------------------------------------------
DllExport void   swLinkedListDestroy(int listID){
	assert(listID>0);
	LinkListActivate(listID);
	swLinkedListClear(listID);
	LinkList *pLinkList=activeLinkList;
	LinkList *pLinkListTemp=NULL;
	if(pLinkList->next==NULL){               
		pLinkListTemp=pLinkList->prev;
		pLinkListTemp->next=NULL;
		linkListS.end=pLinkListTemp;
	}else{
		pLinkListTemp=pLinkList->prev;
		pLinkListTemp->next=pLinkList->next;
		pLinkListTemp=pLinkList->next;
		if(pLinkListTemp!=NULL) pLinkListTemp->prev=pLinkList->prev;
	}
	free(pLinkList);
	LinkListActivate(INVALID_LINKED_LIST_ID);
	return;
}


//--------------------------------------------------------------------------------
DllExport void   swLinkedListDel(int listID,void *obj){
	assert(listID>0);
	assert(swLinkedListContains(listID,obj));
	LinkListNode *pLinkListNodeNext,*pLinkListNodePrev;    
	LinkListActivate(listID);
	LinkListNode *pLinkListNode=activeLinkList->nodeS.next;
	while(pLinkListNode!=NULL){
		if(pLinkListNode->pObj==obj){
			pLinkListNodePrev=pLinkListNode->prev;
			if(pLinkListNode->next==NULL){
				pLinkListNodePrev->next=NULL;
				activeLinkList->nodeS.end=pLinkListNodePrev;

			}else{ 
				pLinkListNodePrev->next=pLinkListNode->next;
				pLinkListNodeNext=pLinkListNode->next;
				pLinkListNodeNext->prev=pLinkListNodePrev;
			}
			free(pLinkListNode);
			activeLinkList->size--;
			return;
		}//end of if
		pLinkListNode=pLinkListNode->next;
	}//end of while
	return;
}

//--------------------------------------------------------------------------------
DllExport int   swLinkedListSize(int listID){
	assert(listID>0);  
	LinkListActivate(listID);
	return activeLinkList->size;
}

//--------------------------------------------------------------------------------
void*   LinkListGet(LinkList *list){
	if(list->nodeS.selected!=NULL) 
		return ((LinkListNode*)list->nodeS.selected)->pObj;
	else 
		return NULL;
}


//--------------------------------------------------------------------------------
DllExport void*  swLinkedListGetFirst(int listID){
	assert(listID>0);  
	LinkListActivate(listID);
	activeLinkList->nodeS.selected=activeLinkList->nodeS.next;
	return LinkListGet(activeLinkList);
}


//--------------------------------------------------------------------------------
DllExport void*   swLinkedListGetNext(int listID){
	assert(listID>0);  
	LinkListActivate(listID);
	if(activeLinkList->nodeS.selected!=NULL)
		activeLinkList->nodeS.selected=((LinkListNode*)activeLinkList->nodeS.selected)->next;
	return LinkListGet(activeLinkList);
}

//--------------------------------------------------------------------------------
DllExport void*  swLinkedListGetPrev(int listID){
	assert(listID>0);  
	LinkListActivate(listID);
	if(activeLinkList->nodeS.selected!=NULL)
		activeLinkList->nodeS.selected=((LinkListNode*)activeLinkList->nodeS.selected)->prev;
	return LinkListGet(activeLinkList);
}

//--------------------------------------------------------------------------------
DllExport void*  swLinkedListGetLast(int listID){
	assert(listID>0);  
	LinkListActivate(listID),
	activeLinkList->nodeS.selected=activeLinkList->nodeS.end;
	return LinkListGet(activeLinkList);
}


//--------------------------------------------------------------------------------
DllExport void   swLinkedListAdd(int listID,void* obj){
	assert(listID>0);  
	assert(obj!=NULL);
	LinkListActivate(listID);
	LinkListNode *pLinkListNode=(LinkListNode*)malloc(sizeof(LinkListNode)); //Allocation & Linking
	LinkListNode *pLinkListEndNode=(LinkListNode*)activeLinkList->nodeS.end;
	pLinkListEndNode->next=pLinkListNode;
	pLinkListNode->prev=pLinkListEndNode;
	activeLinkList->nodeS.end=pLinkListNode;
	pLinkListNode->next=NULL;
	activeLinkList->size++;
	pLinkListNode->pObj=obj;
}



//--------------------------------------------------------------------------------
DllExport void  swLinkedListAddAfter(int listID,void* refObj,void *obj){
	assert(listID>0);
	assert(swLinkedListContains(listID,refObj));
	assert(obj!=NULL);
	LinkListActivate(listID);
	LinkListNode *pLinkListNode=activeLinkList->nodeS.selected=activeLinkList->nodeS.next;
	while(pLinkListNode!=NULL){
		if(pLinkListNode->pObj==refObj){
			LinkListNode *pLinkListNew=(LinkListNode*)malloc(sizeof(LinkListNode)); //Allocation & Linking
			pLinkListNew->pObj=obj;
			pLinkListNew->next=pLinkListNode->next;
			pLinkListNew->prev=pLinkListNode;
			pLinkListNode->next=pLinkListNew;				
		}
		pLinkListNode=pLinkListNode->next;
	}
}




//--------------------------------------------------------------------------------
DllExport void*  swLinkedListGet(int listID,int index){
	assert(listID>0);
	assert(index<=swLinkedListSize(listID));
	LinkListActivate(listID);
	void *obj=swLinkedListGetFirst(listID);
	if(index==0)
		return obj;

	for(int i=1;i<=index;i++){
		obj=swLinkedListGetNext(listID);			
	}
	return obj;
}



//--------------------------------------------------------------------------------
DllExport void  swLinkedListIterate(int listID,void(*func)(void*)){
void (*ptIterateFunc)(void *obj); 
	assert(listID>0);
	assert(func!=NULL);
	ptIterateFunc=func;
	void *obj=swLinkedListGetFirst(listID);		
	while(obj!=NULL){
		(*ptIterateFunc)(obj);
		obj=swLinkedListGetNext(listID);
	}
}


//--------------------------------------------------------------------------------
DllExport bool  swLinkedListContains(int listID,void *obj){
	assert(listID>0);
	assert(obj!=NULL);
	void *node=swLinkedListGetFirst(listID);		
	while(node!=NULL){
		if(node==obj){
			return true;
		}
		node=swLinkedListGetNext(listID);
	}
	return false;
}



