#include "include/AudioHelper.h"
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

using namespace CocosDenshion;

AudioHelper::AudioHelper()
{
}

AudioHelper::~AudioHelper()
{
	m_audioHelper=NULL;
}
AudioHelper::CGarbo AudioHelper::Garbo;
AudioHelper* AudioHelper::m_audioHelper=NULL;
AudioHelper* AudioHelper::Singleton()
{
	if (m_audioHelper==NULL)
	{
		m_audioHelper =new AudioHelper();
	}
	return m_audioHelper;
}

void AudioHelper::PlayLoginBackMusic(bool b)
{
	if (b)
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic("audio/musicLoingbg.wma",true);
	else
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

