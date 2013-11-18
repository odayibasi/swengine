#include "SWGameIn.h"

typedef struct{
	int     id;
	swValueModifierMode mode;
	bool dir; //false ->min  true ->max
	float   *val;
	float   min;
	float   max;
	float   vel;
	float   acc;
}ValueModifier;


int valModifierList;
int valModifierCounter=0;



//-------------------------------------------------------------
DllExport void  swValueModifierInit(){
	valModifierList=swLinkedListCreate();
}


//-------------------------------------------------------------
DllExport void  swValueModifierDeInit(){
	ValueModifier *vModfr=(ValueModifier*)swLinkedListGetFirst(valModifierList);
	while(vModfr!=NULL){
		free(vModfr);
		vModfr=(ValueModifier*)swLinkedListGetNext(valModifierList);
	}
	swLinkedListDestroy(valModifierList);
}


//-------------------------------------------------------------
DllExport int  swValueModifierCreate(swValueModifierMode mode,float *value,float min,float max,float vel,float acc){
	ValueModifier *vModfr=(ValueModifier *)malloc(sizeof(ValueModifier));
	vModfr->id=valModifierCounter++;
	vModfr->min=min;
	vModfr->max=max;
	vModfr->mode=mode;
	vModfr->dir=true;
	vModfr->val=value;
	if((*vModfr->val)==min){
		vModfr->dir=true;
	}else if((*vModfr->val)==max){
		vModfr->dir=false;
	}else{
	    (*vModfr->val)=min;
		vModfr->dir=true;
	}
	vModfr->vel=vel;
	vModfr->acc=acc;
	swLinkedListAdd(valModifierList,vModfr);
	return vModfr->id;
}


//-------------------------------------------------------------
ValueModifier* swValueModifierGet(int id){
	ValueModifier *vModfr=(ValueModifier*)swLinkedListGetFirst(valModifierList);
	while(vModfr!=NULL){
		if(vModfr->id==id)
			return vModfr;
		vModfr=(ValueModifier*)swLinkedListGetNext(valModifierList);
	}
	return NULL;
}


//-------------------------------------------------------------
DllExport void  swValueModifierDestroy(int id){
	ValueModifier *modifier=swValueModifierGet(id);
	swLinkedListDel(valModifierList,modifier);
	free(modifier);
}

//-------------------------------------------------------------
DllExport void swValueModifierExecute(int id,float dTime){
	ValueModifier *modifier=swValueModifierGet(id);
	modifier->vel+=dTime*modifier->acc;
	if(modifier->dir)
		(*modifier->val)+=modifier->vel*dTime;
	else
		(*modifier->val)-=modifier->vel*dTime;

	if(modifier->mode==SW_VALUE_MODIFIER_01_LOOP && ((float)(*modifier->val))>modifier->max){
		(*modifier->val)=modifier->min;
	}

	if(modifier->mode==SW_VALUE_MODIFIER_10_LOOP && ((float)(*modifier->val))<modifier->min){
		(*modifier->val)=modifier->max;
	}

	if(modifier->mode==SW_VALUE_MODIFIER_010_LOOP && ((float)(*modifier->val))<modifier->min){
		modifier->dir=true;
	}

	if(modifier->mode==SW_VALUE_MODIFIER_010_LOOP && ((float)(*modifier->val))>modifier->max){
		modifier->dir=false;
	}

}


