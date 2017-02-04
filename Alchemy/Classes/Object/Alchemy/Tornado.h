//
//  Tornado.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Tornado__
#define __Alchemy__Tornado__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Tornado : public Alchemy
{
public:
	Tornado(unsigned char index);
	Tornado(string name);
	~Tornado();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int isAttack;
	Size m_winSize;
	cc_timeval event_time[2];
	
	int m_bulletFireTime;
	bool fire_flag;

	std::vector<CCArmature*> m_bullets;
	CCArmature* FireBullet();
	void OnEndOfBullet(CCNode* pNode);
};

#endif /* defined(__Alchemy__Tornado__) */
