//
//  PEPopUpSetting.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 7. 4..
//
//

#include "PEPopUpSetting.h"
#include "../Sound/PEBackgroundMusic.h"
#include "../Sound/PESoundEffect.h"
#include "PEPopUpManager.h"

bool PEPopUpSetting::init()
{
	/*
    if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)) )
    {
        return false;
    }
	 */
	autorelease();
	setKeypadEnabled(true);
	
	Size winSize = CCDirector::sharedDirector()->getWinSize();
	
	//backLayer
	CCLayerColor* backLayer=CCLayerColor::create(ccc4(0,0,0,150), winSize.width, winSize.height);
	backLayer->setAnchorPoint(ccp(0,0));
	backLayer->setPosition(ccp(0,0));
	this->addChild(backLayer);
	
	//popUpLayer
	popUpBack = CCSprite::create("Layer/lPopUp/lPopUpBack.png");
	popUpBack->setPosition( ccp((winSize.width/2), (winSize.height/2)+100) );
	this->addChild(popUpBack);
	backSize = popUpBack->getContentSize();
	
	CCSprite* settingTitle = CCSprite::create("Layer/lPopUp/lOption.png");
	settingTitle->setPosition(  ccp((backSize.width/2), (backSize.height/2 + 300)) );
	popUpBack->addChild(settingTitle);
	
	/* load BGM on/off */
	BGMOFFbtn = NULL;
	bool BGM_onoff = PEBackgroundMusic::sharedPEBackgroundMusic()->PE_get_onoff();
	
	CCMenuItemImage *BGMOFFItem = CCMenuItemImage::create(
														  PEPopUpManager::BGM_FILE_NAME[BGM_onoff][0],
														  PEPopUpManager::BGM_FILE_NAME[BGM_onoff][1],
														  this,
														  menu_selector(PEPopUpSetting::BGMonoff) );
    BGMOFFbtn = CCMenu::create(BGMOFFItem, NULL);
	Size BGMOFFbtnSize = BGMOFFItem->getContentSize();
    BGMOFFbtn->setPosition(ccp(BGMOFFbtnSize.width/2+35, backSize.height/2+20));
    popUpBack->addChild(BGMOFFbtn);
	
	EFFECTOFFbtn = NULL;
	bool EFFECT_onoff = PESoundEffect::sharedPESoundEffect()->PE_get_onoff();
	CCMenuItemImage *EFFECTOFFItem = CCMenuItemImage::create(
															 PEPopUpManager::EFFECT_FILE_NAME[EFFECT_onoff][0],
															 PEPopUpManager::EFFECT_FILE_NAME[EFFECT_onoff][1],
															 this,
															 menu_selector(PEPopUpSetting::EFFECTonoff) );
    EFFECTOFFbtn = CCMenu::create(EFFECTOFFItem, NULL);
	Size EFFECTOFFbtnSize = EFFECTOFFItem->getContentSize();
    EFFECTOFFbtn->setPosition(ccp(backSize.width - (EFFECTOFFbtnSize.width/2+35), backSize.height/2+20));
    popUpBack->addChild(EFFECTOFFbtn);
	
	CCMenuItemImage *CREDITItem = CCMenuItemImage::create(
														   "Layer/lPopUp/lCreditBase.png",
														   "Layer/lPopUp/lCreditTouch.png",
														   this,
														   menu_selector(PEPopUpSetting::credit) );
    CCMenu*  CREDITbtn= CCMenu::create(CREDITItem, NULL);
    CREDITbtn->setPosition(ccp(backSize.width/2, backSize.height/2 - 200.0f));
    popUpBack->addChild(CREDITbtn);


    return true;
}

void PEPopUpSetting::BGMonoff(CCObject* pSender)
{
	bool BGM_onoff = PEBackgroundMusic::sharedPEBackgroundMusic()->PE_get_onoff();
	CCLog("BGM - %d\n", BGM_onoff);
	if(BGM_onoff)
	{
        PEBackgroundMusic::sharedPEBackgroundMusic()->PE_set_onoff(false);
		BGM_onoff = false;
	}
	else
	{
        PEBackgroundMusic::sharedPEBackgroundMusic()->PE_set_onoff(true);
		PEBackgroundMusic::sharedPEBackgroundMusic()->PE_play(0);
		BGM_onoff = true;
	}
	
	if(BGMOFFbtn != NULL)
		BGMOFFbtn->removeFromParent();
	
	CCMenuItemImage *BGMOFFItem = CCMenuItemImage::create(
														  PEPopUpManager::BGM_FILE_NAME[BGM_onoff][0],
														  PEPopUpManager::BGM_FILE_NAME[BGM_onoff][1],
														  this,
														  menu_selector(PEPopUpSetting::BGMonoff) );
    BGMOFFbtn = CCMenu::create(BGMOFFItem, NULL);
	Size BGMOFFbtnSize = BGMOFFItem->getContentSize();
    BGMOFFbtn->setPosition(ccp(BGMOFFbtnSize.width/2+35, backSize.height/2+20));
    popUpBack->addChild(BGMOFFbtn);
}

void PEPopUpSetting::EFFECTonoff(CCObject* pSender)
{
	bool EFFECT_onoff = PESoundEffect::sharedPESoundEffect()->PE_get_onoff();
	if(EFFECT_onoff)
	{
		PESoundEffect::sharedPESoundEffect()->PE_set_onoff(false);
        EFFECT_onoff = false;
	}
	else
	{
		PESoundEffect::sharedPESoundEffect()->PE_set_onoff(true);
		EFFECT_onoff = true;
	}
	
	if(EFFECTOFFbtn != NULL)
		EFFECTOFFbtn->removeFromParent();
	
	CCMenuItemImage *EFFECTOFFItem = CCMenuItemImage::create(
															 PEPopUpManager::EFFECT_FILE_NAME[EFFECT_onoff][0],
															 PEPopUpManager::EFFECT_FILE_NAME[EFFECT_onoff][1],
															 this,
															 menu_selector(PEPopUpSetting::EFFECTonoff) );
	EFFECTOFFbtn = CCMenu::create(EFFECTOFFItem, NULL);
	Size EFFECTOFFbtnSize = EFFECTOFFItem->getContentSize();
    EFFECTOFFbtn->setPosition(ccp(backSize.width - (EFFECTOFFbtnSize.width/2+35), backSize.height/2+20));
    popUpBack->addChild(EFFECTOFFbtn);
}

void PEPopUpSetting::credit(CCObject* pSender)
{
	(pListener->*resume)();
	removeFromParentAndCleanup(true);
}

void PEPopUpSetting::keyBackClicked(void)
{
	(pListener->*resume)();
	removeFromParentAndCleanup(true);
}

void PEPopUpSetting::setResume(CCObject* target, SEL_Resume pResume)
{
	pListener = target;
	resume = pResume;
}
