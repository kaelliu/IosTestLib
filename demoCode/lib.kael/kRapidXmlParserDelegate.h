//
//  kRapidXmlParserDelegate.h
//
//  Created by kael on 12/17/12.
//
//

#ifndef _kRapidXmlParserDelegate_h
#define _kRapidXmlParserDelegate_h
#include "rapidxml.hpp"
// parser base interface
// marco of read node's specify attribute's value
#define K_GET_RAPIDXML_ATTRIBUTE_VALUE(pAttr,node,attrKey) rapidxml::xml_attribute<>* pAttribute##pAttr = (node)->first_attribute((attrKey));\
    if(pAttribute##pAttr){(pAttr) = pAttribute##pAttr->value();}

class kRapidXmlParserDelegate
{
public:
    virtual void toStruct(const rapidxml::xml_document<>& doc,void* pdata)=0;
    virtual ~kRapidXmlParserDelegate(){};
};

#endif
