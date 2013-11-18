#ifndef SWCORE_H
#define SWCORE_H


#include "SWTypes.h"
#include "SWUtil.h"



#ifndef DllExport
#define DllExport extern "C" __declspec(dllexport)
#endif


//==================================================================================================
//                  WINDOW API
// //Don't call windows api functions. This functions only use from SWEngine
//=================================================================================================
DllExport void swWindowInit(HINSTANCE _hInstance, HICON _hIcon);
DllExport void swWindowDeInit();
DllExport bool swWindowIsActive();
DllExport void swWindowSetCloseListener(void (*callback)(void));
DllExport bool swWindowPeekMsg(MSG *Msg);
DllExport void swWindowSwap(void);
DllExport bool swWindowSetUpPixelFormat(HDC windowHDC,byte colorBits,byte depthBits,byte accumBits, byte stencilBits);
DllExport HDC  swWindowGetDC();
DllExport int  swWindowGetWidth();
DllExport int  swWindowGetHeight();
DllExport void swWindowSwitchFullScreen(void);
DllExport HWND swWindowCreate(char* title, int width, int height, bool bFullScreen,bool bCursor);


//==================================================================================================
//                  INPUT API
// //Don't call windows api functions. This functions only use from SWEngine
//=================================================================================================
typedef struct _swKeyboardState{
  BOOL keyESCAPE,key1,key2,key3,key4,key5,key6,key7,key8,key9,key0,keyMINUS,keyEQUALS,keyBACK,keyTAB,keyQ;
  BOOL keyW,keyE,keyR,keyT,keyY,keyU,keyI,keyO,keyP,keyLBRACKET,keyRBRACKET,keyRETURN,keyLCONTROL,keyA;
  BOOL keyS,keyD,keyF,keyG,keyH,keyJ,keyK,keyL,keySEMICOLON,keyAPOSTROPHE,keyGRAVE,keyLSHIFT,keyBACKSLASH,keyZ,keyX;
  BOOL keyC,keyV,keyB,keyN,keyM,keyCOMMA,keyPERIOD,keySLASH,keyRSHIFT,keyMULTIPLY,keyLMENU,keySPACE,keyCAPITAL,keyF1;
  BOOL keyF2,keyF3,keyF4,keyF5,keyF6,keyF7,keyF8,keyF9,keyF10,keyNUMLOCK,keySCROLL,keyNUMPAD7,keyNUMPAD8,keyNUMPAD9;
  BOOL keySUBTRACT,keyNUMPAD4,keyNUMPAD5,keyNUMPAD6,keyADD,keyNUMPAD1,keyNUMPAD2,keyNUMPAD3,keyNUMPAD0;
  BOOL keyDECIMAL,keyOEM_102,keyF11,keyF12,keyF13,keyF14,keyF15,keyKANA,keyABNT_C1,keyCONVERT,keyNOCONVERT;
  BOOL keyYEN,keyABNT_C2,keyNUMPADEQUALS,keyPREVTRACK,keyAT,keyCOLON,keyUNDERLINE,keyKANJI,keySTOP,keyAX,keyUNLABELED;
  BOOL keyNEXTTRACK,keyNUMPADENTER,keyRCONTROL,keyMUTE,keyCALCULATOR,keyPLAYPAUSE,keyMEDIASTOP,keyVOLUMEDOWN,keyVOLUMEUP;
  BOOL keyWEBHOME,keyNUMPADCOMMA,keyDIVIDE,keySYSRQ,keyRMENU,keyPAUSE,keyHOME,keyUP,keyPRIOR,keyLEFT,keyRIGHT;
  BOOL keyEND,keyDOWN,keyNEXT,keyINSERT,keyDELETE,keyLWIN,keyRWIN,keyAPPS,keyPOWER,keySLEEP,keyWAKE,keyWEBSEARCH;
  BOOL keyWEBFAVORITES,keyWEBREFRESH,keyWEBSTOP,keyWEBFORWARD,keyWEBBACK,keyMYCOMPUTER,keyMAIL,keyMEDIASELECT;
  BOOL keyPGDOWN,keyPGUP;
}swKeyboardState;


