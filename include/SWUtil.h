#ifndef SWUTIL_H
#define SWUTIL_H


#include <windows.h>
#include <stdio.h>
#include <assert.h>
#include "SWTypes.h"


#ifndef DllExport
#define DllExport extern "C" __declspec(dllexport)
#endif


#define SW_WHERESTR "[file %s, line %d] "
#define SW_WHEREARG __FILE__,__LINE__


//==================================================================================================
//                  LINKEDLIST API
//=================================================================================================

DllExport int	 swLinkedListCreate();
DllExport void   swLinkedListDestroy(int listID);
DllExport void   swLinkedListAdd(int listID, void *obj);
DllExport void   swLinkedListDel(int listID,void *obj);
DllExport void*  swLinkedListGet(int listID,int index);
DllExport void*  swLinkedListGetFirst(int listID);
DllExport void*  swLinkedListGetLast(int listID);
DllExport void*  swLinkedListGetNext(int listID);
DllExport void*  swLinkedListGetPrev(int listID);
DllExport int    swLinkedListSize(int listID);
DllExport void   swLinkedListIterate(int listID,void(*func)(void*));
DllExport void   swLinkedListClear(int listID);
DllExport bool   swLinkedListContains(int listID,void *obj);




//==================================================================================================
//                  STACK API
//=================================================================================================

DllExport int		swStackCreate();
DllExport void		swStackDestroy(int stackID);
DllExport void		swStackPush(int stackID, void *obj);
DllExport void*		swStackPop(int stackID);
DllExport void*		swStackPeek(int stackID);
DllExport bool	    swStackIsEmpty(int stackID);
DllExport int		swStackSize(int stackID);


//==================================================================================================
//                  STRING API
//=================================================================================================
DllExport int    swStringGetLength(char *str);
DllExport char*  swStringGetChrAdress(char *str,int ch);
DllExport int    swStringGetChrPosition(char *str,char ch);
DllExport bool   swStringEquals(char *str1, char *str2);
DllExport bool   swStringContains(char *str,char *searchStr);
DllExport char*  swStringConcat(char *p1,char *p2); //Don't use in loop it allocate mem for all call
DllExport void   swStringConcat1(char *p1,char *p2);
//Don't use in loop it allocate mem for all call
DllExport char*  swStringConcatEx(char *str1, int start1,int end1,char *str2, int start2,int end2); 
DllExport void   swStringCopy(char *str1,char *str2);
DllExport void   swStringCopyEx(char *str1,char *str2,int start,int stop);
DllExport void   swStringReplaceChrInString(char *str,char oldchr,char *newchr);
DllExport int    swStringChrCountInString(char *str,char findchr);
DllExport void   swString2LowerCase(char *str);
DllExport void   swString2UpperCase(char *str);
DllExport float  swString2Float(char *p);
DllExport int    swString2Int(char *p);
DllExport bool   swString2Bool(char *p);
DllExport char * swStringParse(char * string,const char * control);
DllExport void   swStringFormatInt(int zeroCount,char *temp,int val);


//==================================================================================================
//                  LOGGER API
//=================================================================================================

DllExport FILE* swLoggerOpen();
DllExport void  swLoggerLog(const char* log,...);
DllExport void  swLoggerClose();



//==================================================================================================
//                  MATH API
//=================================================================================================
#define SW_MATH_PI 3.14678f

DllExport float  swMathCos(float degree);
DllExport float  swMathSin(float degree);
DllExport float  swMathDegreeToRadian(float degree);
DllExport float  swMathRadianToDegree(float radian);
DllExport float  swMathDegree(float x0,float y0,float x1,float y1);
DllExport float  swMathDistance(float x0,float y0,float x1,float y1);
DllExport float  swMathMax(float val1, float val2);
DllExport float  swMathMin(float val1, float val2);
DllExport float  swMathAbs(float val);
DllExport float  swMathSign(float val);
DllExport float  swMathSqrt(float val);
DllExport bool   swMathIsPowerTwo(float val);
DllExport bool   swMathIsInRangeInt(int val,int minVal,int maxVal);
DllExport bool   swMathIsInRangeFloat(float val,float minVal,float maxVal);
DllExport int    swMathClampInt(int val,int minVal,int maxVal);
DllExport float  swMathClampFloat(float val,float minVal,float maxVal);
DllExport float  swMathRandomFloat(float minVal,float maxVal);
DllExport int    swMathRandomInt(int minVal,int maxVal);
DllExport void   swMathSetSeed(int randomSeed);
DllExport void   swMathSourceCalculate(swRect *rect,int xGridSize,int yGridSize,int xGridIndex,int yGridIndex);
DllExport void   swMathSource2Target(swPoint *s,swPoint *t,swRect *target,swRect *source,float rot,swPoint *wPoint);


//==================================================================================================
//                  INTERSECTION API
//=================================================================================================

DllExport bool swIntersectionLineAndLine(swPoint *line0Start,swPoint *line0End,swPoint *line1Start,swPoint *line1End);
DllExport bool swIntersectionLineAndPoint(swPoint *lineStart,swPoint *lineEnd,swPoint *point);
DllExport bool swIntersectionCircleAndPoint(swPoint *center,float radious,swPoint *point);
DllExport bool swIntersectionCircleAndLine(swPoint *center,float radious,swPoint *line0Start,swPoint *line0End);
DllExport bool swIntersectionCircleAndCircle(swPoint *center0,float radious0,swPoint *center1,float radious1);
DllExport bool swIntersectionRectAndPoint(swRect *rect,swPoint *point);
DllExport bool swIntersectionRectAndPoint2(swRect *rect,float x,float y);
DllExport bool swIntersectionRectAndLine(swRect *rect,swPoint *line0Start,swPoint *line0End);
DllExport bool swIntersectionBoundaryAndBoundary(swPolygon *b1,swPolygon *b2);
DllExport bool swIntersectionBoundaryAndPoint(swPolygon *b1,swPoint *pos);
DllExport bool swIntersectionBoundaryAndLine(swPolygon *b1,swPoint *line0Start,swPoint *line0End);
DllExport bool swIntersectionBoundaryAndRect(swPolygon *boundary,swRect *rect);
DllExport bool swIntersectionRectAndRect(swRect *r0,swRect *r1);



//==================================================================================================
//                  TIMER API
//=================================================================================================
DllExport void   swTimerInit();  //Don't call this functions. This function only use from SWEngine
DllExport void   swTimerDeInit(); //Don't call this functions. This function only use from SWEngine
DllExport void	 swTimerTick(float seconds); //Don't call this functions. This function only use from SWEngine
DllExport int    swTimerCreate(float delaySeconds,void *obj,void(*callBack)(void *));
DllExport void   swTimerDestroy(int timerID);
DllExport void   swTimerStart(int timerID);
DllExport void   swTimerStop(int timerID);
DllExport bool   swTimerIsRunning(int timerID);
DllExport void   swTimerUpdateDelaySeconds(int timerID,float delaySeconds);


#endif 
