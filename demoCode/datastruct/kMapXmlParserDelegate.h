//
//  kMapXmlParserDelegate.h
//
//  Created by kael on 12/26/12.
//
//

#ifndef __kMapXmlParserDelegate__
#define __kMapXmlParserDelegate__

#include"../lib.kael/kRapidXmlParserDelegate.h"

class kMapXmlParserDelegate:public kRapidXmlParserDelegate
{
public:
    virtual ~kMapXmlParserDelegate(){}
    virtual void toStruct(const rapidxml::xml_document<>& doc,void* pdata);//
};

#endif /* defined(__kMapXmlParserDelegate__) */
