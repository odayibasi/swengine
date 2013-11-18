#include "SWCoreIn.h"
#include <il/il.h>
#include <il/ilu.h>
#include <il/ilut.h>

#pragma comment (lib,"DevIL.lib")   
#pragma comment (lib,"ILU.lib")   
#pragma comment (lib,"ILUT.lib")   

//-------------------------------------------------------------------------------------------
void swILInit(){

	bool ilVersionNOK=ilGetInteger(IL_VERSION_NUM) < IL_VERSION ;
	bool iluVesionNOK=iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION; 
	bool ilutVersionNOK=ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION;
	if(ilVersionNOK || iluVesionNOK ||ilutVersionNOK){
		printf("DevIL version is different...exiting!\n");
	}
  	ilInit(); /* Initialization of DevIL */

	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilEnable(IL_ORIGIN_SET);

}

//-------------------------------------------------------------------------------------------
void swILDeInit(){

}



//-------------------------------------------------------------------------------------------
void swILLoadImage(IMG *img,char *path){
	ILboolean success; 
	char fsFullPath[MAX_PATH];

	swStringCopy(fsFullPath,swFileSystemGetResourcePath());
	swStringConcat1(fsFullPath,path);
	ilGenImages(1, &img->ilID); /* Generation of one image name */
	ilBindImage(img->ilID); /* Binding of image name */
	success = ilLoadImage(fsFullPath); /* Loading of image "image.jpg" */

	if (success){
		img->bpp=ilGetInteger(IL_IMAGE_BPP);
		img->height=ilGetInteger(IL_IMAGE_HEIGHT);
		img->width=ilGetInteger(IL_IMAGE_WIDTH);
		if(img->bpp==4){
			success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); 
		}else{
			success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE); 
		}
		img->imageData=	ilGetData();
	}
}


//-------------------------------------------------------------------------------------------
void swILDeleteImage(IMG *img){
	ilDeleteImages(1, &img->ilID); /* Because we have already copied image data into texture data
							   we can release memory used by image. */
}
