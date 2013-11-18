#ifndef SWENGINE_H
#define SWENGINE_H

#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include "SWTypes.h"
#include "SWUtil.h"
#include "SWCore.h"
#include "SWServices.h"
#include "SWGame.h"
#include "SWGui.h"


#ifndef DllExport
#define DllExport extern "C" __declspec(dllexport)
#endif



typedef struct{
	void  (*appRun)(void);
	int  width;
	int  height;
	bool fullScreen;
	bool cursor;
	char *title;
	char *path;
	HICON icon;
	HINSTANCE hInstance;
}swApplication;


DllExport bool  swEngineInit(swApplication *app);
DllExport void  swEngineRun();
DllExport void  swEngineExit();






#endif 

 