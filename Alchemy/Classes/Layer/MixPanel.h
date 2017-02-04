#ifndef Alchemy_MixPanel
#define Alchemy_MixPanel

#include "Common.h"
#include "PETouchGesture.h"
#include "Field.h"

#define AXIS_X 0
#define AXIS_Y 1
#define BOUNDARY_MIN 0
#define BOUNDARY_MAX 1

#define ICON_NUM_MAX 27
#define MIX_RESULT_MAX 4

using namespace cocostudio;

enum e_peElement
{
	FIRE = 0,
	WIND,
	WATER,
	EARTH,
};

enum e_peTouchOrigin
{
	TO_UNKNOWN = 0,
	TO_ELEMENT,
	TO_MIX,
	TO_FIELD
};

class MixResource;
class Item;
class Field;
class PEIcon;
class PEProgressBar;

class MixPanel : public Layer, public PETouchGesture
{
public:
	MixPanel();
	~MixPanel();
	bool init();
	virtual void onExit();
	//void registerWithTouchDispatcher(void);
	
	void TouchesBegan(__Set *pTouches, Event* pEvent);
	void TouchesMoved(__Set *pTouches, Event* pEvent);
	void TouchesEnded(__Set *pTouches, Event* pEvent);
	virtual void onDoubleTap(Vec2 pos);
	void setField(Field* field);
	void setPEIcon(PEIcon* peicon);
	void setResourceData(SpriteBatchNode* batchNode);
	void sendPass(void);
	
private:
	void resetPanel();
	bool PE_checkClickMixBtn(Vec2* pos);
	void cancel_display_icon(int idx);
	void add_alchemy_icon(int icon_index);
    void reset_alchemy_icon(void);
    void check_alchemy_icon_valid(void);
	void makeIcon(int icon_index, int element_index);

	MixResource* icon[ICON_NUM_MAX];			/* MAX : ICON_NUM_MAX */
	Sprite* icon_background[ICON_NUM_MAX];
	MixResource* alchemy_icon[MIX_RESULT_MAX];  /* MAX : MIX_RESULT_MAX */
	int last_icon_index;
	int circle_index[4];
	int icon_count_per_circle[4];

	bool check_mixed;
	Field* mField;
	PEIcon* mPEIcon;

	Sprite* select_noti;
	Sprite* mix_invalid_noti;
	int touched_id;

	Sprite* mixPanel;
	Armature* mixBtn;
	Armature* doorLife[5];
	int doorLifeCount;
	void decreaseDoorLife(int num);
	bool send_fail_flag;
	void sendFail(float in);

	int selected_index;
	int select_touch_action;
	int select_alchemy_icon_index;
	int previous_selected_index;
	
	PEProgressBar* mana_bar;
	PEProgressBar* con_bar;
	void regen_con_mana(Ref *obj);
	void particle_end(Ref* pObject);
	void bar_change(Ref* pObject);
    void add_particle_to_bar(Ref* object);
	SpriteBatchNode* batch_par;
    
	bool double_tap_called;
	

};

#endif
