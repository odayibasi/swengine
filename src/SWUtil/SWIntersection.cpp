#include "SWUtilIn.h"
#include "SWVertex3.h"
#include <math.h>

#define EPS				  2.7182818284590452354

//Sedgewick Yontemindeki LineIntersection Kontrolü
//-------------------------------------------------------------------------------------------
bool ccw(swPoint *p1, swPoint *p2, swPoint *p3){
	float dx1, dx2, dy1, dy2;

	dx1 = p2->x - p1->x;
	dy1 = p2->y - p1->y;
	dx2 = p3->x - p2->x;
	dy2 = p3->y - p2->y;
	if (dy1 *dx2 < dy2 *dx1)
		return true;
	else
		return false;
}


/*
Calculate the intersection of a ray and a sphere
The line segment is defined from p1 to p2
The sphere is of radius r and centered at sc
There are potentially two points of intersection given by
p = p1 + mu1 (p2 - p1)
p = p1 + mu2 (p2 - p1)
Return FALSE if the ray doesn't intersect the sphere.
*/
bool intesectionLineAndCircle(Vertex3 p1,Vertex3 p2,Vertex3 sc,float r,float *mu1,float *mu2){
	float a,b,c;
	float bb4ac;
	Vertex3 dp;

	dp.x = p2.x - p1.x;
	dp.y = p2.y - p1.y;
	dp.z = p2.z - p1.z;
	a = dp.x * dp.x + dp.y * dp.y + dp.z * dp.z;
	b = 2 * (dp.x * (p1.x - sc.x) + dp.y * (p1.y - sc.y) + dp.z * (p1.z - sc.z));
	c = sc.x * sc.x + sc.y * sc.y + sc.z * sc.z;
	c += p1.x * p1.x + p1.y * p1.y + p1.z * p1.z;
	c -= 2 * (sc.x * p1.x + sc.y * p1.y + sc.z * p1.z);
	c -= r * r;
	bb4ac = b * b - 4 * a * c;
	if (swMathAbs(a) < EPS || bb4ac < 0) {
		*mu1 = 0;
		*mu2 = 0;
		return false;
	}

	*mu1 = (-b + sqrt(bb4ac)) / (2 * a);
	*mu2 = (-b - sqrt(bb4ac)) / (2 * a);

	return true;
}



//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionLineAndLine(swPoint *line0Start,swPoint *line0End,swPoint *line1Start,swPoint *line1End){
	bool check1 =ccw(line0Start, line0End, line1Start) != ccw(line0Start, line0End, line1End);
	bool check2 =ccw(line1Start, line1End, line0Start) != ccw(line1Start,line1End, line0End);
	return check1 && check2;
}


//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionLineAndPoint(swPoint *lineStart,swPoint *lineEnd,swPoint *point){
	//TODO implement
	return false;
}


//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionCircleAndPoint(swPoint *center,float radious,swPoint *point){
	float dist=swMathDistance(point->x,point->y,center->x,center->y);
	return dist<radious?true:false;
}


//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionCircleAndLine(swPoint *center,float radious,swPoint *line0Start,swPoint *line0End){
Vertex3 v3S,v3E,v3C;
float mu1,mu2;
	swVertex3Set(&v3S,line0Start->x,line0Start->y,0);
	swVertex3Set(&v3E,line0End->x,line0End->y,0);
	swVertex3Set(&v3C,center->x,center->y,0);
	return intesectionLineAndCircle(v3S,v3E,v3C,radious,&mu1,&mu2);
}

//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionCircleAndCircle(swPoint *center0,float radious0,swPoint *center1,float radious1){
	float dist=swMathDistance(center0->x,center0->y,center1->x,center1->y);
	if(dist<=radious0+radious1)
		return true;
	return false;

}

//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionRectAndPoint2(swRect *rect,float x,float y){
	if (x>=rect->x && y>=rect->y && x<=swRectXPlusW(rect) && y <=swRectYPlusH(rect)){
		return true;
	}
	return false;
}


