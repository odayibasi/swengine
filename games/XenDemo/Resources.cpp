#include "../../include/SWEngine.h"
#include "XenCommon.h"


swDimension winSize={1024,768};

//Audio
int         bgMusicBufferID;
int			clawWpnSoundBufferID;
int			clawWpnCollideSoundBufferID;
int			barrelExplodeSoundBufferID;


//Intro
int			fontID;
int         logoID;
int         xenRunID;

//editor
int         editorFontID;
int         editorLogoID;
int         editorIconSetID;


//Shader
int         shdGrayscaled;
int         shdSharpen;
int         shdDiognalBlur;
int         shdInverted;
int         shdEmboss;
int         shdMultiplier;
int         shdShockWave;


//Wall & Bg
int         bgWallImgID;
int         edgeWallImgID;

int         columnPartID;
int         columnBlockID;

int         clawOthersID;
int         clawPitID;
int			barrelID;
int			barrelSlowMotionID;
int         particleLitID;
int         airventID;
int			turretSpriteID;

int         hutID;
int         fenceID;
int         labelID;
int         doorID;

int         elevatorID;
int         elevatorPartID;


//Claw
int         clawBodySprID;
int         clawArmSprID;
int         clawHandSprID;
int         clawTargetImgID;

int         img7D8ID;
int         img7D8Party;
int         img7D8Symbol;


char		clawBodyPath[64]="Claw\\ClawBodyAnim\\";
char		clawArmPath[64]="Claw\\ClawArmAnim\\";
char		clawHandPath[64]="Claw\\ClawHandAnim\\";
char		clawTargetPath[64]="Claw\\ClawTarget.tga";


//Defender
int			defenderAvoidID;
int			defenderRotateID;
int			defenderFireID;


char		defenderAvoidPath[64]="Defender\\Avoid\\";
char		defenderRotatePath[64]="Defender\\Rotate\\";
char		defenderFirePath[64]="Defender\\Fire\\";


//WeaponIcon
int        bulletIcon;
int        acidIcon;
int        lawIcon;
int        laserIcon;
int        gravityIcon;
int        guidedIcon;
int        misketIcon;
int        cristalIcon;

//Weapon
int        wpnBullet;
int        wpnEBullet;

//Explosion
int        explosionID;



//HUD
int  hudEngineStartLedID,hudDangerLedID;
int  hudHealthID,hudArmorID;
int  hudWeaponID,hudWeaponBtnID,hudWeaponTxtID;
int  hudBombPanelShadowID, hudLayoutID, hudCockpitGlowID;
int  hudBombBarID,hudAmmoBarID;
int  hudCockpitCrashID,hudCockpitStillID,huCockpitExplodeID;
int  hudBombID;

//Entity
int			cargoBoxID;
int			laserHoseID;
int			platformID;


//MaiGui
int			xenLogoImgID;
int         playBtnImgID;
int         playBtnMOverImgID;
int         exitBtnImgID;
int         exitBtnMOverImgID;
int         creditsBtnImgID;
int         creditsBtnMOverImgID;
int         storyBtnImgID;
int         storyBtnMOverImgID;
int         hScoreBtnImgID;
int         hScoreBtnMOverImgID;
int         helpBtnImgID;
int         helpBtnMOverImgID;


//LevelLayout
int			xenLvlLayoutImgID;
int			xenLvlLayoutCogImgID;
int			xenLvlLayoutValidImgID;
int			backBtnImgID;
int			backBtnMOverImgID;
int			continueBtnImgID;
int			continueBtnMOverImgID;


//-------------------------------------------------------------------------------------------
void unregisterGLSLShader(){
	//TODO add destroy function to GLSL
}


