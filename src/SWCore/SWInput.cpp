#include "SWCoreIn.h"

#pragma comment (lib,"dxguid.lib")         
#pragma comment (lib,"dxerr8.lib")         
#pragma comment (lib,"dinput8.lib")     

#define DIRECTINPUT_VERSION 0x0800
#include <windows.h>
#include <dinput.h>


LPDIRECTINPUT8		  g_lpDI=NULL;
LPDIRECTINPUTDEVICE   g_lpKeyboard=NULL;
LPDIRECTINPUTDEVICE   g_lpMouse=NULL;
HWND				  g_hWnd=NULL;


swPoint               prevMousePos={0,0};

//-------------------------------------------------------------------------------------------
bool swInputCreateKeyboard(HWND hWnd){

	HRESULT hr;
	DWORD   flags;
	bool    isExclusive=false;

	g_hWnd=hWnd;
	//Device yarat (keyboard)
	hr=IDirectInput8_CreateDevice(g_lpDI,GUID_SysKeyboard, (LPDIRECTINPUTDEVICE8A*)&g_lpKeyboard, NULL);		
	if(FAILED(hr)) return false;

	//Set data format
	hr=IDirectInputDevice_SetDataFormat(g_lpKeyboard,&c_dfDIKeyboard);
	if(FAILED(hr)) return false;

	//SetCooperativeLevel
	if(isExclusive==true) flags=DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
	else flags=DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
	hr=IDirectInputDevice_SetCooperativeLevel(g_lpKeyboard,hWnd,flags);
	if(FAILED(hr)) return false;

	//Input device'a eriþim..
	hr=IDirectInputDevice_Acquire(g_lpKeyboard);
	if(FAILED(hr)) return false;

	return true;
}

//-------------------------------------------------------------------------------------------
bool swInputCreateMouse(HWND hWnd){
	HRESULT hr;
	DWORD   flags;
	bool    isExclusive=false;

	//Device yarat (Mouse)
	hr=IDirectInput8_CreateDevice(g_lpDI,GUID_SysMouse,(LPDIRECTINPUTDEVICE8A*)&g_lpMouse,NULL);
	if(FAILED(hr))return false;

	//Set data format
	hr=IDirectInputDevice_SetDataFormat(g_lpMouse,&c_dfDIMouse);
	if(FAILED(hr))return false;

	//SetCooperativeLevel
	if(isExclusive==true) flags=DISCL_FOREGROUND | DISCL_EXCLUSIVE;
	else flags=DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;

	hr=IDirectInputDevice_SetCooperativeLevel(g_lpMouse,hWnd,flags);    
	if(FAILED(hr)) return false;

	//Input device'a eriþim..
	hr=IDirectInputDevice_Acquire(g_lpMouse);
	if(FAILED(hr))return false;
	return true;
}



//-------------------------------------------------------------------------------------------
DllExport bool swInputInit(){
	HRESULT  hr=DirectInput8Create(GetModuleHandle(NULL),DIRECTINPUT_VERSION,IID_IDirectInput8,(void **)&g_lpDI,NULL);	
	if(FAILED(hr)) return false;


	HWND hwnd=swWindowGetHWND();
	if(!swInputCreateKeyboard(hwnd))
		return false;

	if(!swInputCreateMouse(hwnd))
		return false;

	return true;
}

//-------------------------------------------------------------------------------------------
DllExport void swInputDeInit(){
	if(g_lpDI){
		if(g_lpKeyboard){
			IDirectInputDevice_Unacquire(g_lpKeyboard);
			IDirectInputDevice_Release(g_lpKeyboard);
			g_lpKeyboard=NULL;
		}

		if(g_lpMouse){
			IDirectInputDevice_Unacquire(g_lpMouse);
			IDirectInputDevice_Release(g_lpMouse);
			g_lpMouse=NULL;
		}

		IDirectInput8_Release(g_lpDI);
		g_lpDI=NULL;
	}
}

