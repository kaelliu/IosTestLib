//
//  kXmlParser.h
//  xml file parser
//
//  Created by kael on 12/5/12.
//
//

#ifndef __kXmlParser__
#define __kXmlParser__

#include "cocos2d.h"
#include <string>
using namespace cocos2d;
using namespace std;
// xml parser delegate from ccsaxparser
class kXmlParser:public CCSAXDelegator,CCObject
{
public:
    static kXmlParser * parserWithFile(const char *tmxFile);
    bool initHXmlParse(const char* xmlName);
    // rewrite CCSAXDelegator 
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    // end
    std::string root_name;
    bool isJumpHeadData;
    CCDictionary* mDic;         // for simple key value mode <key>value</key>
private:
    std::string startXmlElement;//用来记录每个key前字段
    std::string endXmlElement;  //用来记录每个key后字段
    std::string currString;     //记录每个value的值
};

#endif 
