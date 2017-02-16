#ifndef Alchemy_MonsterIcon
#define Alchemy_MonsterIcon

#include "Monster.h"

class MonsterIcon : public PEObject, public Sprite
{
public:
	MonsterIcon(unsigned char index);
	~MonsterIcon();

	static MonsterIcon* create(unsigned char index);
	static SpriteBatchNode* PE_MONSTER_ICON_getBatchNode(void);

protected:

private:
	static SpriteBatchNode* m_pBatchNode;
	static void PE_makeResource();
};

#endif
