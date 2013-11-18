#include "SWCoreIn.h"
#include <direct.h>

char *executionPath=NULL;
char *resourcePath=NULL;
char  fsFullPath[1024];

DWORD dwError;
WIN32_FIND_DATA FindFileData;


//-------------------------------------------------------------------------------------------
DllExport bool swFileSystemInit(){
char tempReal[512];
	if( _getcwd(tempReal,512)!= NULL ){
		executionPath=swStringConcat("",tempReal);
		return true;
	}
		
	return false;
	
}

//-------------------------------------------------------------------------------------------
DllExport char* swFileSystemGetProgramWorkingPath(){
	return executionPath;
}


//-------------------------------------------------------------------------------------------
DllExport void  swFileSystemSetResourcePath(char *path){
	resourcePath=swStringConcat(executionPath,path);
}

//-------------------------------------------------------------------------------------------
DllExport char* swFileSystemGetResourcePath(){
	return resourcePath;
}

//-------------------------------------------------------------------------------------------
DllExport FILE* swFileSystemOpenFile(char *path,char *mode){
char fsFullPath[MAX_PATH];
	swStringCopy(fsFullPath,resourcePath);
	swStringConcat1(fsFullPath,path);
	FILE *file=fopen(fsFullPath,mode);
	return file;
}


//-------------------------------------------------------------------------------------------
DllExport void  swFileSystemQueryFiles(char *folderPath,int fileLinkedListID,char *extensionFilter){
	char fsFullPath[MAX_PATH];
	swStringCopy(fsFullPath,resourcePath);
	swStringConcat1(fsFullPath,folderPath);
	strncat(fsFullPath, "\\*", 3);
	HANDLE hFind = FindFirstFile(fsFullPath,&FindFileData);
	if (hFind != INVALID_HANDLE_VALUE){
		while (FindNextFile(hFind, &FindFileData) != 0) 
		{
				char* p=strrchr(FindFileData.cFileName,'.');   
				++p;
				char t[10];
				char extFilter[10];
				strcpy(t,p);
				strcpy(extFilter,extensionFilter);
				strupr(t);
				strupr(extFilter);
				if(strcmp(t,"")==0){
					continue;
				}else if(strcmp(extFilter,"")==0){
					char *fileName=swStringConcat("",FindFileData.cFileName);
					swLinkedListAdd(fileLinkedListID,fileName);                
				}else if(strcmp(t,extFilter)==0){
					char *fileName=swStringConcat("",FindFileData.cFileName);
					swLinkedListAdd(fileLinkedListID,fileName);
				}
		}
		 
	}
}
