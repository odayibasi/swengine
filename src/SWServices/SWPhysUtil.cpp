#include "SWServicesIn.h"

float ratioMeterOfPixel=1.0f;



//-------------------------------------------------------------------------------------------
void swPhysUtilMeterOfPixelRatio(float ratio){
	ratioMeterOfPixel=ratio;
}

//-------------------------------------------------------------------------------------------
float swPhysUtilConvert(float pixel){
	return pixel/ratioMeterOfPixel;
}

//-------------------------------------------------------------------------------------------
float swPhysUtilReConvert(float meter){
	return meter*ratioMeterOfPixel;
}


//-------------------------------------------------------------------------------------------
void swPhysUtilConvertRect(swRect *rPixel,swRect *rMeter){
	rMeter->x=swPhysUtilConvert(rPixel->x);
	rMeter->y=swPhysUtilConvert(rPixel->y);
	rMeter->w=swPhysUtilConvert(rPixel->w);
	rMeter->h=swPhysUtilConvert(rPixel->h);
}


