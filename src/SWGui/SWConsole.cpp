#include "SWGuiIn.h"



#define MAX_CHAR_INSTR 64 
#define CMD_TAG_LEN	   8 


typedef struct _swConsoleStr{
	char str[MAX_CHAR_INSTR];	
}swConsoleStr;


int			consoleFontID=0;
int			consoleFontSet=0;
float		consoleFontSize=0;
swColor		*consoleFontColor=NULL;
swColor		*consoleBgColor=NULL;
swRect		consoleTarget;
int			consoleLayer;
bool		consoleVisible=false;
int			consoleDispID=-1;
int         consoleStrNo=0;
swKeybBehaviourListener consoleKeyListener;


int         consoleStrList=-1;
int			char_counter;
swConsoleStr *activeStr=NULL;



//-------------------------------------------------------------------------------------------
DllExport void swConsoleSetFont(int fontID,int set,swColor *color,float size){
	consoleFontID=fontID;
	consoleFontSet=set;
	consoleFontColor=color;
	consoleFontSize=size;
}

//-------------------------------------------------------------------------------------------
DllExport void swConsoleSetBgColor(swColor *color){
	consoleBgColor=color;
}


//-------------------------------------------------------------------------------------------
DllExport void swConsoleSetPos(float x,float y){
	consoleTarget.x=x;
	consoleTarget.y=y;
}


//-------------------------------------------------------------------------------------------
DllExport void swConsoleSetLayer(int layer){
	consoleLayer=layer;
}


//-------------------------------------------------------------------------------------------
DllExport void swConsoleSetSize(float w,float h){
	consoleTarget.w=w;
	consoleTarget.h=h;
}


//-------------------------------------------------------------------------------------------
DllExport void swConsoleSetVisible(bool bVisible){
	consoleVisible=bVisible;
}


//-------------------------------------------------------------------------------------------
void swConsoleCreateNewStr(){
	activeStr=(swConsoleStr *)malloc(sizeof(swConsoleStr));
	swLinkedListAdd(consoleStrList,activeStr);	
	char_counter=CMD_TAG_LEN;
}

//-------------------------------------------------------------------------------------------
DllExport void swConsolePrint(char *string,...){
	swConsoleCreateNewStr();
	va_list ap;										
	va_start(ap, string);									
	vsprintf(activeStr->str, string, ap);						
	va_end(ap);				
}


//-------------------------------------------------------------------------------------------
void swConsoleAddCommandTagToActiveStr(){
char cmdTag[9]="COMMAND>";
	swStringCopy(activeStr->str,cmdTag);
}

//-------------------------------------------------------------------------------------------
DllExport void swConsoleClear(){
	swConsoleStr *str=(swConsoleStr *)swLinkedListGetFirst(consoleStrList);
	while(str!=NULL){
		swConsoleStr* delStr=str; 
		str=(swConsoleStr *)swLinkedListGetNext(consoleStrList);
		swLinkedListDel(consoleStrList,delStr);
		free(delStr);
	}
	swConsoleCreateNewStr();
	swConsoleAddCommandTagToActiveStr();
}



//-------------------------------------------------------------------------------------------
void swConsoleAddCommandChar(char c){
	if(char_counter<MAX_CHAR_INSTR-1){
		activeStr->str[char_counter]=c;
		activeStr->str[char_counter+1]='\0';
		char_counter++;
	}
}


//-------------------------------------------------------------------------------------------
void swConsoleDeleteCommandChar(){
	if(char_counter>CMD_TAG_LEN){
		activeStr->str[char_counter-1]=32;//Space(Bosluk) = 32,0x20 
		char_counter--;
	}
}

//-------------------------------------------------------------------------------------------
void swConsoleGoToPrevStr(){
	if(consoleStrNo>0)
		consoleStrNo--;

}

//-------------------------------------------------------------------------------------------
void swConsoleGoToNextStr(){
	if(consoleStrNo<swLinkedListSize(consoleStrList)-1)
		consoleStrNo++;
}


//-------------------------------------------------------------------------------------------
void swConsoleDisplayLayout(){
		swGraphicsSetColor1(consoleBgColor);
		swGraphicsRenderSolidRect2(&consoleTarget);
		swGraphicsSetColor1(&SWCOLOR_GRAY);
		swGraphicsRenderLineRect2(&consoleTarget,2);
}


//-------------------------------------------------------------------------------------------
void swConsoleDisplayContext(){

	int strNo=0;

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor1(consoleFontColor);
	swConsoleStr *str=(swConsoleStr *)swLinkedListGetFirst(consoleStrList);
	while(str!=NULL){
		strNo++;
		if(strNo>consoleStrNo){
			float x=consoleTarget.x+20;
			float y=swRectYPlusH(&consoleTarget)+(consoleStrNo-strNo)*(consoleFontSize+5);
			swGraphicsRenderText(consoleFontID,consoleFontSet,consoleFontSize,x,y,0,str->str);
		}
		str=(swConsoleStr *)swLinkedListGetNext(consoleStrList);
	}
	swGraphicsRenderText(consoleFontID,1,12,swRectXPlusW(&consoleTarget)-60,swRectYPlusH(&consoleTarget)-20,0,"StrNo=%i",consoleStrNo);
	swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
}

//-------------------------------------------------------------------------------------------
void swConsoleDisplay(void *obj){

	swConsoleDisplayLayout();
	swConsoleDisplayContext();
}

//-------------------------------------------------------------------------------------------
void swConsoleKeyPressed(swKeyEnum key){

char cmdExec[MAX_CHAR_INSTR];

	switch(key){
		case SWKEY_RETURN:
			swConsoleAddCommandChar('\0');
			swStringCopyEx(cmdExec,activeStr->str,8,swStringGetLength(activeStr->str));
			swDSLExecuteCommand(cmdExec);
			swConsoleCreateNewStr();
			swConsoleAddCommandTagToActiveStr();
			break;

		case SWKEY_BACKSPACE:
			swConsoleDeleteCommandChar();
			break;

		case SWKEY_UP:
			swConsoleGoToPrevStr();
			break;

		case SWKEY_DOWN:
			swConsoleGoToNextStr();
			break;

	}
}


//-------------------------------------------------------------------------------------------
DllExport void swConsoleInit(){
	consoleStrList=swLinkedListCreate();
	consoleDispID=swDispManagerAdd(swConsoleDisplay,NULL,&consoleVisible,NULL,&consoleLayer);
	consoleKeyListener.typed=swConsoleAddCommandChar;
	consoleKeyListener.pressed=swConsoleKeyPressed;
	consoleKeyListener.released=NULL;
	swKeybBehaviourAdd(&consoleKeyListener);
	swConsoleCreateNewStr();
	swConsoleAddCommandTagToActiveStr();

}

//-------------------------------------------------------------------------------------------
DllExport void swConsoleDeInit(){
	swKeybBehaviourDel(&consoleKeyListener);
	swDispManagerDel(consoleDispID);
	swLinkedListDestroy(consoleStrList);
}

