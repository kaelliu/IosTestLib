//
//  kSingleton.h
//  Created by kael on 12/6/12.
//
//

#ifndef __kSingleton__
#define __kSingleton__
#include <assert.h>
template <typename T> class kSingletonTemplate
{
protected:
    static T* m_singleton;
public:
    kSingletonTemplate()
    {
        assert(!m_singleton);
    #if defined( _MSC_VER ) && _MSC_VER < 1200
        int offset = (int)(T*)1 - (int)(kSingleton <T>*)(T*)1;
        m_singleton = (T*)((int)this + offset);
    #else
        m_singleton = static_cast< T* >( this );
    #endif
    }
    
    ~kSingletonTemplate()
    {
        assert( m_singleton );  m_singleton = 0; 
    }
    
    static T& getSingleton()
    {
        assert(m_singleton);
        return *m_singleton;
    }
    
    static T* getSingletonPtr()
    {
        return m_singleton;
    }
};

#endif /* defined(__kSingleton__) */
