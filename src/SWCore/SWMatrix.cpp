#include "SWCoreIn.h"


/*-------------------------------------------------------------------------------------------
   FONKSIYON ISMI:InitMat4x4 
   YAPTIGI IS: Verilen Mat4x4i birim matrixe cevirir
                  [1,0,0,0]
				  [0,1,0,0]
				  [0,0,1,0]
				  [0,0,0,1]
-------------------------------------------------------------------------------------------*/
void swMat4x4Reset(Mat4x4 *m){

    m->index[0]=1;  m->index[1]=0;  m->index[2]=0;  m->index[3]=0;     //column 0
    m->index[4]=0;  m->index[5]=1;  m->index[6]=0;  m->index[7]=0;     //column 1
    m->index[8]=0;  m->index[9]=0;  m->index[10]=1; m->index[11]=0;    //column 2
    m->index[12]=0; m->index[13]=0; m->index[14]=0; m->index[15]=1;    //column 3
}



//-------------------------------------------------------------------------------------------
void swMat4x4Set(Mat4x4 *m,float f0,float f1,float f2,float f3,
							float f4,float f5,float f6,float f7,
							float f8,float f9,float f10,float f11,
							float f12,float f13,float f14,float f15){

	m->index[0]=f0;  m->index[1]=f1;  m->index[2]=f2;  m->index[3]=f3;     //column 0
	m->index[4]=f4;  m->index[5]=f5;  m->index[6]=f6;  m->index[7]=f7;     //column 1
	m->index[8]=f8;  m->index[9]=f9;  m->index[10]=f10; m->index[11]=f11;    //column 2
	m->index[12]=f12; m->index[13]=f13; m->index[14]=f14; m->index[15]=f15;    //column 3
}