//-------------------------------------------------------------------------------------------
void registerGLSLShader(){

	if(xenDemoIsSupportPostProcessing()){
		shdGrayscaled=swGraphicsCreateGLSLShader("GLSLScript/fixed.vert","GLSLScript/grayscale.frag");
		shdSharpen=swGraphicsCreateGLSLShader("GLSLScript/fixed.vert","GLSLScript/sharpen.frag");
		shdDiognalBlur=swGraphicsCreateGLSLShader("GLSLScript/fixed.vert","GLSLScript/diognalblur.frag");
		shdInverted=swGraphicsCreateGLSLShader("GLSLScript/fixed.vert","GLSLScript/inverted.frag");
		shdEmboss=swGraphicsCreateGLSLShader("GLSLScript/fixed.vert","GLSLScript/emboss.frag");
		shdMultiplier=swGraphicsCreateGLSLShader("GLSLScript/fixed.vert","GLSLScript/multiplier.frag");
		shdShockWave=swGraphicsCreateGLSLShader("GLSLScript/fixed.vert","GLSLScript/shockwave.frag");
	}
}


//-------------------------------------------------------------------------------------------
void unregisterWeaponIconResources(){
	swGraphicsDestroyImg(bulletIcon);
	swGraphicsDestroyImg(acidIcon);
	swGraphicsDestroyImg(lawIcon);
	swGraphicsDestroyImg(laserIcon);
	swGraphicsDestroyImg(gravityIcon);
	swGraphicsDestroyImg(guidedIcon);
	swGraphicsDestroyImg(misketIcon);
	swGraphicsDestroyImg(cristalIcon);
}


//-------------------------------------------------------------------------------------------
void registerWeaponIconResources(){
	bulletIcon=swGraphicsCreateImg("Weapon/BulletIcon.TGA");;
	acidIcon=swGraphicsCreateImg("Weapon/AcidIcon.TGA");
	lawIcon=swGraphicsCreateImg("Weapon/LawIcon.TGA");
	laserIcon=swGraphicsCreateImg("Weapon/LaserIcon.TGA");
	gravityIcon=swGraphicsCreateImg("Weapon/GravityIcon.TGA");
	guidedIcon=swGraphicsCreateImg("Weapon/GuidedIcon.TGA");
	misketIcon=swGraphicsCreateImg("Weapon/MisketIcon.TGA");
	cristalIcon=swGraphicsCreateImg("Weapon/CristalIcon.TGA");
}



//-------------------------------------------------------------------------------------------
void unregisterHudResources(){
	//Resource Loading
	swGraphicsDestroyImg(hudLayoutID);

	//Health & Shield
	swGraphicsDestroyImg(hudHealthID);
	swGraphicsDestroyImg(hudArmorID);

	//Led
	swGraphicsDestroyImg(hudDangerLedID);
	swGraphicsDestroyImg(hudEngineStartLedID);

	//Weapon
	swGraphicsDestroyImg(hudWeaponID);
	swGraphicsDestroyImg(hudWeaponTxtID);
	swGraphicsDestroyImg(hudWeaponBtnID);


	//Ammo & Bomb Bar
	swGraphicsDestroyImg(hudBombBarID);
	swGraphicsDestroyImg(hudAmmoBarID);

	//Bomb
	swGraphicsDestroyImg(hudBombPanelShadowID);
	swGraphicsDestroyImg(hudBombID);

	//Cockpit
	swGraphicsDestroyImg(hudCockpitGlowID);
	swGraphicsDestroyImg(hudCockpitStillID);
	swGraphicsDestroyImg(hudCockpitCrashID);
	swGraphicsDestroyImg(huCockpitExplodeID);
}



//-------------------------------------------------------------------------------------------
void registerHudResources(){
	//Resource Loading
	hudLayoutID=swGraphicsCreateImg("HUD/InVehicleGUILayout.tga");

	//Health & Shield
	hudHealthID=swGraphicsCreateImg("HUD/InVehicleHealth.tga");
	hudArmorID=swGraphicsCreateImg("HUD/InVehicleArmor.tga");

	//Led
	hudDangerLedID=swGraphicsCreateImg("HUD/DangerLed.tga");
	hudEngineStartLedID=swGraphicsCreateImg("HUD/EngineLed.tga");

	//Weapon
	hudWeaponID=swGraphicsCreateSprite("HUD/Weapon/");
	hudWeaponTxtID=swGraphicsCreateSprite("HUD/WeaponTxt/");
	hudWeaponBtnID=swGraphicsCreateSprite("HUD/WeaponBtn/");


	//Ammo & Bomb Bar
	hudBombBarID=swGraphicsCreateSprite("HUD/BombBar/");
	hudAmmoBarID=swGraphicsCreateSprite("HUD/AmmoBar/");

	//Bomb
	hudBombPanelShadowID=swGraphicsCreateImg("HUD/BombPanelShadow.tga");
	hudBombID=swGraphicsCreateSprite("HUD/Bomb/");

	//Cockpit
	hudCockpitGlowID=swGraphicsCreateImg("HUD/CockpitGlow.tga");
	hudCockpitStillID=swGraphicsCreateSprite("HUD/CockpitStill/");
	hudCockpitCrashID=swGraphicsCreateSprite("HUD/CockpitCrash/");
	huCockpitExplodeID=swGraphicsCreateSprite("HUD/CockpitExplode/");
}


