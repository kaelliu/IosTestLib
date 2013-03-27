//
//  kSharedData.h
//
//  Created by kael on 12/26/12.
//
//

#ifndef _kSharedData_h
#define _kSharedData_h
#include "kAction.h"
struct kRoleDto{
    int rid;// role id
    unsigned short mid;// map id
    unsigned char job; // job
    unsigned short x;  // position x
    unsigned short y;  // position y
    unsigned short lv; // 
};

struct kSharedData{
    std::list<kAction*> automatic_actions;
    kRoleDto rd;
};


#endif
