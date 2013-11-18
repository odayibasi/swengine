#include "SWCoreIn.h"

int		camListID=-1;
int		camIdCounter=0;
swCam	camDefault;


//-------------------------------------------------------------------------------------------
void swCamInit(){
	camListID=swLinkedListCreate();
	camDefault.x=0;
	camDefault.y=0;
	camDefault.rot=0;
	camDefault.zoom=1.0f;

}
//-------------------------------------------------------------------------------------------
void swCamDeInit(){
	swLinkedListClear(camListID);
	swLinkedListDestroy(camListID);
	camListID=-1;
	camIdCounter=0;	
}

//-------------------------------------------------------------------------------------------
swCam *swCamGet(int camID){
	if(camID==SW_CAM_DEFAULT)
		return &camDefault;

	swCam *cam=(swCam*)swLinkedListGetFirst(camListID);
	while(cam!=NULL){
		if(cam->id==camID){
			return cam;
		}
		swCam *cam=(swCam*)swLinkedListGetNext(camListID);
	}
	return NULL;
}

//-------------------------------------------------------------------------------------------
DllExport int  swGraphicsCreateCam(){
	swCam *cam=(swCam*)malloc(sizeof(swCam));
	cam->id=camIdCounter;
	cam->rot=0;
	cam->zoom=1.0;
	cam->x=0;
	cam->y=0;
	camIdCounter++;
	swLinkedListAdd(camListID,cam);
	return cam->id;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsDestroyCam(int camID){
	swCam* cam=swCamGet(camID);
	swLinkedListDel(camListID,cam);
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsSetCam(int camID,float x,float y,float rot,float zoom){
	swCam* cam=swCamGet(camID);
	cam->x=x;
	cam->y=y;
	cam->rot=rot;
	cam->zoom=zoom;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsSetCamPos(int camID,float x,float y){
	swCam* cam=swCamGet(camID);
	cam->x=x;
	cam->y=y;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsSetCamPosX(int camID,float x){
	swCam* cam=swCamGet(camID);
	cam->x=x;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsSetCamPosY(int camID,float y){
	swCam* cam=swCamGet(camID);
	cam->y=y;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsSetCamRot(int camID,float rot){
	swCam* cam=swCamGet(camID);
	cam->rot=rot;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsSetCamZoom(int camID,float zoom){
	swCam* cam=swCamGet(camID);
	cam->zoom=zoom;
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsAddCamPosX(int camID,float dX){
	swCam* cam=swCamGet(camID);
	cam->x+=dX;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsAddCamPosY(int camID,float dY){
	swCam* cam=swCamGet(camID);
	cam->y+=dY;
}


//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsAddCamRot(int camID,float dR){
	swCam* cam=swCamGet(camID);
	cam->rot+=dR;
}

//-------------------------------------------------------------------------------------------
DllExport void  swGraphicsAddCamZoom(int camID,float dZ){
	swCam* cam=swCamGet(camID);
	cam->zoom+=dZ;
}


//-------------------------------------------------------------------------------------------
DllExport float swGraphicsGetCamPosX(int camID){
	swCam* cam=swCamGet(camID);
	return cam->x;
}

//-------------------------------------------------------------------------------------------
DllExport float swGraphicsGetCamPosY(int camID){
	swCam* cam=swCamGet(camID);
	return cam->y;
}

//-------------------------------------------------------------------------------------------
DllExport float swGraphicsGetCamRot(int camID){
	swCam* cam=swCamGet(camID);
	return cam->rot;
}

//-------------------------------------------------------------------------------------------
DllExport float swGraphicsGetCamZoom(int camID){
   swCam* cam=swCamGet(camID);
   return cam->zoom;
}
