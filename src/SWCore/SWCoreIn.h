#ifndef SWCORE_IN_H
#define SWCORE_IN_H

#pragma comment (lib, "winmm.lib")
#pragma comment (lib,"../../lib/SWTypes.lib")   
#pragma comment (lib,"../../lib/SWUtil.lib")   

#include "../../include/SWCore.h"

//===============================================================================
//               WINDOW
//================================================================================

HWND swWindowGetHWND();


//===============================================================================
//                CAMERA
//================================================================================

typedef struct _swCam{
	int id;
	float x;
	float y;
	float rot;
	float zoom;
}swCam;

void swCamInit();
void swCamDeInit();
swCam *swCamGet(int camID);

//===============================================================================
//                MATRIX 4x4
//================================================================================
typedef struct{
	float index[16];
}Mat4x4;


void swMat4x4Reset(Mat4x4 *m);
void swMat4x4Set(Mat4x4 *m,float f0,float f1,float f2,float f3,
				 float f4,float f5,float f6,float f7,
				 float f8,float f9,float f10,float f11,
				 float f12,float f13,float f14,float f15);


//===============================================================================
//                VECTOR 4
//================================================================================
typedef struct _Vec4{
	float index[4];
} Vec4;


void  swVectorSet(Vec4 *v,float f0, float f1,float f2,float f3);
void  swVectorCopy(Vec4 *v1, Vec4 *v2);
Vec4* swVectorClone(Vec4 *v);
bool  swVectorEquals(Vec4 *v1,Vec4 *v2);


//===============================================================================
//                TRANSFORM
//================================================================================
void swTransformInit(Mat4x4 *TM);
void swTransformSetLocation(float x, float y, float z);
void swTransformRotateZ(float degree);



//===============================================================================
//                TGA
//================================================================================


typedef struct _IMG{
	unsigned int    ilID;
	byte			TGAcompare[12];							
	byte			header[6];
	int				width;
	int				height;
	int             bpp;
	int             imageSize;
	byte            *imageData;
}IMG;


bool swTGASave(char *path, short int width, short int height, unsigned char *outImage);
void swTGALoad(IMG *tga, char *path);


//===============================================================================
//                SPRITE
//================================================================================

typedef struct _Sprite{
	int  id;
	char *path;
	bool powerTwo;
    int  count;
	int  width;
	int  height;
    int  texIDS[50];
}Sprite;




int   swGraphicsBindTexture(int width,int height,int bpp,byte *imageData);
void  swGraphicsSaveScreenShot(char *path,swImgType type);
char *swGraphicsGetCardVendor();

void swGraphicsBindSprite(Sprite *sprite,int index);
void swGraphicsUnBindSprite(Sprite *sprite);
void swGraphicsUpdateModelMatrix(float x,float y, float rot);
void swGraphicsRenderImg1(float tx, float ty, float tw, float th,float sx, float sy, float sw, float sh);
void swGraphicsRenderImg2(float tx, float ty, float tw, float th,float sx, float sy, float sw, float sh,float sW,float sH);



void swSpriteInit();
void swSpriteDeInit();
void swSpriteDestroy(Sprite *spr);
Sprite* swSpriteCreateFromFilePath(char *filePath);
Sprite* swSpriteCreateFromFolderPath(char *folderPath);
Sprite* swSpriteCreateFromSpesification(int width,int height,int iBytesPerPixel);
Sprite* swSpriteGetById(int id);
Sprite* swSpriteGetByPath(char *path);





//===============================================================================
//                FBO
//================================================================================
void swFBOInit();
void swFBODeInit();
int swFBOCreate(Sprite *spr);
void swFBODestroy(int id);
void swFBODisabled();
void swFBOEnabled(int id);
void swFBOClear();
int swFBOGetImgId(int id);



//===============================================================================
//                FONT
//================================================================================

typedef struct _Font{
	int id;
	int texID;
	int baseID;
	char *path;
}Font;

void   swFontInit();
void   swFontDeInit();
Font*  swFontCreate(char *filePath);
void   swFontDestroy(Font *font);
Font*  swFontGetById(int id);
Font*  swFontGetByPath(char *path);

//===============================================================================
//                SHADER
//================================================================================
int  swShaderLoad(char *vertFileName, char *fragFileName);
void swShaderActive(int program);
void swShaderChangeUniform1i(int program, char *name,int value);
void swShaderChangeUniform1f(int program, char *name,float val1);
void swShaderChangeUniform2f(int program, char *name,float val1,float val2);
void swShaderChangeUniform3f(int program, char *name,float val1, float val2, float val3);
void swShaderChangeUniform4f(int program, char *name,float val1, float val2, float val3, float val4);

//===============================================================================
//                IL(IMAGE LIBRARY)
//================================================================================
void swILInit();
void swILDeInit();
void swILLoadImage(IMG *tga,char *path);
void swILDeleteImage(IMG *tga);




#endif 