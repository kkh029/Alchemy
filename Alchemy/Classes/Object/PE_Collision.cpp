#include "PE_Collision.h"
#include "Monster.h"

PE_Collision* PE_Collision::instant = new PE_Collision();

PE_Collision::PE_Collision() {
}

PE_Collision::~PE_Collision() {
	
}

PE_Collision* PE_Collision::getPE_Collision() {
	if(!instant)
		instant = new PE_Collision();
	return instant;
}

void PE_Collision::PE_clearVector()
{
	for(int i=0; i<COL_NUM; i++)
		m_monsters_matrix[i].clear();
}

void PE_Collision::PE_reset()
{
	PE_clearVector();
}

void PE_Collision::addMonster(Monster* obj) {
    Vec2 index = broadPos->getPosIndex(obj->getPosition());
    m_monsters_matrix[(int)index.x].push_back(obj);
}

void PE_Collision::PE_updateMatrix()
{
	Monster* obj;
	int check_arrived_monster = 0;
    for(int i=0; i<COL_NUM; i++)
    {
        int monster_total = m_monsters_matrix[i].size();
     
        while(monster_total--)
        {
            obj = m_monsters_matrix[i][monster_total];
            Vec2 index = broadPos->getPosIndex(obj->getPosition());

            if(index.y < 0 || obj->getHp() <= 0)
            {
                if(index.y < 0)
                {
                    check_arrived_monster++;
                    (pListener->*hitDoor)(1);
                }
                
                if(obj->getHp() <= 0)
                {
                    int type = rand()%2;
                    int value = obj->getCircle();
                    
                    CCInteger* data = CCInteger::create(value*4 + type);
                    CCFloat* pos_x = CCFloat::create(obj->getPositionX());
                    CCFloat* pos_y = CCFloat::create(obj->getPositionY());
                    CCArray* param = CCArray::create(data, pos_x, pos_y, NULL);
                    CCNotificationCenter::sharedNotificationCenter()->postNotification("regen_con_mana", param);
                }

                m_monsters_matrix[i].erase(m_monsters_matrix[i].begin()+monster_total);
                obj->setVisible(false);
                obj->ball->setPosition(obj->getPosition());
                obj->ball->getAnimation()->playWithIndex(3, -1, -1, 0, 0);
                CCDelayTime* pDelayTime = CCDelayTime::create(1.0f);
                CCCallFuncO* pCallFuncO =  CCCallFuncO::create(this, callfuncO_selector(PE_Collision::removeMonster), obj);
                obj->ball->runAction(CCSequence::create(pDelayTime, pCallFuncO, NULL));
            }
        }
    }
}

void PE_Collision::removeMonster(CCObject* pObject)
{
    Monster* obj = (Monster*)pObject;
    obj->ball->setVisible(false);
    obj->ball->removeFromParent();
    obj->removeFromParent();
}

void PE_Collision::setHitDoorCallback(CCObject* target, SEL_HITDOOR callback)
{
	pListener = target;
	hitDoor = callback;
}

int PE_Collision::PE_get_monster_num(void)
{
    int total_num = 0;
    for(int i=0; i<COL_NUM; i++)
        total_num += m_monsters_matrix[i].size();
    return total_num;
}