//-------------------------------------------------------------------------------------------
void unregisterSoundResources(){
	swAudioDestroyBuffer(bgMusicBufferID);
}

//-------------------------------------------------------------------------------------------
void registerSoundResources(){
	barrelExplodeSoundBufferID=swAudioCreateBuffer("Sound/Explode.ogg",SW_AUDIO_BUFFER_TYPE_OGG);
	clawWpnSoundBufferID=swAudioCreateBuffer("Sound/WpnBulletShot.wav",SW_AUDIO_BUFFER_TYPE_WAV);
	clawWpnCollideSoundBufferID=swAudioCreateBuffer("Sound/WpnBulletCollide.wav",SW_AUDIO_BUFFER_TYPE_WAV);
	bgMusicBufferID=swAudioCreateBuffer("XenDemo.ogg",SW_AUDIO_BUFFER_TYPE_OGG_STREAM);	
}



//-------------------------------------------------------------------------------------------
void unregisterEditorResources(){
	swGraphicsDestroyImg(editorFontID);
	swGraphicsDestroyImg(editorLogoID);
	swGraphicsDestroyImg(editorIconSetID);
}


//-------------------------------------------------------------------------------------------
void registerEditorResources(){
	editorFontID=swGraphicsCreateImg("Editor/Font.tga");
	editorLogoID=swGraphicsCreateImg("Editor/Logo.tga");
	editorIconSetID=swGraphicsCreateImg("Editor/IconSet.tga");
	swNumPropWinSetDependency(editorLogoID,editorFontID,editorIconSetID);
}


//-------------------------------------------------------------------------------------------
void unregisterBgTileResources(){
	swGraphicsDestroyImg(edgeWallImgID);
	swGraphicsDestroyImg(columnPartID);
	swGraphicsDestroyImg(columnBlockID);
	swGraphicsDestroyImg(elevatorID);
	swGraphicsDestroyImg(elevatorPartID);
	swGraphicsDestroyImg(clawOthersID);
	swGraphicsDestroyImg(clawPitID);
	swGraphicsDestroyImg(particleLitID);
	swGraphicsDestroyImg(hutID);
	swGraphicsDestroyImg(fenceID);
	swGraphicsDestroyImg(labelID);
	swGraphicsDestroyImg(doorID);	
}



//-------------------------------------------------------------------------------------------
void unregisterMainGuiResources(){
	swGraphicsDestroyImg(xenLogoImgID);
	swGraphicsDestroyImg(playBtnImgID);
	swGraphicsDestroyImg(playBtnMOverImgID);
	swGraphicsDestroyImg(exitBtnImgID);
	swGraphicsDestroyImg(exitBtnMOverImgID);
	swGraphicsDestroyImg(creditsBtnImgID);
	swGraphicsDestroyImg(creditsBtnMOverImgID);
	swGraphicsDestroyImg(storyBtnImgID);
	swGraphicsDestroyImg(storyBtnMOverImgID);
	swGraphicsDestroyImg(hScoreBtnImgID);
	swGraphicsDestroyImg(hScoreBtnMOverImgID);
	swGraphicsDestroyImg(helpBtnImgID);
	swGraphicsDestroyImg(helpBtnMOverImgID);
	
	swGraphicsDestroyImg(xenLvlLayoutImgID);
	swGraphicsDestroyImg(xenLvlLayoutCogImgID);
	swGraphicsDestroyImg(xenLvlLayoutValidImgID);
	swGraphicsDestroyImg(backBtnImgID);
	swGraphicsDestroyImg(backBtnMOverImgID);	
	swGraphicsDestroyImg(continueBtnImgID);
	swGraphicsDestroyImg(continueBtnMOverImgID);

}

