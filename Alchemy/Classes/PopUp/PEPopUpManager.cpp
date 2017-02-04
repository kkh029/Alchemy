#include "PEPopUpManager.h"
#include "PEPopupStop.h"
#include "PEPopupFail.h"
#include "PEPopupSuccess.h"

#define INTRO_FADE_OUT_DELAY	1.0f

char PEPopUpManager::BGM_FILE_NAME[2][2][50] =
{
	{
		"Layer/lPopUp/lBgmOffBase.png","Layer/lPopUp/lBgmOffTouch.png"
	},
	{
		"Layer/lPopUp/lBgmOnBase.png","Layer/lPopUp/lBgmOnTouch.png"
	}
};

char PEPopUpManager::EFFECT_FILE_NAME[2][2][50] =
{
	{
		"Layer/lPopUp/lEffectOffBase.png","Layer/lPopUp/lEffectOffTouch.png"
	},
	{
		"Layer/lPopUp/lEffectOnBase.png","Layer/lPopUp/lEffectOnTouch.png"
	}
};

enum GAME_STATUS
{
	ePLAY = 0,
	ePAUSE,
};

bool PEPopUpManager::init()
{
	if ( !CCLayer::init() ) 
    {
        return false;
    }
	autorelease();
	/* notification Receiver */
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,	callfuncO_selector(PEPopUpManager::scene_popup),"scene_popup", NULL);
	isPause = false;

	return true;
}

void PEPopUpManager::onExit()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "scene_popup");
}

void PEPopUpManager::scene_popup(CCObject *obj){

	CCString *pParam=(CCString*)obj;
	CCLayer* popup;
	int popup_call_index = pParam->intValue();

	CCLog("notification %d", pParam->intValue());

	if(!isPause)
	{
		isPause = true;
		
		switch(popup_call_index)
		{
			case POPUP_STOP:
				(pListener_pause->*pause)();
				CCDirector::sharedDirector()->pause();
				popup= new PEPopupStop();
				popup->init();
				this->addChild(popup);
				break;
			
			case POPUP_FAIL:
				(pListener_pause->*pause)();
				CCDirector::sharedDirector()->pause();
				popup = new PEPopupFail();
				popup->init();
				addChild(popup);
				break;
			
			default:
				if(popup_call_index>10
				   && popup_call_index % 10 == POPUP_SUCCESS)
				{
					popup = new PEPopupSuccess(popup_call_index/10);
					popup->init();
					this->addChild(popup);
				}
				break;
				
		}
	}
	else 
	{
		if(isPause && popup_call_index == POPUP_RESUME)
		{
			(pListener_resume->*resume)();
			isPause = false;
			CCDirector::sharedDirector()->resume();
		}
		
		if(popup_call_index == POPUP_END)
			CCDirector::sharedDirector()->end();
	}


}

void PEPopUpManager::setResume(CCObject* target, SEL_Resume pResume)
{
	pListener_resume = target;
	resume = pResume;
}

void PEPopUpManager::setPause(CCObject* target, SEL_Resume pPause)
{
	pListener_pause = target;
	pause = pPause;
}