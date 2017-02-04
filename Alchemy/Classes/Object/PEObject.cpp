#include "PEObject.h"

PEObject::PEObject() {
	m_name = "";
	m_index = 0;
	m_circle = 0;
	m_hp	= 0;
	m_type = 0;
	m_block = false;
	m_ani_default = 0;
	m_ani_fad_out = -1;
	m_ani_attack = -1;
	m_ani_special = -1;
	m_hitTime = 0;
	m_winSize = CCDirector::sharedDirector()->getWinSize();
}

PEObject::PEObject(PE_s_resource resource)
{
	m_name = resource.name;
	m_index = resource.index;
	m_circle = resource.circle;
	m_hp = resource.hp;
	m_type = resource.type;
	m_block = resource.block;
}

PEObject::PEObject(PE_s_monster monster) {
	m_name = monster.name;
	m_index = monster.index;
	m_circle = monster.circle;
	m_hp	= monster.hp;
	m_type = monster.type;
}

PEObject::~PEObject() {

}

string PEObject::getName() {
	return m_name;
}

void PEObject::PE_setName(string name)
{
	m_name = name;
}

int PEObject::getIndex() {
	return m_index;
}

unsigned char PEObject::getCircle() {
	return m_circle;
}

int PEObject::getHp() {
	return m_hp;
}

void PEObject::setHp(int hp) {
	m_hp = hp;
}

unsigned char PEObject::getType() {
	return m_type;
}

bool PEObject::getBlock() {
	return m_block;
}

void PEObject::setPosXIndex(int x)
{
	m_pos_index.x = x;
}

int PEObject::getPosXIndex(void)
{
	return m_pos_index.x;
}

void PEObject::setPosYIndex(int y)
{
	m_pos_index.y = y;
}

int PEObject::getPosYIndex(void)
{
	return m_pos_index.y;
}

void PEObject::setPosIndex(Vec2 pos)
{
	m_pos_index.x = (int)pos.x;
	m_pos_index.y = (int)pos.y;
}

Vec2 PEObject::getPosIndex(void)
{
	return m_pos_index;
}

unsigned char PEObject::PE_getResourceType()
{
	return m_type;
}

unsigned char PEObject::PE_getResourceIndex(void)
{
	return m_index;
}

void PEObject::PE_setResourceIndex(unsigned char index)
{
	m_index = index;
}

void PEObject::Hit(int attackPoint)
{
	if(m_hp > 0)
	{
		m_hp -= attackPoint;
	}
}
