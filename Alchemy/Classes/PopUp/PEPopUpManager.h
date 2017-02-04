#ifndef __PEPopUpManager__
#define __PEPopUpManager__

#include "Common.h"

class GameLayer;

enum E_POPUP_TYPE
{
	POPUP_STOP = 0,
	POPUP_SUCCESS,
	POPUP_FAIL,
	POPUP_RESUME,
	POPUP_END
};

typedef void (CCObject::*SEL_Resume)(void);
typedef void (CCObject::*SEL_PAUSE)(void);

class PEPopUpManager: public CCLayer
{
private:
	bool isPause;
	static bool set_Noti_receiver;
	
	void scene_popup(CCObject *obj);
	virtual void onExit();
	
	CCObject*	pListener_resume;
	CCObject*	pListener_pause;
    SEL_Resume	resume;
	SEL_PAUSE	pause;

public:
	bool init();
	
	void setResume(CCObject* target, SEL_Resume pResume) ;
	void setPause(CCObject* target, SEL_Resume pPause) ;
	
	static char BGM_FILE_NAME[2][2][50];
	static char EFFECT_FILE_NAME[2][2][50];

};

#endif // __PEPopUpManager__