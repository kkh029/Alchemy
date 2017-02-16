#include "Alchemy.h"
#include "../Layer/GameLayer.h"
#include "../Util/PETime.h"
#include "Alchemy/Mist.h"
#include "Alchemy/Glass.h"
#include "Alchemy/Steam.h"
#include "Alchemy/Flame.h"
#include "Alchemy/Mud.h"
#include "Alchemy/Ice.h"
#include "Alchemy/PlainWater.h"
#include "Alchemy/Sand.h"
#include "Alchemy/Tornado.h"
#include "Alchemy/Rock.h"
#include "Alchemy/Virus.h"
#include "Alchemy/Plant.h"
#include "Alchemy/FireTalisman.h"
#include "Alchemy/WaterTalisman.h"
#include "Alchemy/WindTalisman.h"
#include "Alchemy/EarthTalisman.h"
#include "Alchemy/Thunder.h"
#include "Alchemy/HighGlass.h"
#include "Alchemy/SandStorm.h"
#include "Alchemy/Icicle.h"
#include "Alchemy/Block.h"
#include "Alchemy/Homunculus.h"


SpriteBatchNode* Alchemy::m_pBatchNode_bullets;

PE_s_resource Alchemy::resource_table[RESOURCE_MAX] =
{
	/*
	index circle  type	   res1    res2	 	block   hp		name */
	{0,		0,	NONE,		0,		0,		false, 	0,		{0, 0, 0, 0},	NULL},
	/*1*/
	{1,		1,	RESOURSE,	0,		0,		false,	0,		{13, 10,  7, 12},		"Wind"},
	{2,		1,	RESOURSE,	0,		0,		false,	0,		{10, 11,  5,  9},		"Water"},
	{3,		1,	RESOURSE,	0,		0,		false,	0,		{ 7,  5,  8,  6},		"Fire"},
	{4,		1,	RESOURSE,	0,		0,		false,	0,		{12,  9,  6, 14},		"Earth"},
	{5,		2,	MAGIC_AIR,	2,		3,		false,	0,		{ 0,  0, 15, 16},		"Mist"},
	{6,		2,	MAGIC_GND,	3,		4,		false,	0,		{19, 18, 17, 20},		"Glass"},
	{7,		2,	MAGIC_AIR,	1,		3,		false,	0,		{ 0, 21,  0,  0},		"Steam"},
	{8,		2,	TOWER,		3,		3,		true,	0,		{ 0,  0,  0,  0},		"Flame"},
	{9,		2,	MAGIC_GND,	2,		4,		false,	0,		{ 0,  0, 25, 26},		"Mud"},
	{10,	2,	MAGIC_INS,	1,		2,		false,	0,		{ 0, 24,  0,  0},		"Ice"},
	/*11*/
	{11,	2,	TOWER,		2,		2,		true,	0,		{ 0,  0,  0,  0},		"PlainWater"},
	{12,	2,	MAGIC_AIR,	1,		4,		false,	0,		{23,  0, 22,  0},		"Sand"},
	{13,	2,	TOWER,		1,		1,		true,	0,		{ 0,  0,  0,  0},		"Tornado"},
	{14,	2,	TOWER,		4,		4,		true,	0,		{ 0,  0,  0,  0},		"Rock"},
	{15,	3,	MAGIC_AIR,	3,		5,		false,	0,		{ 0,  0,  0,  0},		"Virus"},
	{16,	3,	TOWER,		4,		5,		true,	0,		{ 0,  0,  0,  0},		"Plant"},
	{17,	3,	TALISMAN,	3,		6,		true,	0,		{ 0,  0,  0,  0},		"FireTalisman"},
	{18,	3,	TALISMAN,	2,		6,		true,	0,		{ 0,  0,  0,  0},		"WaterTalisman"},
	{19,	3,	TALISMAN,	1,		6,		true,	0,		{ 0,  0,  0,  0},		"WindTalisman"},
	{20,	3,	TALISMAN,	4,		6,		true,	0,		{ 0,  0,  0,  0},		"EarthTalisman"},
	/* 21 */
	{21,	3,	MAGIC_AIR,	2,		7,		false,	0,		{ 0,  0,  0,  0},		"Thunder"},
	{22,	3,	MAGIC_GND,	3,		12,		false,	0,		{ 0,  0,  0,  0},		"HighGlass"},
	{23,	3,	MAGIC_AIR,	1,		12,		false,	0,		{ 0,  0,  0,  0},		"SandStorm"},
	{24,	3,	MAGIC_INS,	2,		10,		false,	0,		{ 0,  0,  0,  0},		"Icicle"},
	{25,	3,	TOWER,		3,		9,		true,	0,		{ 0,  0,  0,  0},		"Block"},
	{26,	3,	TOWER,		4,		9,		true,	0,		{ 0,  0,  0,  0},		"Homunculus"},
};

