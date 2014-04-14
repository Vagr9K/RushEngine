#include "EventManagers.h"
#include "../AdvFeatures/Misc.h"

void SystemEventing::LogData (string Type, string Data, bool Throw)
        {
#ifdef __WINDOWS__
		time_t TmNow = time(0);
		struct tm TimeNow;
		localtime_s(&TimeNow, &TmNow);
		string DataToWrite = "\n";
		DataToWrite += "Date : ";
		DataToWrite += ToString(TimeNow.tm_mday);
		DataToWrite += "/";
		DataToWrite += ToString(TimeNow.tm_mon + 1);
		DataToWrite += "/";
		DataToWrite += ToString(TimeNow.tm_year + 1900);
		DataToWrite += " ";
		DataToWrite += ToString(TimeNow.tm_hour);
		DataToWrite += ":";
		DataToWrite += ToString(TimeNow.tm_min);
		DataToWrite += "\n";
		DataToWrite += "Data Type : ";
		DataToWrite += Type;
		DataToWrite += "\n";
		DataToWrite += "Data : ";
		DataToWrite += Data;
		DataToWrite += "\n";

		ofstream Log("logs.txt", std::ios_base::app | std::ios_base::out);
		Log << DataToWrite;
		Log.close();
#endif
		SDL_Log(("RushEngine Error: " +Type+" "+Data).c_str());
	}
void SystemEventing::GraphicsError (string Error)
        {
		LogData("Graphics Error", Error, true);
	}
void SystemEventing::OPSLog (string OPS)
        {
		LogData("OPS log.", OPS, false);
	}
void SystemEventing::ObjectsError (string Error)
        {
		LogData("Objects error", Error, true);
	}

void SystemEventing::AudioError(string Error)
{
	LogData("Audio error", Error, true);
}

void SystemEventing::EngineError(string Error)
{
	LogData("Engine error", Error, true);
}

void GlobalEventManager::Update()
    {
		if (!InLoop || !UseLooping)
		{
			SDL_PollEvent(&GlobalEvent);
		}
	}

