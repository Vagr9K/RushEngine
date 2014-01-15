// EventManagers.cpp
//

#include "EventManagers.h"
#define LZZ_INLINE inline
void SystemEventing::LogData (string Type, string Data, bool Throw)
        {

		time_t TmNow = time(0);
		struct tm TimeNow;
		localtime_s(&TimeNow, &TmNow);
		string DataToWrite = "\n";
		DataToWrite += "Date : ";
		DataToWrite += to_string(TimeNow.tm_mday);
		DataToWrite += "/";
		DataToWrite += to_string(TimeNow.tm_mon + 1);
		DataToWrite += "/";
		DataToWrite += to_string(TimeNow.tm_year + 1900);
		DataToWrite += " ";
		DataToWrite += to_string(TimeNow.tm_hour);
		DataToWrite += ":";
		DataToWrite += to_string(TimeNow.tm_min);
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
		/*
		if (Throw == true)
		{
		throw Data;
		}
		*/
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
void GlobalEventManager::Update ()
        {
		//TODO: Check performance problems.
		SDL_PollEvent(&GlobalEvent);
	}
#undef LZZ_INLINE
