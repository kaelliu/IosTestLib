//
//  kGameModel.cpp
//  cctest01
//
//  Created by kael on 12/6/12.
//
//

#include "kGameModel.h"
#include "kDefination.h"

// init the static member,or it will wrong at link baby
template<> kGameModel* kSingleton<kGameModel>::_singleton = NULL;

void kGameModel::onNetworkDataCome(short cmd, const Json::Value&)
{
    switch (cmd) {
        case MAIN_CMD_LOGIN:
            ;
            break;
            
        default:
            break;
    }
}

kGameModel::~kGameModel()
{
    //
}