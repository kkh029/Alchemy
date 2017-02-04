//
//  PEProgressBar.h
//  Alchemy
//
//  Created by Kyounghwan on 2014. 9. 21..
//
//

#ifndef __Alchemy__PEProgressBar__
#define __Alchemy__PEProgressBar__

#include "Common.h"

class PEProgressBar : public CCNode
{
public:
	static PEProgressBar* create(string bar_name, int max, bool direction, const Vec2& anchor);
	void change_pre_bar(int value);
	void change_result_bar(int value);
	int get_remain_value(void);
	float get_bar_end_pos(void);
	float get_bar_width(void);
	Vec2 get_bar_start_pos(void);
	void set_bar_start_pos(Vec2 start);
    void push_particle_to_vector(CCParticleSun* object);
    void erase_particle_from_vector(void);

private:
	CCProgressTimer* result_bar;
	CCProgressTimer* pre_bar;
	Vec2 pos;
	int max;
	int current_pre_value;
	int current_result_value;
	int direction;
	float bar_width;
	std::vector<CCParticleSun*> regen_particle;
};

#endif /* defined(__Alchemy__PEProgressBar__) */
