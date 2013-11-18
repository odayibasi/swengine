#include "SWCoreIn.h"
#include <gl/glew.h>		// Header File For The GLu32 Library
#include <gl/wglew.h>		// Header File For The GLu32 Library
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library

int fontListID=-1;
int fontIDCounter=0;


//-------------------------------------------------------
void swFontInit(){
	fontListID=swLinkedListCreate();
}

//-------------------------------------------------------
void swFontDeInit(){
	Font *font=(Font*)swLinkedListGetFirst(fontListID);
	while(font!=NULL){
		glDeleteLists(font->baseID,256);
		font=(Font*)swLinkedListGetNext(fontListID);
	}
	swLinkedListClear(fontListID);
	swLinkedListDestroy(fontListID);
	fontListID=-1;
	fontIDCounter=0;
}


//-------------------------------------------------------
Font* swFontGetById(int id){
	Font *font=(Font*)swLinkedListGetFirst(fontListID);
	while(font!=NULL){
		if(font->id==id){
			return font;
		}
		font=(Font*)swLinkedListGetNext(fontListID);
	}
	return NULL;
}


//-------------------------------------------------------
Font* swFontGetByPath(char *path){
	Font *font=(Font*)swLinkedListGetFirst(fontListID);
	while(font!=NULL){
		if(swStringEquals(font->path,path)){
			return font;
		}
		font=(Font*)swLinkedListGetNext(fontListID);
	}
	return NULL;
}




//-------------------------------------------------------
Font* swFontCreate(char *filePath){

	Font* font=swFontGetByPath(filePath);
	if(font!=NULL){
		return font;
	}

	font=(Font*)malloc(sizeof(Font));
	font->id=fontIDCounter++;
	swLinkedListAdd(fontListID,font);

	IMG tga;
	swTGALoad(&tga,filePath);
	font->baseID=glGenLists(256);	
	font->texID=swGraphicsBindTexture(tga.width,tga.height,tga.bpp,tga.imageData);
	font->path=filePath;
	free(tga.imageData);

	// Creating 256 Display Lists
	glBindTexture(GL_TEXTURE_2D, font->texID);			// Select Our Font Texture
	for (int loop=0; loop<256; loop++)						// Loop Through All 256 Lists
	{
		float cx=(float)(loop%16)/16.0f;						// X Position Of Current Character
		float cy=(float)(loop/16)/16.0f;						// Y Position Of Current Character

		glNewList(font->baseID+loop,GL_COMPILE);				// Start Building A List
			glBegin(GL_QUADS);							// Use A Quad For Each Character
				glTexCoord2f(cx,1-cy-0.0625f);			// Texture Coord (Bottom Left)
				glVertex2i(0,0);						// Vertex Coord (Bottom Left)
				glTexCoord2f(cx+0.0625f,1-cy-0.0625f);	// Texture Coord (Bottom Right)
				glVertex2i(16,0);						// Vertex Coord (Bottom Right)
				glTexCoord2f(cx+0.0625f,1-cy);			// Texture Coord (Top Right)
				glVertex2i(16,16);						// Vertex Coord (Top Right)
				glTexCoord2f(cx,1-cy);					// Texture Coord (Top Left)
				glVertex2i(0,16);						// Vertex Coord (Top Left)
			glEnd();									// Done Building Our Quad (Character)
			glTranslated(10,0,0);						// Move To The Right Of The Character
		glEndList();									// Done Building The Display List
	}// Loop Until All 256 Are Built

	return font;
}

//-------------------------------------------------------
void  swFontDestroy(Font *font){
	swLinkedListDel(fontListID,font);
	glDeleteLists(font->baseID,256);
	free(font);
}





