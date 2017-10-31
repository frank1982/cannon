
#ifndef Cannon_h
#define Cannon_h

#include "cocos2d.h"
#include "Constant.h"

using namespace cocos2d;
//单例
class Cannon{
 
public:
    
    static Cannon* GetInstance();
    //Sprite* _cannonBase;
    //Sprite* _cannonGun;
    CannonStatus _cannon_status;//暂时只控制状态
    
    
private:
    Cannon();   //构造函数是私有的
    ~Cannon();
    static Cannon* m_instance;
};


#endif /* Cannon_h */
