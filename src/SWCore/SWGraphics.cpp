#include "SWCoreIn.h"

#pragma comment (lib,"opengl32.lib")      
#pragma comment (lib,"glu32.lib")         
#pragma comment(lib, "glew32.lib")

#include <gl/glew.h>		// Header File For The GLu32 Library
#include <gl/wglew.h>		// Header File For The GLu32 Library
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library
#include <math.h>


HGLRC			renderingContext;
bool			GLSLSupport=false;
bool			RectTexSupport=false;
bool			PointSpriteSupport=false;
bool            FBOSupport=false;

swPoint			camPos={0,0};
float			camRot=0;
float			camZoom=1.0f;
swPoint			defaultWeight={0.5,0.5};
swRect			defaultSource={0,0,1,1};
swBlendingMode	activeBlendingMode=SW_BLENDING_MODE_NONE;
bool			uvScrollingActive=false;


//-------------------------------------------------------------------------------------------
void swGraphicsBindDCToRC(HDC deviceContext){
	renderingContext=wglCreateContext(deviceContext);
	wglMakeCurrent(deviceContext,renderingContext);
}

//-------------------------------------------------------------------------------------------
void swGraphicsUnBindDCToRC(){
 	if(renderingContext){
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(renderingContext);
	}
}


//-------------------------------------------------------------------------------------------
void swGraphicsInitExtensions(){
	glewInit();
	GLSLSupport=GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader;
	PointSpriteSupport=GLEW_ARB_point_sprite;
	RectTexSupport=GLEW_ARB_texture_rectangle;
	FBOSupport=GLEW_EXT_framebuffer_object;
	
}

//-------------------------------------------------------------------------------------------
DllExport bool swGraphicsIsSupportGLSL(){
	return GLSLSupport;
}

//-------------------------------------------------------------------------------------------
DllExport bool swGraphicsIsSupportRectTex(){
	return RectTexSupport;
}

//-------------------------------------------------------------------------------------------
DllExport bool swGraphicsIsSupportPointSprite(){
	return PointSpriteSupport;
}

//-------------------------------------------------------------------------------------------
DllExport bool swGraphicsIsSupportFBOSupport(){
	return FBOSupport;
}

//-------------------------------------------------------------------------------------------
DllExport int swGraphicsCreateGLSLShader(char *pathVertShader,char *pathFragShader){
	return swShaderLoad(pathVertShader,pathFragShader);
}

//-------------------------------------------------------------------------------------------
DllExport void swGraphicsActiveGLSLShader(int shaderID){
	swShaderActive(shaderID);
}

//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetGLSLShaderIntAttrb(int program, char *name,int value){
	swShaderChangeUniform1i(program,name,value);	
}

//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetGLSLShaderFloatAttrb(int program, char *name,float value){
	swShaderChangeUniform1f(program,name,value);	
}

//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetGLSLShaderVec2Attrb(int program, char *name,swVec2 vec2){
	swShaderChangeUniform2f(program,name,vec2.x,vec2.y);	
}

//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetGLSLShaderPointAttrb(int program, char *name,swPoint point){
	swShaderChangeUniform2f(program,name,point.x,point.y);	
}

//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetGLSLShaderDimensionAttrb(int program, char *name,swDimension dim){
	swShaderChangeUniform2f(program,name,dim.w,dim.h);	
}

//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetGLSLShaderColorAttrb(int program, char *name,swColor color){
	swShaderChangeUniform4f(program,name,color.r,color.g,color.b,color.a);	
}


//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetGLSLShaderRectAttrb(int program, char *name,swRect rect){
	swShaderChangeUniform4f(program,name,rect.x,rect.y,rect.w,rect.h);	
}


//-------------------------------------------------------------------------------------------
void swGraphicsInitViewport(){
	glViewport(0,0,swWindowGetWidth(),swWindowGetHeight());
}


//-------------------------------------------------------------------------------------------
void swGraphicsInitProjection(){

	if(camZoom<=0)
		return;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,swWindowGetWidth()/camZoom,0,swWindowGetHeight()/camZoom);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//-------------------------------------------------------------------------------------------
