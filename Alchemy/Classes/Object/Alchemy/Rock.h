//
//  Rock.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Rock__
#define __Alchemy__Rock__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Rock : public Alchemy
{
public:
	Rock(unsigned char index);
	Rock(string name);
	~Rock();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int isAttack;
	Size m_winSize;
};

#endif /* defined(__Alchemy__Rock__) */
