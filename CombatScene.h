

#ifndef CombatScene_h
#define CombatScene_h

#include "cocos2d.h"
#include "CombatBgLayer.h"
#include "CombatCtrlLayer.h"
#include "PhysicLayer.h"


using namespace cocos2d;

class CombatScene : public cocos2d::Scene
{
public:
    
    static cocos2d::Scene* createScene(int stageNum);
    virtual bool init();
    CREATE_FUNC(CombatScene);
    CCSize visibleSize;
    Vec2 origin;
    int stageNum;
    
    CombatBgLayer* bgLayer;
    CombatCtrlLayer* ctrlLayer;
    PhysicLayer* physicLayer;
    
    
};

#endif /* CombatScene_h */
