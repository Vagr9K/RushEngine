#include "Logger.h"
#include <iostream>
using namespace std;


class Eventing
{
public:
	Eventing();
	~Eventing();
	void OnGraphicsError(string Error);




private:

};

Eventing::Eventing()
{

}

Eventing::~Eventing()
{
}

void Eventing::OnGraphicsError(string Error)
{
	Logger::Log("Graphics", Error);
}