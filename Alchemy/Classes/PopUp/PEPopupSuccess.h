#ifndef __PEPopupSuccess__
#define __PEPopupSuccess__

#include "Common.h"

class PEPopupSuccess: public Layer
{
private:
	Sprite* popUpBack;
	Size backSize;

	Sprite* makeStageNumber(int num, float *size);
	void resume(Ref* pSender);
	void restart(Ref* pSender);
	void exit(Ref* pSender);
	int door_num;
	
public:
	PEPopupSuccess(int door_num);
	~PEPopupSuccess();
	bool init();

};

#endif // _PEPopupSuccess__
