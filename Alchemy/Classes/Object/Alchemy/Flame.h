//
//  Flame.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Flame__
#define __Alchemy__Flame__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Flame : public Alchemy
{
public:
	Flame(unsigned char index);
	Flame(string name);
	~Flame();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int m_bulletFireTime;
	int isAttack;

	Size m_winSize;
	Vec2 field_index;
	std::vector<Sprite*> m_bullets;
	Sprite* FireBullet();
    SpriteBatchNode* batch_bullet;
    SpriteBatchNode* batch_fire;
	void OnEndOfBullet(Ref* object);
    void OnEndOfFire(Ref* object);
	int bullet_time_count;
	int bullet_time_last;
    
};

#endif /* defined(__Alchemy__Flame__) */
