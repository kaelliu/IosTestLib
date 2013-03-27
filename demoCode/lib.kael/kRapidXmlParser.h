//
//  kRapidXmlParser.h
//
//  Created by kael on 12/17/12.
//
//

#ifndef _kRapidXmlParser_h
#define _kRapidXmlParser_h

#include"kRapidXmlFile.h"
#include "cocos2d.h"
#include "kRapidXmlParserDelegate.h"
// parser wrapper
class kRapidXmlParser
{
public:
    kRapidXmlParser(const char* filename,kRapidXmlParserDelegate* delegate)
    {
        const char* path = cocos2d::CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(filename);
        kRapidXmlFile<char> file(path);
        doc.parse<0>(file.data());
        m_delegate = delegate;
    }
    
    ~kRapidXmlParser()
    {
        doc.clear();
        if (m_delegate) {
            // you should make sure delegate be delete outside
//            delete m_delegate;
//            m_delegate = NULL;
        }
    }
    
    // xml data to relate struct data
    void toStruct(void* pdata)
    {
        m_delegate->toStruct(doc,pdata);
    }
    
//    void setDelegate(kRapidXmlParserDelegate* delegate);
protected:
    xml_document<> doc;
    kRapidXmlParserDelegate* m_delegate;
};

#endif
