//
//  kEllipseLayer.cpp
//  cctest01
//
//  Created by kael on 12/5/12.
//
//

#include "kEllipseLayer.h"
using namespace cocos2d;
kEllipseLayer::kEllipseLayer()
{
}

void kEllipseLayer::draw()
{
    CHECK_GL_ERROR_DEBUG();
    
    ccDrawCircle(ccp(0, 0), 16, 350, 300, false, 1, 1);
    
    CHECK_GL_ERROR_DEBUG();
}

bool kEllipseLayer::init()
{
    return true;
}