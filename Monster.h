

#ifndef Monster_h
#define Monster_h

#include "cocos2d.h"
#include "DragonBonesHeaders.h"
#include "dragonBones/cocos2dx/CCDragonBonesHeaders.h"
#include "Constant.h"

using namespace cocos2d;
using namespace dragonBones;




class Monster{

public:
    
    MonsterType TYPE;
    float LIFE;
    float SPEED;
    float PHSIC_DEFENSE;
    float FIRE_DEFENSE;
    MonsterStatus STATUS;
    Sprite* MONSTER_SP;
    //CCFactory factory;
    CCArmatureDisplay* MONSTER_ARMATURE_DISPLAY;
    Sprite* LIFE_SP;
    /*
    virtual void PLAY_ANIMATION_WALK()=0;
    virtual void PLAY_ANIMATION_HIT()=0;
    virtual void PLAY_ANIMATION_ONHIT()=0;
    CCDictionary LOOTRATE;
    virtual void PUTATPOSITION(Vec2 point)=0;
    virtual void SETSCALE(float scale)=0;
    */
    void PLAY_ANIMATION_WALK();
    void PLAY_ANIMATION_HIT();
    void PLAY_ANIMATION_ONHIT();
    CCDictionary LOOTRATE;
    void PUTATPOSITION(Vec2 point);
    void SETSCALE(float scale);

};


#endif /* Monster_h */
