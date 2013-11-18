#include "SWServicesIn.h"


int keybBLList=-1;
float   lastTypedTime=0;
float   typedSleepTime=0.1f;
bool    bCapsLock=false;
swKeyboardState prevKeybState;


//-------------------------------------------------------------------------------------------
DllExport void swKeybBehaviourInit(){
	keybBLList=swLinkedListCreate();
}


//-------------------------------------------------------------------------------------------
DllExport void swKeybBehaviourDeInit(){
	swLinkedListDestroy(keybBLList);
}


//-------------------------------------------------------------------------------------------
DllExport void swKeybBehaviourAdd(swKeybBehaviourListener *listener){
	swLinkedListAdd(keybBLList,listener);
}


//-------------------------------------------------------------------------------------------
DllExport void swKeybBehaviourDel(swKeybBehaviourListener *listener){
	swLinkedListDel(keybBLList,listener);
}


//-------------------------------------------------------------------------------------------
DllExport void swKeybBehaviourSetTypedSleepTime(float dTime){
	typedSleepTime=dTime;
}



//-------------------------------------------------------------------------------------------
char swKeybBehaviourConvert2Number(swKeyboardState *keybState){

	char typedChar=-1;

	if(keybState->key0){
		typedChar='0';				
	}else if(keybState->key1){
		typedChar='1';				
	}else if(keybState->key2){
		typedChar='2';				
	}else if(keybState->key3){
		typedChar='3';				
	}else if(keybState->key4){
		typedChar='4';				
	}else if(keybState->key5){
		typedChar='5';				
	}else if(keybState->key6){
		typedChar='6';				
	}else if(keybState->key7){
		typedChar='7';				
	}else if(keybState->key8){
		typedChar='8';				
	}else if(keybState->key9){
		typedChar='9';	
	}

	return typedChar;
}


//-------------------------------------------------------------------------------------------
char swKeybBehaviourConvert2Symbols(swKeyboardState *keybState){
	char typedChar=-1;

	if(keybState->key0){
		typedChar='=';				
	}else if(keybState->key1){
		typedChar='!';				
	}else if(keybState->key2){
		typedChar='\'';				
	}else if(keybState->key3){
		typedChar='^';				
	}else if(keybState->key4){
		typedChar='+';				
	}else if(keybState->key5){
		typedChar='%';				
	}else if(keybState->key6){
		typedChar='&';				
	}else if(keybState->key7){
		typedChar='/';				
	}else if(keybState->key8){
		typedChar='(';				
	}else if(keybState->key9){
		typedChar=')';
	}
	return typedChar;
}



//-------------------------------------------------------------------------------------------
char swKeybBehaviourConvert2LowerCase(swKeyboardState *keybState){

	char typedChar=-1;

	if(keybState->keyQ){
		typedChar='q';				
	}else if(keybState->keyW){
		typedChar='w';				
	}else if(keybState->keyE){
		typedChar='e';				
	}else if(keybState->keyR){
		typedChar='r';				
	}else if(keybState->keyT){
		typedChar='t';				
	}else if(keybState->keyY){
		typedChar='y';				
	}else if(keybState->keyU){
		typedChar='u';				
	}else if(keybState->keyI){
		typedChar='i';				
	}else if(keybState->keyO){
		typedChar='o';				
	}else if(keybState->keyP){
		typedChar='p';				
	}else if(keybState->keyA){
		typedChar='a';				
	}else if(keybState->keyS){
		typedChar='s';				
	}else if(keybState->keyD){
		typedChar='d';				
	}else if(keybState->keyF){
		typedChar='f';				
	}else if(keybState->keyG){
		typedChar='g';				
	}else if(keybState->keyH){
		typedChar='h';				
	}else if(keybState->keyJ){
		typedChar='j';				
	}else if(keybState->keyK){
		typedChar='k';				
	}else if(keybState->keyL){
		typedChar='l';				
	}else if(keybState->keyZ){
		typedChar='z';				
	}else if(keybState->keyX){
		typedChar='x';				
	}else if(keybState->keyC){
		typedChar='c';				
	}else if(keybState->keyV){
		typedChar='v';				
	}else if(keybState->keyB){
		typedChar='b';				
	}else if(keybState->keyN){
		typedChar='n';				
	}else if(keybState->keyM){
		typedChar='m';				
	}else if(keybState->keySPACE){
		typedChar=32;
	}else if(keybState->keySUBTRACT){
		typedChar='-';
	}

	return typedChar;

}


