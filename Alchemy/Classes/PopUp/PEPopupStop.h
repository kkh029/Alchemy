#ifndef __PEPopupStop__
#define __PEPopupStop__

#include "Common.h"

class PEPopupStop: public Layer
{
private:
	Sprite* popUpBack;
	Size backSize;

	Menu* BGMOFFbtn;
	Menu* EFFECTOFFbtn;

	Sprite* makeStageNumber(int num, float *size);
	void resume(Ref* pSender);
	void restart(Ref* pSender);
	void exit(Ref* pSender);
	void BGMonoff(Ref* pSender);
	void EFFECTonoff(Ref* pSender);

public:
	bool init();

};

#endif // _PEPopupStop__
