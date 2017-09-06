

#ifndef GameScene_h
#define GameScene_h

#include "DragonBonesHeaders.h"
#include "dragonBones/cocos2dx/CCDragonBonesHeaders.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include <cmath>



using namespace dragonBones;
USING_NS_CC;
using namespace cocos2d::ui;


class GameScene : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(GameScene);
    int _nowStageNum;
    
    CCFactory factory;
    dragonBones::Armature* _armature;
    dragonBones::CCArmatureDisplay* _armatureDisplay;
    //CCLayer* bgLayer;

    CCLayer* groundLayer;
    
    CCSize visibleSize;
    Vec2 origin;
    
    void loadCannon();
    void loadDriver();
    CCSprite* cannonGunSp;
    
    
    CCSprite* driverBgSp;
    CCSprite* driverPointerSp;
    CCPoint tmpTouchPointCatched;
    float driverAngle;
    float bombRadius;
    //添加物理世界创建方法
    void setPhyWorld(PhysicsWorld* world){
        m_world = world;
    }
    PhysicsWorld* m_world;
    CCSprite* bombSp;
    
    
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    
    void Update(float dt);
};


#endif /* GameScene_h */
