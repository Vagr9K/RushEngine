#include "iostream"
using namespace std;

class AudioEngine;
class AudioEffectBASE
{

};

class AudioMusicBASE
{
	Mix_Music* Element;
	bool WasNotPlaying;
	int Volume;
public:
	AudioMusicBASE(string PathToFile)
	{
		
		Element = NULL;
		Element = Mix_LoadMUS(PathToFile.c_str());
		WasNotPlaying = true;
		Volume = 64;
		
	}
	~AudioMusicBASE()
	{
		Mix_FreeMusic(Element);
	}
	void TrackState(void (*Fuction)())
	{
		Mix_HookMusicFinished(Fuction);
	}
	void Play(int Loops = 0)
	{
		Mix_PlayMusic(Element, Loops);
		
		if (WasNotPlaying)
		{
			SetMusicVolume(Volume);
			WasNotPlaying = false;
		}
	}
	void Pause()
	{

		Mix_PauseMusic();
		WasNotPlaying = true;
	}
	void Resume()
	{
		Mix_ResumeMusic();
		WasNotPlaying = false;
	}
	void Restart()
	{

		Mix_RewindMusic();
		WasNotPlaying = false;
	}
	void Stop()
	{
		
		Mix_HaltMusic();
		WasNotPlaying = true;
	}
	void SetMusicVolume(int Volume)
	{
		this->Volume = Volume;
		if (!WasNotPlaying)
		{
			Mix_VolumeMusic(Volume);
		}
	}
};

