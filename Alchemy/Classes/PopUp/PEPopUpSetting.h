//
//  PEPopUpSetting.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 7. 4..
//
//

#ifndef __Alchemy__PEPopUpSetting__
#define __Alchemy__PEPopUpSetting__

#include "../Common.h"

typedef void (CCObject::*SEL_Resume)(void);

class PEPopUpSetting: public CCLayer
{
public:
	bool init();
	void setResume(CCObject* target, SEL_Resume pResume) ;

private:
	CCSprite* popUpBack;
	Size backSize;
	
	CCMenu* BGMOFFbtn;
	CCMenu* EFFECTOFFbtn;
	
	void BGMonoff(CCObject* pSender);
	void EFFECTonoff(CCObject* pSender);
	void credit(CCObject* pSender);
	
	void keyBackClicked(void);
	
	CCObject*	pListener;
    SEL_Resume    resume;
};

#endif /* defined(__Alchemy__PEPopUpSetting__) */