//-------------------------------------------------------------------------------------------
DllExport void swInputListenMouse(swMouseState *state){

	DIMOUSESTATE dims;
	ZeroMemory(&dims,sizeof(dims));
	HRESULT hr=IDirectInputDevice_GetDeviceState(g_lpMouse,sizeof(DIMOUSESTATE),(LPVOID)&dims);
	if(FAILED(hr)){
		hr=IDirectInputDevice_Acquire(g_lpMouse);
		while(hr==DIERR_INPUTLOST) hr=IDirectInputDevice_Acquire(g_lpMouse);
		if(FAILED(hr))
			return;
	}

	state->btnLEFT=(dims.rgbButtons[0] & 0x80);
	state->btnRIGHT=(dims.rgbButtons[1] & 0x80);
	state->btnMIDDLE=(dims.rgbButtons[2] & 0x80);
    state->dx=(float)dims.lX;
	state->dy=(float)dims.lY;

	//FIXME Used Win32 for MouseInput But we must use DX
	POINT cursor;
	bool bSuccess=GetCursorPos(&cursor);

	RECT rect;
	GetWindowRect(g_hWnd, &rect);
	
	if(bSuccess){
		state->x=cursor.x-rect.left;
		state->y=rect.bottom-cursor.y;
		state->dx=state->x-prevMousePos.x;
		state->dy=prevMousePos.y-state->y;
		prevMousePos.x=state->x;
		prevMousePos.y=state->y;
	}
}



