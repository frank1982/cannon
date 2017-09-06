//
//  MapScene.h


#ifndef MapScene_h
#define MapScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameScene.h"

class MapScene : public cocos2d::Scene
{
public:
    
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MapScene);
    void loadFullPathes();
    void loadPathAndStageFlag(int nowProcess);
};


#endif /* MapScene_h */
