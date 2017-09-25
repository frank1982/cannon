
#ifndef PhysicLayer_h
#define PhysicLayer_h
#include "Monster.h"
#include "Pirate.h"


using namespace cocos2d;

class PhysicLayer : public cocos2d::LayerColor
{
    
public:
    
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(PhysicLayer);
    int STAGENUM;
    
    Vec2 origin;
    CCSize visibleSize;

    void loadCannon();
    void loadLife();
    void loadBarrier();
    
    std::vector<Sprite*> _lifeVector;
    Sprite* cannonBase;
    Sprite* cannonGun;
    Sprite* barrierSp;
    Sprite* _shellSp;
    void cannonShoot(float shootAngle);
    PhysicsWorld* m_world;
    
    void update(float dt);
    bool _inExplosion;
    void notificationHandler(Ref* obj);
    
    //CCFactory factory;
    //dragonBones::Armature* _armature;
    //dragonBones::CCArmatureDisplay* _armatureDisplay;
    
    void monsterManagerWork();
    void addMonster(MonsterType monsterType,Vec2 position);
    void statusManagerWork();//FSM
    
    std::vector<Monster> _monsterVectors;//所有monster数组

};

#endif /* PhysicLayer_h */