typedef enum _swKeyEnum{
	SWKEY_ESC,	SWKWY_PAUSE,SWKEY_RETURN,SWKEY_TAB,SWKEY_BACKSPACE,
	SWKEY_0,SWKEY_1,SWKEY_2,SWKEY_3,SWKEY_4,SWKEY_5,SWKEY_6,SWKEY_7,SWKEY_8,SWKEY_9,
	SWKEY_F1,SWKEY_F2,SWKEY_F3,SWKEY_F4,SWKEY_F5,SWKEY_F6,SWKEY_F7,SWKEY_F8,SWKEY_F9,SWKEY_F10,
	SWKEY_F11,SWKEY_F12,SWKEY_F13,SWKEY_F14,SWKEY_F15,
	SWKEY_EQUALS,SWKEY_MINUS,SWKEY_DIVIDE,SWKEY_ADD,SWKEY_MULTIPLY,
	SWKEY_LBRACKET,SWKEY_RBRACKET,
	SWKEY_LCONTROL,SWKEY_RCONTROL,
	SWKEY_LSHIFT,SWKEY_RSHIFT,
	SWKET_PGDOWN,SWKEY_PGUP,
	SWKEY_A,SWKEY_B,SWKEY_C,SWKEY_D,SWKEY_E,SWKEY_F,SWKEY_G,SWKEY_H,SWKEY_I,SWKEY_J,SWKEY_K,SWKEY_L,SWKEY_M,
	SWKEY_N,SWKEY_O,SWKEY_P,SWKEY_R,SWKEY_S,SWKEY_T,SWKEY_U,SWKEY_V,SWKEY_Y,SWKEY_Z,SWKEY_Q,SWKEY_W,SWKEY_X,
	SWKEY_COMMA,SWKEY_SPACE,SWKEY_CAPITAL,SWKEY_UNDERLINE,
	SWKEY_UP,SWKEY_DOWN,SWKEY_LEFT,SWKEY_RIGHT,
	SWKEY_HOME,SWKEY_END,
	SWKEY_DELETE,SW_KEY_INSERT,SWKEY_PAUSE,
}swKeyEnum;




typedef struct _swMouseState{
  BOOL  btnLEFT,btnRIGHT,btnMIDDLE;
  float dx,dy;
  float x,y;
}swMouseState;

DllExport void swKeyboardStateCopy(swKeyboardState *state1,swKeyboardState *state2);


DllExport bool swInputInit();
DllExport void swInputDeInit();
DllExport void swInputListenKeyboard(swKeyboardState *state);
DllExport void swInputListenMouse(swMouseState *state);

//==================================================================================================
//                  SYSTEM API
//=================================================================================================

typedef enum _swImgType{
  SW_IMGTYPE_TGA,
}swImgType;


DllExport bool	swSystemInit();//Don't call this functions. This function only use from SWEngine
DllExport void	swSystemUpdate(); //Don't call this functions. This function only use from SWEngine
DllExport float swSystemGetElapsedSeconds();
DllExport void  swSystemCaptureScreen(char *path,swImgType type);
DllExport char* swSystemGetGraphicsCardVendor();


////==================================================================================================
////                  SOUND API
////=================================================================================================

DllExport void swAudioInit(void); //Don't call this functions. This function only use from SWEngine
DllExport void swAudioDeInit(void); //Don't call this functions. This function only use from SWEngine
DllExport void swAudioUpdate(void); //Don't call this functions. This function only use from SWEngine





//Buffer
typedef enum _swAudioBufferType{
	SW_AUDIO_BUFFER_TYPE_WAV,
	SW_AUDIO_BUFFER_TYPE_OGG,
	SW_AUDIO_BUFFER_TYPE_OGG_STREAM,
}swAudioBufferType;

DllExport int		swAudioCreateBuffer(char *path, swAudioBufferType bufferType);
DllExport void		swAudioDestroyBuffer(int bufferID);



//Source
typedef enum _swAudioSourceState{
  SW_AUDIO_SOURCE_STATE_NOBUFFER,
  SW_AUDIO_SOURCE_STATE_INITIAL,
  SW_AUDIO_SOURCE_STATE_PLAYING,
  SW_AUDIO_SOURCE_STATE_PAUSE,
  SW_AUDIO_SOURCE_STATE_STOP,
}swAudioSourceState;


DllExport int					swAudioCreateSource();
DllExport void					swAudioDestroySource(int sourceID);
DllExport void					swAudioBindSourceAndBuffer(int sourceID,int bufferID);
DllExport void					swAudioPlaySource(int sourceID);
DllExport void					swAudioPauseSource(int sourceID);
DllExport void					swAudioStopSource(int sourceID);
DllExport void					swAudioRewindSource(int sourceID);
DllExport swAudioSourceState	swAudioGetSourceState(int sourceID);
DllExport char*					swAudioGetSourceStateText(int sourceID);
DllExport void					swAudioSetSourcePosition(int sourceID,float x,float y,float z);
DllExport void					swAudioSetSourcePitch(int sourceID,float pitch);
DllExport void					swAudioSetSourceGain(int sourceID,float gain);
DllExport void					swAudioSetSourceLoop(int sourceID,bool loop);



