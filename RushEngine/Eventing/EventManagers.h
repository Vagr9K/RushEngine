#pragma once

#include <fstream>
#include <ios>
#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <string>
using namespace std;


#include "EventComponents.h"

#if __cplusplus <= 199711L
#define to_string(Number) to_string(static_cast<long long>(Number))
#endif

class SystemEventing : public Events
{
public:
	void LogData(string Type, string Data, bool Throw)
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
	void GraphicsError(string Error)
	{
		LogData("Graphics Error", Error, true);
	}
	void OPSLog(string OPS)
	{
		LogData("OPS log.", OPS, false);
	}
	void ObjectsError(string Error)
	{
		LogData("Objects error", Error, true);
	}
};

class GlobalEventManager
{
public:
	SDL_Event GlobalEvent;
public:
	void Update()
	{
		//TODO: Check performance problems.
		SDL_PollEvent(&GlobalEvent);
	}
};