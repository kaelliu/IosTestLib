//
//  kCommonEditbox.h
//  demoCode
//
//  Created by kael on 12/22/12.
//
//

#ifndef __demoCode__kCommonEditbox__
#define __demoCode__kCommonEditbox__

#include "cocos2d.h"
class kCommonEditbox:public cocos2d::CCTextFieldTTF,public cocos2d::CCTextFieldDelegate
                   , public cocos2d::CCTouchDelegate
{
public:
//    CREATE_FUNC(kCommonEditbox);
    virtual ~kCommonEditbox();
    // init a editor box
    static kCommonEditbox* textFieldWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::CCTextAlignment eAlignment = cocos2d::kCCTextAlignmentLeft, const char* pszFontName = "Arial", float fFontSize = 20.0f, const cocos2d::ccColor3B& fontColor = cocos2d::ccBLACK,const char * placeholder="kael");
    bool initWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::CCTextAlignment eAlignment, const char* pszFontName, float fFontSize, const cocos2d::ccColor3B& fontColor,const char * placeholder="kael");
    virtual void updateCursor(float dt);
    
    virtual void onEnter();

	virtual void onExit();
    
    virtual bool attachWithIME();
    
    virtual bool detachWithIME();
//
    virtual void insertText(const char * text, int len);
//
	virtual void deleteBackward();
    const char * getContents(){return this->getString();}
    // CCLayer Touch
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    // is touch in textfield
    bool isInTextField(cocos2d::CCTouch *pTouch);
    void clearContent(){}
protected:
    kCommonEditbox();
    CC_SYNTHESIZE(float, m_fSpeed, Speed);
	CC_SYNTHESIZE(int, m_nLimitFontCount, LimitFontCount);
	CC_SYNTHESIZE(bool, m_bIsHideTheTextAfterInput, IsHideTheTextAfterInput);
    cocos2d::CCRect getRect();
    // click start position
    cocos2d::CCPoint m_beginPos;
};

#endif /* defined(__demoCode__kCommonEditbox__) */
