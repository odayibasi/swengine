#include "DSL.h"
#include "../../include/SWEngine.h"


typedef struct _lvlCmd{
  char cmd[MAX_CHAR_DLS_CMD];
}lvlCmd;

typedef struct _lvl{
   char filename[512];	
   int cmdListID; 
}lvl;

int			lvlListID=-1;
int         lvlFileListID=-1;

//-------------------------------------------------------------------------------------------
void dslExecuterParseLvl(char* folderPath,char *filename){
char temp[MAX_CHAR_DLS_CMD];	
char fsFullPath[MAX_PATH];
	swStringCopy(fsFullPath,swFileSystemGetResourcePath());
	swStringConcat1(fsFullPath,folderPath);
	swStringConcat1(fsFullPath,filename);
	FILE *file=fopen(fsFullPath,"rt");
	if(file==NULL){
		return;
	}

	lvl* level=(lvl*)malloc(sizeof(lvl));
	swLinkedListAdd(lvlListID,level);
	swStringCopy(level->filename,filename);
	level->cmdListID=swLinkedListCreate();
	while(!feof(file)){   
		fgets(temp,MAX_CHAR_DLS_CMD,file);
		if(swDSLIsValidCommand(temp)){
			lvlCmd *lvlCommand=(lvlCmd*)malloc(sizeof(lvlCmd));
			swStringCopy(lvlCommand->cmd,temp);
			swLinkedListAdd(level->cmdListID,lvlCommand);
			//swLoggerLog("%s",temp);
		}
	}
	fclose(file);		
}


//-------------------------------------------------------------------------------------------
void dslExecuterReset(){


	if(lvlListID!=-1){
		lvl* l=(lvl*)swLinkedListGetFirst(lvlListID);
		while(l!=NULL){
			lvl* l2=(lvl*)swLinkedListGetNext(lvlListID);
			swLinkedListClear(l->cmdListID);
			swLinkedListDestroy(l->cmdListID);
			swStringCopy(l->filename,"");
			l=l2;
		}
		swLinkedListClear(lvlListID);
		swLinkedListDestroy(lvlListID);
	}

	if(lvlFileListID!=-1){
		swLinkedListClear(lvlFileListID);
		swLinkedListDestroy(lvlFileListID);
	}

	
	lvlListID=swLinkedListCreate();
	lvlFileListID=swLinkedListCreate();

}



//-------------------------------------------------------------------------------------------
void dslExecuterParseFolder(char *folderPath){
	dslExecuterReset();
	swLoggerLog("%s=============\n",folderPath);
	swFileSystemQueryFiles(folderPath,lvlFileListID,"lvl");
	int count=swLinkedListSize(lvlFileListID);
	for(int i=0;i<count;i++){
		char* filename=(char*)swLinkedListGet(lvlFileListID,i);
		dslExecuterParseLvl(folderPath,filename);
	}
}


//-------------------------------------------------------------------------------------------
lvl* dslGetLevel(char *filename){
	lvl* l=(lvl*)swLinkedListGetFirst(lvlListID);
	while(l!=NULL){
		if(swStringEquals(l->filename,filename)){
			return l;
		}
		l=(lvl*)swLinkedListGetNext(lvlListID);
	}
	return NULL;
}



//-------------------------------------------------------------------------------------------
void dslExecuterExecuteLevel(char *filename){
	lvl* l=dslGetLevel(filename);
	if(l==NULL){
		return;
	}

	lvlCmd* lCmd=(lvlCmd*)swLinkedListGetFirst(l->cmdListID);
	while(lCmd!=NULL){
		swDSLExecuteCommand(lCmd->cmd);
		lCmd=(lvlCmd*)swLinkedListGetNext(l->cmdListID);
	}
}



