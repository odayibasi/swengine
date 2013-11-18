#include "SWCoreIn.h"

LARGE_INTEGER   ticksPerSecond;
LARGE_INTEGER   startTime;
float           elapsedSeconds=0;

//-------------------------------------------------------------------------------------------
DllExport bool swSystemInit(void){

	//Seed Number
	swMathSetSeed(timeGetTime());

	//Timer
	if (!QueryPerformanceFrequency(&ticksPerSecond))
		return false;
		QueryPerformanceCounter(&startTime);
		return true;


} 


//-------------------------------------------------------------------------------------------
DllExport void swSystemUpdate(){
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	elapsedSeconds = ((float)currentTime.QuadPart - (float)startTime.QuadPart) / (float)ticksPerSecond.QuadPart;
}


//-------------------------------------------------------------------------------------------
DllExport float swSystemGetElapsedSeconds(void){
	return elapsedSeconds;
}

//-------------------------------------------------------------------------------------------
DllExport void  swSystemCaptureScreen(char *path,swImgType type){
	swGraphicsSaveScreenShot(path,type);
}



//-------------------------------------------------------------------------------------------
DllExport char* swSystemGetGraphicsCardVendor(){
	return swGraphicsGetCardVendor();
}

