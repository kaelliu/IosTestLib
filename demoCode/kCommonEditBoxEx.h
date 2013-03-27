//
//  kCommonEditBoxEx.h
//  demoCode
//
//  Created by kael on 12/22/12.
//
//

#ifndef __demoCode__kCommonEditBoxEx__
#define __demoCode__kCommonEditBoxEx__

#include "cocos2d.h"
#include "cocos-ext.h"
class kCommonEditBoxEx:public cocos2d::CCLayer,cocos2d::extension::CCEditBoxDelegate
{
public:
    virtual ~kCommonEditBoxEx();
    // init a editor box
    static kCommonEditBoxEx* textFieldWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::extension::CCScale9Sprite* pNormal9SpriteBg,cocos2d::CCTextAlignment eAlignment = cocos2d::kCCTextAlignmentLeft, const char* pszFontName = "Arial", float fFontSize = 20.0f, const cocos2d::ccColor3B& fontColor = cocos2d::ccBLACK);

//    CREATE_FUNC(kCommonEditBoxEx);
    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
protected:
    cocos2d::extension::CCEditBox* editbox;
    bool initWithWidthAndHeight(float fContentWidth, float fContentHeight,cocos2d::extension::CCScale9Sprite* pNormal9SpriteBg, cocos2d::CCTextAlignment eAlignment, const char* pszFontName, float fFontSize, const cocos2d::ccColor3B& fontColor);
};

#endif /* defined(__demoCode__kCommonEditBoxEx__) */
