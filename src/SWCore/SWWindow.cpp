#include "SWCoreIn.h"
#include "resource.h"

int windowWidth=800;
int windowHeight=600;
DWORD windowStyle=false;
HINSTANCE windowInstanceHandler;
HICON	  windowIcon;
HDC  windowHDC;   
HWND windowHWND;
PIXELFORMATDESCRIPTOR windowPFD;
bool windowActive;
void (*windowCloseListener)(void);


//-------------------------------------------------------------------------------------------
DllExport void swWindowInit(HINSTANCE _hInstance, HICON _hIcon){
	windowInstanceHandler=_hInstance;
	windowIcon=_hIcon;
}


//-------------------------------------------------------------------------------------------
DllExport void swWindowDeInit(){
	if(windowHDC) ReleaseDC(windowHWND,windowHDC);    
    ChangeDisplaySettings(NULL,0);
}


//-------------------------------------------------------------------------------------------
DllExport bool swWindowIsActive(){
	return windowActive;
}


//-------------------------------------------------------------------------------------------
DllExport bool swWindowPeekMsg(MSG *Msg){

	if(PeekMessage(Msg,NULL,0,0,PM_REMOVE)) 
	{
		DispatchMessage(Msg);  
		TranslateMessage(Msg); 
		return true;
	}
	return false;
}


//-------------------------------------------------------------------------------------------
DllExport void swWindowSwap(void){
  SwapBuffers(windowHDC);
}


//-------------------------------------------------------------------------------------------
DllExport bool swWindowSetUpPixelFormat(HDC windowHDC,byte colorBits,byte depthBits,byte accumBits, byte stencilBits)
{
	int pixelformat;
	BOOL setpixfor=FALSE;
	windowPFD.nSize=sizeof(PIXELFORMATDESCRIPTOR);
	windowPFD.nVersion=1;
	windowPFD.dwFlags=PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	windowPFD.dwLayerMask=PFD_MAIN_PLANE;
	windowPFD.iPixelType=PFD_TYPE_RGBA;
	windowPFD.cColorBits=colorBits;
	windowPFD.cDepthBits=depthBits;
	windowPFD.cAccumBits=accumBits;
	windowPFD.cStencilBits=stencilBits;

	pixelformat=ChoosePixelFormat(windowHDC,&windowPFD);
	if(pixelformat==false)
	{
		MessageBox(NULL,"ChoosePixelFormat Failed","Error",MB_ICONEXCLAMATION | MB_OK);
		return false;
	}

	setpixfor=SetPixelFormat(windowHDC,pixelformat,&windowPFD);

	if(setpixfor==false)
	{
        MessageBox(NULL,"SetPixelFormat","Error",MB_ICONEXCLAMATION | MB_OK);
		return false;
	}
	return true;
}



//-------------------------------------------------------------------------------------------
DllExport HDC swWindowGetDC(){ 
	windowHDC=GetDC(windowHWND);
	return windowHDC;
}


//-------------------------------------------------------------------------------------------
HWND swWindowGetHWND(){ 
	return windowHWND;
}



//-------------------------------------------------------------------------------------------
DllExport int swWindowGetWidth(){
  return windowWidth;
}

//-------------------------------------------------------------------------------------------
DllExport int swWindowGetHeight(){
  return windowHeight;
}


//-------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND windowHWND,UINT Message,WPARAM wparam,LPARAM lparam)
{	
	switch(Message)
	{


	case WM_ACTIVATE:	


		if (!HIWORD(wparam))					// Check Minimization State
		{
			windowActive=true;						// Program Is Active
		}
		else
		{
			windowActive=false;						// Program Is No Longer Active
		}

		return NULL;
	

	//case WM_PAINT:
	//	BeginPaint(windowHWND,&ps);
	//	EndPaint(windowHWND,&ps);
	//	break;

	case WM_KEYDOWN:                    
        break;
		
	case WM_CLOSE:
		DestroyWindow(windowHWND);
		(*windowCloseListener)();
		break;

	case WM_DESTROY:
	    break;

	default:
		return DefWindowProc(windowHWND,Message,wparam,lparam);
	}
	
	return 0;
}


