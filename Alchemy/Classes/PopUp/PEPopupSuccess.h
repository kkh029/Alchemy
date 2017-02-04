#ifndef __PEPopupSuccess__
#define __PEPopupSuccess__

#include "Common.h"

class PEPopupSuccess: public CCLayer
{
private:
	CCSprite* popUpBack;
	Size backSize;

	CCSprite* makeStageNumber(int num, float *size);
	void resume(CCObject* pSender);
	void restart(CCObject* pSender);
	void exit(CCObject* pSender);
	int door_num;
	
public:
	PEPopupSuccess(int door_num);
	~PEPopupSuccess();
	bool init();

};

#endif // _PEPopupSuccess__
