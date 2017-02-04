#include "ElePanda.h"

PE_s_monster ElePanda::param_ElePanda =
{
    3,
    3,
    "ElePanda",
    MONSTER_TYPE_WALKER,
    250,
    30,
    80,
    0.5
};

ElePanda::ElePanda():Monster(param_ElePanda) {

}

ElePanda::~ElePanda() {

}

Monster* ElePanda::create() 
{
	ElePanda* pElePanda = new ElePanda();

	return pElePanda;
}