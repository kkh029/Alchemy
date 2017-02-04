#ifndef __PEPopupStop__
#define __PEPopupStop__

#include "Common.h"

class PEPopupStop: public CCLayer
{
private:
	CCSprite* popUpBack;
	Size backSize;

	CCMenu* BGMOFFbtn;
	CCMenu* EFFECTOFFbtn;

	CCSprite* makeStageNumber(int num, float *size);
	void resume(CCObject* pSender);
	void restart(CCObject* pSender);
	void exit(CCObject* pSender);
	void BGMonoff(CCObject* pSender);
	void EFFECTonoff(CCObject* pSender);

public:
	bool init();

};

#endif // _PEPopupStop__
