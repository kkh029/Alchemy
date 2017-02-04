//
//  Plant.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Plant__
#define __Alchemy__Plant__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Plant : public Alchemy
{
public:
	Plant(unsigned char index);
	Plant(string name);
	~Plant();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	int isAttack;
	Size m_winSize;
};

#endif /* defined(__Alchemy__Plant__) */
