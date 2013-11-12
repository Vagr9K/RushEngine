#include <fstream>
#include <ctime>
#include <string>
#include <iostream>
using namespace std;

class Logger
{
public:
	Logger(){}
	static void Log(string Type, string Error)
	{
		time_t TmNow = time(0);
		struct tm TimeNow;
		localtime_s(&TimeNow ,&TmNow);
		ofstream Log;
		
		Log.open("logs.txt", ios::binary || ios::out);
		Log << endl;
		Log << endl;
		/*
		Log << TimeNow.tm_mday;
		Log << "-" + (TimeNow.tm_mon + 1);
		Log << "-" + (TimeNow.tm_year + 1990);
		Log << "-" + TimeNow.tm_hour;
		Log<<"-" + TimeNow.tm_min;
		*/
		Log << endl;
		Log << "Error Type : " + Type;
		Log << endl;
		Log << Error;
		Log << endl;
		Log << endl;
		Log.close();

		throw new string("Error type: " + Type + "/n " + Error);


	}
	



};

