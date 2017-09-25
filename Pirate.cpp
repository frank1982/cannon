
#include <stdio.h>
#include "Pirate.h"

Pirate::Pirate(){
    
    CCLOG("create a pirate");
    TYPE=PIRATE;
    STATUS=NORMAL;
    LIFE=100;
    SPEED=5;
    PHSIC_DEFENSE=10;
    FIRE_DEFENSE=0;
    
    dragonBones::CCFactory::factory.loadDragonBonesData("res/skeleton/demo_ske.json");
    dragonBones::CCFactory::factory.loadTextureAtlasData("res/skeleton/demo_tex.json");
    MONSTER_ARMATURE_DISPLAY = nullptr;
    MONSTER_ARMATURE_DISPLAY = dragonBones::CCFactory::factory.buildArmatureDisplay("pirate");

    
}

Pirate::~Pirate(){
    
}
//所有的虚函数都要实现
void Pirate::PLAY_ANIMATION_WALK(){};
void Pirate::PLAY_ANIMATION_HIT(){};
void Pirate::PLAY_ANIMATION_ONHIT(){};
void Pirate::PUTATPOSITION(Vec2 point){
    
    MONSTER_ARMATURE_DISPLAY->setPosition(point);
};
void Pirate::SETSCALE(float scale){
    
    MONSTER_ARMATURE_DISPLAY->setScale(scale);
};
