#ifndef Alchemy_Item
#define Alchemy_Item

#include "Common.h"

struct PE_s_item {
	unsigned char Id;
	char name[20];
	bool useable;
	bool wearable;
};

class Item : public Sprite {
public:
	Item(unsigned char Id, Vec2 position);
	~Item();

	static Item* create(int id, Vec2 position);
	static void PE_makeResource();
	static SpriteBatchNode* PE_ITEM_getBatchNode(void);

	void update(float dt);
	void take();
	void OnTakeItem(Ref* pObject);

	int getId();
	string getName();
	bool getUseable();
	bool getWearable();
	int getStartTime();
	void setStartTime(int startTime);

	static const int ITEM_MAX = 3;
	static PE_s_item item_table[ITEM_MAX];
	
protected:
	unsigned char m_Id;
	string m_name;
	bool m_useable;
	bool m_wearable;
	int m_startTime;

	static SpriteBatchNode* m_pBatchNode_Item;
	Size m_winSize;
	Vec2 m_velocity;
	float m_destination;

private:
	bool m_takeFlag;
};
#endif
