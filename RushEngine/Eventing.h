#include <fstream>
#include <ios>
#include <cstdlib>
#include <ctime>
#include <assert.h>
using namespace std;




class GEEventing
{

public:
	void LogData(string Type, string Data, bool Throw)
	{

		time_t TmNow = time(0);
		struct tm TimeNow;
		localtime_s(&TimeNow, &TmNow);
		ofstream Log("logs.txt", std::ios_base::app | std::ios_base::out);;


		Log << "\n";
		Log << TimeNow.tm_mday;
		Log << "-" + (TimeNow.tm_mon + 1);
		Log << "-" + (TimeNow.tm_year + 1990);
		Log << "-" + TimeNow.tm_hour;
		Log << "-" + TimeNow.tm_min;

		Log << "\n";
		Log << "Data Type : ";
		Log << Type.c_str();
		Log << "\n";
		Log << Data.c_str();
		Log << "\n";
		Log.close();
		if (Throw==true)
		{
			throw Data;
		}

		


	}
	void OnGraphicsError(string Error)
	{
		LogData("Graphics Error", Error, true);
	}
	void OPSLog(string OPS)
	{
		LogData("OPS log.", OPS, false);
	}
};


