#ifndef __PEPopupFail__
#define __PEPopupFail__

#include "Common.h"

class PEPopupFail: public CCLayer
{
private:
	CCSprite* popUpBack;
	Size backSize;
	
	CCSprite* makeStageNumber(int num, float *size);
	void resume(CCObject* pSender);
	void restart(CCObject* pSender);
	void exit(CCObject* pSender);
	
public:
	bool init();

};

#endif // _PEPopupFail__