//-------------------------------------------------------------------------------------------
void registerMainGuiResources(){
	xenLogoImgID=swGraphicsCreateImg("MainGui/Xen.TGA");
	playBtnImgID=swGraphicsCreateImg("MainGui/btnPlayNormal.tga");
	playBtnMOverImgID=swGraphicsCreateImg("MainGui/btnPlayMOver.tga");
	exitBtnImgID=swGraphicsCreateImg("MainGui/btnExitNormal.tga");
	exitBtnMOverImgID=swGraphicsCreateImg("MainGui/btnExitMOver.tga");
	creditsBtnImgID=swGraphicsCreateImg("MainGui/btnCreditsNormal.tga");
	creditsBtnMOverImgID=swGraphicsCreateImg("MainGui/btnCreditsMOver.tga");
	storyBtnImgID=swGraphicsCreateImg("MainGui/btnStoryNormal.tga");
	storyBtnMOverImgID=swGraphicsCreateImg("MainGui/btnStoryMOver.tga");
	hScoreBtnImgID=swGraphicsCreateImg("MainGui/btnHighScoreNormal.tga");
	hScoreBtnMOverImgID=swGraphicsCreateImg("MainGui/btnHighScoreMOver.tga");
	helpBtnImgID=swGraphicsCreateImg("MainGui/btnControlsNormal.tga");
	helpBtnMOverImgID=swGraphicsCreateImg("MainGui/btnControlsMOver.tga");
	
	xenLvlLayoutImgID=swGraphicsCreateImg("MainGui/XenopLayout.tga");
	xenLvlLayoutCogImgID=swGraphicsCreateImg("MainGui/XenopLayoutCog.tga");
	xenLvlLayoutValidImgID=swGraphicsCreateImg("MainGui/XenopLayoutValid.tga");
	backBtnImgID=swGraphicsCreateImg("MainGui/btnSubCloseNormal.tga");
	backBtnMOverImgID=swGraphicsCreateImg("MainGui/btnSubCloseMOver.tga");
	continueBtnImgID=swGraphicsCreateImg("MainGui/btnNextNormal.tga");
	continueBtnMOverImgID=swGraphicsCreateImg("MainGui/btnNextMOver.tga");


}






//-------------------------------------------------------------------------------------------
void registerBgTileResources(){
	bgWallImgID=swGraphicsCreateImg("BgWall/WallBG128.TGA");
	edgeWallImgID=swGraphicsCreateImg("BgWall/WallEdge32.TGA");
	columnPartID=swGraphicsCreateImg("Column/ColumnPart.TGA");
	columnBlockID=swGraphicsCreateImg("Column/ColumnBlock.TGA");

	elevatorID=swGraphicsCreateImg("Elevator/Elevator01.TGA");
	elevatorPartID=swGraphicsCreateImg("Elevator/ElevatorPart.TGA");

	clawOthersID=swGraphicsCreateImg("BgTiles/ClawOthers.tga");
	clawPitID=swGraphicsCreateImg("BgTiles/ClawPit.tga");
	particleLitID=swGraphicsCreateImg("ParticleLit.tga");
	hutID=swGraphicsCreateImg("BgTiles/Hut01.tga");	
	fenceID=swGraphicsCreateImg("BgTiles/Fence01.tga");	
	labelID=swGraphicsCreateImg("BgTiles/Label01.tga");	
	doorID=swGraphicsCreateImg("BgTiles/DoorGeneral01.tga");	
}


//-------------------------------------------------------------------------------------------
void unregisterEntityResources(){
	swGraphicsDestroyImg(laserHoseID);
	swGraphicsDestroyImg(airventID);
	swGraphicsDestroyImg(barrelSlowMotionID);
	swGraphicsDestroyImg(barrelID);
	swGraphicsDestroySprite(turretSpriteID);
	swGraphicsDestroyImg(cargoBoxID);
}



