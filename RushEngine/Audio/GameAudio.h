#include "iostream"
using namespace std;

#include "../Objects/ObjectManager.h"


class GameAudio
{
	ObjDBManager<AudioElement>* ManagerDB;
	AudioElement* AuElement;
public:
	GameAudio(string Path, AudioType Type, ObjDBManager<AudioElement>* ManagerDB)
	{
		this->ManagerDB = ManagerDB;
		AuElement = new AudioElement(Path, Type);
		ManagerDB->AddToCreate(AuElement);
	}
	void Play(int LoopCount = 0)
	{
		AuElement->RePlay = true;
		AuElement->LoopCount = LoopCount;
	}
	void Pause()
	{
		AuElement->Playing = false;
	}
	void RePlay()
	{
		AuElement->RePlay = true;
	}
	int getVolume()
	{
		if (AuElement->Type == EFFECT)
		{
			return Mix_VolumeChunk(AuElement->Effect, -1);
		}
		else
		{
			return Mix_VolumeMusic(-1);
		}
	}
	void setVolume(int Volume)
	{
		if (AuElement->Type == EFFECT)
		{
			Mix_VolumeChunk(AuElement->Effect, Volume);
		}
		else
		{
			Mix_VolumeMusic(Volume);
		}
	}

};