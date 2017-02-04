#ifndef Alchemy_ElePanda
#define Alchemy_ElePanda

#include "Common.h"
#include "../Monster.h"

class ElePanda : public Monster {
public:
	ElePanda();
	~ElePanda();

	static Monster* create(void);
    static PE_s_monster param_ElePanda;
    
private:

};

#endif