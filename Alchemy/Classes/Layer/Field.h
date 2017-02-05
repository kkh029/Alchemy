#ifndef Alchemy_Field
#define Alchemy_Field

#include "Common.h"
#include "PEBoardPos.h"
#include "MixPanel.h"
#include "../Object/Alchemy.h"
#include "../Object/PE_Collision.h"
#include "../Object/Monster.h"
#include "../Object/PEObject.h"

class MixPanel;
class Item;

class Pot: public Node
{
public:
	Pot();
	~Pot();
	static Pot*  create(void);
	void color_change(void);
private:
	Sprite* magic_circle_back;
	Sprite* magic_circle;
	Armature* pot;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int goto_bright;
	int change_index;

	void pot_color_change(void);
	bool init(void);
};

class Field : public Layer
{
public:
	bool init();
	void update(float dt);
	void SpawnMonsters(int monster_index, float speed_scale);
	void CheckCollisions();
	void SetMixPanel(MixPanel* pMixPanel);
	void SpawnItem(Ref* pMonster);
	bool peTouchMoveFromMix(Touch* pTouch, PEObject* object);
	bool peTouchEndFromMix(Touch* pTouch, PEObject* object);
	virtual void onExit();
	
protected:
	
private:
	Pot* m_pot;
	PEBoardPos *broadPos;
	int m_monsterSpawnTime;
	PE_Collision* m_pCollision;
	std::vector<Item*> m_items;
	Alchemy* m_pBoard[COL_NUM][ROW_NUM];
	Size m_winSize;
	SpriteBatchNode* m_pBatchNode;
	
	Size background_size;
	Vec2 m_prevTouchPos;
	Sprite* m_pBackground;
	
	MixPanel* m_pMixPanel;
	bool draw_noti_box(Touch* touch, int index);
	
	DrawNode *box;
	Touch* mTouch;
	float m_move_to_y;
	int touched_id;
	
	void openBall(Ref* pObject);
	void createMonster(Ref* pObject);
	void removeBall(Ref* pObject);
	int rand_num_count[6];
	
	/*	
		0 : FireTalisman,
		1 : WaterTalisman,
		2 : WindTalisman,
		3 :	EarthTalisman
	 */
	int talisman_flag[COL_NUM][ROW_NUM];

	bool send_success_flag;
};

#endif
