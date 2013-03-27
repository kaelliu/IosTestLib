//
//  kCommonEditBoxEx.cpp
//  demoCode
//
//  Created by kael on 12/22/12.
//
//

#include "kCommonEditBoxEx.h"
using namespace cocos2d;
using namespace cocos2d::extension;
kCommonEditBoxEx::~kCommonEditBoxEx()
{
    
}

kCommonEditBoxEx* kCommonEditBoxEx::textFieldWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::extension::CCScale9Sprite* pNormal9SpriteBg,cocos2d::CCTextAlignment eAlignment, const char* pszFontName, float fFontSize , const cocos2d::ccColor3B& fontColor)
{
    kCommonEditBoxEx* pTextField = new kCommonEditBoxEx;
    
	if (pTextField && pTextField->initWithWidthAndHeight(fContentWidth, fContentHeight,pNormal9SpriteBg, eAlignment, pszFontName, fFontSize, fontColor))
	{
		pTextField->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pTextField);
	}
    
	return pTextField;
}

bool kCommonEditBoxEx::initWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::extension::CCScale9Sprite* pNormal9SpriteBg,cocos2d::CCTextAlignment eAlignment, const char* pszFontName, float fFontSize, const cocos2d::ccColor3B& fontColor)
{
    
    CCAssert(fContentWidth > 0.0f, "wrong size");
    //        if(!initWithTexture(NULL, CCRectZero)){
    //            return false;
    //        }
    //
    cocos2d::CCSize contentSize = CCSizeMake(fContentWidth, fContentHeight);
    //		CC_BREAK_IF(!CCTextFieldTTF::create("hello kael", pszFontName, fFontSize, contentSize, eAlignment));
    editbox = cocos2d::extension::CCEditBox::create(CCSizeMake(fContentWidth, fContentHeight), pNormal9SpriteBg);
    editbox->setPosition(ccp(0,0));
    editbox->setAnchorPoint(ccp(0,0));
    editbox->setFontColor(fontColor);
    editbox->setPlaceHolder("");
    editbox->setMaxLength(8);
    editbox->setReturnType(cocos2d::extension::kKeyboardReturnTypeDone);
    editbox->setDelegate(this);
    this->addChild(editbox);
    return true;
}

void kCommonEditBoxEx::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox){}
void kCommonEditBoxEx::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox){}
void kCommonEditBoxEx::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text){}
void kCommonEditBoxEx::editBoxReturn(cocos2d::extension::CCEditBox* editBox){}
