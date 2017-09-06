#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "DragonBonesHeaders.h"
#include "dragonBones/cocos2dx/CCDragonBonesHeaders.h"
#include "cocos2d.h"
using namespace dragonBones;
class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
    CCFactory factory;
    dragonBones::Armature* _armature;
    dragonBones::CCArmatureDisplay* _armatureDisplay;
    //static const std::string NORMAL_ANIMATION_GROUP;
   
};

#endif // __HELLOWORLD_SCENE_H__
