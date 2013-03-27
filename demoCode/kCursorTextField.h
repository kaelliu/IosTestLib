//
//  kCursorTextField.h
//
// Created by kael on 12/22/12.
//

#ifndef CursorInputDemo_CursorTextField_h
#define CursorInputDemo_CursorTextField_h

#include "cocos2d.h"

USING_NS_CC;

class kCursorTextField: public CCTextFieldTTF, public CCTextFieldDelegate, public CCTouchDelegate
{
private:
    // start poisition 
    CCPoint m_beginPos;
    
    CCSprite *m_pCursorSprite;
    
    CCAction *m_pCursorAction;
                 
    CCPoint m_cursorPos;
    
    // contents
    std::string *m_pInputText;
    CC_SYNTHESIZE(bool, m_bIsHideTheTextAfterInput, IsHideTheTextAfterInput);
public:
    kCursorTextField();
    ~kCursorTextField();
    
    // static
    static kCursorTextField* textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);
    
    // CCLayer
    void onEnter();
    void onExit();
    
    // init the cursor sprite
    void initCursorSprite(int nHeight);
    
    // CCTextFieldDelegate
    virtual bool onTextFieldAttachWithIME(CCTextFieldTTF *pSender);
    virtual bool onTextFieldDetachWithIME(CCTextFieldTTF * pSender);
    virtual bool onTextFieldInsertText(CCTextFieldTTF * pSender, const char * text, int nLen);
    virtual bool onTextFieldDeleteBackward(CCTextFieldTTF * pSender, const char * delText, int nLen);

    // CCLayer Touch
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    //
    bool isInTextField(CCTouch *pTouch);
    // get rect of this
    CCRect getRect();
    
    // open ime window
    void openIME();
    // close ime window
    void closeIME();
};

#endif
