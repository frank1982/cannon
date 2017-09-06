
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

    
};


#endif /* MainScene_h */
