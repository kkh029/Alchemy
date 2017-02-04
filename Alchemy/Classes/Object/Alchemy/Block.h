//
//  Block.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Block__
#define __Alchemy__Block__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Block : public Alchemy
{
public:
	Block(unsigned char index);
	~Block();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	Size m_winSize;
};

#endif /* defined(__Alchemy__Flame__) */