//Listener
DllExport void					swAudioSetListenerPosition(float x,float y,float z);




//==================================================================================================
//                  FILESYSTEM API
//=================================================================================================
DllExport bool  swFileSystemInit();//Don't call this functions. This function only use from SWEngine
DllExport void  swFileSystemSetResourcePath(char *name);
DllExport char* swFileSystemGetProgramWorkingPath();
DllExport char* swFileSystemGetResourcePath();
DllExport FILE* swFileSystemOpenFile(char *path,char *mode);
DllExport void  swFileSystemQueryFiles(char *folderPath,int fileLinkedListID,char *extensionFilter);


//==================================================================================================
//                  IMAGE API
//=================================================================================================
DllExport void	swImgBufferLoad(char *path, swImgType imgType);
DllExport void	swImgBufferFree();
DllExport int	swImgBufferGetWidth();
DllExport int	swImgBufferGetHeight();
DllExport void	swImgBufferGetPixel(int x,int y,swColor *color);




//==================================================================================================
//                  GRAPHICS API
//=================================================================================================


//Initialize
DllExport void  swGraphicsInit(); //Don't call this functions. This function only use from SWEngine
DllExport void  swGraphicsDeInit(); //Don't call this functions. This function only use from SWEngine

//Scene
DllExport void  swGraphicsBeginScene();  
DllExport void  swGraphicsEndScene();  


//BackgroundColor
DllExport void swGraphicsSetBgColor0(float r,float g,float b);
DllExport void swGraphicsSetBgColor1(float r,float g,float b,float a);
DllExport void swGraphicsSetBgColor2(swColor *bgColor);

//Color
DllExport void  swGraphicsSetColor0(float r,float g,float b,float a);
DllExport void  swGraphicsSetColor1(swColor *c);


//Camera
#define SW_CAM_DEFAULT -1	

DllExport int   swGraphicsCreateCam();
DllExport void  swGraphicsDestroyCam(int camID);
DllExport void  swGraphicsSetCam(int camID,float x,float y,float rot,float zoom);
DllExport void  swGraphicsSetCamPos(int camID,float x,float y);
DllExport void  swGraphicsSetCamPosX(int camID,float x);
DllExport void  swGraphicsSetCamPosY(int camID,float y);
DllExport void  swGraphicsSetCamRot(int camID,float rot);
DllExport void  swGraphicsSetCamZoom(int camID,float zoom);
DllExport void  swGraphicsAddCamPosX(int camID,float dX);
DllExport void  swGraphicsAddCamPosY(int camID,float dY);
DllExport void  swGraphicsAddCamRot (int camID,float dR);
DllExport void  swGraphicsAddCamZoom(int camID,float dZ);
DllExport float swGraphicsGetCamPosX(int camID);
DllExport float swGraphicsGetCamPosY(int camID);
DllExport float swGraphicsGetCamRot(int camID);
DllExport float swGraphicsGetCamZoom(int camID);
DllExport void  swGraphicsActiveCam(int camID);


//Blending
typedef enum{
  SW_BLENDING_MODE_NONE,
  SW_BLENDING_MODE_ADDITIVE,
  SW_BLENDING_MODE_ADDITIVE_ACCORDING2_ALPHA,
  SW_BLENDING_MODE_SOLID,
  SW_BLENDING_MODE_SKETCH,
}swBlendingMode;

DllExport void  swGraphicsSetBlendingMode(swBlendingMode mode);
DllExport swBlendingMode swGraphicsGetBlendingMode();


//Rendering Target
#define SW_RENDERING_TARGET_DEFAULT -1		
DllExport int   swGraphicsCreateRenderingTarget(int width, int height, int iBytesPerPixel);
DllExport void  swGraphicsDestroyRenderingTarget(int targetID);
DllExport void  swGraphicsSetRenderingTarget(int targetID);
DllExport void  swGraphicsClearRenderingTarget();
DllExport int   swGraphicsRenderingTargetGetImgID(int targetID);

//Query
DllExport bool swGraphicsIsSupportGLSL();
DllExport bool swGraphicsIsSupportRectTex();
DllExport bool swGraphicsIsSupportPointSprite();
DllExport bool swGraphicsIsSupportFBOSupport();