int swGraphicsBindTexture(int width,int height,int bpp,byte *imageData){     

	//Color Type
	int colorType=GL_RGB;
	if(bpp==3)
		colorType=GL_RGB;
	else if(bpp==4)
		colorType=GL_RGBA;

	//PowerTwo
	bool bPowerTwo=(swMathIsPowerTwo((float)width) && swMathIsPowerTwo((float)height));
	int  texType;
	if(bPowerTwo==true)
		texType=GL_TEXTURE_2D;  
	else
		texType=GL_TEXTURE_RECTANGLE_ARB;

	GLuint texID;

	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glGenTextures(1, &texID);						
	glBindTexture(texType,texID);	

	glTexParameterf(texType, GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameterf(texType, GL_TEXTURE_MAG_FILTER,GL_LINEAR);     

	glTexParameterf(texType, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
	glTexParameterf(texType, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);     


	glTexImage2D(texType,0,colorType,width,height, 0,colorType, GL_UNSIGNED_BYTE,imageData);
	return texID;
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsInit(){
	swGraphicsBindDCToRC(swWindowGetDC());
	swGraphicsInitExtensions();
	swGraphicsInitViewport();
	swGraphicsInitProjection();
	swSpriteInit();
	swFontInit();
	swFBOInit();
	swCamInit();
	swILInit();

}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsDeInit(){
	swILDeInit();
	swCamDeInit();
	swFBODeInit();
	swFontDeInit();
	swSpriteDeInit();
	swGraphicsUnBindDCToRC();
}



//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsBeginScene(){
	glClear(GL_COLOR_BUFFER_BIT);
	swGraphicsSetColor0(0,0,0,0);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
}  

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsEndScene(){
	glFinish();
	swWindowSwap();
}


//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetBgColor0(float r,float g,float b){
	glClearColor(r,g,b,0);
}


//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetBgColor1(float r,float g,float b,float a){
	glClearColor(r,g,b,a);
}


