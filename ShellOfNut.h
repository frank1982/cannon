
#ifndef ShellOfNut_h
#define ShellOfNut_h



#include "Monster.h"
#include "Constant.h"
#include "Shell.h"

class ShellOfNut:public Shell{
    
public:
    
    ShellOfNut();
    ~ShellOfNut();
    
    void PLAY_ANIMATION_BOOM();
    void PLAY_ANIMATION_FLY();
    void BOOM();
    
};


#endif /* ShellOfNut_h */
