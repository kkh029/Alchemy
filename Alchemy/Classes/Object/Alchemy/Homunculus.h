//
//  Homunculus.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Homunculus__
#define __Alchemy__Homunculus__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Homunculus : public Alchemy
{
public:
	Homunculus(unsigned char index);
	~Homunculus();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int ani_curr_index;
	bool attack_check;
	Size m_winSize;
};

#endif /* defined(__Alchemy__Homunculus__) */
