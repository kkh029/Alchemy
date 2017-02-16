#ifndef __PEPopupFail__
#define __PEPopupFail__

#include "Common.h"

class PEPopupFail: public Layer
{
private:
	Sprite* popUpBack;
	Size backSize;
	
	Sprite* makeStageNumber(int num, float *size);
	void resume(Ref* pSender);
	void restart(Ref* pSender);
	void exit(Ref* pSender);
	
public:
	bool init();

};

#endif // _PEPopupFail__
