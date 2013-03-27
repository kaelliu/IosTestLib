//
//  kSingleton.h
//
//  Created by kael on 12/6/12.
//
//

#ifndef _kSingleton_h
#define _kSingleton_h

template <typename T>
class kSingleton
{
protected:
    static T* _singleton;
    kSingleton(){};
    kSingleton(const T& copy){}
public:
    virtual ~kSingleton(){
        if (_singleton) {
            delete _singleton;
            _singleton = 0;
        }
    }
    
    static T& getInstance()
    {
        if (_singleton==0) {
            _singleton = new T;
        }
        return *_singleton;
    }
    
    static T* getInstancePtr()
    {
        if (_singleton==0) {
            _singleton = new T;
        }
        return _singleton;
    }
};

#endif
