#ifndef XEN_CARGOBOX_H
#define XEN_CARGOBOX_H

//DataStructure
typedef struct _xenCargoBox{
	int			bodyID;
	int         dispID;
	int			layer;
	bool		bEnabled;
	swRect		target;
	float		rot;
}xenCargoBox;




xenCargoBox*cargoBoxCreate(int layer, float x, float y);

#endif



