//
//  Glass.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Glass__
#define __Alchemy__Glass__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Glass : public Alchemy
{
public:
	Glass(unsigned char index);
	~Glass();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
	timeval life_time[2];
	timeval attack_time[2];
};

#endif /* defined(__Alchemy__Glass__) */
