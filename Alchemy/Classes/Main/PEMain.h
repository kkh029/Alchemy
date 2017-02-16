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

class PEStageBtn : public Node
{
public:
	static PEStageBtn* create(int index, bool valid);
	int get_stage_stars(void);
	void set_stage_stars(int star);
	void toggle_btn(bool flag);
	void set_valid(bool valid);
	bool get_valid(void);
	Rect get_boundingbox(void);
	
private:
	int stage;
	int stars;
	bool is_valid;
	bool isTouched;
	Sprite* touched_btn_back;
	Sprite* touched_btn_back_select;
	Sprite* stage_num_text;
	
	int load_stage_stars(void);
	Sprite* makeStageNumber(int num, float *size, bool is_visible);
	void init_btn(int index, bool valid);
};

class PEMain : public Layer
{
public:
	bool init();

	static Scene* scene();

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *event);
	
protected:
	
private:
	//void introOut(Ref* in);
	//Sprite* m_title;
	void startMain(float in);
	void back(Ref* pSender);
	void resume(void);
	void setting(Ref* pSender);
	void note();
	void stage();
	void infinite();
	void profile();
	void shop();
	void stage_select(int stage);
	void side_btn(Ref* pSender);
	void change_stage_table(int btn_index);

	void init_bottonBtn();
	void init_topBtn();
	void init_Main_stageBtn(int stage_num_start);
	void init_Main_stage_side_btn();

	void title_out();
	void title_in(Ref* obj);
	void changeMainCard();

	bool PE_check_bottom_btn(Vec2 pos);
	int  check_touched_btn(Vec2 pos);

	PEStageBtn* stage_btn[12];
	Menu* main_stage_back;
	Menu* main_stage_next;
	Vec2 main_left_top;
	int select_stage_btn;

	void (PEMain::*onButtonSelect[4])();
	void onEndOfSelecctorMoving(Ref* obj);
	void back_key_clicked_reset(float in);

	Sprite* bottom_select_stroke;
	Sprite* bottom_unselect_icon_array[4];
	Sprite* bottom_select_icon_array[4];
	int last_selected_bottom_icon;
	int selected_bottom_icon;
	int tracking_bottom_icon;
	bool bottom_btn_selected;
	bool bottom_ani_playing;
	bool bottom_card_enable;
	int main_stage_index;

	Sprite* main_title_array[4];
	Sprite* main_card_array[4];
	Sprite* main_card;
	
	Menu* top_btn;

	int touched_id;
};


#endif /* defined(__Alchemy__PEMain__) */