//-------------------------------------------------------------------------------------------
char swKeybBehaviourConvert2UpperCase(swKeyboardState *keybState){

	char typedChar=-1;

	if(keybState->keyQ){
		typedChar='Q';				
	}else if(keybState->keyW){
		typedChar='W';				
	}else if(keybState->keyE){
		typedChar='E';				
	}else if(keybState->keyR){
		typedChar='R';				
	}else if(keybState->keyT){
		typedChar='T';				
	}else if(keybState->keyY){
		typedChar='Y';				
	}else if(keybState->keyU){
		typedChar='U';				
	}else if(keybState->keyI){
		typedChar='I';				
	}else if(keybState->keyO){
		typedChar='O';				
	}else if(keybState->keyP){
		typedChar='P';				
	}else if(keybState->keyA){
		typedChar='A';				
	}else if(keybState->keyS){
		typedChar='S';				
	}else if(keybState->keyD){
		typedChar='D';				
	}else if(keybState->keyF){
		typedChar='F';				
	}else if(keybState->keyG){
		typedChar='G';				
	}else if(keybState->keyH){
		typedChar='H';				
	}else if(keybState->keyJ){
		typedChar='J';				
	}else if(keybState->keyK){
		typedChar='K';				
	}else if(keybState->keyL){
		typedChar='L';				
	}else if(keybState->keyZ){
		typedChar='Z';				
	}else if(keybState->keyX){
		typedChar='X';				
	}else if(keybState->keyC){
		typedChar='C';				
	}else if(keybState->keyV){
		typedChar='V';				
	}else if(keybState->keyB){
		typedChar='B';				
	}else if(keybState->keyN){
		typedChar='N';				
	}else if(keybState->keyM){
		typedChar='M';				
	}
	return typedChar;

}



//-------------------------------------------------------------------------------------------
char swKeybBehaviourGetTyped(swKeyboardState *keybState){

	char typedChar=-1;

	if(!keybState->keyCAPITAL && keybState->keyCAPITAL) bCapsLock=!bCapsLock;

	bool bShift=keybState->keyLSHIFT || keybState->keyRSHIFT;
	
	if((!bCapsLock && !bShift) || (bCapsLock && bShift)){
		typedChar=swKeybBehaviourConvert2LowerCase(keybState);
	}else{
		typedChar=swKeybBehaviourConvert2UpperCase(keybState);
	}

	if(typedChar!=-1)
		return typedChar;
	

	if(!bShift){
		typedChar=swKeybBehaviourConvert2Number(keybState);
	}else{
		typedChar=swKeybBehaviourConvert2Symbols(keybState);
	}
	return typedChar;

}


//-------------------------------------------------------------------------------------------
void  swKeybBehaviourFireTyped(char typedChar){
void(*typedFunc)(char typedChar);
	
	float currentSec=swSystemGetElapsedSeconds();
	if(typedChar!=-1){
		if(currentSec-lastTypedTime>typedSleepTime)
			lastTypedTime=currentSec;
		else
			typedChar=-1;
	}

	swKeybBehaviourListener *obj=(swKeybBehaviourListener*)swLinkedListGetFirst(keybBLList);
	while(obj!=NULL){
		if(obj->typed!=NULL && typedChar!=-1){
			typedFunc=obj->typed;
			(*typedFunc)(typedChar);
		}
		obj=(swKeybBehaviourListener*)swLinkedListGetNext(keybBLList);
	}
}


