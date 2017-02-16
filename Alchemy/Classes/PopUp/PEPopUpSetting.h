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

typedef void (Ref::*SEL_Resume)(void);

class PEPopUpSetting: public Layer
{
public:
	bool init();
	void setResume(Ref* target, SEL_Resume pResume) ;

private:
	Sprite* popUpBack;
	Size backSize;
	
	CCMenu* BGMOFFbtn;
	CCMenu* EFFECTOFFbtn;
	
	void BGMonoff(Ref* pSender);
	void EFFECTonoff(Ref* pSender);
	void credit(Ref* pSender);
	
	Ref*	pListener;
    SEL_Resume    resume;
};

#endif /* defined(__Alchemy__PEPopUpSetting__) */
