#include "Item.h"
#include "../Layer/Field.h"

CCSpriteBatchNode* Item::m_pBatchNode_Item;

PE_s_item Item::item_table[ITEM_MAX] = {
	/*
	id		name			useable	wearable*/
	{0,		NULL,			false,	false},
	{1,		"ConPotion",	true,	false},
	{2,		"ManaPotion",	true,	false},
};

// Initialize
Item::Item(unsigned char id, Vec2 position){
	if(Item::m_pBatchNode_Item == NULL)
		Item::PE_makeResource();
	
	setAnchorPoint(ccp(0.5f, 0.5f));
	setPosition(position);
	setVisible(true);
	scheduleUpdate();

	m_Id = id;
	m_name = item_table[id].name;
	m_useable = item_table[id].useable;
	m_wearable = item_table[id].wearable;
	m_takeFlag = false;
	m_startTime = PETime::GetTime();
	m_velocity = ccp((rand() % 5 - 2), 10.0f);
	m_velocity = ccpAdd(m_velocity, ccp(0.5f, 0.0f));

	m_destination =  position.y - (rand() % 41);

	m_winSize = CCDirector::sharedDirector()->getWinSize();
}

Item::~Item() {

}

Item* Item::create(int id, Vec2 position) {
	string name = item_table[id].name;
	name.append(".png");
	CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name.c_str());

	Item* pItem = new Item(id, position);
	if(pItem && pItem->initWithSpriteFrame(pFrame)) {
		Item::m_pBatchNode_Item->addChild(pItem);
		pItem->autorelease();
		return pItem;
	}

	CC_SAFE_DELETE(pItem);
	return NULL;
}

void Item::update(float dt) {
	if(getPositionY() < m_destination || m_takeFlag)
		return;

	Vec2 gravity = Vec2Make(0.0f, -15.0f * dt);

	m_velocity = ccpAdd(m_velocity, gravity);

	Vec2 position = ccpAdd(getPosition(), m_velocity);

	if(position.x < getContentSize().width * 0.5f)
		position.x = getContentSize().width * 0.5f;
	else if(position.x > m_winSize.width - getContentSize().width * 0.5f)
		position.x = m_winSize.width - getContentSize().width * 0.5f;

	setPosition(position);
}

void Item::take() {
	m_takeFlag = true;
	float distanceX = getPositionX() - 50.0f;
	float distanceY = getPositionY() - 430.0f;
	float duration = distanceY / 300;

	setStartTime(PETime::GetTime());
	
	CCCallFuncO* pCallFuncO =  CCCallFuncO::create(this, callfuncO_selector(Item::OnTakeItem), this);
	//CCMoveBy* pMoveBy = CCMoveBy::create(duration, ccp(-distanceX, -distanceY));
	ccBezierConfig bezierConfig;
	bezierConfig.endPosition = ccp(50.0f, 500.f);
	bezierConfig.controlPoint_2 = ccp(50.0f, 600.0f);
	switch(rand()%2) {
	case 0:
		bezierConfig.controlPoint_1 = ccp(100.0f, 1500.0f);
		break;
	case 1:
		bezierConfig.controlPoint_1 = ccp(getPositionX(), 400.0f);
		break;
	}
	
	CCBezierTo* pBezier = CCBezierTo::create(duration, bezierConfig);

	this->runAction(CCSequence::create(pBezier, pCallFuncO, NULL));
}

void Item::OnTakeItem(CCObject* pObject) {
	Item* pItem = (Item*)pObject;
	pItem->stopAllActions();
	pItem->setVisible(false);
}

// Prepare Resource
void Item::PE_makeResource() {
	Item::m_pBatchNode_Item = CCSpriteBatchNode::create("Item/Item.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Item/Item.plist");
}

CCSpriteBatchNode* Item::PE_ITEM_getBatchNode() {
	if(Item::m_pBatchNode_Item == NULL)
		Item::PE_makeResource();
	return Item::m_pBatchNode_Item;
}

// GET / SET Func
int Item::getId() {
	return m_Id;
}

string Item::getName() {
	return m_name;
}

bool Item::getUseable() {
	return m_useable;
}

bool Item::getWearable() {
	return m_wearable;
}

int Item::getStartTime() {
	return m_startTime;
}

void Item::setStartTime(int startTime) {
	m_startTime = startTime;
}

