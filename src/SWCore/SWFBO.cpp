#include "SWCoreIn.h"

#include <gl/glew.h>		// Header File For The GLu32 Library
#include <gl/wglew.h>		// Header File For The GLu32 Library
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library


typedef struct _FBO{
	int  id;
	GLuint  glID;
	Sprite *sprite;
}FBO;



int fboListID=-1;
int fboIDCounter=0;


//-------------------------------------------------------------------------------------------
void swFBOInit(){
	fboListID=swLinkedListCreate();
}


//-------------------------------------------------------------------------------------------
void swFBODeInit(){
	swLinkedListClear(fboListID);
	swLinkedListDestroy(fboListID);
	fboListID=-1;
	fboIDCounter=0;
}

//-------------------------------------------------------------------------------------------
int swFBOCreate(Sprite *spr){
	FBO *fbo=(FBO*)malloc(sizeof(FBO));
	fbo->sprite=spr;
	glGenFramebuffersEXT(1, &fbo->glID);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo->glID); 
	
	// And attach it to the FBO so we can render to it
	GLint type=GL_TEXTURE_2D;
	if(!spr->powerTwo){
		type=GL_TEXTURE_RECTANGLE_ARB;
	}
		
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, type, fbo->sprite->texIDS[0], 0);
	GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
	if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
		exit(1);
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);	// Unbind the FBO for now
	fbo->id=fboIDCounter++;
	swLinkedListAdd(fboListID,fbo);
	return fbo->id;
 }


//-------------------------------------------------------------------------------------------
FBO *swFBOGet(int id){
	FBO *fbo=(FBO*)swLinkedListGetFirst(fboListID);
	while(fbo!=NULL){
		if(fbo->id==id){
			return fbo;
		}
		fbo=(FBO*)swLinkedListGetNext(fboListID);
	}
	return NULL;
}


//-------------------------------------------------------------------------------------------
void swFBODestroy(int id){
	FBO *fbo=swFBOGet(id);
	glDeleteFramebuffersEXT(1, &fbo->glID);
	swSpriteDestroy(fbo->sprite);
	free(fbo);
 }


//-------------------------------------------------------------------------------------------
void swFBOEnabled(int id){
	
		// First we bind the FBO so we can render to it
		FBO *fbo=swFBOGet(id);
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo->glID);
	
		// Save the view port and set it to the size of the texture
		glPushAttrib(GL_VIEWPORT_BIT);
		glViewport(0,0,fbo->sprite->width,fbo->sprite->height);
	
		//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//glClear(GL_COLOR_BUFFER_BIT);	// Clear Screen And Depth Buffer
		glLoadIdentity();

}


//-------------------------------------------------------------------------------------------
void swFBOClear(){
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
}


//-------------------------------------------------------------------------------------------
int swFBOGetImgId(int id){
	FBO *fbo=swFBOGet(id);
	return fbo->sprite->id;
}



//-------------------------------------------------------------------------------------------
void swFBODisabled(){
	// Restore old view port and set rendering back to default frame buffer
	glPopAttrib();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

