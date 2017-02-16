//
//  PEProgressBar.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 9. 21..
//
//

#include "PEProgressBar.h"


PEProgressBar* PEProgressBar::create(string bar_name, int max, bool direction, const Vec2& anchor)
{
	PEProgressBar* pt = new PEProgressBar();
	pt->max = max;
	pt->current_pre_value = max;
	pt->current_result_value = max; 
	pt->direction = direction;
	CCProgressTimer* pResultBar;
	CCProgressTimer* pPreBar;
	
	Sprite* result_bar_image = Sprite::create(bar_name.c_str());
	pResultBar = CCProgressTimer::create(result_bar_image);
	pResultBar->setType(kCCProgressTimerTypeBar);
	pResultBar->setMidpoint(Vec2(direction,0));
	pResultBar->setBarChangeRate(Vec2(1, 0));
	pResultBar->setPercentage(100.0f);
	pResultBar->setAnchorPoint(anchor);
	pResultBar->setColor(ccc3(255,128,128));
	pt->result_bar = pResultBar;
	pt->addChild(pResultBar);
	pt->bar_width = result_bar_image->getContentSize().width;
	
	Sprite* pre_bar_image = Sprite::create(bar_name.c_str());
	pPreBar = CCProgressTimer::create(pre_bar_image);
	pPreBar->setType(kCCProgressTimerTypeBar);
	pPreBar->setMidpoint(Vec2(direction,0));
	pPreBar->setBarChangeRate(Vec2(1, 0));
	pPreBar->setPercentage(100.0f);
	pPreBar->setAnchorPoint(anchor);
	pt->pre_bar = pPreBar;
	pt->addChild(pPreBar);
    
    pt->regen_particle.clear();
	return pt;
}

void PEProgressBar::change_pre_bar(int value)
{
	int change_value = current_result_value + value;

	if(change_value < 0)
	{
		change_value = 0;
	}
	else if(change_value > max)
	{
		change_value = max;
	}
	
	current_pre_value = change_value;
	pre_bar->setPercentage((float)(change_value*100/max));
}

void PEProgressBar::change_result_bar(int value)
{
	int change_value = current_result_value + value;

	if(change_value < 0)
	{
		change_value = 0;
	}
	else if(change_value > max)
	{
		change_value = max;
	}
	
	if(current_result_value != change_value)
	{
		current_result_value = change_value;
		result_bar->setPercentage((float)(current_result_value*100/max));
        
        int particle_num = regen_particle.size();
        if(particle_num)
        {
            for(int i=0; i<particle_num; i++)
            {
                CCParticleSun* par = regen_particle[i];
                if(direction)
                    par->setPosition(Vec2(get_bar_start_pos().x + get_bar_end_pos(), get_bar_start_pos().y));
                else
                    par->setPosition(Vec2(get_bar_start_pos().x - get_bar_end_pos(), get_bar_start_pos().y));
            }
        }
	}
	
	if(current_pre_value != current_result_value)
	{
		change_pre_bar(0);
	}
}

int PEProgressBar::get_remain_value(void)
{
	return current_result_value;
}

float PEProgressBar::get_bar_end_pos(void)
{
	float end_pos = bar_width*(result_bar->getPercentage())/100;
	return end_pos;
}

float PEProgressBar::get_bar_width(void)
{
	return bar_width;
}

Vec2 PEProgressBar::get_bar_start_pos(void)
{
	return pos;
}

void PEProgressBar::set_bar_start_pos(Vec2 start)
{
	pos = start;
}

void PEProgressBar::push_particle_to_vector(CCParticleSun* object)
{
    regen_particle.push_back(object);
}

void PEProgressBar::erase_particle_from_vector(void)
{
    regen_particle.erase(regen_particle.begin());
}
