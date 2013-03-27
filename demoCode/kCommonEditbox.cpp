//
//  kCommonEditbox.cpp
//  demoCode
//
//  Created by kael on 12/22/12.
//
//

#include "kCommonEditbox.h"
using namespace cocos2d;
#define NO_FONT_COUNT_LIMIT -1
const static float DELTA = 0.5f;
kCommonEditbox::kCommonEditbox():
m_fSpeed(0.5f),
m_nLimitFontCount(NO_FONT_COUNT_LIMIT)
{
    
}

kCommonEditbox::~kCommonEditbox()
{
}

kCommonEditbox* kCommonEditbox::textFieldWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::CCTextAlignment eAlignment, const char* pszFontName, float fFontSize, const cocos2d::ccColor3B& fontColor,const char * placeholder)
{
    kCommonEditbox* pTextField = new kCommonEditbox;
    
	if (pTextField && pTextField->initWithWidthAndHeight(fContentWidth, fContentHeight, eAlignment, pszFontName, fFontSize, fontColor,placeholder))
	{
		pTextField->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pTextField);
	}
    
	return pTextField;
}

bool kCommonEditbox::initWithWidthAndHeight(float fContentWidth, float fContentHeight, cocos2d::CCTextAlignment eAlignment, const char* pszFontName, float fFontSize, const cocos2d::ccColor3B& fontColor,const char * placeholder)
{
	do
	{
		CCAssert(fContentWidth > 0.0f, "wrong size");
//        if(!initWithTexture(NULL, CCRectZero)){
//            return false;
//        }
		//
		CCSize contentSize = CCSizeMake(fContentWidth, fContentHeight);
//		CC_BREAK_IF(!CCTextFieldTTF::create("hello kael", pszFontName, fFontSize, contentSize, eAlignment));
        this->initWithString("", pszFontName, fFontSize, contentSize, eAlignment);
		this->setContentSize(contentSize);
		this->setColor(fontColor);
        this->setPlaceHolder(placeholder);
        
		return true;
	} while (0);
	
	return false;
}

void kCommonEditbox::updateCursor(float dt)
{
	static bool bIsCursorShowed = false;
    
	if (bIsCursorShowed)
	{
		std::string strText = this->getString();
		strText += "|";
		CCLabelTTF::setString(strText.c_str());
	}
	else
	{
		CCLabelTTF::setString(this->getString());
	}
    
	bIsCursorShowed = !bIsCursorShowed;
}

void kCommonEditbox::onEnter()
{
	CCTextFieldTTF::onEnter();
    cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,10,true);
    this->setDelegate(this);
}

void kCommonEditbox::onExit()
{
	CCTextFieldTTF::onExit();
    cocos2d::CCDirector::sharedDirector() ->getTouchDispatcher()->removeDelegate(this);
}

bool kCommonEditbox::attachWithIME()
{
	bool bResult = false;
    
	bResult = CCTextFieldTTF::attachWithIME();
    
	if (bResult)
	{
		this->schedule(schedule_selector(kCommonEditbox::updateCursor), m_fSpeed);
	}
    
	this->setVisible(true);
    
	return bResult;
}

bool kCommonEditbox::detachWithIME()
{
	bool bResult = false;
    
	bResult = CCTextFieldTTF::detachWithIME();
    
	if (bResult)
	{
		this->unschedule(schedule_selector(kCommonEditbox::updateCursor));
	}
    
	if (m_bIsHideTheTextAfterInput)
	{
		this->setVisible(false);
	}
    
	CCLabelTTF::setString(this->getString());
    
	return bResult;
}

void kCommonEditbox::insertText( const char * text, int len )
{
	if ((NO_FONT_COUNT_LIMIT == m_nLimitFontCount) || (this->m_nCharCount + len <= m_nLimitFontCount) )
	{
		CCTextFieldTTF::insertText(text, len);
	}
}

void kCommonEditbox::deleteBackward()
{
	CCTextFieldTTF::deleteBackward();
}


bool kCommonEditbox::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_beginPos = pTouch->getLocationInView();
    m_beginPos = CCDirector::sharedDirector()->convertToGL(m_beginPos);
    return true;
}

void kCommonEditbox::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint endPos = pTouch->getLocationInView();
    endPos = CCDirector::sharedDirector()->convertToGL(endPos);
    
    // is click event
    if (::abs(endPos.x - m_beginPos.x) > DELTA ||
        ::abs(endPos.y - m_beginPos.y))
    {
        // not click event,map be swipe or other
        m_beginPos.x = m_beginPos.y = -1;
        return;
    }
    isInTextField(pTouch) ? attachWithIME() : detachWithIME();

}

cocos2d::CCRect kCommonEditbox::getRect()
{
    CCSize size = getContentSize();
    return  CCRectMake(-size.width / 2, -size.height / 2, size.width, size.height);
}

// is touch in textfield
bool kCommonEditbox::isInTextField(CCTouch *pTouch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(pTouch));
}
