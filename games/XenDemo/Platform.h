#ifndef XEN_PLATFORM_H
#define XEN_PLATFORM_H

//DataStructure
typedef struct _xenPlatform{
	int			bodyID;
	int         dispID;
	int			layer;
	swRect		target;
}xenPlatform;


void platformCreate(float x,float y);

#endif