//Shader
#define SW_DISABLED_SHADER_ID 0
DllExport int  swGraphicsCreateGLSLShader(char *pathVertShader,char *pathFragShader);
DllExport void swGraphicsActiveGLSLShader(int shaderID);
DllExport void swGraphicsSetGLSLShaderIntAttrb(int program, char *name,int value);
DllExport void swGraphicsSetGLSLShaderFloatAttrb(int program, char *name,float value);
DllExport void swGraphicsSetGLSLShaderVec2Attrb(int program, char *name,swVec2 vec2);
DllExport void swGraphicsSetGLSLShaderPointAttrb(int program, char *name,swPoint point);
DllExport void swGraphicsSetGLSLShaderDimensionAttrb(int program, char *name,swDimension dim);
DllExport void swGraphicsSetGLSLShaderColorAttrb(int program, char *name,swColor color);
DllExport void swGraphicsSetGLSLShaderRectAttrb(int program, char *name,swRect rect);


////Rendering
////--Point
DllExport void  swGraphicsRenderPoint0(float x,float y,float size);
DllExport void  swGraphicsRenderPoint1(swPoint *point,float size);

//--Line
DllExport void  swGraphicsRenderLine0(float x0,float y0,float x1,float y1,float width);
DllExport void  swGraphicsRenderLine1(swPoint *startP,swPoint *endP,float width);
DllExport void  swGraphicsRenderLine2(swPoint *startP,swPoint *endP,float width,float rot);
DllExport void  swGraphicsRenderLine3(swPoint *startP,swPoint *endP,float width,float rot,swPoint *weight);


//
////--Rect
DllExport void  swGraphicsRenderPointRect0(float x,float y,float w,float h,float size);
DllExport void  swGraphicsRenderPointRect1(swPoint *pos,swDimension *dim,float size);
DllExport void  swGraphicsRenderPointRect2(swRect *rect,float size);
DllExport void  swGraphicsRenderPointRect3(swRect *rect,float size,float rot);
DllExport void  swGraphicsRenderPointRect4(swRect *rect,float size,float rot,swPoint *weight);

DllExport void  swGraphicsRenderLineRect0(float x,float y,float w,float h,float width);
DllExport void  swGraphicsRenderLineRect1(swPoint *pos,swDimension *dim,float width);
DllExport void  swGraphicsRenderLineRect2(swRect *rect,float width);
DllExport void  swGraphicsRenderLineRect3(swRect *rect,float width,float rot);
DllExport void  swGraphicsRenderLineRect4(swRect *rect,float width,float rot,swPoint *weight);

DllExport void  swGraphicsRenderSolidRect0(float x,float y,float w,float h);
DllExport void  swGraphicsRenderSolidRect1(swPoint *pos,swDimension *dim);
DllExport void  swGraphicsRenderSolidRect2(swRect *rect);
DllExport void  swGraphicsRenderSolidRect3(swRect *rect,float rot);
DllExport void  swGraphicsRenderSolidRect4(swRect *rect,float rot,swPoint *weight);


////--Elips
DllExport void  swGraphicsRenderPointElips0(float x,float y,float w,float h,int count,float size);
DllExport void  swGraphicsRenderPointElips1(swPoint *pos,swDimension *dim,int count,float size);
DllExport void  swGraphicsRenderPointElips2(swPoint *pos,swDimension *dim,int count,float size,float rot);
DllExport void  swGraphicsRenderPointElips3(swPoint *pos,swDimension *dim,int count, float size, float rot,swPoint *weight);
DllExport void  swGraphicsRenderPointElips4(float x,float y,float w, float h,int count, float size, float rot,swPoint *weight);


DllExport void  swGraphicsRenderLineElips0(float x,float y,float w,float h,int count,float width);
DllExport void  swGraphicsRenderLineElips1(swPoint *pos,swDimension *dim,int count,float width);
DllExport void  swGraphicsRenderLineElips2(swPoint *pos,swDimension *dim,int count,float width,float rot);
DllExport void  swGraphicsRenderLineElips3(swPoint *pos,swDimension *dim,int count, float width,float rot, swPoint *weight);
DllExport void  swGraphicsRenderLineElips4(float x,float y,float w, float h,int count, float width,float rot, swPoint *weight);



DllExport void  swGraphicsRenderSolidElips0(float x,float y,float w,float h,int count);
DllExport void  swGraphicsRenderSolidElips1(swPoint *pos,swDimension *dim,int count);
DllExport void  swGraphicsRenderSolidElips2(swPoint *pos,swDimension *dim,int count,float rot);
DllExport void  swGraphicsRenderSolidElips3(swPoint *pos,swDimension *dim,int count, float rot, swPoint *weight);
DllExport void  swGraphicsRenderSolidElips4(float x,float y,float w,float h,int count, float rot, swPoint *weight);


