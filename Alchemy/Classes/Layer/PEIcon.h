//
//  PEIcon.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 2. 11..
//
//

#ifndef __Alchemy__PEIcon__
#define __Alchemy__PEIcon__

#include "../Common.h"

#define POSITION_ICON_PAUSE_X 1010.0f
#define POSITION_ICON_PAUSE_Y 1845.0f
#define POSITION_ICON_SOUND_X 875.0f
#define POSITION_ICON_SOUND_Y 1845.0f

class PEIcon : public CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(int stage);
	virtual void onExit();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void m_setTouchEnabled(bool enabled);
	bool PE_con_PreCheck(int spend);
	bool PE_mana_PreCheck(int spend);
	bool PE_con_Check(int spend);
	bool PE_mana_Check(int spend);

	void PE_addCrystal(CCObject *obj);
	void PE_subDoor(CCObject *obj);
	
private:
	void onSoundOnOff(CCObject* pSender);
	void init_soundBTN();
	CCMenu* pauseBtn;
	CCMenu* soundBtn;
	bool isMute;
	bool touch_enable;
	void pauseCall(CCObject* pSender);
	int m_stage;
	
	int door_energy;
	int crystal_num;
	int door_num;
	int door_max;
	CCLabelTTF* door_num_text;
	CCLabelTTF* crystal_num_text;

	CCProgressTimer* mana_before_bar;
	CCProgressTimer* mana_later_bar;
	CCLabelTTF* mana_text;
	int mana_before;
	int mana_later;
	int mana_max;

	CCProgressTimer* con_before_bar;
	CCProgressTimer* con_later_bar;
	CCLabelTTF* con_text;
	int con_before;
	int con_later;
	int con_max;
};

#endif /* defined(__Alchemy__PEIcon__) */
