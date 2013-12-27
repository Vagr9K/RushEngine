#include <vector>
#include <iostream>
using namespace std;
struct Event
{
	string EventName;
	bool EventState = false;
	vector<string> EventArgs;
	Event(string Name, bool State)
	{
		EventName = Name;
		EventState = State;
	}
	void AddArgument(string Argument)
	{
		EventArgs.push_back(Argument);
	}
	void ClearArguments()
	{
		EventArgs.clear();
	}
	void AddArgumentFromZero(string Argument)
	{
		ClearArguments();
		AddArgument(Argument);
		
	}
	void ClearAll()
	{
		EventStae = false;
		ClearArguments();
	}
	
	
};

struct Events
{
	vector<Event> Events;
	Events()
	{
		
	}
	Event* FindEvent(string EventName)
	{
		Event* FoundEvent = NULL;
		for(unsigned int i=0; i = Events.size(); i++)
		{
			if(Events.at(i).EventName = EventName)
			{
				FoundEvent = &(Events.at(i));
				break;
			}
		}
		return FoundEvent;
	}
	void AddArgumentToLast(string Argument)
	{
		Event* lastEvent = &Events.back();
		lastEvent->AddArgument(Argument);
	}
	AddEvent(string EventName, bool EventState)
	{
		EventAddr = FindEvent(EventName);
		if(EventAddr == NULL)
		{
			Event NewEvent(EventName, EventState);
			Events.push_back(NewEvent);
		}
		else
		{	
			EventAddr->EventState = EventState;
		}
	}
	AddEvent(string EventName, bool EventState, string Argument)
	{
		AddEvent(EventName, EventState);
		AddArgumentToLast(Argument);	
	}
	void NullifyEvents()
	{
		for(unsigned int i=0;i<Events.size();i++)
		{
			Events.at(i).ClearAll();
		}
	}
	void ClearEvents()
	{
		Events.clear();
	}
	
};