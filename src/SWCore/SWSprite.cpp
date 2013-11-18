#include "SWCoreIn.h"

#include <gl/gl.h>			// Header File For The OpenGL32 Library


int sprList=-1;
int sprCounter=0;


//-------------------------------------------------------
void swSpriteInit(){
	sprList=swLinkedListCreate();
}

//-------------------------------------------------------
void swSpriteDeInit(){
	Sprite *spr=(Sprite*)swLinkedListGetFirst(sprList);
	while(spr!=NULL){
	    glDeleteTextures(spr->count,(GLuint*)spr->texIDS);
		spr=(Sprite*)swLinkedListGetNext(sprList);
	}

	swLinkedListClear(sprList);
	swLinkedListDestroy(sprList);
	sprCounter=0;
}


//-------------------------------------------------------
Sprite* swSpriteCreateFromFilePath(char *filePath){
	
	Sprite* spr=swSpriteGetByPath(filePath);
	if(spr!=NULL){
		return spr;
	}

	//Load Image
	IMG img;
	swILLoadImage(&img,filePath);

	
	spr=(Sprite*)malloc(sizeof(Sprite));
	spr->id=sprCounter++;
	spr->path=filePath;
	spr->count=1;
	swLinkedListAdd(sprList,spr);
	spr->width=img.width; spr->height=img.height;
	spr->texIDS[0]=swGraphicsBindTexture(img.width,img.height,img.bpp,img.imageData);
	spr->powerTwo=swMathIsPowerTwo((float)img.width) && swMathIsPowerTwo((float)img.height);
	swILDeleteImage(&img);
	return spr;
}

//-------------------------------------------------------
Sprite* swSpriteCreateFromFolderPath(char *folderPath){
	Sprite* spr=swSpriteGetByPath(folderPath);
	if(spr!=NULL){
		return spr;
	}

	spr=(Sprite*)malloc(sizeof(Sprite));
	spr->id=sprCounter++;
	spr->path=folderPath;
	swLinkedListAdd(sprList,spr);

	//Load TGA
	int filesListID=swLinkedListCreate();
	swFileSystemQueryFiles(folderPath,filesListID,"");
	spr->count=swLinkedListSize(filesListID);

	IMG img;
	int  imgId=0;
	char filePath[MAX_PATH];
	char* imgName=(char*)swLinkedListGetFirst(filesListID);
	while(imgName!=NULL){
		swStringCopy(filePath,folderPath);
		swStringConcat1(filePath,imgName);
		swILLoadImage(&img,filePath);
		spr->width=img.width; spr->height=img.height;
		spr->texIDS[imgId++]=swGraphicsBindTexture(img.width,img.height,img.bpp,img.imageData);
		spr->powerTwo=swMathIsPowerTwo((float)img.width) && swMathIsPowerTwo((float)img.height);
		swILDeleteImage(&img);
		imgName=(char*)swLinkedListGetNext(filesListID);
	}
	swLinkedListDestroy(filesListID);
	return spr;
}



//-------------------------------------------------------
Sprite* swSpriteCreateFromSpesification(int width,int height,int bpp){
	Sprite *spr=(Sprite*)malloc(sizeof(Sprite));
	spr->id=sprCounter++;
	spr->path=NULL;
	spr->count=1;
	swLinkedListAdd(sprList,spr);

	spr->width=width; spr->height=height;
	spr->texIDS[0]=swGraphicsBindTexture(width,height,bpp,NULL);
	spr->powerTwo=swMathIsPowerTwo((float)width) && swMathIsPowerTwo((float)height);
	return spr;
}



//-------------------------------------------------------
void swSpriteDestroy(Sprite *spr){
	glDeleteTextures(spr->count,(GLuint*)spr->texIDS);
	swLinkedListDel(sprList,spr);
	free(spr);
}


//-------------------------------------------------------
Sprite* swSpriteGetById(int id){
	Sprite *spr=(Sprite*)swLinkedListGetFirst(sprList);
	while(spr!=NULL){
		if(spr->id==id){
			return spr;
		}
		spr=(Sprite*)swLinkedListGetNext(sprList);
	}
	return NULL;
}

//-------------------------------------------------------
Sprite* swSpriteGetByPath(char *path){
	Sprite *spr=(Sprite*)swLinkedListGetFirst(sprList);
	while(spr!=NULL){
		if(swStringEquals(spr->path,path)){
			return spr;
		}
		spr=(Sprite*)swLinkedListGetNext(sprList);
	}
	return NULL;
}
