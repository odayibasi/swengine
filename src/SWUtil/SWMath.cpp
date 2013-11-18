#include "SWUtilIn.h"
#include <math.h>

#define PIOVER180		   0.0174532925199432957692369076848861f
#define PIUNDER180		  57.2957795130823208767981548141052f
#define DEGTORAD(deg) ((PIOVER180)*(deg))
#define RADTODEG(rad) ((PIUNDER180)*(rad))
#define MAX(X,Y)      ((X) > (Y) ? (X) : (Y))
#define MIN(X,Y)      ((X) < (Y) ? (X) : (Y))
#define ABS(X)        ((X) >  0 ? (X) : -(X))
#define SIGN(X)		  ((X) <  0 ? (-1) : (1))
#define SWAP(X,Y,T) T = X; X = Y; Y = T

unsigned int seed=0;

//-------------------------------------------------------------------------------------------
DllExport float swMathDegreeToRadian(float degree){
	return DEGTORAD(degree);
}

//-------------------------------------------------------------------------------------------
DllExport float swMathRadianToDegree(float radian){
     return RADTODEG(radian);
}

//-------------------------------------------------------------------------------------------
DllExport float swMathDegree(float x0,float y0,float x1,float y1){

	float dX=x1-x0;
	float dY=y1-y0;
	float result=RADTODEG(0);	
	float dRad=(float)atan(dY/dX);

	if(dX>0 && dY>0){
		result=RADTODEG(dRad); 
	}else if(dX<0 && dY>0){
		result=(180+RADTODEG(dRad)); 
	}else if(dX<0 && dY<0){
		result=(180+RADTODEG(dRad));  
	}else if(dX>0 && dY<0){
		result=(360+RADTODEG(dRad));  
	}else if(dX>0 && dY==0){
		result=0;
	}else if(dX==0 && dY>0){
		result=90;
	}else if(dX<0 && dY==0){
		result=180;
	}else if(dX==0 && dY<0){
		result=270;
	}
	return result;
}


//-------------------------------------------------------------------------------------------
DllExport float  swMathCos(float degree){
	return cos(swMathDegreeToRadian(degree));
}

//-------------------------------------------------------------------------------------------
DllExport float  swMathSin(float degree){
	return sin(swMathDegreeToRadian(degree));
}


//-------------------------------------------------------------------------------------------
DllExport float swMathDistance(float x0,float y0,float x1,float y1){
	float dX=x1-x0;
	float dY=y1-y0;
	return (float)sqrt(dX*dX+dY*dY);
}


//-------------------------------------------------------------------------------------------
DllExport float swMathSqrt(float val){
	return sqrtf(val);
}



//-------------------------------------------------------------------------------------------
DllExport float swMathMax(float val1, float val2){
	return MAX(val1,val2);
}


//-------------------------------------------------------------------------------------------
DllExport float  swMathMin(float val1, float val2){
	return MIN(val1,val2);
}

//-------------------------------------------------------------------------------------------
DllExport float swMathAbs(float val){
	return ABS(val);
}

//-------------------------------------------------------------------------------------------
DllExport float swMathSign(float val){
  return (float)SIGN(val);
}

//-------------------------------------------------------------------------------------------
DllExport bool swMathIsPowerTwo(float val){
	for(int i=0;i<15;i++){
		if(pow(2,i)==val) 
			return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------
DllExport bool swMathIsInRangeInt(int val,int minVal,int maxVal){
	return val>minVal && val<maxVal;
}

//-------------------------------------------------------------------------------------------
DllExport bool swMathIsInRangeFloat(float val,float minVal,float maxVal){
	return val>minVal && val<maxVal;
}

//-------------------------------------------------------------------------------------------
DllExport int swMathClampInt(int val,int minVal,int maxVal){
	if(val<minVal)
		return minVal;

	if(val>maxVal)
		return maxVal;

	return val;
}


//-------------------------------------------------------------------------------------------
DllExport float swMathClampFloat(float val,float minVal,float maxVal){
	if(val<minVal)
		return minVal;

	if(val>maxVal)
		return maxVal;

	return val;
}

//-------------------------------------------------------------------------------------------
DllExport float  swMathRandomFloat(float minVal,float maxVal){
	seed=214013*seed+2531011;
	return minVal+(seed>>16)*(1.0f/65535.0f)*(maxVal-minVal);
}


//-------------------------------------------------------------------------------------------
DllExport int  swMathRandomInt(int minVal,int maxVal){
	seed=214013*seed+2531011;
	return minVal+(seed ^ seed>>15)%(maxVal-minVal+1);
}


//-------------------------------------------------------------------------------------------
DllExport void swMathSetSeed(int randomSeed){
	seed=randomSeed;
}


//-------------------------------------------------------------------------------------------
DllExport void   swMathSourceCalculate(swRect *rect,int xGridSize,int yGridSize,int xGridIndex,int yGridIndex){
	rect->w=1.0f/xGridSize;
	rect->h=1.0f/yGridSize;
	rect->x=xGridIndex*rect->w;
	rect->y=yGridIndex*rect->h;
}

//---------------------------------------------------------
DllExport void swMathSource2Target(swPoint *s,swPoint *t,swRect *target,swRect *source,float rot,swPoint *wPoint){
	float sint,cost;
	float x,y,wX,wY,sX,sY;


	wX=wPoint->x;
	wY=wPoint->y;

	sint=(float)sin(swMathDegreeToRadian(rot));
	cost=(float)cos(swMathDegreeToRadian(rot));

	sX=source->x+(source->w*s->x);
	sY=source->y+(source->h*s->y);

	x=wX*target->w+(sX*target->w-target->w/2);
	y=wY*target->h+(sY*target->h-target->h/2);

	t->x=(x*cost-y*sint)+target->x+target->w/2-wX*target->w;
	t->y=(x*sint+y*cost)+target->y+target->h/2-wY*target->h;

}