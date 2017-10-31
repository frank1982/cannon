

#include <stdio.h>
#include "Cannon.h"

Cannon* Cannon:: m_instance  = NULL;//初始化在主线程之前
Cannon::Cannon(){

    CCLOG("初始化大炮");
    _cannon_status=readyForLoadShell;
    
}

Cannon* Cannon::GetInstance(){

    if(m_instance == NULL){  //判断是否第一次调用
        m_instance = new Cannon();
    }
    return m_instance;
}
