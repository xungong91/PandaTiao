#ifndef _AUDIO_HELPER_H_
#define _AUDIO_HELPER_H_

class AudioHelper
{
public:
	~AudioHelper();
	static AudioHelper* Singleton();
	void PlayLoginBackMusic(bool b);
private:
	static AudioHelper* m_audioHelper;
	AudioHelper();
	class CGarbo
	{
	public:
		~CGarbo()
		{
			if (AudioHelper::m_audioHelper)
				delete m_audioHelper;
		}
	};
	static CGarbo Garbo;
};
#endif