////--Arcs
DllExport void  swGraphicsRenderPointArcs(float x,float y,float w, float h,int count, float size, float rot,swPoint *weight,float startAngle,float stopAngle);
DllExport void  swGraphicsRenderLineArcs(float x,float y,float w, float h,int count, float width,float rot, swPoint *weight, float startAngle,float stopAngle);


DllExport void  swGraphicsRenderSolidArcs0(float x,float y,float w,float h,int count,float startAngle,float stopAngle);
DllExport void  swGraphicsRenderSolidArcs4(float x,float y,float w,float h,int count, float rot, swPoint *weight, float startAngle,float stopAngle);



////--Polygon
DllExport void  swGraphicsRenderSolidPolygon0(int count,swPoint *pointS);
DllExport void  swGraphicsRenderSolidPolygon1(int pointLinkedListID);
DllExport void  swGraphicsRenderSolidPolygon2(swPolygon *polygon);

DllExport void  swGraphicsRenderLinePolygon0(int count,swPoint *pointS,float width);
DllExport void  swGraphicsRenderLinePolygon1(int pointLinkedListID,float width);
DllExport void  swGraphicsRenderLinePolygon2(swPolygon *polygon,float width);

DllExport void  swGraphicsRenderPointPolygon0(int count,swPoint *pointS,float size);
DllExport void  swGraphicsRenderPointPolygon1(int pointLinkedListID,float size);
DllExport void  swGraphicsRenderPointPolygon2(swPolygon *polygon,float size);

//--Image
DllExport int   swGraphicsCreateImg(char *filePath); 
DllExport void  swGraphicsDestroyImg(int imgID);  
DllExport void  swGraphicsSetImgUVScrollable(int imgID,bool bEnabled);
DllExport void  swGraphicsRenderImg0(int imgID,swRect *t);
DllExport void  swGraphicsRenderImg1(int imgID,swRect *t,float rot);
DllExport void  swGraphicsRenderImg2(int imgID,swRect *t,swRect *s);
DllExport void  swGraphicsRenderImg3(int imgID,swRect *t,swRect *s,float rot);
DllExport void  swGraphicsRenderImg4(int imgID,swRect *t,float rot, swPoint *weight);
DllExport void  swGraphicsRenderImg5(int imgID,swRect *t,swRect *s,float rot, swPoint *weight);


//--Sprite
static swRect SW_SPRITE_SOURCE_DEFAULT={0,0,1,1};
static swRect SW_SPRITE_SOURCE_MIRRORY={1,0,-1,1};
static swRect SW_SPRITE_SOURCE_MIRRORX={0,1,1,-1};
static swRect SW_SPRITE_SOURCE_MIRRORXY={1,1,-1,-1};


DllExport int   swGraphicsCreateSprite(char *folderPath);  
DllExport void  swGraphicsDestroySprite(int spriteID);
DllExport void  swGraphicsSetSpriteUVScrollable(int spriteID,bool bEnabled);
DllExport int   swGraphicsGetCountOfImgInSprite(int spriteID);
DllExport void  swGraphicsRenderSprite0(int spriteID,int index,swRect *t);
DllExport void  swGraphicsRenderSprite1(int spriteID,int index,swRect *t,float rot);
DllExport void  swGraphicsRenderSprite2(int spriteID,int index,swRect *t,swRect *s);
DllExport void  swGraphicsRenderSprite3(int spriteID,int index,swRect *t,swRect *s,float rot);
DllExport void  swGraphicsRenderSprite4(int spriteID,int index,swRect *t,float  rot, swPoint *weight);
DllExport void  swGraphicsRenderSprite5(int spriteID,int index,swRect *t,swRect *s,float rot, swPoint *weight);


//--Font
DllExport int   swGraphicsCreateFont(char *filePath);  
DllExport void  swGraphicsDestroyFont(int fontID);  
DllExport void  swGraphicsRenderText(int fontID,int set,float size,float x,float y,float rot,char *string,...);


//--PointSprite	

typedef struct _swPointSprite{
	swPoint pos;
	swColor color;
}swPointSprite;

DllExport int   swGraphicsCreatePointSprite(char *filePath); 
DllExport void  swGraphicsDestroyPointSprite(int pointSpriteID); 
DllExport void  swGraphicsRenderPointSprite0(int pointSpriteID,float pointSize,int count,swColor *colorS,swPoint* pointS); 
DllExport void  swGraphicsRenderPointSprite1(int pointSpriteID,float pointSize,int count,swPointSprite *pointSprites); 
DllExport void  swGraphicsRenderPointSprite2(int pointSpriteID,float pointSize,int pointSpriteListID); 







#endif