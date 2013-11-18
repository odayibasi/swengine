#include "../../include/SWEngine.h"
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    



swApplication audioPlayApp;
swKeyboardState keybState;

int apOggStreamSourceID=-1;
int apOggStreamBufferID=-1;

int apOggSourceID=-1;
int apOggBufferID=-1;

int  apWavSourceID=-1;
int  apWavBufferID=-1;

int apFontID=-1;




//-------------------------------------------------------------------------------------------
void listenKeybPressed(swKeyEnum key){

	if(key==SWKEY_1){
		swAudioPlaySource(apOggStreamSourceID);
	}

	if(key==SWKEY_2){
		swAudioPlaySource(apOggSourceID);
	}

	if(key==SWKEY_3){
		swAudioPlaySource(apWavSourceID);
	}


}



//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	//Input Handling
	swInputListenKeyboard(&keybState);
	swKeybBehaviourExecute(&keybState);
	
	//Listen Esc and Exit
	if(keybState.keyESCAPE){
		swEngineExit();
	}
	swGraphicsBeginScene();
		swGraphicsSetBgColor0(0,0,0.6);
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		swGraphicsSetColor0(1,1,1,1);

		swGraphicsRenderText(apFontID,0,12,50, 70,0,"Key 1   Restart Ogg Stream");
		swGraphicsRenderText(apFontID,0,12,50, 90,0,"Key 2   Restart Ogg");
		swGraphicsRenderText(apFontID,0,12,50,110,0,"Key 3   Restart Wav");
	swGraphicsEndScene();

	//Process Input 
	//Process System & AI
	//Rendering
}


//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){ 

	//Application Settings
	audioPlayApp.hInstance=hInstance;
	audioPlayApp.fullScreen=false;
	audioPlayApp.cursor=true;
	audioPlayApp.width=800;
	audioPlayApp.height=600;
	audioPlayApp.title="Audio Play";
	audioPlayApp.path="\\rsc\\AudioPlay\\";
	audioPlayApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&audioPlayApp);


	//Init My Application
	//Register KeybBehaviour Listener
	swKeybBehaviourListener keyListener;
	keyListener.typed=NULL;
	keyListener.pressed=listenKeybPressed;
	keyListener.released=NULL;
	swKeybBehaviourAdd(&keyListener);

	//Load Resource And Generate SWID
	apFontID=swGraphicsCreateFont("Font.tga");

	

	//OGG STREAM
	apOggStreamBufferID=swAudioCreateBuffer("BgMusic.ogg",SW_AUDIO_BUFFER_TYPE_OGG_STREAM);
	apOggStreamSourceID=swAudioCreateSource();
	swAudioBindSourceAndBuffer(apOggStreamSourceID,apOggStreamBufferID);
	swAudioPlaySource(apOggStreamSourceID);

	//OGG
	apOggSourceID=swAudioCreateSource();
	apOggBufferID=swAudioCreateBuffer("blizzard.ogg",SW_AUDIO_BUFFER_TYPE_OGG);

	swAudioSetSourceGain(apOggSourceID,5.0);
	swAudioSetSourceLoop(apOggSourceID,false);
	swAudioBindSourceAndBuffer(apOggSourceID,apOggBufferID);
	swAudioPlaySource(apOggSourceID);

	//WAV
	apWavSourceID=swAudioCreateSource();
	apWavBufferID=swAudioCreateBuffer("winged.wav",SW_AUDIO_BUFFER_TYPE_WAV);

	swAudioBindSourceAndBuffer(apWavSourceID,apWavBufferID);
	swAudioPlaySource(apWavSourceID);

	swEngineRun();
	swEngineExit();

	return 0;
}
