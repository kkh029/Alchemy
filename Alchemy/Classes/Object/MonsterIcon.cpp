#include "MonsterIcon.h"

CCSpriteBatchNode* MonsterIcon::m_pBatchNode;

MonsterIcon::MonsterIcon(unsigned char index) : PEObject() {
	if(m_pBatchNode == NULL)
		PE_makeResource();

	char icon_name[20];
	sprintf(icon_name, "i%s.png", Monster::monster_table[index].name);

	CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon_name);
	initWithSpriteFrame(pFrame);
	autorelease();
}

MonsterIcon::~MonsterIcon() {

}

MonsterIcon* MonsterIcon::create(unsigned char index) {
	MonsterIcon* pMonsterIcon = new MonsterIcon(index);
	MonsterIcon::m_pBatchNode->addChild(pMonsterIcon);
	return pMonsterIcon;
}

void MonsterIcon::PE_makeResource() {
	MonsterIcon::m_pBatchNode = CCSpriteBatchNode::create("Monster/Monster.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Monster/Monster.plist");
}

CCSpriteBatchNode* MonsterIcon::PE_MONSTER_ICON_getBatchNode() {
	if(MonsterIcon::m_pBatchNode == NULL)
		MonsterIcon::PE_makeResource();
	return MonsterIcon::m_pBatchNode;
}