//-------------------------------------------------------------------------------------------
void registerEntityResources(){
	laserHoseID=swGraphicsCreateImg("ElectricGate/ElectricalHose.TGA");
	airventID=swGraphicsCreateSprite("AirVent/");
	barrelID=swGraphicsCreateImg("Barrel.tga");
	barrelSlowMotionID=swGraphicsCreateImg("BarrelSlowMotion.tga");
	turretSpriteID=swGraphicsCreateSprite("Turret/");
	platformID=swGraphicsCreateImg("Platform.tga");
	cargoBoxID=swGraphicsCreateImg("CargoBox.tga");
}


//-------------------------------------------------------------------------------------------
void unregisterWeaponResources(){
	swGraphicsDestroyImg(wpnBullet);
	swGraphicsDestroyImg(wpnEBullet);
}


//-------------------------------------------------------------------------------------------
void registerWeaponResources(){
	wpnBullet=swGraphicsCreateImg("Weapon/WpnBullet.TGA");
	wpnEBullet=swGraphicsCreateImg("Weapon/EWpnBullet.TGA");
}



//-------------------------------------------------------------------------------------------
void unregisterClawResources(){
	swGraphicsDestroySprite(clawBodySprID);
	swGraphicsDestroySprite(clawArmSprID);
	swGraphicsDestroySprite(clawHandSprID);
	swGraphicsDestroyImg(clawTargetImgID);
}


//-------------------------------------------------------------------------------------------
void registerClawResources(){
	clawBodySprID=swGraphicsCreateSprite(clawBodyPath);
	clawArmSprID=swGraphicsCreateSprite(clawArmPath);
	clawHandSprID=swGraphicsCreateSprite(clawHandPath);
	clawTargetImgID=swGraphicsCreateImg(clawTargetPath);
}


//-------------------------------------------------------------------------------------------
void unregisterDefenderResources(){
	swGraphicsDestroySprite(defenderAvoidID);
	swGraphicsDestroySprite(defenderRotateID);
	swGraphicsDestroySprite(defenderFireID);
}


//-------------------------------------------------------------------------------------------
void registerDefenderResources(){
	defenderAvoidID=swGraphicsCreateSprite(defenderAvoidPath);
	defenderRotateID=swGraphicsCreateSprite(defenderRotatePath);
	defenderFireID=swGraphicsCreateSprite(defenderFirePath);
}


//-------------------------------------------------------------------------------------------
void unregisterNeonResources(){
	swGraphicsDestroyImg(img7D8ID);
	swGraphicsDestroyImg(img7D8Party);
	swGraphicsDestroyImg(img7D8Symbol);
}


//-------------------------------------------------------------------------------------------
void registerNeonResources(){
	img7D8ID=swGraphicsCreateImg("Neon7D8/7D8.TGA");
	img7D8Party=swGraphicsCreateImg("Neon7D8/7D8Party.TGA");
	img7D8Symbol=swGraphicsCreateImg("Neon7D8/7D8Symbol.TGA");
}


//-------------------------------------------------------------------------------------------
void unregisterFXResources(){
	swGraphicsDestroySprite(explosionID);
}


//-------------------------------------------------------------------------------------------
void registerFXResources(){
	explosionID=swGraphicsCreateSprite("MushroomExplosion/");
}


//-------------------------------------------------------------------------------------------
void unregisterIntroResources(){
	swGraphicsDestroyFont(fontID);
	swGraphicsDestroyImg(logoID);
	swGraphicsDestroySprite(xenRunID);

}


//-------------------------------------------------------------------------------------------
void registerIntroResources(){
	fontID=swGraphicsCreateFont("swFont.TGA");
	logoID=swGraphicsCreateImg("swLogo.TGA");
	xenRunID=swGraphicsCreateSprite("XenRun/");	
}

//-------------------------------------------------------------------------------------------
void resourceInit(){


	#ifdef DEBUG
	//registerEditorResources();
	#endif

	registerSoundResources();
	registerGLSLShader();
	
	registerMainGuiResources();
	registerHudResources();
	registerIntroResources();
	registerBgTileResources();
	registerNeonResources();
	registerEntityResources();
	registerClawResources();
	registerDefenderResources();
	registerWeaponIconResources();
	registerWeaponResources();
	registerFXResources();
}

