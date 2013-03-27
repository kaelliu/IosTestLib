//
//  kCommonStruct.h
//
//  Created by kael on 12/26/12.
//
//

#ifndef _kCommonStruct_h
#define _kCommonStruct_h
// common data struct for editor data
#include<string>
#include<map>
struct kNpcStruct
{
    unsigned short id;
    std::string name;// npc name
    std::string icon;// animate picture
    std::string face;// head
    short x;
    short y;
    std::string dialogure;
};

// normal/hero fb portal in map struct
struct kFbNode
{
    std::string fbList;// fb id list
    short x;
    short y;// portal position
    //unsigned char type;// 1 for normal,2 for hero
};

struct kMapStruct
{
    int   mid;// map id
    short initx;// role initial position x
    short inity;
    unsigned short column;
    std::string name;// map name
    std::string walkArr;// walkable or unwalkable array for path finding in this map
    std::map<unsigned short,kNpcStruct> npclist;
    kFbNode normal;
    kFbNode hero;
};

#endif
