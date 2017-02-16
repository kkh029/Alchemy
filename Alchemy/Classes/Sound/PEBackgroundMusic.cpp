//
//  PEBackgroundMusic.cpp
//  Alchemy
//
//  Created by Kyounghwan on 2014. 2. 10..
//
//

#include "PEBackgroundMusic.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

PEBackgroundMusic* PEBackgroundMusic::sInstance = new PEBackgroundMusic();

s_PE_BGM PEBackgroundMusic::m_BGM_list[BGM_INDEX_MAX]=
{
    {NULL,0},
	{"BGM/main1.mp3", 50000}, 
	{"BGM/main2.mp3", 50000},
	{"BGM/bonus.mp3", 79000},
	{"BGM/inventory.mp3", 39000},
	{"BGM/theme12.mp3", 96000}
};

PEBackgroundMusic::PEBackgroundMusic()
{
}

PEBackgroundMusic::~PEBackgroundMusic()
{}

PEBackgroundMusic* PEBackgroundMusic::sharedPEBackgroundMusic()
{
    static PEBackgroundMusic s_SharedPEBackgroundMusic;
    s_SharedPEBackgroundMusic.onoff = UserDefault::sharedUserDefault()->getBoolForKey("BGM");
    return &s_SharedPEBackgroundMusic;
}

void PEBackgroundMusic::PE_play(int index)
{
    if(index != 0)
        m_music_index = index;
    if(onoff)
    {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(PEBackgroundMusic::m_BGM_list[m_music_index].name, true);
    }
}

void PEBackgroundMusic::PE_stop()
{
    if(onoff)
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

void PEBackgroundMusic::PE_pause()
{
    if(onoff)
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void PEBackgroundMusic::PE_resume()
{
    if(onoff)
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void PEBackgroundMusic::PE_mute(bool isMute)
{
    if(onoff)
    {
        if(isMute)
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
        else
            SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
    }
}


void PEBackgroundMusic::PE_set_onoff(bool flag)
{
    onoff = flag;
    if(!onoff)
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
    UserDefault::sharedUserDefault()->setBoolForKey("BGM", onoff);
}

bool PEBackgroundMusic::PE_get_onoff(void)
{
    return onoff;
}
