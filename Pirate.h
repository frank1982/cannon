
#ifndef Priate_h
#define Priate_h

#include "Monster.h"
#include "Constant.h"

class Pirate:public Monster{

public:
    
    Pirate();
    ~Pirate();
 
    void PLAY_ANIMATION_WALK();
    void PLAY_ANIMATION_HIT();
    void PLAY_ANIMATION_ONHIT();
    void PUTATPOSITION(Vec2 point);
    void SETSCALE(float scale);
     
};


#endif /* Priate_h */
