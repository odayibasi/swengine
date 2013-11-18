#include "SWCoreIn.h"
#include <gl/glew.h>		// Header File For The GLEW Library
#include <gl/gl.h>			// Header File For The OpenGL32 Library




//-------------------------------------------------------------------------------------------
DllExport int swGraphicsCreatePointSprite(char *filePath){
	Sprite *sprite=swSpriteCreateFromFilePath(filePath);
	return sprite->id;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsDestroyPointSprite(int pointSpriteID){
	Sprite *sprite=swSpriteGetById(pointSpriteID);
	swSpriteDestroy(sprite);
}


//-------------------------------------------------------------------------------------------
DllExport void swGraphicsRenderPointSprite0(int pointSpriteID,float pointSize,int count,swColor *colorS,swPoint* pointS){
	glPointSize(pointSize);
	Sprite *sprite=swSpriteGetById(pointSpriteID);
	swGraphicsBindSprite(sprite,0);

	glTexEnvf(GL_POINT_SPRITE_ARB,GL_COORD_REPLACE_ARB, GL_TRUE);
	glEnable(GL_POINT_SPRITE_ARB);
	glBegin(GL_POINTS);

	for(int i=0;i<count;i++){
		swColor c=colorS[i];
		swPoint p=pointS[i];
		glColor4f(c.r,c.g,c.b,c.a);
		glVertex2f(p.x,p.y);
	}

	glEnd();
	glDisable(GL_POINT_SPRITE_ARB);
	swGraphicsUnBindSprite(sprite);

} 


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointSprite1(int pointSpriteID,float pointSize,int count,swPointSprite *pointSprites){

	glPointSize(pointSize);
	Sprite *sprite=swSpriteGetById(pointSpriteID);
	swGraphicsBindSprite(sprite,0);

	glTexEnvf(GL_POINT_SPRITE_ARB,GL_COORD_REPLACE_ARB, GL_TRUE);
	glEnable(GL_POINT_SPRITE_ARB);
	glBegin(GL_POINTS);

	for(int i=0;i<count;i++){
		swPointSprite pointSprite=pointSprites[i];
		swPoint p=pointSprite.pos;
		swColor c=pointSprite.color;
		glColor4f(c.r,c.g,c.b,c.a);
		glVertex2f(p.x,p.y);
	}
	glEnd();
	glDisable(GL_POINT_SPRITE_ARB);
	swGraphicsUnBindSprite(sprite);

}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderPointSprite2(int pointSpriteID,float pointSize,int pointSpriteListID){

	glPointSize(pointSize);
	Sprite *sprite=swSpriteGetById(pointSpriteID);
	swGraphicsBindSprite(sprite,0);

	glTexEnvf(GL_POINT_SPRITE_ARB,GL_COORD_REPLACE_ARB, GL_TRUE);
	glEnable(GL_POINT_SPRITE_ARB);
	glBegin(GL_POINTS);

	swPointSprite* pointSprite=(swPointSprite*)swLinkedListGetFirst(pointSpriteListID);

	while(pointSprite!=NULL){
		swPoint p=pointSprite->pos;
		swColor c=pointSprite->color;
		glColor4f(c.r,c.g,c.b,c.a);
		glVertex2f(p.x,p.y);
		pointSprite=(swPointSprite*)swLinkedListGetNext(pointSpriteListID);

	}
	glEnd();
	glDisable(GL_POINT_SPRITE_ARB);
	swGraphicsUnBindSprite(sprite);
}
