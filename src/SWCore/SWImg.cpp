#include "SWCoreIn.h"

typedef struct _ImgBuffer{
   IMG tga;
}ImgBuffer;

ImgBuffer imgBuffer;

//-------------------------------------------------------------------------------------------
DllExport void swImgBufferLoad(char *path,swImgType imgType){
	swTGALoad(&imgBuffer.tga,path);
}

//-------------------------------------------------------------------------------------------
DllExport void swImgBufferFree(){
	free(imgBuffer.tga.imageData);
}

//-------------------------------------------------------------------------------------------
DllExport int swImgBufferGetWidth(){
	return imgBuffer.tga.width;
}

//-------------------------------------------------------------------------------------------
DllExport int swImgBufferGetHeight(){
	return imgBuffer.tga.height;
}

//-------------------------------------------------------------------------------------------
DllExport void swImgBufferGetPixel(int x,int y,swColor *color){
	IMG *tga=&imgBuffer.tga;
	int loc=((tga->width*y)+x)*tga->bpp;
	color->r=(float)(tga->imageData[loc]/255.0f);
	color->g=(float)(tga->imageData[loc+1]/255.0f);
	color->b=(float)(tga->imageData[loc+2]/255.0f);
	if(tga->bpp==4) color->a=(float)(tga->imageData[loc+2]/255.0f);
	else color->a=0.0f;
}