#include "../../include/SWEngine.h"

#pragma comment (lib,"../../lib/SWUtil.lib")    
#pragma comment (lib,"../../lib/SWTypes.lib")    
#pragma comment (lib,"../../lib/SWCore.lib")    
#pragma comment (lib,"../../lib/SWEngine.lib")    
#pragma comment (lib,"../../lib/SWGame.lib")    
#pragma comment (lib,"../../lib/SWServices.lib")    


swApplication simplePersistApp;
int           renderCount=0;

typedef struct{
  char* name;
  int width;
  int size;
}AData;


typedef struct{
	char* name;
	int age;
	int mass;
}BData;



//-------------------------------------------------------------------------------------------
void saveAData(FILE *file,void *obj){
	AData* aData=(AData*)obj;
	fprintf(file,"name=%s size=%i width=%i \n",aData->name,aData->size,aData->width);

}

//-------------------------------------------------------------------------------------------
void saveBData(FILE *file,void *obj){
	BData* bData=(BData*)obj;
	fprintf(file,"name=%s age=%i mass=%i \n",bData->name,bData->age,bData->mass);
}


//-------------------------------------------------------------------------------------------
void GameLoop(){ 

	renderCount++;
	if(renderCount==5){
		FILE *file=swFileSystemOpenFile("PersistSample.txt","wt");
		swPersistManagerExecute(file);   
		fclose(file);
	}
}


//-------------------------------------------------------------------------------------------
AData* createAData(char *name, int size, int width){
	AData *aData=(AData*)malloc(sizeof(AData));
	aData->name=name;
	aData->size=size;
	aData->width=width;
	return aData;
}


//-------------------------------------------------------------------------------------------
BData* createBData(char *name, int age, int mass){
	BData *bData=(BData*)malloc(sizeof(BData));
	bData->name=name;
	bData->age=age;
	bData->mass=mass;
	return bData;
}


//-------------------------------------------------------------------------------------------
void GameInit(){ 

	swPersistManagerAdd(saveAData,createAData("A1",12,13));
	swPersistManagerAdd(saveAData,createAData("A2",13,14));
	swPersistManagerAdd(saveAData,createAData("A3",15,16));
	swPersistManagerAdd(saveBData,createBData("B1",100,200));
	swPersistManagerAdd(saveAData,createAData("A3",15,16));
	swPersistManagerAdd(saveBData,createBData("B2",200,300));

}




//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{ 


	//Application Settings
	simplePersistApp.hInstance=hInstance;
	simplePersistApp.fullScreen=false;
	simplePersistApp.cursor=true;
	simplePersistApp.width=800;
	simplePersistApp.height=600;
	simplePersistApp.title="Simple Persist";
	simplePersistApp.path="\\rsc\\SimplePersist\\";
	simplePersistApp.appRun=GameLoop;

	//Application Execution
	swEngineInit(&simplePersistApp);
	GameInit();
	swEngineRun();
	swEngineExit();

	return 0;
}