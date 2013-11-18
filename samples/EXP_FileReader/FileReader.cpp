#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd){ 
	FILE *fp;
	char str[128];

	if((fp = fopen("Demo.txt", "rt"))==NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}

	while(!feof(fp)) {
		if(fgets(str, 126, fp)) 
			printf("%s", str);
	}

	fclose(fp);
	return 0;
}
