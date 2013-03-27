//
//  kGameModel.h
//
//  Created by kael on 12/6/12.
//
//

#ifndef __kGameModel__
#define __kGameModel__

// Game data placeholder
#include "kSingleton.h"
#include "json.h"
class kGameModel:public kSingleton<kGameModel>
{
    //friend class kSingleton<kGameModel>;
public:
    //kGameModel();
    virtual ~kGameModel();
    void onNetworkDataCome(short cmd,const Json::Value&);
protected:
    // ROLE DATA,SAVE PLACE
};

#endif /* defined(__kGameModel__) */
