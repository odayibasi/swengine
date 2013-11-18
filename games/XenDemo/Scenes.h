#ifndef XEN_SCENES_H
#define XEN_SCENES_H

//Intro
void introInit();
void introDeInit();
void introRun();


//About
void aboutInit();
void aboutRun();
void aboutDeInit();


//Scene
void sceneGenerate();
void sceneIntroInit();
void sceneIntroRun();
void sceneIntroDeInit();
void scenePlayInit();
void scenePlayRun();
void scenePlayRestart();
void scenePlayExit();


//MainGui
void mainGui_MainPageDisplay();
void mainGui_LevelSelectionDisplay();

#endif