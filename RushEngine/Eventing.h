
#include <fstream>
#include <ios>
#include <cstdlib>
#include <ctime>
#include <assert.h>
using namespace std;





class GEEventing
{

public:
	void LogError(string Type, string Error)
	{

		time_t TmNow = time(0);
		struct tm TimeNow;
		localtime_s(&TimeNow, &TmNow);
		ofstream Log("logs.txt", std::ios_base::app | std::ios_base::out);;


		Log << "\n";
		Log << "\n";

		Log << TimeNow.tm_mday;
		Log << "-" + (TimeNow.tm_mon + 1);
		Log << "-" + (TimeNow.tm_year + 1990);
		Log << "-" + TimeNow.tm_hour;
		Log << "-" + TimeNow.tm_min;

		Log << "\n";
		Log << "Error Type : ";
		Log << Type.c_str();
		Log << "\n";
		Log << Error.c_str();
		Log << "\n";
		Log << "\n";
		Log.close();


		assert(("Error type: " + Type + "/n " + Error, true));


	}
	void OnGraphicsError(string Error)
	{
		LogError("Graphics Error", Error);
	}

};


