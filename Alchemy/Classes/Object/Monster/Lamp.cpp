//
//  Lamp.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 7. 13..
//
//

#include "Lamp.h"

PE_s_monster Lamp::param_Lamp = {
/* index    */    4,
/* circle   */    3,
/* name     */    "Lamp",
/* type     */    MONSTER_TYPE_WALKER,
/* HP       */    50,
/* AP       */    100,
/* range    */    80,
/* speed    */    1.0f
};
Lamp::Lamp():Monster(param_Lamp) {
	
}

Lamp::~Lamp() {
	
}

Monster* Lamp::create()
{
	Lamp* pLamp = new Lamp();
	
	return pLamp;
}