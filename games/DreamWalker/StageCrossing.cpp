#include "Stages.h"

#define COUNT_OF_CROSS_PLATFORM 13
#define MAX_GREEN 6
#define RAND_TIME 5

typedef struct Velocity_Vector{
	float x;
	float y;
}Velocity;

Velocity velocity;

Platform *crossPlatforms[COUNT_OF_CROSS_PLATFORM];

float destination[COUNT_OF_CROSS_PLATFORM];

extern int imgCrossPlatformID;
extern int imgStageCrossingBgID; 
extern int sprActorID;

swRect rectBgCrossing={0,128,1024,512};
float currentTime[COUNT_OF_CROSS_PLATFORM];
float LastMovementTime[COUNT_OF_CROSS_PLATFORM];
bool first;
bool ActivateClick = false;
float acceleration[COUNT_OF_CROSS_PLATFORM];

bool jumper = false;

Actor *crossActor;

extern swMouseState mousState;
swMousBehaviourListener stageCrossingMBListener;

int difficulty = 0; //MAX_GREEN-difficulty green platform ;)

extern int fontID;
extern int score;
extern int bgSoundSourceID;


float randomizationTime;
float CurentRandomizationTime = 0;
extern void (*activeFunc)(void);

int colorBuffer=-1;

//Colors
extern int imgColorIDS[3];




//---------------------------------------------------------------------------------
void calculateScore(){

	if(crossActor->bindedPlatformID==-1){
		return;
	}

	colorBuffer=-1;
	if(crossPlatforms[crossActor->bindedPlatformID]->color==0){
		score+=1000;
	}else{
		score-=1000;
	}

}



//---------------------------------------------------------------------------------
// TODO ERROR IN CALCULATION
void calculateScore2(int deltaScorePlus, int deltaScoreNegative){

	if(crossActor->bindedPlatformID==-1){
		return;
	}


	if(crossPlatforms[crossActor->bindedPlatformID]->color==0){
		score+=1000;
	}else{
		if(colorBuffer==-1){
			colorBuffer=crossPlatforms[crossActor->bindedPlatformID]->color;
		}else{
			score-=1000;
			colorBuffer=-1;

		}
	}

}



//---------------------------------------------------------------------------------
void randomizePlatformColor(){
	for(int i = 0; i<COUNT_OF_CROSS_PLATFORM; i++)
		crossPlatforms[i]->color = 2;

	for(int i = 0; i < MAX_GREEN - difficulty; i++){
		int j = i;
		while(j==i){
			double randomIndex = rand() % COUNT_OF_CROSS_PLATFORM;

			if(crossPlatforms[(int)randomIndex]->color){
				crossPlatforms[(int)randomIndex]->color = 0;
				j++;
			}
		}
	}

	for(int i=0;i<COUNT_OF_CROSS_PLATFORM;i++){
		double randomColor = rand()%2 + 1;

		if(crossPlatforms[i]->color)
			crossPlatforms[i]->color = (int)randomColor;

	}
}


//---------------------------------------------------------------------------------
void advancedActBindingToPlatform(Actor* act, Platform* plt,float x){
	act->target.x = swMathClampFloat(x,plt->target.x,plt->target.x + plt->target.w);
	act->target.y = swRectYPlusH(&plt->target);
}

