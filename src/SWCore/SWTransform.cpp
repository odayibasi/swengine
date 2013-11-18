#include "SWCoreIn.h"
#include <math.h>

//---VARIABLE------------------
Vec4 obj_pos,obj_u,obj_v,obj_n; 

								  //obj_pos  objenin o anki posisyonu icin
								  //obj_u    objenin x coordinati
                                  //obj_v    objenin y ekseni 
                                  //obj_n    objenin z ekseni 


Mat4x4 *selectedObjTM;
                     



/*-------------------------------------------------------------------------------------------
   FONKSIYON ISMI:SetTransformMatrix
   YAPTIGI IS: TransformMatrix'ini set ediyoruz. 
               OpenGL Mat4x4 Yapisina gore  

                [ux,vx,nx,tx]
                [uy,vy,ny,ty]
                [uz,vz,nz,tz]
                [0 ,0 ,0 ,1]

-------------------------------------------------------------------------------------------*/
void setTransformMatrix(Vec4 *pos,Vec4 *u,Vec4 *v,Vec4 *n){


selectedObjTM->index[0]=u->index[0]; 
selectedObjTM->index[1]=v->index[0]; 
selectedObjTM->index[2]=n->index[0]; 
selectedObjTM->index[3]=0;

selectedObjTM->index[4]=u->index[1];  
selectedObjTM->index[5]=v->index[1];  
selectedObjTM->index[6]=n->index[1];  
selectedObjTM->index[7]=0; 

selectedObjTM->index[8]=u->index[2];
selectedObjTM->index[9]=v->index[2];
selectedObjTM->index[10]=n->index[2];
selectedObjTM->index[11]=0;

selectedObjTM->index[12]=pos->index[0];
selectedObjTM->index[13]=pos->index[1];
selectedObjTM->index[14]=pos->index[2];
selectedObjTM->index[15]=1;

}


//----------------------------------------------------
void swTransformInit(Mat4x4 *TM){

//position
	obj_pos.index[0]=TM->index[12];
	obj_pos.index[1]=TM->index[13];
	obj_pos.index[2]=TM->index[14];
	obj_pos.index[3]=1.0;

//x ekseni vektörü
	obj_u.index[0]=TM->index[0];
	obj_u.index[1]=TM->index[4];
	obj_u.index[2]=TM->index[8];
	obj_u.index[3]=0.0;
  
//y ekseni vektörü
	obj_v.index[0]=TM->index[1];
	obj_v.index[1]=TM->index[5];
	obj_v.index[2]=TM->index[9];
	obj_v.index[3]=0.0;

//z ekseni vektörü
	obj_n.index[0]=TM->index[2];
	obj_n.index[1]=TM->index[6];
	obj_n.index[2]=TM->index[10];
	obj_n.index[3]=0.0;

	selectedObjTM=(Mat4x4 *)TM;
}



//----------------------------------------------------
void swTransformRotateZ(float degree){

	Vec4 temp;
	float sint,cost;
	

	swVectorCopy(&temp,&obj_u);
	sint=(float)sin(swMathDegreeToRadian(degree));
	cost=(float)cos(swMathDegreeToRadian(degree));

	obj_u.index[0] = (temp.index[0] * cost - obj_v.index[0] * sint);
	obj_u.index[1] = (temp.index[1] * cost - obj_v.index[1] * sint);
	obj_u.index[2] = (temp.index[2] * cost - obj_v.index[2] * sint);

	obj_v.index[0] = (obj_v.index[0] * cost + temp.index[0] * sint);
	obj_v.index[1] = (obj_v.index[1] * cost + temp.index[1] * sint);
	obj_v.index[2] = (obj_v.index[2] * cost + temp.index[2] * sint);

    setTransformMatrix(&obj_pos,&obj_u,&obj_v,&obj_n);
}


//---------------------------------------------------------
void swTransformSetLocation(float x, float y, float z){
    obj_pos.index[0]=x;
    obj_pos.index[1]=y;
    obj_pos.index[2]=z;
    setTransformMatrix(&obj_pos,&obj_u,&obj_v,&obj_n);
}




