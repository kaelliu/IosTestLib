//
//  kXmlParser.cpp
//  cctest01
//
//  Created by kael on 12/5/12.
//
//

#include "kXmlParser.h"

kXmlParser * kXmlParser::parserWithFile(const char *tmxFile)
{
    kXmlParser *pRet = new kXmlParser();
    if(pRet->initHXmlParse(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool kXmlParser::initHXmlParse(const char* xmlName)
{
    mDic = CCDictionary::create();
    CCSAXParser _par;
    if (false == _par.init("UTF-8") )
    {
        CCLog("-----请使用utf-8格式!");
        return false;
    }
    _par.setDelegator(this);
    const char* _path =CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(xmlName);
    return _par.parse(_path);
}

// call back

void kXmlParser::startElement(void *ctx, const char *name, const char **atts)
{
    CC_UNUSED_PARAM(ctx);
    startXmlElement = (char*)name;
    // do your own work here,name is key,atts is attribute,see CCTMXTiledMap 's xml operation as detail
    if(!isJumpHeadData){
        CCLog("------jump root name");
        isJumpHeadData=true;
        root_name=startXmlElement;
        return;
    }
}

void kXmlParser::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    endXmlElement = (char*)name;
    if(endXmlElement==root_name){// tail of data
        CCLog("read xml over");
        isJumpHeadData=false;
        root_name="";
        return;
    }
}

//
void kXmlParser::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    currString=string((char*)ch,0,len);
    CCString *ccStr =new CCString();// 
    ccStr->m_sString=currString;
    if(root_name!=""){
        // not value incluse,skip it
        if (ccStr->m_sString.find("\n")!=string::npos) {
            return;
        }
        mDic->setObject(ccStr,startXmlElement);
        CCLog("-----key:%s, value:%s",startXmlElement.c_str(),mDic->valueForKey(startXmlElement)->m_sString.c_str());
    }
}

