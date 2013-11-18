#ifndef XEN_SOUND_H
#define XEN_SOUND_H


typedef enum _xenSoundType{
  SOUND_OF_CLAW_WEAPON_BULLET_SHOT,
  SOUND_OF_CLAW_WEAPON_BULLET_COLLIDE,
  SOUND_OF_BARREL_EXPLODE,
}xenSoundType;

void soundInit();
void soundDeInit();
void soundPlay(xenSoundType type);

#endif
