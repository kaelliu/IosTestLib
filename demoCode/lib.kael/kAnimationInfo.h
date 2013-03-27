//
//  kAnimationInfo.h
//  cctest01
//
//  Created by kael on 12/5/12.
//
//

#ifndef __kAnimationInfo_h
#define __kAnimationInfo_h

// animation info
struct kAnimationInfo
{
    // strtk parse consider /xFF as unsigned char and also char
    // so here use short for instead
    unsigned short from;
    unsigned short to;
    unsigned short anchor_x;
    unsigned short anchor_y;
    char          name[16];
};

// avatar layer info
// layer contain an animation info
/*
    layer_container
        |-> layer one
                |-> sprite -> animation containter
                    |-> animation info
        |-> layer two 
        ...
    such as a man with weapon,mount,shadow,effect together
    p2.layer
    <weapon zorder=1 lx=30 ly=100/>
    <mount zorder=2 lx=0 ly=200/>
    <shadow zorder=3 lx=0 ly=120/>
    1.need change all animation
    2.consider anchor all in 0.5,0.5
*/
struct kLayerInfo {
    unsigned char zorder;
    int layerPosx;
    int layerPoxy;
    char layerName[16];
};

#endif