//---------------------------------------------------------------------------------
void actorJump(Actor* act,Velocity* velo){
	if(fabs(velo->x) < 0.01 && fabs(velo->y) < 0.01){
		jumper = false;
	}else{
		act->target.x += velo->x;
		act->target.y += velo->y;
		velo->y -= 0.1;
		for(int i = 0; i<COUNT_OF_CROSS_PLATFORM; i++){
			bool totalCollision = swIntersectionRectAndRect(&act->target, &crossPlatforms[i]->target);
			if(totalCollision){
				bindActorToPlatform(act,crossPlatforms[i]);
				CurentRandomizationTime = swSystemGetElapsedSeconds();
				if(CurentRandomizationTime - randomizationTime > 0.5)
					randomizationTime = CurentRandomizationTime -2.5;
				velo->x = 0;
				velo->y = 0;
				jumper = false;
				act->bindedPlatformID = i;
				calculateScore();
				break;
			}
		} //end of for


		if(act->target.y < 128){
			score-=10000;
			bindActorToPlatform(act,crossPlatforms[0]);
			act->bindedPlatformID = 0;
			velo->x = 0;
			velo->y = 0;
		}
	}
}
//---------------------------------------------------------------------------------
void SetDestination(int index){
	int power = rand()%2;
	destination[index] = rand() % (534 - 150) + 150;
	acceleration[index] = rand() % 5 + 1;
}
//---------------------------------------------------------------------------------
void MovePlatforms(){
	for(int i=1; i<COUNT_OF_CROSS_PLATFORM-1; i++){
		if(fabs(destination[i] - crossPlatforms[i]->target.y) > 0.1){
			if(destination[i] > crossPlatforms[i]->target.y)
				crossPlatforms[i]->target.y += 0.1 * acceleration[i];
			else if(destination[i] < crossPlatforms[i]->target.y)
				crossPlatforms[i]->target.y -= 0.1 * acceleration[i];
		}
	}
}

//---------------------------------------------------------------------------------
void stageCrossingMBReleased(float x, float y){
	//Release me from this prison
	jumper = true;
	ActivateClick = true;
}

