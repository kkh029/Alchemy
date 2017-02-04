//
//  PEIntroLayer.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 2. 10..
//
//

#ifndef __Alchemy__PEMain__
#define __Alchemy__PEMain__

#include "../Common.h"

class PEStageBtn : public CCNode
{
public:
	static PEStageBtn* create(int index, bool valid);
	int get_stage_stars(void);
	void set_stage_stars(int star);
	void toggle_btn(bool flag);
	void set_valid(bool valid);
	bool get_valid(void);
	CCRect get_boundingbox(void);
	
private:
	int stage;
	int stars;
	bool is_valid;
	bool isTouched;
	CCSprite* touched_btn_back;
	CCSprite* touched_btn_back_select;
	CCSprite* stage_num_text;
	
	int load_stage_stars(void);
	CCSprite* makeStageNumber(int num, float *size, bool is_visible);
	void init_btn(int index, bool valid);
};

class PEMain : public CCLayer
{
public:
	bool init();

	static CCScene* scene();

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouch, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouch, CCEvent *pEvent);
	
protected:
	
private:
	//void introOut(CCObject* in);
	//CCSprite* m_title;
	void startMain(float in);
	void back(CCObject* pSender);
	void resume(void);
	void setting(CCObject* pSender);
	void note();
	void stage();
	void infinite();
	void profile();
	void shop();
	void stage_select(int stage);
	void side_btn(CCObject* pSender);
	void change_stage_table(int btn_index);

	void init_bottonBtn();
	void init_topBtn();
	void init_Main_stageBtn(int stage_num_start);
	void init_Main_stage_side_btn();

	void title_out();
	void title_in(CCObject* obj);
	void changeMainCard();

	bool PE_check_bottom_btn(Vec2 pos);
	int  check_touched_btn(Vec2 pos);

	PEStageBtn* stage_btn[12];
	CCMenu* main_stage_back;
	CCMenu* main_stage_next;
	Vec2 main_left_top;
	int select_stage_btn;

	void (PEMain::*onButtonSelect[4])();
	void onEndOfSelecctorMoving(CCObject* obj);

	void keyBackClicked(void);
	void back_key_clicked_reset(float in);

	CCSprite* bottom_select_stroke;
	CCSprite* bottom_unselect_icon_array[4];
	CCSprite* bottom_select_icon_array[4];
	int last_selected_bottom_icon;
	int selected_bottom_icon;
	int tracking_bottom_icon;
	bool bottom_btn_selected;
	bool bottom_ani_playing;
	bool bottom_card_enable;
	int main_stage_index;

	CCSprite* main_title_array[4];
	CCSprite* main_card_array[4];
	CCSprite* main_card;
	
	CCMenu* top_btn;

	int touched_id;
};


#endif /* defined(__Alchemy__PEMain__) */
