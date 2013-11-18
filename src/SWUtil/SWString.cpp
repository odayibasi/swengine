#include "SWUtilIn.h"


//-------------------------------------------------------------------------------------------
DllExport int swStringGetLength(char *str){
	return (int)strlen(str);
}


//-------------------------------------------------------------------------------------------
DllExport char* swStringGetChrAdress(char *str,int ch){
	return strchr(str,ch);
}

//-------------------------------------------------------------------------------------------
DllExport int swStringGetChrPosition(char *str,char ch){
	int pos=0;
	while(*str!='\0'){
		if(*str==ch)
			return pos;
		str++;
		pos++;
	}	
	return -1;
}

//-------------------------------------------------------------------------------------------
DllExport bool swStringEquals(char *str1, char *str2){
	if(strcmp(str1,str2)==0){
		return true;
	}else{
		return false;
	}
}





//-------------------------------------------------------------------------------------------
DllExport char* swStringConcat(char *p1,char *p2){
	int len;
	char *p;
	len=(int)strlen(p1)+(int)strlen(p2);
	p=(char*)malloc(sizeof(char)*len);             
	strcpy(p,p1);
	strcat(p,p2);
	return p;
}

//-------------------------------------------------------------------------------------------
DllExport void swStringConcat1(char *p1,char *p2){
	strcat(p1,p2);
}


//-------------------------------------------------------------------------------------------
DllExport char* swStringConcatEx(char *str1, int start1,int end1,char *str2, int start2,int end2){
	int p=0;
	char *result=(char*)malloc(sizeof(char)*(end1-start1+end2-start2+1));    

	for(int i=start1;i<end1;++i)
		result[p++]=str1[i];		

	for(int j=start2;j<end2;++j)
		result[p++]=str2[j];

	result[p]='\0';
	return result;
}


//-------------------------------------------------------------------------------------------
DllExport void swStringCopy(char *str1,char *str2){
	strcpy(str1,str2);
}


//-------------------------------------------------------------------------------------------
DllExport void swStringCopyEx(char *str1,char *str2,int start,int stop){
  int count=0;
  for(count=start;count<stop;count++){
	  str1[count-start]=str2[count];
  }
  str1[count-start]='\0';
}


//-------------------------------------------------------------------------------------------
DllExport bool swStringContains(char *str,char *searchStr){
	int pos;
	char temp[255];
	if(str==NULL || searchStr==NULL) 
		return false;

	pos=swStringGetChrPosition(str,searchStr[0]);
	if(pos!=-1){
		swStringCopyEx(temp,str,pos,pos+(int)strlen(searchStr));
		if(strcmp(searchStr,temp)==0){ 
			return true;
		}else{
			swStringCopyEx(temp,str,pos+1,(int)strlen(str));
			return swStringContains(temp,searchStr);
		} 
	}
	return false;
}


//-------------------------------------------------------------------------------------------
DllExport void swStringReplaceChrInString(char *str,char oldchr,char *newchr){
	int pos;
	char temp[50];
	char temp1[200];
	char *p;

	pos=swStringGetChrPosition(str,oldchr);
	if(pos!=-1){
		strcpy(temp1,"");
		while(pos!=-1){
			swStringCopyEx(temp,str,0,pos);
			strcat(temp1,temp);
			strcat(temp1,newchr);
			p=strchr(str,oldchr);
			strcpy(str,++p);
			pos=swStringGetChrPosition(str,oldchr);
		}
		strcat(temp1,str);
		strcpy(str,temp1);
	}
}



//-------------------------------------------------------------------------------------------
DllExport int swStringChrCountInString(char *str,char findchr){

	char temp[128];
	int count=0;
	swStringCopy(temp,str);
	int pos=swStringGetChrPosition(temp,findchr);
	while(pos!=-1){
	  count++;
	  swStringCopyEx(temp,temp,pos+1,strlen(temp));
	  pos=swStringGetChrPosition(temp,findchr);
	}
	return count;
}



//-------------------------------------------------------------------------------------------
DllExport void swString2LowerCase(char *str){
	strlwr(str);
}

//-------------------------------------------------------------------------------------------
DllExport void swString2UpperCase(char *str){
	strupr(str);
}

//-------------------------------------------------------------------------------------------
DllExport float swString2Float(char *p){
	return atof(p);     
}


//-------------------------------------------------------------------------------------------
DllExport int swString2Int(char *p){
	return atoi(p);     
}

//-------------------------------------------------------------------------------------------
DllExport bool swString2Bool(char *p){
	if(swStringEquals(p,"true")){
		return true;
	}else{
		return false;
	}
}

//-------------------------------------------------------------------------------------------
DllExport char * swStringParse(char * string,const char * control){
	return strtok(string,control);
}


//----------------------------------------------------------------
DllExport void swStringFormatInt(int zeroCount,char *temp,int val){
	int  i,len;
	char valCharS[20];

	sprintf(valCharS,"%i",val);
	len=(int)strlen(valCharS);

	temp[zeroCount]='\0';
	for(i=zeroCount-len;i<zeroCount;i++)
		temp[i]=valCharS[i-(zeroCount-len)];

	for(i=0;i<zeroCount-len;i++)
		temp[i]='0';
}


