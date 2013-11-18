#include "SWCoreIn.h"


#include <windows.h>
#include <gl/glew.h>		// Header File For The GLu32 Library
#include <gl/wglew.h>		// Header File For The GLu32 Library
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library

typedef struct _Sampler{
	char *name;
	unsigned int index;
}Sampler;

typedef struct _Shader{
	int  ID;
	char *path;
	GLhandleARB program;
	Sampler *samplers;
	unsigned int nSamplers;
}Shader;


//-------------------------------------------------------------------------------------------
char *swShaderReadText(FILE *f) {

	char *text = NULL;
	int length = 0;
	if (f != NULL){
		fseek( f, 0, SEEK_END );
		length = ftell(f);
		rewind(f);
		if (length > 0) {
			text = (char *)malloc(sizeof(char) * (length+1));
			length = (int)fread(text,sizeof(char),length,f);
			text[length] = '\0';
		}	
		fclose(f);
	}

	return text;
}


//-------------------------------------------------------------------------------------------
int swShaderLoad(char *vertFileName, char *fragFileName) {
char *srcVert,*srcFrag;
FILE *file=NULL;
const char * vv;
const char * ff;
GLhandleARB progVert,progFrag,progShader;
	
	

		if(!swGraphicsIsSupportGLSL())
								return -1;

		//Create Vertex & Frag Shader Obj
		progVert = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
		progFrag = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);	
	
		//Load Vert Shader Text
		file=swFileSystemOpenFile(vertFileName, "rt");
		if(file==NULL)
			return 0;
		srcVert = swShaderReadText(file);

		//Load Frag Shader Text
		file=swFileSystemOpenFile(fragFileName, "rt");
		if(file==NULL)
			return 0;
		srcFrag= swShaderReadText(file);
	

		//Set Shader Text To ShaderObj Source
		vv=srcVert;
		ff=srcFrag;
		glShaderSourceARB(progVert, 1, &vv,NULL);
		glShaderSourceARB(progFrag, 1, &ff,NULL);
		free(srcVert);free(srcFrag);

		//Compile Vert & Frag Shader
		glCompileShaderARB(progVert);
		glCompileShaderARB(progFrag);
	
		//Create Program Shader
		progShader=glCreateProgramObjectARB();
		
		//Attach Program Shader with VertProg & FragProg 
		glAttachObjectARB(progShader,progVert);
		glAttachObjectARB(progShader,progFrag);
	
		//Link & Use ProgShader
		glLinkProgramARB(progShader);
		glUseProgramObjectARB(progShader);

		return progShader;
}





//-------------------------------------------------------------------------------------------
void swShaderActive(int program) {
	if(swGraphicsIsSupportGLSL()){
		glUseProgramObjectARB(program);
	}
}


//-------------------------------------------------------------------------------------------
void swShaderChangeUniform1i(int program, char *name,int val1){
	int location = glGetUniformLocation(program, name);
	assert(location >= 0);
	glUniform1i(location, val1);
}



//-------------------------------------------------------------------------------------------
void swShaderChangeUniform1f(int program, char *name,float val1){
	int location = glGetUniformLocation(program, name);
	assert(location >= 0);
	glUniform1f(location, val1);
}


//-------------------------------------------------------------------------------------------
void swShaderChangeUniform2f(int program, char *name,float val1,float val2){
	int location = glGetUniformLocation(program, name);
	assert(location >= 0);
	glUniform2f(location, val1,val2);
}


//-------------------------------------------------------------------------------------------
void swShaderChangeUniform3f(int program, char *name,float val1, float val2, float val3){
	int location = glGetUniformLocation(program, name);
	assert(location >= 0);
	glUniform3f(location,val1,val2,val3);
}


//-------------------------------------------------------------------------------------------
void swShaderChangeUniform4f(int program, char *name,float val1, float val2, float val3, float val4){
	int location = glGetUniformLocation(program, name);
	assert(location >= 0);
	glUniform4f(location,val1,val2,val3,val4);
}
