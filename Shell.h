
#ifndef Shell_h
#define Shell_h

#include "cocos2d.h"
#include "Constant.h"

using namespace cocos2d;

class Shell{
    
public:
    
    ShellType TYPE;
    float DAMAGE;
    

    Sprite* SHELL_SP;

    void PLAY_ANIMATION_BOOM();
    void PLAY_ANIMATION_FLY();
    void BOOM();

    
};

#endif /* Shell_h */
