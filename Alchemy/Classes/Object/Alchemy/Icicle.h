//
//  Icicle.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Icicle__
#define __Alchemy__Icicle__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Icicle : public Alchemy
{
public:
	Icicle(unsigned char index);
	Icicle(string name);
	~Icicle();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
};

#endif /* defined(__Alchemy__Icicle__) */