//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetBgColor2(swColor *bgColor){
	glClearColor(bgColor->r,bgColor->g,bgColor->b,bgColor->a);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsSetColor0(float r,float g,float b,float a){
	glColor4f(r,g,b,a);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsSetColor1(swColor *c){
	swGraphicsSetColor0(c->r,c->g,c->b,c->a);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsSetBlendingMode(swBlendingMode mode){
	
	activeBlendingMode=mode;
	if(mode==SW_BLENDING_MODE_NONE){
		glDisable(GL_BLEND);
	}else{
		glEnable(GL_BLEND);
		switch(mode){
			case SW_BLENDING_MODE_ADDITIVE:
				glBlendFunc(GL_ONE,GL_ONE);
				break;
			case SW_BLENDING_MODE_SKETCH:
				glBlendFunc(GL_ONE_MINUS_DST_COLOR,GL_ONE);
				break;
			case SW_BLENDING_MODE_SOLID:
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				break;
			case SW_BLENDING_MODE_ADDITIVE_ACCORDING2_ALPHA:
				glBlendFunc(GL_SRC_ALPHA,GL_ONE);
				break;			
			default:
				glDisable(GL_BLEND);
				break;
		}
	}
}


//-------------------------------------------------------------------------------------------
DllExport swBlendingMode swGraphicsGetBlendingMode(){
	return activeBlendingMode;
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsSetRenderingTarget(int targetID){
	if(targetID==SW_RENDERING_TARGET_DEFAULT){
		swFBODisabled();
	}else{
		swFBOEnabled(targetID);
	}
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsClearRenderingTarget(){
	swFBOClear();
}

//-------------------------------------------------------------------------------------------
DllExport int  swGraphicsCreateRenderingTarget(int width, int height, int iBytesPerPixel){
	Sprite *spr=swSpriteCreateFromSpesification(width,height,iBytesPerPixel);
	return swFBOCreate(spr);
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsDestroyRenderingTarget(int targetID){
	swFBODestroy(targetID);
}


//-------------------------------------------------------------------------------------------
DllExport int   swGraphicsRenderingTargetGetImgID(int targetID){
	return swFBOGetImgId(targetID);
}


//-------------------------------------------------------------------------------------------
void swGraphicsUpdateViewMatrix(){
Mat4x4 camTM;
	swMat4x4Reset(&camTM);
	swTransformInit(&camTM);
	swTransformSetLocation(-camPos.x,-camPos.y,0);
	swTransformRotateZ(camRot);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(camTM.index);
}


//-------------------------------------------------------------------------------------------
DllExport void swGraphicsActiveCam(int camID){
	swCam *cam=swCamGet(camID);
	if(camZoom!=cam->zoom){
		camZoom=cam->zoom;
		swGraphicsInitProjection();
	}
	camPos.x=cam->x;
	camPos.y=cam->y;
	camRot=cam->rot;
	swGraphicsUpdateViewMatrix();
}


//-------------------------------------------------------------------------------------------
void swGraphicsUpdateModelMatrix(float x,float y, float rot){
	Mat4x4 objTM;
	swMat4x4Reset(&objTM);
	swTransformInit(&objTM);
	swTransformRotateZ(rot);
	swTransformSetLocation(x,y,0);
	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(objTM.index);
}


//-------------------------------------------------------------------------------------------
DllExport int swGraphicsCreateImg(char *filePath){
    Sprite *sprite=swSpriteCreateFromFilePath(filePath);
	return sprite->id;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsDestroyImg(int imgID){
	Sprite *sprite=swSpriteGetById(imgID);
	swSpriteDestroy(sprite);
}


//-------------------------------------------------------------------------------------------
void swGraphicsBindSprite(Sprite *sprite,int index){
	int texType;
	if(sprite->powerTwo)
		texType=GL_TEXTURE_2D;
	else
		texType=GL_TEXTURE_RECTANGLE_ARB;

	glEnable(texType);
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(texType,sprite->texIDS[index]);
}


//-------------------------------------------------------------------------------------------
void swGraphicsUnBindSprite(Sprite *sprite){
	int texType;
	if(sprite->powerTwo)
		texType=GL_TEXTURE_2D;
	else
		texType=GL_TEXTURE_RECTANGLE_ARB;

	glDisable(texType);
}

//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetImgUVScrollable(int imgID,bool bEnabled){
	Sprite *sprite=swSpriteGetById(imgID);
	swGraphicsBindSprite(sprite,0);	
	int texType=sprite->powerTwo ? GL_TEXTURE_2D : GL_TEXTURE_RECTANGLE_ARB;
	if(bEnabled){
		glTexParameterf(texType, GL_TEXTURE_WRAP_S,GL_REPEAT);	
		glTexParameterf(texType, GL_TEXTURE_WRAP_T,GL_REPEAT);     
	}else{
		glTexParameterf(texType, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
		glTexParameterf(texType, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);     
	}
	swGraphicsUnBindSprite(sprite);
}


//-------------------------------------------------------------------------------------------
DllExport void swGraphicsSetSpriteUVScrollable(int spriteID,bool bEnabled){
	Sprite *sprite=swSpriteGetById(spriteID);
	int texType=sprite->powerTwo ? GL_TEXTURE_2D : GL_TEXTURE_RECTANGLE_ARB;
	int count=swGraphicsGetCountOfImgInSprite(spriteID);
	
	for(int i=0;i<count;i++){
		swGraphicsBindSprite(sprite,i);	
		if(bEnabled){
			glTexParameterf(texType, GL_TEXTURE_WRAP_S,GL_REPEAT);	
			glTexParameterf(texType, GL_TEXTURE_WRAP_T,GL_REPEAT);     
		}else{
			glTexParameterf(texType, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);	
			glTexParameterf(texType, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);     
		}
	}
	swGraphicsUnBindSprite(sprite);
}




//-------------------------------------------------------------------------------------------
DllExport int  swGraphicsCreateSprite(char *folderPath){
	Sprite *sprite=swSpriteCreateFromFolderPath(folderPath);
	return sprite->id;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsDestroySprite(int spriteID){
	Sprite *sprite=swSpriteGetById(spriteID);
	swSpriteDestroy(sprite);
}


//-------------------------------------------------------------------------------------------
DllExport int  swGraphicsGetCountOfImgInSprite(int spriteID){
	Sprite *sprite=swSpriteGetById(spriteID);
	return sprite->count;
}



//-------------------------------------------------------------------------------------------
DllExport int   swGraphicsCreateFont(char *filePath){
	Font *font=swFontCreate(filePath);
	return font->id;
}  

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsDestroyFont(int fontID){
	Font *font=swFontGetById(fontID);
	swFontDestroy(font);
}  

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsRenderText(int fontID,int set,float size,float x,float y,float rot,char *string,...){
	Font *font=swFontGetById(fontID);

	if (set>1)
		set=1;

	char text[256];								
	va_list ap;										

	va_start(ap, string);									
	vsprintf(text, string, ap);						
	va_end(ap);				

	int count=swStringGetLength(text);
	for(int i=0;i<count;i++){
		switch(text[i]){
			case -16: //ð
				text[i]=129;
				break;
			case -48: //Ð
				text[i]=128;
				break;
			case -4: //ü
				text[i]=131;
				break;
			case -36: //Ü
				text[i]=130;
				break;
			case -2: //þ
				text[i]=133;
				break;
			case -34: //Þ
				text[i]=132;
				break;
			case -3: //i
				text[i]=135;
				break;
			case -35: //Ý
				text[i]=134;
				break;
			case -10: //ö
				text[i]=137;
				break;
			case -42: //Ö
				text[i]=136;
				break;
			case -25: //ç
				text[i]=138;
				break;
			case -57: //Ç
				text[i]=139;
				break;
			default:
				break;
		}
	}



	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, font->texID);			
  	glPushMatrix();
		glRotatef(rot,0,0,1);
		glTranslatef(x,y,0);
		glScalef(size/16,size/16,1);
		glListBase(font->baseID-32+(128*set));				// Choose The Font Set (0 or 1)
		glCallLists(count,GL_UNSIGNED_BYTE,text);			// Write The Text To The Screen
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}





//-------------------------------------------------------------------------------------------
void  swGraphicsSaveScreenShot(char *path,swImgType type){
	unsigned char *outputImage = 0;

	// Allocate the neccessary memory.
	int w=swWindowGetWidth();
	int h=swWindowGetHeight();
	outputImage = (unsigned char*)malloc(w * h * 3);

	// Clear the variable.
	memset(outputImage, 0, w * h * 3);

	// You use the glReadPixels() to read every pixel on the screen
	// that you specify.  You must use one less than each size.
	glReadPixels(0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, outputImage);


	swTGASave(path,(short int)w,(short int)h,outputImage);
}



//-------------------------------------------------------------------------------------------
char *swGraphicsGetCardVendor(){
	return (char *)glGetString(GL_VENDOR);
}

