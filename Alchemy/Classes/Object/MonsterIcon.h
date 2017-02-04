#ifndef Alchemy_MonsterIcon
#define Alchemy_MonsterIcon

#include "Monster.h"

class MonsterIcon : public PEObject, public CCSprite
{
public:
	MonsterIcon(unsigned char index);
	~MonsterIcon();

	static MonsterIcon* create(unsigned char index);
	static CCSpriteBatchNode* PE_MONSTER_ICON_getBatchNode(void);

protected:

private:
	static CCSpriteBatchNode* m_pBatchNode;
	static void PE_makeResource();
};

#endif