//---------------------------------------------------------------------------------
void stageCrossingInit(){
	//Platform
	for(int i=0;i<COUNT_OF_CROSS_PLATFORM;i++){
		crossPlatforms[i] = new Platform();
		crossPlatforms[i]->target.x = (1024/COUNT_OF_CROSS_PLATFORM)*(i*0.94) + 25;
		crossPlatforms[i]->target.y = 365;
		crossPlatforms[i]->target.h = 10;
		crossPlatforms[i]->target.w = 50;
		crossPlatforms[i]->color    = 2;
		destination[i]			    = crossPlatforms[i]->target.y;
		acceleration[i]             = 0.0;
		currentTime[i]              = 0.0;
		LastMovementTime[i]         = 0.0;
	} 

	randomizePlatformColor();

	first = true;

	//Actor
	crossActor = new Actor();
	bindActorToPlatform(crossActor, crossPlatforms[0]);
	crossActor->target.w = 50;
	crossActor->target.h = 50;
	crossActor->bindedPlatformID = -1;

	//Mouse
	stageCrossingMBListener.dragging = NULL;
	stageCrossingMBListener.moving   = NULL;
	stageCrossingMBListener.pressed  = NULL;
	stageCrossingMBListener.released = stageCrossingMBReleased;

	swMousBehaviourAdd(&stageCrossingMBListener);

	ActivateClick = false;

	//Velocity
	velocity.x = 0;
	velocity.y = 0;

	//Jumping
	jumper = false;

	randomizationTime = swSystemGetElapsedSeconds();

	//Active Function
	activeFunc=stageCrossingExecute;
}
//---------------------------------------------------------------------------------
void stageCrossingExecute(){

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
	swGraphicsSetColor0(1,1,0,1);
	swGraphicsRenderText(false,1,32,650,650,0,"Score %i",score);

	swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
	swGraphicsSetColor1(&SWCOLOR_WHITE);

	/*Background*/
	swGraphicsRenderImg0(imgStageCrossingBgID,&rectBgCrossing);

	/*Actor*/
	if(jumper){
		actorJump(crossActor,&velocity);
	}
	else if(mousState.btnLEFT && ActivateClick)
	{
		float differencex = fabs(mousState.x       - crossActor->target.x - crossActor->target.w/2);
		float differencey = fabs(mousState.y       - crossActor->target.y - crossActor->target.w/2);
		int signx         = swMathSign(mousState.x - crossActor->target.x - crossActor->target.w/2);
		int signy         = swMathSign(mousState.y - crossActor->target.y - crossActor->target.w/2);

		swGraphicsSetColor1(&SWCOLOR_BLUE);
		swGraphicsRenderLine0(crossActor->target.x + crossActor->target.w/2,
			crossActor->target.y + crossActor->target.h/2,
			(mousState.x) * (differencex < 100.0) +
			(crossActor->target.x + signx * 100)*(differencex > 100.0),
			(mousState.y) * (differencey < 100.0) +
			(crossActor->target.y + signy * 100)*(differencey > 100.0),3.0);

		velocity.x = (mousState.x - crossActor->target.x - crossActor->target.w/2) * (differencex < 100.0) +
			(signx * 100)*(differencex > 100.0);
		velocity.x /= 15;
		velocity.y = (mousState.y - crossActor->target.y - crossActor->target.w/2) * (differencey < 100.0) +
			(signy * 100)*(differencey > 100.0);
		velocity.y /= 15;
	}else if(ActivateClick && crossActor->bindedPlatformID != -1){
		if(destination[crossActor->bindedPlatformID] > crossPlatforms[crossActor->bindedPlatformID]->target.y)
			velocity.y = 0.1 * acceleration[crossActor->bindedPlatformID];
		else if(destination[crossActor->bindedPlatformID] < crossPlatforms[crossActor->bindedPlatformID]->target.y)
			velocity.y = -0.1 * acceleration[crossActor->bindedPlatformID];
		if(!crossActor->bindedPlatformID)
			velocity.y = 0;
		crossActor->target.y += velocity.y;
	}
	swGraphicsRenderSprite0(sprActorID,crossActor->animIndex,&crossActor->target);

	/*Platforms*/
	for(int i = 0; i<COUNT_OF_CROSS_PLATFORM-1; i++){		
		if(currentTime[i] - LastMovementTime[i] > 30.0 || first || fabs(destination[i] - crossPlatforms[i]->target.y) < 0.1){
			SetDestination(i);
			LastMovementTime[i] = swSystemGetElapsedSeconds();
		}
		currentTime[i] = swSystemGetElapsedSeconds();
	}

	MovePlatforms();

	CurentRandomizationTime = swSystemGetElapsedSeconds();

	bool randomize = false;

	if(CurentRandomizationTime - randomizationTime > 3)
		randomize = true;

	for(int i=0;i<COUNT_OF_CROSS_PLATFORM;i++){
		if(crossPlatforms[i]->color == 2)  swGraphicsSetColor1(&SWCOLOR_RED);
		else if(crossPlatforms[i]->color == 1)  swGraphicsSetColor0(1.0,1.0,0.0,1.0);
		else if(!crossPlatforms[i]->color)  swGraphicsSetColor1(&SWCOLOR_GREEN);

		if(randomize)
		{
			randomizePlatformColor();
			randomizationTime = CurentRandomizationTime;
			//calculateScore2(1000,1000);
		}

		//swGraphicsRenderLineRect2(&crossPlatforms[i]->target,3.0);
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_SOLID);
		swGraphicsSetColor1(&SWCOLOR_WHITE);
		swGraphicsRenderImg0(imgCrossPlatformID,&crossPlatforms[i]->target);

		swGraphicsSetBlendingMode(SW_BLENDING_MODE_NONE);
		swGraphicsSetColor0(1,1,1,1);
		swRect rect;
		swRectCopy(&rect,&crossPlatforms[i]->target);
		rect.x+=20; rect.y-=10; rect.w-=40; rect.h-=4;
		swGraphicsRenderImg0(imgColorIDS[crossPlatforms[i]->color],&rect);

	}
	if(first) first = !first;

	if(!ActivateClick){
		swGraphicsSetBlendingMode(SW_BLENDING_MODE_ADDITIVE);
		swGraphicsSetColor0(0,1,0,1);
		swGraphicsRenderText(false,0,32,120,80,0,"Click, Drag & Release To Reach The Green");
	}

	if(score<=0){
		swAudioStopSource(bgSoundSourceID);
		activeFunc=stageEndOfSceneInit;
	}

}
//---------------------------------------------------------------------------------
void stageCrossingDeInit(){
	//
}