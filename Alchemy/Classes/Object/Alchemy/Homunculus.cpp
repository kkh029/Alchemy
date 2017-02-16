//
//  Homunculus.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 3. 1..
//	1312	Homunculus	3	50	0.5	30	-	Tower	근접			1104	1205	2
//  animation 에러로 인한 임시 코드

#include "Homunculus.h"
#include "WindTalisman.h"
#include "WaterTalisman.h"
#include "EarthTalisman.h"
#include "FireTalisman.h"

#define DEFAULT_INDEX	0
#define ATTACT_INDEX	1
#define LOOP			-1

#define AP 30
#define HP 50

Homunculus::Homunculus(unsigned char index)
	:Alchemy(Alchemy::resource_table[index])
{
	attack_check = false;

	m_hp = HP;
	m_max_hp = HP;
	m_ap = AP;
	
	ap_up = false;
	speed_up = false;
	hp_up = false;
	cure = false;

	x_pos_offset = 0.0f;
	y_pos_offset = 15.0f;
}

Homunculus::~Homunculus()
{}

Alchemy* Homunculus::create(PEObject* obj) 
{
	Homunculus* pHomunculus = new Homunculus(obj->PE_getResourceIndex());

	return pHomunculus;
}

void Homunculus::PE_initAnimation()
{
	ArmatureAnimation* ani;
	
	init(m_name.c_str());
	setAnchorPoint(Vec2(0.5f, 0.0f));
	ani = getAnimation();
	ani_curr_index = DEFAULT_INDEX;
	ani->playWithIndex(DEFAULT_INDEX, -1, -1);
}


bool Homunculus::PE_update(unsigned int flag) {
	ArmatureAnimation* ani = getAnimation();
	Vec2 index = getPosIndex();
	Vec2 tower_pos = getPosition();
	int idx_x = index.x;
	int idx_y = index.y;
	int monster_total = 0;
	Rect tower_box =  getBoundingBox();
	tower_box.setRect(tower_box.getMinX(), tower_box.getMidY(), tower_box.getMaxX(), tower_box.getMaxY()+60.0f);
	
	if( ((flag) & 0x1) != ap_up)
	{
		if(!ap_up)
		{
			ap_up = true;
			m_ap = AP*2;
		}
		else
		{
			ap_up = false;
			m_ap = AP;
		}
		log("[AP] %d", m_ap);
	}
	if( ((flag>>1) & 0x1) != cure)
	{
		if(!cure)
		{
			cure = true;
			PE_cure(true);
		}
		else
		{
			cure = false;
		}
		log("[Cure] %s", (cure)?"ON":"OFF");
	}
	if( (flag>>2 & 0x1) != speed_up)
	{
		if(!speed_up)
		{
			speed_up = true;
			ani->setSpeedScale(3.0f);
		}
		else
		{
			speed_up = false;
			ani->setSpeedScale(1.0f);
		}
		log("[Speed] %f", ani->getSpeedScale());
	}
	if( (flag>>3 & 0x1) != hp_up)
	{
		if(!hp_up)
		{
			hp_up = true;
			m_hp += HP/5;
			m_max_hp += HP/5;
		}
		else
		{
			hp_up = false;
			m_max_hp -= HP/5;
			m_hp = (m_hp>m_max_hp)?m_max_hp:m_hp;
		}
		log("[Max HP] %d", m_max_hp);
	}
	
	for(int y=idx_y; y<idx_y+2; y++)
	{
		if(y>ROW_NUM-1) continue;
				
		int monster_num = m_pCollision->m_monsters_matrix[idx_x].size();
		monster_total += monster_num;
		if(monster_num>0)
		{
			for(int i=0; i<monster_num; i++)
			{
				Monster* obj;
				obj = m_pCollision->m_monsters_matrix[idx_x][i];
				
			//	if(tower_box.intersectsRect(obj->getBoundingBox())
			//	   && ani_curr_index == DEFAULT_INDEX)
				if(ani_curr_index == DEFAULT_INDEX)
				{
					ani_curr_index = ATTACT_INDEX;
					ani->playWithIndex(ATTACT_INDEX, -1, -1);
				}
				//else if(!tower_box.intersectsRect(obj->getBoundingBox())
				//		&& ani_curr_index == ATTACT_INDEX)
				//{
				//	ani_curr_index = DEFAULT_INDEX;
				//	ani->playWithIndex(DEFAULT_INDEX, -1, -1, LOOP, TWEEN_EASING_MAX);
				//}
				
				if(ani_curr_index == ATTACT_INDEX)
				{
					if(attack_check == false
					   && ani->getCurrentFrameIndex() > 30)
					{
						obj->Hit(m_ap);
						attack_check = true;
						break;
					}
					else if(attack_check == true
							&& ani->getCurrentFrameIndex() <= 30)
					{
						attack_check = false;
					}
				}
			}
			
		}
	}
	if(monster_total == 0)
	{
		if(ani_curr_index == ATTACT_INDEX)
		{
			ani_curr_index = DEFAULT_INDEX;
			ani->playWithIndex(DEFAULT_INDEX, -1, -1);
		}
	}

	if(cure)
	{
		PE_cure(false);
	}

	return m_alive;
}