//-------------------------------------------------------------------------------------------
DllExport void swInputListenKeyboard(swKeyboardState *state){
#define KEYDOWN(name,key) (name[key] & 0x80)

	char buffer[256];
	HRESULT hr=IDirectInputDevice_GetDeviceState(g_lpKeyboard,sizeof(buffer),(LPVOID)&buffer);
	if(FAILED(hr)){
		hr=IDirectInputDevice_Acquire(g_lpKeyboard);
		while(hr==DIERR_INPUTLOST) hr=IDirectInputDevice_Acquire(g_lpKeyboard);
		if(FAILED(hr))
			return;
	}


	//CheckIllegalCase
	state->keyYEN=KEYDOWN(buffer,DIK_YEN);
	if(state->keyYEN){
		state->keyYEN=false;
		return;
	}

	
	state->key0=KEYDOWN(buffer,DIK_0);
	state->key1=KEYDOWN(buffer,DIK_1);
	state->key2=KEYDOWN(buffer,DIK_2);
	state->key3=KEYDOWN(buffer,DIK_3);
	state->key4=KEYDOWN(buffer,DIK_4);
	state->key5=KEYDOWN(buffer,DIK_5);
	state->key6=KEYDOWN(buffer,DIK_6);
	state->key7=KEYDOWN(buffer,DIK_7);
	state->key8=KEYDOWN(buffer,DIK_8);
	state->key9=KEYDOWN(buffer,DIK_9);
	state->keyA=KEYDOWN(buffer,DIK_A);
	state->keyABNT_C1=KEYDOWN(buffer,DIK_ABNT_C1);
	state->keyABNT_C2=KEYDOWN(buffer,DIK_ABNT_C2);
	state->keyADD=KEYDOWN(buffer,DIK_ADD);
	state->keyAPOSTROPHE=KEYDOWN(buffer,DIK_APOSTROPHE);
	state->keyAPPS=KEYDOWN(buffer,DIK_APPS);
	state->keyAT=KEYDOWN(buffer,DIK_AT);
	state->keyAX=KEYDOWN(buffer,DIK_AX);
	state->keyB=KEYDOWN(buffer,DIK_B);
	state->keyBACK=KEYDOWN(buffer,DIK_BACK);
	state->keyBACKSLASH=KEYDOWN(buffer,DIK_BACKSLASH);
	state->keyC=KEYDOWN(buffer,DIK_C);
	state->keyCALCULATOR=KEYDOWN(buffer,DIK_CALCULATOR);
	state->keyCAPITAL=KEYDOWN(buffer,DIK_CAPITAL);
	state->keyCOLON=KEYDOWN(buffer,DIK_COLON);
	state->keyCOMMA=KEYDOWN(buffer,DIK_COMMA);
	state->keyCONVERT=KEYDOWN(buffer,DIK_CONVERT);
	state->keyD=KEYDOWN(buffer,DIK_D);
	state->keyDECIMAL=KEYDOWN(buffer,DIK_DECIMAL);
	state->keyDELETE=KEYDOWN(buffer,DIK_DELETE);
	state->keyDIVIDE=KEYDOWN(buffer,DIK_DIVIDE);
	state->keyDOWN=KEYDOWN(buffer,DIK_DOWN);
	state->keyE=KEYDOWN(buffer,DIK_E);
	state->keyEND=KEYDOWN(buffer,DIK_END);
	state->keyEQUALS=KEYDOWN(buffer,DIK_EQUALS);
	state->keyESCAPE=KEYDOWN(buffer,DIK_ESCAPE);
	state->keyF=KEYDOWN(buffer,DIK_F);
	state->keyF1=KEYDOWN(buffer,DIK_F1);
	state->keyF10=KEYDOWN(buffer,DIK_F10);
	state->keyF12=KEYDOWN(buffer,DIK_F12);
	state->keyF13=KEYDOWN(buffer,DIK_F13);
	state->keyF14=KEYDOWN(buffer,DIK_F14);
	state->keyF15=KEYDOWN(buffer,DIK_F15);
	state->keyF2=KEYDOWN(buffer,DIK_F2);
	state->keyF3=KEYDOWN(buffer,DIK_F3);
	state->keyF4=KEYDOWN(buffer,DIK_F4);
	state->keyF5=KEYDOWN(buffer,DIK_F5);
	state->keyF6=KEYDOWN(buffer,DIK_F6);
	state->keyF7=KEYDOWN(buffer,DIK_F7);
	state->keyF8=KEYDOWN(buffer,DIK_F8);
	state->keyF9=KEYDOWN(buffer,DIK_F9);
	state->keyG=KEYDOWN(buffer,DIK_G);
	state->keyGRAVE=KEYDOWN(buffer,DIK_GRAVE);
	state->keyH=KEYDOWN(buffer,DIK_H);
	state->keyHOME=KEYDOWN(buffer,DIK_HOME);
	state->keyI=KEYDOWN(buffer,DIK_I);
	state->keyINSERT=KEYDOWN(buffer,DIK_INSERT);
	state->keyJ=KEYDOWN(buffer,DIK_J);
	state->keyK=KEYDOWN(buffer,DIK_K);
	state->keyKANA=KEYDOWN(buffer,DIK_KANA);
	state->keyKANJI=KEYDOWN(buffer,DIK_KANJI);
	state->keyL=KEYDOWN(buffer,DIK_L);
	state->keyLBRACKET=KEYDOWN(buffer,DIK_LBRACKET);
	state->keyLCONTROL=KEYDOWN(buffer,DIK_LCONTROL);
	state->keyLEFT=KEYDOWN(buffer,DIK_LEFT);
	state->keyLMENU=KEYDOWN(buffer,DIK_LMENU);
	state->keyLSHIFT=KEYDOWN(buffer,DIK_LSHIFT);
	state->keyLWIN=KEYDOWN(buffer,DIK_LWIN);
	state->keyM=KEYDOWN(buffer,DIK_M);
	state->keyMAIL=KEYDOWN(buffer,DIK_MAIL);
	state->keyMEDIASELECT=KEYDOWN(buffer,DIK_MEDIASELECT);
	state->keyMEDIASTOP=KEYDOWN(buffer,DIK_MEDIASTOP);
	state->keyMINUS=KEYDOWN(buffer,DIK_MINUS);
	state->keyMULTIPLY=KEYDOWN(buffer,DIK_MULTIPLY);
	state->keyMUTE=KEYDOWN(buffer,DIK_MUTE);
	state->keyMYCOMPUTER=KEYDOWN(buffer,DIK_MYCOMPUTER);
	state->keyN=KEYDOWN(buffer,DIK_N);
	state->keyNEXT=KEYDOWN(buffer,DIK_NEXT);
	state->keyNEXTTRACK=KEYDOWN(buffer,DIK_NEXTTRACK);
	state->keyNOCONVERT=KEYDOWN(buffer,DIK_NOCONVERT);
	state->keyNUMLOCK=KEYDOWN(buffer,DIK_NUMLOCK);
	state->keyNUMPAD0=KEYDOWN(buffer,DIK_NUMPAD0);
	state->keyNUMPAD1=KEYDOWN(buffer,DIK_NUMPAD1);
	state->keyNUMPAD2=KEYDOWN(buffer,DIK_NUMPAD2);
	state->keyNUMPAD3=KEYDOWN(buffer,DIK_NUMPAD3);
	state->keyNUMPAD4=KEYDOWN(buffer,DIK_NUMPAD4);
	state->keyNUMPAD5=KEYDOWN(buffer,DIK_NUMPAD5);
	state->keyNUMPAD6=KEYDOWN(buffer,DIK_NUMPAD6);
	state->keyNUMPAD7=KEYDOWN(buffer,DIK_NUMPAD7);
	state->keyNUMPAD8=KEYDOWN(buffer,DIK_NUMPAD8);
	state->keyNUMPAD9=KEYDOWN(buffer,DIK_NUMPAD9);
	state->keyNUMPADCOMMA=KEYDOWN(buffer,DIK_NUMPADCOMMA);
	state->keyNUMPADENTER=KEYDOWN(buffer,DIK_NUMPADENTER);
	state->keyNUMPADEQUALS=KEYDOWN(buffer,DIK_NUMPADEQUALS);
	state->keyO=KEYDOWN(buffer,DIK_O);
	state->keyOEM_102=KEYDOWN(buffer,DIK_OEM_102);
	state->keyP=KEYDOWN(buffer,DIK_P);
	state->keyPAUSE=KEYDOWN(buffer,DIK_PAUSE);
	state->keyPGDOWN=KEYDOWN(buffer,DIK_PGDN);
	state->keyPGUP=KEYDOWN(buffer,DIK_PGDN);
	state->keyPERIOD=KEYDOWN(buffer,DIK_PERIOD);
	state->keyPLAYPAUSE=KEYDOWN(buffer,DIK_PLAYPAUSE);
	state->keyPOWER=KEYDOWN(buffer,DIK_POWER);
	state->keyPREVTRACK=KEYDOWN(buffer,DIK_PREVTRACK);
	state->keyPRIOR=KEYDOWN(buffer,DIK_PRIOR);
	state->keyQ=KEYDOWN(buffer,DIK_Q);
	state->keyR=KEYDOWN(buffer,DIK_R);
	state->keyRBRACKET=KEYDOWN(buffer,DIK_RBRACKET);
	state->keyRCONTROL=KEYDOWN(buffer,DIK_RCONTROL);
	state->keyRETURN=KEYDOWN(buffer,DIK_RETURN);
	state->keyRIGHT=KEYDOWN(buffer,DIK_RIGHT);
	state->keyRMENU=KEYDOWN(buffer,DIK_RMENU);
	state->keyRSHIFT=KEYDOWN(buffer,DIK_RSHIFT);
	state->keyRWIN=KEYDOWN(buffer,DIK_RWIN);
	state->keyS=KEYDOWN(buffer,DIK_S);
	state->keySCROLL=KEYDOWN(buffer,DIK_SCROLL);
	state->keySEMICOLON=KEYDOWN(buffer,DIK_SEMICOLON);
	state->keySLASH=KEYDOWN(buffer,DIK_SLASH);
	state->keySLEEP=KEYDOWN(buffer,DIK_SLEEP);
	state->keySPACE=KEYDOWN(buffer,DIK_SPACE);
	state->keySTOP=KEYDOWN(buffer,DIK_STOP);
	state->keySUBTRACT=KEYDOWN(buffer,DIK_SUBTRACT);
	state->keySYSRQ=KEYDOWN(buffer,DIK_SYSRQ);
	state->keyT=KEYDOWN(buffer,DIK_T);
	state->keyTAB=KEYDOWN(buffer,DIK_TAB);
	state->keyU=KEYDOWN(buffer,DIK_U);
	state->keyUNDERLINE=KEYDOWN(buffer,DIK_UNDERLINE);
	state->keyUNLABELED=KEYDOWN(buffer,DIK_UNLABELED);
	state->keyUP=KEYDOWN(buffer,DIK_UP);
	state->keyV=KEYDOWN(buffer,DIK_V);
	state->keyVOLUMEDOWN=KEYDOWN(buffer,DIK_VOLUMEDOWN);
	state->keyVOLUMEUP=KEYDOWN(buffer,DIK_VOLUMEUP);
	state->keyW=KEYDOWN(buffer,DIK_W);
	state->keyWAKE=KEYDOWN(buffer,DIK_WAKE);
	state->keyWEBBACK=KEYDOWN(buffer,DIK_WEBBACK);
	state->keyWEBFAVORITES=KEYDOWN(buffer,DIK_WEBFAVORITES);
	state->keyWEBFORWARD=KEYDOWN(buffer,DIK_WEBFORWARD);
	state->keyWEBHOME=KEYDOWN(buffer,DIK_WEBHOME);
	state->keyWEBREFRESH=KEYDOWN(buffer,DIK_WEBREFRESH);
	state->keyWEBSEARCH=KEYDOWN(buffer,DIK_WEBSEARCH);
	state->keyWEBSTOP=KEYDOWN(buffer,DIK_WEBSTOP);
	state->keyX=KEYDOWN(buffer,DIK_X);
	state->keyY=KEYDOWN(buffer,DIK_Y);
	state->keyZ=KEYDOWN(buffer,DIK_Z);



}

