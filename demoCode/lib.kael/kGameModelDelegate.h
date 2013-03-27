//
//  kGameModelDelegate.h
//
//  Created by kael on 12/6/12.
//
//

#ifndef _kGameModelDelegate_h
#define _kGameModelDelegate_h

// Game Model,which implete the game logic interface for other class call
class kGameModelDelegate
{
public:
    virtual ~kGameModelDelegate()=0;
    virtual void onNetworkDataCome(short cmd,void* pdata)=0;
};

#endif
