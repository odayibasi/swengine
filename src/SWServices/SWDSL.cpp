#include "SWServicesIn.h"


typedef struct _swDSLCmd{
	void (*cmdFunc)(int,swArg *cArgs);
	char *name;
	int  countArg;
	swArg *argS;
}swDSLCmd;

int			dslCmdList=-1;
char        dslComment='#';
char        dslSeparator='&';


//-------------------------------------------------------------------------------------------
void swDSLGetArg(char *fullCmd,int argIndex,char *arg){
	char * pch;
	int   counter=0;
	char  temp[MAX_CHAR_DLS_CMD];
	swStringCopy(temp,fullCmd);
	pch=swStringParse(temp," &");
	while(pch!=NULL){
		if(counter==argIndex+1){
			swStringCopy(arg,pch);
		}
		counter++;
		pch = swStringParse(NULL, " &");
	}
}


//-------------------------------------------------------------------------------------------
swDSLCmd* swDSLMatchCommand(char *command, int argCount){
	swDSLCmd *cmd=(swDSLCmd *)swLinkedListGetFirst(dslCmdList);
	while(cmd!=NULL){
		if(swStringEquals(command,cmd->name) && cmd->countArg==argCount){
			return cmd;
		}
		cmd=(swDSLCmd *)swLinkedListGetNext(dslCmdList);
	}
	return NULL;
}


//-------------------------------------------------------------------------------------------
DllExport bool swDSLExecuteCommand(char *fullCmd){
	
	void (*cmdFunc)(int,swArg*);
	char command[MAX_CHAR_DLS_CMD];
	int argCount;
	char arg[MAX_CHAR_DLS_CMD];
	
	int posSpace=swStringGetChrPosition(fullCmd,32);
	bool onlyCmd=posSpace==-1;
	if(onlyCmd){
		swStringCopyEx(command,fullCmd,0,strlen(fullCmd));
		argCount=0;
	}else{
		swStringCopyEx(command,fullCmd,0,posSpace); 
		argCount=swStringChrCountInString(fullCmd,dslSeparator);
	}

	swDSLCmd *cmd=swDSLMatchCommand(command,argCount);
	if(cmd==NULL){
		return false;
	}else{
		for(int i=0;i<argCount;i++){
			swArgType type=cmd->argS[i].type;
			swDSLGetArg(fullCmd,i,arg);
			switch(type){
				case SW_ARG_BOOL:
					cmd->argS[i].arg.bVal=swString2Bool(arg);
					break;
				case SW_ARG_INT:
					cmd->argS[i].arg.iVal=swString2Int(arg);
					break;
				case SW_ARG_FLOAT:
					cmd->argS[i].arg.fVal=swString2Float(arg);
					break;
				case SW_ARG_STRING:
					swStringCopy(cmd->argS[i].arg.sVal,arg);
					break;
				default:
					return false;
			}
		}

		swLoggerLog("%s\n",command);
		cmdFunc=cmd->cmdFunc;
		(*cmdFunc)(cmd->countArg,cmd->argS);
		return true;
	}
}



//-------------------------------------------------------------------------------------------
DllExport void  swDSLRegisterCommand(void(*cmdFunc)(int,swArg *cArgs),char *cmdName,int count,swArg *zArgs){
	swDSLCmd *cmd=(swDSLCmd*)malloc(sizeof(swDSLCmd));
	cmd->cmdFunc=cmdFunc;
	cmd->name=cmdName;
	cmd->countArg=count;
	cmd->argS=zArgs;
	swLinkedListAdd(dslCmdList,cmd);
}


//-------------------------------------------------------------------------------------------
DllExport bool swDSLIsValidCommand(char *fullCmd){
	char command[MAX_CHAR_DLS_CMD];
	int argCount;
	int posSpace=swStringGetChrPosition(fullCmd,32);
	bool onlyCmd=posSpace==-1;
	if(onlyCmd){
		swStringCopyEx(command,fullCmd,0,strlen(fullCmd));
		argCount=0;
	}else{
		swStringCopyEx(command,fullCmd,0,posSpace); 
		argCount=swStringChrCountInString(fullCmd,dslSeparator);
	}

	swDSLCmd *cmd=swDSLMatchCommand(command,argCount);
	return cmd!=NULL;
}

//-------------------------------------------------------------------------------------------
DllExport void swDSLInit(){
	dslCmdList=swLinkedListCreate();			
}


//-------------------------------------------------------------------------------------------
DllExport void swDSLDeInit(){
	swLinkedListDestroy(dslCmdList);
}
