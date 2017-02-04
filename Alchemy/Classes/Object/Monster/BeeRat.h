#ifndef Alchemy_BeeRat
#define Alchemy_BeeRat

#include "Common.h"
#include "../Monster.h"

class BeeRat : public Monster {
public:
	BeeRat();
	~BeeRat();

	static Monster* create(void);
    static PE_s_monster param_BeeRat;

private:

};

#endif