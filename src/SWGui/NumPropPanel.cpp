#include "SWGuiIn.h"




//-------------------------------------------------------------------------------------------
void swNumPropPanelDisplay(NumPropPanel *panel){
		   
	//Update Up/Down
	panel->downBtn.rect.x=swRectXPlusW(&panel->rect)-panel->downBtn.rect.w;
	panel->downBtn.rect.y=panel->rect.y+2.5f;

	panel->upBtn.rect.x=swRectXPlusW(&panel->rect)-panel->upBtn.rect.w;
	panel->upBtn.rect.y=panel->rect.y+(panel->visbProp+1)*25+2.5f;

	swGraphicsSetColor0(0.4f,0.4f,0.4f,1.0f);
	float x0=swRectMidX(&panel->downBtn.rect);
	swGraphicsRenderLine0(x0,swRectYPlusH(&panel->downBtn.rect),x0,panel->upBtn.rect.y,2);


	int size=swLinkedListSize(panel->iPropList);
	int count=(size<=panel->visbProp) ? size : panel->visbProp;

	//Display PropComponent
	int index=panel->iPropIndex;	
	for(int i=index;i<count+index;i++){
		if(i<swLinkedListSize(panel->iPropList)){
			PropComponent *prop=(PropComponent*)swLinkedListGet(panel->iPropList,i);
			prop->rect.x=panel->rect.x;
			prop->rect.y=panel->upBtn.rect.y-(i+1-index)*25;
			swPropComponentDisplay(prop);
		}
	}

	//Display Button;
	swNumPropControlBtnDisplay(&panel->upBtn);
	swNumPropControlBtnDisplay(&panel->downBtn);		

}


//-------------------------------------------------------------------------------------------
void swNumPropPanelInput(NumPropPanel *panel,swKeyboardState *keybState,swMouseState *mousState){

	swNumPropControlBtnInput(&panel->upBtn,keybState,mousState);
	swNumPropControlBtnInput(&panel->downBtn,keybState,mousState);

	int size=swLinkedListSize(panel->iPropList);
	int count=(size<=panel->visbProp) ? size : panel->visbProp;


	int index=panel->iPropIndex;	
	for(int i=index;i<count+index;i++){
		PropComponent *prop=(PropComponent*)swLinkedListGet(panel->iPropList,i);
		swPropComponentInput(prop,keybState,mousState);
	}
}
