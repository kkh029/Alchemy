//
//  PlainWater.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__PlainWater__
#define __Alchemy__PlainWater__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class PlainWater : public Alchemy
{
public:
	PlainWater(unsigned char index);
	PlainWater(string name);
	~PlainWater();

	static Alchemy* create(PEObject*  obj);
	
	void OnEndOfBullet(CCNode* pNode);

	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int m_bulletFireTime;
	bool isAttack;
	bool fire_flag;
	
	std::vector<Sprite*> m_bullets;
	Sprite* FireBullet();
};

#endif /* defined(__Alchemy__PlainWater__) */
