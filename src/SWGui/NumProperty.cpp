#include "SWGuiIn.h"


int numPropFontID=-1;


//-------------------------------------------------------------------------------------------
void swNumPropSetFont(int fontID){
	numPropFontID=fontID;
}


//-------------------------------------------------------------------------------------------
void swNumPropDisplay(PropModel *prop,float x0,float y0){

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor0(1,1,1,0.5);
	if(prop->type==NUMPROP_TYPE_INT){
		swGraphicsRenderText(numPropFontID,0,12,x0,y0,0,"%s=%i",prop->name,(*prop->ip.iVal));
	}else if(prop->type==NUMPROP_TYPE_ENUM){
		int iVal=(*prop->ep.iVal);
		char* enumStr=(char*)swLinkedListGet(prop->ep.enumStrList,iVal);
		swGraphicsRenderText(numPropFontID,0,12,x0,y0,0,"%s=%s",prop->name,enumStr);
	}else if(prop->type==NUMPROP_TYPE_FLOAT){
		swGraphicsRenderText(numPropFontID,0,12,x0,y0,0,"%s=%1.2f",prop->name,(*prop->fp.fVal));
	}else if(prop->type==NUMPROP_TYPE_DOUBLE){
		swGraphicsRenderText(numPropFontID,0,12,x0,y0,0,"%s=%d",prop->name,(*prop->dp.dVal));
	}
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);


}


//-------------------------------------------------------------------------------------------
void swEnumPropProcess(EnumPropModel *prop,eNumPropEvntType type){

	if(type==NUMPROP_EVNT_TYPE_INC){
		(*prop->iVal)+=prop->iDelta;
	}else if(type==NUMPROP_EVNT_TYPE_DEC){
		(*prop->iVal)-=prop->iDelta;
	}
	(*prop->iVal)=swMathClampInt(*prop->iVal,prop->iMin,prop->iMax);
}



//-------------------------------------------------------------------------------------------
void swIntPropProcess(IntPropModel *prop,eNumPropEvntType type){
 
	if(type==NUMPROP_EVNT_TYPE_INC){
		(*prop->iVal)+=prop->iDelta;
	}else if(type==NUMPROP_EVNT_TYPE_DEC){
		(*prop->iVal)-=prop->iDelta;
	}
 	(*prop->iVal)=swMathClampInt(*prop->iVal,prop->iMin,prop->iMax);
}



//-------------------------------------------------------------------------------------------
void swFloatPropProcess(FloatPropModel *prop,eNumPropEvntType type){
float  *fVal=prop->fVal;	
	
	if(type==NUMPROP_EVNT_TYPE_INC){
	     *fVal+=prop->fDelta;
	}else if(type==NUMPROP_EVNT_TYPE_DEC){
		 *fVal-=prop->fDelta;
	}
	
	*fVal=swMathClampFloat(*fVal,prop->fMin,prop->fMax);
}


//-------------------------------------------------------------------------------------------
void swDoublePropProcess(DoublePropModel *prop,eNumPropEvntType type){
double  *dVal=prop->dVal;
	if(type==NUMPROP_EVNT_TYPE_INC){
		*dVal+=prop->dDelta;
	}else if(type==NUMPROP_EVNT_TYPE_DEC){
		*dVal-=prop->dDelta;
	}
}


//-------------------------------------------------------------------------------------------
void swNumPropProcess(PropModel *prop,eNumPropEvntType type){
	if(prop->type==NUMPROP_TYPE_INT){
		swIntPropProcess(&prop->ip,type);
	}else if(prop->type==NUMPROP_TYPE_ENUM){
		swEnumPropProcess(&prop->ep,type);
	}else if(prop->type==NUMPROP_TYPE_FLOAT){
		swFloatPropProcess(&prop->fp,type);
	}else if(prop->type==NUMPROP_TYPE_DOUBLE){
		swDoublePropProcess(&prop->dp,type);
	}
}

