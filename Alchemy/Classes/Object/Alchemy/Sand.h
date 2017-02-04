//
//  Sand.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Sand__
#define __Alchemy__Sand__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Sand : public Alchemy
{
public:
	Sand(unsigned char index);
	Sand(string name);
	~Sand();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

private:
};

#endif /* defined(__Alchemy__Sand__) */
