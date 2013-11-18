#include "SWUtilIn.h"


FILE *logFile=NULL;

//-------------------------------------------------------------------------------------------
DllExport FILE* swLoggerOpen(){
	if(logFile==NULL){
		logFile=fopen("log.txt","wt");
	}
	return logFile;
}

//-------------------------------------------------------------------------------------------
DllExport void swLoggerLog(const char* log,...){
	va_list args;
	va_start(args,log);
	vfprintf(swLoggerOpen(), log, args ); 
	va_end( args );
}

//-------------------------------------------------------------------------------------------
DllExport void swLoggerClose(){
	assert(logFile!=NULL);
	fclose(logFile);
}





 