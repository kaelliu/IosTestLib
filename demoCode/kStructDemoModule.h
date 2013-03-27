//
//  kStructDemoModule.h
//  demoCode
//
//  Created by kael on 12/22/12.
//
//

#ifndef demoCode_kStructDemoModule_h
#define demoCode_kStructDemoModule_h

#include<vector>
struct UserInfo
{
    unsigned short _id;
    unsigned char sexual;
    char name[16];
};
// c->s
struct kRegisterUser
{
    char name[16];
    unsigned char sexual;
};

struct kDeleteUser
{
    unsigned short _id;
};

struct kModifyUser
{
    unsigned short _id;
    char newName[16];
    unsigned char sexual;
};

struct kQueryUser
{
    unsigned short page;
};

// s->c
struct kQueryResult
{
    std::vector<UserInfo> users;
    unsigned short curpage;
};

struct kOperateResult
{
    int code;// if success,code is command what you send,if failed is errorcode
};

#endif