Alchemy* (*create_alchemy[RESOURCE_MAX])(PEObject*) =
{
	NULL,
	/*1*/
	/* 1  */ NULL,
	/* 2  */ NULL,
	/* 3  */ NULL,
	/* 4  */ NULL,
	/* 5  */ Mist::create,
	/* 6  */ Glass::create,
	/* 7  */ Steam::create,
	/* 8  */ Flame::create,
	/* 9  */ Mud::create,
	/* 10 */ Ice::create,
	/*11*/
	/* 11 */ PlainWater::create,
	/* 12 */ Sand::create,
	/* 13 */ Tornado::create,
	/* 14 */ Rock::create,
	/* 15 */ Virus::create,
	/* 16 */ Plant::create,
	/* 17 */ FireTalisman::create,
	/* 18 */ WaterTalisman::create,
	/* 19 */ WindTalisman::create,
	/* 20 */ EarthTalisman::create,
	/* 21 */
	/* 21 */ Thunder::create,
	/* 22 */ HighGlass::create,
	/* 23 */ SandStorm::create,
	/* 24 */ Icicle::create,
	/* 25 */ Block::create,
	/* 26 */ Homunculus::create,
};

Alchemy::Alchemy(PE_s_resource obj)
: PEObject(obj)
{
	m_alive = true;
	m_hp = 20;
	m_max_hp = 20;
	m_pCollision = PE_Collision::getPE_Collision();
	x_pos_offset = 0.0f;
	y_pos_offset = 0.0f;
}

Alchemy::~Alchemy() {
}

Alchemy* Alchemy::create(PEObject* obj) {

	Alchemy* pAlchemy;
	unsigned char index = obj->PE_getResourceIndex();
	if(index < RESOURCE_START || index >= RESOURCE_MAX)
	{
		log("Alchemy create ----------- ERROR! : invalid index access(%d)\n", index);
		return NULL;
	}
	if(create_alchemy[index] != NULL)
	{
		pAlchemy = create_alchemy[index](obj);
	}
	else
	{
		pAlchemy = new Alchemy(Alchemy::resource_table[index]);
		if(pAlchemy == NULL)
		{
			CC_SAFE_DELETE(pAlchemy);
			return NULL;
		}
	}

	pAlchemy->PE_initAnimation();
	pAlchemy->autorelease();
	pAlchemy->start_t = PETime::GetTime();
	return pAlchemy;
}


// GET / SET Function.
Vec2*  Alchemy::GetLocation() {
	return m_location;
}

void Alchemy::SetLocation(Vec2* location) {
	m_location = location;
}

void Alchemy::PE_initAnimation(void)
{
	ArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();
	ani->playWithIndex(0, -1, -1);
}

bool Alchemy::PE_update(unsigned int flag)
{
	return m_alive;
}

void Alchemy::Hit(int attackPoint)
{
	if(m_hp > 0)
	{
		m_hp -= attackPoint;
	}
	else
	{
		m_alive = false;
		this->setVisible(false);
	}
	
}

void Alchemy::PE_cure(bool start)
{
	double diffTime;

	if(start)
	{
		gettimeofday(&event_time[TIME_START], NULL);
		return;
	}
	
	gettimeofday(&event_time[TIME_END], NULL);
	diffTime = time_interval(event_time[TIME_START], event_time[TIME_END]);
	
	if(diffTime > WaterTalisman::CURE)
	{
		m_hp += 1;
		if(m_hp > m_max_hp)
			m_hp = m_max_hp;
		gettimeofday(&event_time[TIME_START], NULL);
	}
	return;
}

void Alchemy::PE_makeResource() {
	Alchemy::m_pBatchNode_bullets = SpriteBatchNode::create("Alchemy/Bullet.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Alchemy/Bullet.plist");
}

SpriteBatchNode* Alchemy::PE_getBatchNode_bullets() {
	if(Alchemy::m_pBatchNode_bullets == NULL)
		Alchemy::PE_makeResource();
	return Alchemy::m_pBatchNode_bullets;
}
