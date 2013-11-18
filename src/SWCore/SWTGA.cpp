#include "SWCoreIn.h"


//-------------------------------------------------------------------------------------------
bool swTGASave(char *path, short int width, short int height, unsigned char *outImage){
	// To save a screen shot is just like reading in a image.  All you do
	// is the opposite.  Istead of calling fread to read in data you call
	// fwrite to save it.

	FILE *pFile;               // The file pointer.
	unsigned char uselessChar; // used for useless char.
	short int uselessInt;      // used for useless int.
	unsigned char imageType;   // Type of image we are saving.
	int index;                 // used with the for loop.
	unsigned char bits;    // Bit depth.
	long Size;                 // Size of the picture.
	int colorMode;
	unsigned char tempColors;

	// Open file for output.
	pFile =swFileSystemOpenFile(path, "wb");

	// Check if the file opened or not.
	if(!pFile) { fclose(pFile); return false; }

	// Set the image type, the color mode, and the bit depth.
	imageType = 2; colorMode = 3; bits = 24;

	// Set these two to 0.
	uselessChar = 0; uselessInt = 0;

	// Write useless data.
	fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);
	fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);

	// Now image type.
	fwrite(&imageType, sizeof(unsigned char), 1, pFile);

	// Write useless data.
	fwrite(&uselessInt, sizeof(short int), 1, pFile);
	fwrite(&uselessInt, sizeof(short int), 1, pFile);
	fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);
	fwrite(&uselessInt, sizeof(short int), 1, pFile);
	fwrite(&uselessInt, sizeof(short int), 1, pFile);

	// Write the size that you want.
	fwrite(&width, sizeof(short int), 1, pFile);
	fwrite(&height, sizeof(short int), 1, pFile);
	fwrite(&bits, sizeof(unsigned char), 1, pFile);

	// Write useless data.
	fwrite(&uselessChar, sizeof(unsigned char), 1, pFile);

	// Get image size.
	Size = width * height * colorMode;

	// Now switch image from RGB to BGR.
	for(index = 0; index < Size; index += colorMode)
	{
		tempColors = outImage[index];
		outImage[index] = outImage[index + 2];
		outImage[index + 2] = tempColors;
	}

	// Finally write the image.
	fwrite(outImage, sizeof(unsigned char), Size, pFile);

	// close the file.
	fclose(pFile);

	return true;
}


//----------------------------------------------------------------
void swTGALoad(IMG *tga,char *path){
	int         temp;
	int			i;
	byte*       imageData; 


	FILE *file=swFileSystemOpenFile(path, "rb");	
	assert(file!=NULL);

	

	if(fread(tga->TGAcompare,1,sizeof(tga->TGAcompare),file)!=sizeof(tga->TGAcompare)){
		fclose(file);
		return;
	}

	if(fread(tga->header,1,sizeof(tga->header),file)!=sizeof(tga->header)){
		fclose(file);
		return;
	}
	
	tga->width=tga->header[1] * 256 + tga->header[0];
	tga->height=tga->header[3] * 256 + tga->header[2];
	tga->bpp=tga->header[4]/8;
	if(tga->width<=0 || tga->height<=0 ||(tga->bpp!=3 && tga->bpp!=4)){
		fclose(file);
		return;
	}

	tga->imageSize=tga->width*tga->height*tga->bpp;
	tga->imageData=(byte *)malloc(tga->imageSize);

	if(tga->imageData==NULL){
		fclose(file);	
		return;
	}

	if(fread(tga->imageData, 1, tga->imageSize, file)!=tga->imageSize){
		free(tga->imageData);				
		fclose(file);
		return;
	}

	for(i=0;i<tga->imageSize;i+=tga->bpp)			
	{										
		imageData=tga->imageData;
		temp=imageData[i];						
		imageData[i]=imageData[i + 2];			
		imageData[i + 2]=temp;					
	}
	fclose (file);	
}


