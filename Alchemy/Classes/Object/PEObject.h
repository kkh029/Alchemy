#ifndef Alchemy_PEObject
#define Alchemy_PEObject

#include "Common.h"

enum eAlchemyType
{
	NONE = -1,
	RESOURSE = 0,
	TOWER,
	MAGIC_AIR,
	MAGIC_GND,
	MAGIC_INS,
	TALISMAN,
};

enum eMonsterType
{
	MONSTER_TYPE_WALKER = 0,
	MONSTER_TYPE_FLYER,
};

struct PE_s_resource
{
	unsigned char index;
	unsigned char circle;
	unsigned char type;   /* eAlchemyType */
	unsigned char res1;   /* Index */
	unsigned char res2;   /* Index */
	bool block;
	int hp;
	int make_candidate[4];
	char name[20];
};

struct PE_s_monster
{
	int index;
	unsigned char circle;
	char name[20];
	unsigned char type;
	int hp;
	int ap;
	int range;
	float movementSpeed;
};


class PEObject
{
public:
	PEObject(unsigned char index);
	PEObject();
	PEObject(PE_s_resource resource);
	PEObject(PE_s_monster monster);
	~PEObject();

	string getName();
	void PE_setName(string name);
	int getIndex();
	unsigned char getCircle();
	int getHp();
	void setHp(int hp);
	unsigned char getType();
	bool getBlock();

	void setPosXIndex(int x);
	int getPosXIndex(void);
	void setPosYIndex(int y);
	int getPosYIndex(void);
	void setPosIndex(Vec2 pos);
	Vec2 getPosIndex(void);

	unsigned char PE_getResourceType();
	unsigned char PE_getResourceIndex(void);
	void PE_setResourceIndex(unsigned char index);

	virtual void Hit(int attackPoint);

protected:
	string m_name;
	int m_index;
	unsigned char m_circle;
	int m_hp;
	int m_ap;
	unsigned char m_type;
	bool m_block;
	bool m_object;  // TRUE = ALCHEMY , FALSE = MONSTER
	unsigned char m_ani_default;
	unsigned char m_ani_fad_out;
	unsigned char m_ani_attack;
	unsigned char m_ani_special;

	Size m_contentSize;
	Size m_winSize;
	Vec2 m_pos_index;
	bool m_alive;
	int m_hitTime;

private:
	
};



#endif