//-------------------------------------------------------------------------------------------
void  swKeybBehaviourFirePressed(swKeyEnum key){
void(*pressedFunc)(swKeyEnum key);
	swKeybBehaviourListener *obj=(swKeybBehaviourListener*)swLinkedListGetFirst(keybBLList);
	while(obj!=NULL){
		if(obj->pressed!=NULL){
			pressedFunc=obj->pressed;
			(*pressedFunc)(key);
		}
		obj=(swKeybBehaviourListener*)swLinkedListGetNext(keybBLList);
	}
}


//-------------------------------------------------------------------------------------------
void  swKeybBehaviourFireReleased(swKeyEnum key){
	void(*releasedFunc)(swKeyEnum key);
	swKeybBehaviourListener *obj=(swKeybBehaviourListener*)swLinkedListGetFirst(keybBLList);
	while(obj!=NULL){
		if(obj->released!=NULL){
			releasedFunc=obj->released;
			(*releasedFunc)(key);
		}
		obj=(swKeybBehaviourListener*)swLinkedListGetNext(keybBLList);
	}
}



//-------------------------------------------------------------------------------------------
void  swKeybBehaviourFireWhenPressedOrRelease(swKeyboardState *kState0,swKeyboardState *kState1,void (*fireFunc)(swKeyEnum)){


	if(!kState0->key0 && kState1->key0){
		(*fireFunc)(SWKEY_0);
	}else if(!kState0->key1 && kState1->key1){
		(*fireFunc)(SWKEY_1);
	}else if(!kState0->key2 && kState1->key2){
		(*fireFunc)(SWKEY_2);
	}else if(!kState0->key3 && kState1->key3){
		(*fireFunc)(SWKEY_3);
	}else if(!kState0->key4 && kState1->key4){
		(*fireFunc)(SWKEY_4);
	}else if(!kState0->key5 && kState1->key5){
		(*fireFunc)(SWKEY_5);
	}else if(!kState0->key6 && kState1->key6){
		(*fireFunc)(SWKEY_6);
	}else if(!kState0->key7 && kState1->key7){
		(*fireFunc)(SWKEY_7);
	}else if(!kState0->key8 && kState1->key8){
		(*fireFunc)(SWKEY_8);
	}else if(!kState0->key9 && kState1->key9){
		(*fireFunc)(SWKEY_9);

	}else if(!kState0->keyBACK && kState1->keyBACK){
		(*fireFunc)(SWKEY_BACKSPACE);
	}else if(!kState0->keyRETURN && kState1->keyRETURN){
		(*fireFunc)(SWKEY_RETURN);
	}else if(!kState0->keyUP && kState1->keyUP){
		(*fireFunc)(SWKEY_UP);	
	}else if(!kState0->keyDOWN && kState1->keyDOWN){
		(*fireFunc)(SWKEY_DOWN);	
	}
	
	
	else if(!kState0->keyF1 && kState1->keyF1){
		(*fireFunc)(SWKEY_F1);
	}else if(!kState0->keyF2 && kState1->keyF2){
		(*fireFunc)(SWKEY_F2);
	}else if(!kState0->keyF3 && kState1->keyF3){
		(*fireFunc)(SWKEY_F3);
	}else if(!kState0->keyF4 && kState1->keyF4){
		(*fireFunc)(SWKEY_F4);
	}else if(!kState0->keyF5 && kState1->keyF5){
		(*fireFunc)(SWKEY_F5);
	}else if(!kState0->keyF6 && kState1->keyF6){
		(*fireFunc)(SWKEY_F6);
	}else if(!kState0->keyF7 && kState1->keyF7){
		(*fireFunc)(SWKEY_F7);
	}else if(!kState0->keyF8 && kState1->keyF8){
		(*fireFunc)(SWKEY_F8);
	}else if(!kState0->keyF9 && kState1->keyF9){
		(*fireFunc)(SWKEY_F9);
	}else if(!kState0->keyF10 && kState1->keyF10){
		(*fireFunc)(SWKEY_F10);
	}else if(!kState0->keyF11 && kState1->keyF11){
		(*fireFunc)(SWKEY_F11);
	}else if(!kState0->keyF12 && kState1->keyF12){
		(*fireFunc)(SWKEY_F12);
	}else if(!kState0->keyF13 && kState1->keyF13){
		(*fireFunc)(SWKEY_F13);
	}else if(!kState0->keyF14 && kState1->keyF14){
		(*fireFunc)(SWKEY_F14);
	}else if(!kState0->keyF15 && kState1->keyF15){
		(*fireFunc)(SWKEY_F15);
	}


	else if(!kState0->keyA && kState1->keyA){
		(*fireFunc)(SWKEY_A);
	}else if(!kState0->keyB && kState1->keyB){
		(*fireFunc)(SWKEY_B);
	}else if(!kState0->keyC && kState1->keyC){
		(*fireFunc)(SWKEY_C);
	}else if(!kState0->keyD && kState1->keyD){
		(*fireFunc)(SWKEY_D);
	}else if(!kState0->keyE && kState1->keyE){
		(*fireFunc)(SWKEY_E);
	}else if(!kState0->keyF && kState1->keyF){
		(*fireFunc)(SWKEY_F);
	}else if(!kState0->keyG && kState1->keyG){
		(*fireFunc)(SWKEY_G);
	}else if(!kState0->keyH && kState1->keyH){
		(*fireFunc)(SWKEY_H);
	}else if(!kState0->keyI && kState1->keyI){
		(*fireFunc)(SWKEY_I);
	}else if(!kState0->keyJ && kState1->keyJ){
		(*fireFunc)(SWKEY_J);
	}else if(!kState0->keyK && kState1->keyK){
		(*fireFunc)(SWKEY_K);
	}else if(!kState0->keyL && kState1->keyL){
		(*fireFunc)(SWKEY_L);
	}else if(!kState0->keyM && kState1->keyM){
		(*fireFunc)(SWKEY_M);
	}else if(!kState0->keyN && kState1->keyN){
		(*fireFunc)(SWKEY_N);
	}else if(!kState0->keyO && kState1->keyO){
		(*fireFunc)(SWKEY_O);
	}else if(!kState0->keyP && kState1->keyP){
		(*fireFunc)(SWKEY_P);
	}else if(!kState0->keyR && kState1->keyR){
		(*fireFunc)(SWKEY_R);
	}else if(!kState0->keyS && kState1->keyS){
		(*fireFunc)(SWKEY_S);
	}else if(!kState0->keyT && kState1->keyT){
		(*fireFunc)(SWKEY_T);
	}else if(!kState0->keyU && kState1->keyU){
		(*fireFunc)(SWKEY_U);
	}else if(!kState0->keyV && kState1->keyV){
		(*fireFunc)(SWKEY_V);
	}else if(!kState0->keyY && kState1->keyY){
		(*fireFunc)(SWKEY_Y);
	}else if(!kState0->keyZ && kState1->keyZ){
		(*fireFunc)(SWKEY_Z);
	}else if(!kState0->keyQ && kState1->keyQ){
		(*fireFunc)(SWKEY_Q);
	}else if(!kState0->keyX && kState1->keyX){
		(*fireFunc)(SWKEY_X);
	}else if(!kState0->keyW && kState1->keyW){
		(*fireFunc)(SWKEY_W);
	}
	else if(!kState0->keyPAUSE && kState1->keyPAUSE){
		(*fireFunc)(SWKEY_PAUSE);
	}


}



//-------------------------------------------------------------------------------------------
DllExport void  swKeybBehaviourExecute(swKeyboardState *keybState){
	swKeybBehaviourFireTyped(swKeybBehaviourGetTyped(keybState));
	swKeybBehaviourFireWhenPressedOrRelease(&prevKeybState,keybState,swKeybBehaviourFirePressed);
	swKeybBehaviourFireWhenPressedOrRelease(keybState,&prevKeybState,swKeybBehaviourFireReleased);
	prevKeybState=(*keybState);
}