//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionRectAndPoint(swRect *rect,swPoint *point){
	return swIntersectionRectAndPoint2(rect,point->x,point->y);
}

//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionRectAndLine(swRect *rect,swPoint *line0Start,swPoint *line0End){

	if(swIntersectionRectAndPoint(rect,line0Start))
			return true;

	if(swIntersectionRectAndPoint(rect,line0End))
		return true;


	swPoint p0={rect->x,rect->y};
	swPoint p1={rect->x+rect->w,rect->y};
	swPoint p2={rect->x+rect->w,rect->y+rect->h};
	swPoint p3={rect->x,rect->y+rect->h};
	

	if(swIntersectionLineAndLine(line0Start,line0End,&p0,&p1))
		 return true;

	if(swIntersectionLineAndLine(line0Start,line0End,&p1,&p2))
		return true;

	if(swIntersectionLineAndLine(line0Start,line0End,&p2,&p3))
		return true;

	if(swIntersectionLineAndLine(line0Start,line0End,&p3,&p1))
		return true;

	return false;


}

//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionBoundaryAndBoundary(swPolygon *b1,swPolygon *b2){
	int a, b, countIntersect;
	a = b = countIntersect = 0;

	for (int i=0; i <b1->count; i++){
		if (i==b1->count-1)
			a=0;
		else
			a=i + 1;

		for (int j=0;j<b2->count-1;j++){
			if (j==b1->count-1)
				b = 0;
			else
				b = j + 1;

			bool bIntersect = swIntersectionLineAndLine(&b1->pointS[i], &b1->pointS[a], &b2->pointS[j], &b2->pointS[b]);
			if (bIntersect){
				++countIntersect;
			} //end of if

		} //end of for j			
		if (countIntersect % 2 == 1){
			return true;
		}
		countIntersect = 0;
	} //end of for i   

	return false;
}

//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionBoundaryAndPoint(swPolygon *b1,swPoint *pos){
	int i, a, countIntersect = 0;
	BOOL bIntersect = FALSE;
	swPoint origin ={0, 0};

	for (i = 0; i < b1->count; i++){

		if ((i + 1) == b1->count)
			a = 0;
		else
			a = i + 1;

		bIntersect = swIntersectionLineAndLine(&origin, pos, &b1->pointS[i], &b1->pointS[a]);
		if (bIntersect){
			++countIntersect;
		}

	}

	if (countIntersect % 2 == 1)
		return true;
	else if (countIntersect % 2 == 0)
		return false;
	else
		return false;

}

//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionBoundaryAndLine(swPolygon *b1,swPoint *line0Start,swPoint *line0End){
	int i, a, countIntersect = 0;
	bool bIntersect = false;


	for (i = 0; i < b1->count; i++){
		if ((i + 1) == b1->count)
			a = 0;
		else
			a = i + 1;

		bIntersect = swIntersectionLineAndLine(line0Start, line0End, &b1->pointS[i], &b1->pointS[a]);
		if (bIntersect){
			++countIntersect;
		}

	}

	if (countIntersect % 2 == 1)
		return true;
	else if (countIntersect % 2 == 0)
		return false;
	else
		return false;

}

//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionBoundaryAndRect(swPolygon *boundary,swRect *rect){

	int size = boundary->count;
	for (int i = 0; i < size; i++){
		if (swIntersectionRectAndPoint(rect,&boundary->pointS[i])){
			return true;
		}
	}
	return false;
}


//-------------------------------------------------------------------------------------------
DllExport bool swIntersectionRectAndRect(swRect *r0,swRect *r1){
	bool flag0=swIntersectionRectAndPoint2(r0, r1->x, r1->y);
    bool flag1=swIntersectionRectAndPoint2(r0, swRectXPlusW(r1),r1->y);
    bool flag2=swIntersectionRectAndPoint2(r0, swRectXPlusW(r1),swRectYPlusH(r1));
	bool flag3=swIntersectionRectAndPoint2(r0, r1->x, swRectYPlusH(r1));
	return  flag0|| flag1 || flag2 ||flag3;
}
