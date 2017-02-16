#include "MonsterIcon.h"

SpriteBatchNode* MonsterIcon::m_pBatchNode;

MonsterIcon::MonsterIcon(unsigned char index) : PEObject() {
	if(m_pBatchNode == NULL)
		PE_makeResource();

	char icon_name[20];
	sprintf(icon_name, "i%s.png", Monster::monster_table[index].name);

	SpriteFrame* pFrame = SpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(icon_name);
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
	MonsterIcon::m_pBatchNode = SpriteBatchNode::create("Monster/Monster.png");
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Monster/Monster.plist");
}

SpriteBatchNode* MonsterIcon::PE_MONSTER_ICON_getBatchNode() {
	if(MonsterIcon::m_pBatchNode == NULL)
		MonsterIcon::PE_makeResource();
	return MonsterIcon::m_pBatchNode;
}