//-------------------------------------------------------------------------------------------
DllExport void swWindowSwitchFullScreen(void){
	int result ;
	DEVMODE dmSettings;									
	memset(&dmSettings,0,sizeof(dmSettings));			
	if(!EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&dmSettings))
	{
		MessageBox(NULL, "Could Not Enum Display Settings", "Error", MB_OK);		//Display Settings Dogru Bir Sekilde Alinamadi
		return;
	}

	dmSettings.dmPelsWidth	= swWindowGetWidth();
	dmSettings.dmPelsHeight	= swWindowGetHeight();
	result = ChangeDisplaySettings(&dmSettings,CDS_FULLSCREEN);	
	if(result != DISP_CHANGE_SUCCESSFUL)
	{
		MessageBox(NULL, "Display Mode Not Compatible", "Error", MB_OK);
		PostQuitMessage(0);
	}
}

//==========================================================================================
DllExport HWND swWindowCreate(char* title, int width, int height, bool bFullScreen,bool bCursor){

	WNDCLASSEX wclass;

	windowHeight=height;
	windowWidth=width;
	

    // Register Window Class
	wclass.cbSize        = sizeof(WNDCLASSEX);
	wclass.style         = 0;
	wclass.lpfnWndProc   = WndProc;                        //Cagrilan Callback fonsiyonu (Windows prosedürü)                       
	wclass.cbClsExtra    = 0;
	wclass.cbWndExtra    = 0;
	wclass.hInstance     = windowInstanceHandler;		   //Uygulamanin Instance'i (exe 'si)
	wclass.hIcon         = windowIcon!=NULL ? windowIcon: LoadIcon(NULL,IDI_WINLOGO);
	wclass.hCursor		 = LoadCursor(NULL,IDC_ARROW);		//Cursor'u yükle (standart ok)
	wclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+2);       //Black background
	wclass.lpszMenuName  = NULL;                           //Menu kodla yaratildi o yüzden NULL
	wclass.lpszClassName = "MyWindowClass";                //class ismi
	wclass.hIconSm       = windowIcon!=NULL ? windowIcon: LoadIcon(NULL,IDI_WINLOGO);



	if(RegisterClassEx(&wclass)==0)                        //Eger Registering Basarisizsa
	{
		MessageBox(NULL,"Can't Register Window Class","Error",MB_ICONEXCLAMATION | MB_OK); //Hata mesajini popupla
		return 0;
	}
 

	if(!bFullScreen){
		windowHWND=CreateWindowEx(  WS_EX_WINDOWEDGE | WS_EX_APPWINDOW,
							"MyWindowClass",
							 title,
							 WS_BORDER | WS_CAPTION | WS_SYSMENU|WS_MINIMIZEBOX,     
							 0,0,windowWidth ,windowHeight, 
							NULL,NULL,windowInstanceHandler,NULL);
	}else{
 
		windowStyle=WS_POPUP;
		windowHWND=CreateWindowEx(WS_EX_APPWINDOW,
							"MyWindowClass",
							 title,
							 WS_POPUP|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,     
							 0,0,windowWidth ,windowHeight, 
							 NULL,NULL,windowInstanceHandler,NULL);

        swWindowSwitchFullScreen();       
	}  
	if(windowHWND==NULL)                        
	{
		MessageBox(NULL,"Can't Create Window","Error",MB_ICONEXCLAMATION | MB_OK); // Hata mesaji 
		return 0;
	}


	ShowWindow(windowHWND,SW_SHOW);					
	ShowCursor(bCursor);
	SetForegroundWindow(windowHWND);	// Slightly Higher Priority
	UpdateWindow(windowHWND);             
	SetFocus(windowHWND);	

	return windowHWND;
}



//=================================================================================
DllExport void swWindowSetCloseListener(void (*callback)(void)){
	windowCloseListener=callback;
}


