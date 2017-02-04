//
//  Ice.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//
//

#ifndef __Alchemy__Ice__
#define __Alchemy__Ice__

#include "Common.h"
#include "../Alchemy.h"
#include "../Monster.h"

class Ice : public Alchemy
{
public:
	Ice(unsigned char index);
	Ice(string name);
	~Ice();

	static Alchemy* create(PEObject*  obj);
	bool PE_update(unsigned int flag);
	void PE_initAnimation(void);

};

#endif /* defined(__Alchemy__Ice__) */
