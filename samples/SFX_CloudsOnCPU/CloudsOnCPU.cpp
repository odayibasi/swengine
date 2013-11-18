#include "../../include/SWEngine.h"
#include <math.h>


//SWEngine
#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWGui.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    


//OpenGL
#include <gl/glew.h>		// Header File For The GLu32 Library
#include <gl/wglew.h>		// Header File For The GLu32 Library
#include <gl/gl.h>			// Header File For The OpenGL32 Library
#include <gl/glu.h>			// Header File For The GLu32 Library

#pragma comment (lib,"opengl32.lib")      
#pragma comment (lib,"glu32.lib")         
#pragma comment(lib, "glew32.lib")


swApplication cloudsOnCPU;




swKeyboardState keybState;

float map32[32 * 32];
float map256[256 * 256];

//-------------------------------------------------------------------------------------------
float Noise(int x, int y, int random)
{
	int n = x + y * 57 + random * 131;
	n = (n<<13) ^ n;
	return (1.0f - ( (n * (n * n * 15731 + 789221) +
		1376312589)&0x7fffffff)* 0.000000000931322574615478515625f);
}


//-------------------------------------------------------------------------------------------
void SetNoise(float  *map){
	float temp[34][34];
	int random=rand() % 5000;

	for (int y=1; y<33; y++) 
		for (int x=1; x<33; x++)
			temp[x][y] = 128.0f + Noise(x,  y,  random)*128.0f;

	for (int x=1; x<33; x++)
	{
		temp[0][x] = temp[32][x];
		temp[33][x] = temp[1][x];
		temp[x][0] = temp[x][32];
		temp[x][33] = temp[x][1];
	}
	temp[0][0] = temp[32][32];
	temp[33][33] = temp[1][1];
	temp[0][33] = temp[32][1];
	temp[33][0] = temp[1][32];

	for (int y=1; y<33; y++){
		for (int x=1; x<33; x++){
			float center = temp[x][y]/4.0f;
			float sides = (temp[x+1][y] + temp[x-1][y] + temp[x][y+1] + temp[x][y-1])/8.0f;
			float corners = (temp[x+1][y+1] + temp[x+1][y-1] + temp[x-1][y+1] + temp[x-1][y-1])/16.0f;

			map32[((x-1)*32) + (y-1)] = center + sides + corners;
		}
	}
}


//-------------------------------------------------------------------------------------------
float Interpolate(float x, float y, float  *map){
	int Xint = (int)x;
	int Yint = (int)y;

	float Xfrac = x - Xint;
	float Yfrac = y - Yint;

	int X0 = Xint % 32;
	int Y0 = Yint % 32;
	int X1 = (Xint + 1) % 32;
	int Y1 = (Yint + 1) % 32;

	float bot = map[X0*32 + Y0] + Xfrac * (map[X1*32 + Y0] - map[X0*32 + Y0]);
	float top = map[X0*32 + Y1] + Xfrac * (map[X1*32 +  Y1] - map[X0*32 + Y1]);

	return (bot + Yfrac * (top - bot));
}


//-------------------------------------------------------------------------------------------
void OverlapOctaves(float  *map32, float  *map256){
	for (int x=0; x<256*256; x++)
		map256[x] = 0;

		for (int octave=0; octave<4; octave++)
			for (int x=0; x<256; x++)
				for (int y=0; y<256; y++)
				{
					float scale = 1 / pow(2, 3-octave);
					float noise = Interpolate(x*scale, y*scale , map32);
					map256[(y*256) + x] += noise / pow(2, octave);
				}
}

//-------------------------------------------------------------------------------------------
void ExpFilter(float  *map)
{
	float cover = 20.0f;
	float sharpness = 0.95f;

	for (int x=0; x<256*256; x++)
	{
		float c = map[x] - (255.0f-cover);
		if (c<0)     c = 0;
		map[x] = 255.0f - ((float)(pow(sharpness, c))*255.0f);
	}
}




//-------------------------------------------------------------------------------------------
void DrawGLScene(){

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1,1,1);
		glLoadIdentity();
		OverlapOctaves(map32, map256);
		ExpFilter(map256);

		glTranslatef(300,300,0);
		char texture[256][256][3];       //Temporary array to hold texture RGB values 

		for(int i=0; i<256; i++)         //Set cloud color value to temporary array
			for(int j=0; j<256; j++) 
			{
				float color = map256[i*256+j]; 
				texture[i][j][0]=color;
				texture[i][j][1]=color;
				texture[i][j][2]=color;
			}

			unsigned int ID;                 //Generate an ID for texture binding                     
			glGenTextures(1, &ID);           //Texture binding 
			glBindTexture(GL_TEXTURE_2D, ID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, texture);

			glMatrixMode(GL_TEXTURE);        //Let's move the clouds from left to right
			static float x=200;    
			x+=0.01f;
			glTranslatef(x,0,0);

			float val=512;

			glEnable(GL_TEXTURE_2D);         //Render the cloud texture
			glBegin(GL_QUADS);
			glTexCoord2d(1,1); glVertex2f(0.5f*val, 0.5f*val);
			glTexCoord2d(0,1); glVertex2f(-0.5f*val, 0.5f*val);
			glTexCoord2d(0,0); glVertex2f(-0.5f*val, -0.5f*val);
			glTexCoord2d(1,0); glVertex2f(0.5f*val, -0.5f*val);
			glEnd(); 
		
}


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	swInputListenKeyboard(&keybState);
	swGraphicsBeginScene();
	DrawGLScene();
	swGraphicsEndScene();

	if(keybState.keyESCAPE){
		swEngineExit();
	}
}

//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 
	//Application Settings
	cloudsOnCPU.hInstance=hInstance;
	cloudsOnCPU.fullScreen=false;
	cloudsOnCPU.cursor=false;
	cloudsOnCPU.width=800;
	cloudsOnCPU.height=600;
	cloudsOnCPU.title="CloudsOnCPU";
	cloudsOnCPU.path="\\rsc\\CloudsOnCPU\\";
	cloudsOnCPU.appRun=GameLoop;

	//Application Execution
	swEngineInit(&cloudsOnCPU);
	SetNoise(map32);
	swEngineRun();
	swEngineExit();

	return 0;
}

