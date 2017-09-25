
#ifndef MainScene_h
#define MainScene_h
#include "cocos2d.h"
#include "cocos-ext.h"
#include "MapScene.h"

class MainScene : public cocos2d::Scene
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);

    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

};


#endif /* MainScene_h */
