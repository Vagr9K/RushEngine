#include <vector>
#include <string>
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
		EventState = false;
		ClearArguments();
	}
	
	
};

struct Events
{
	vector<Event> EventContainer;
	Events()
	{
		
	}
	Event* FindEvent(string EventName)
	{
		Event* FoundEvent = NULL;
		for(unsigned int i=0; i = EventContainer.size(); i++)
		{
			if(EventContainer.at(i).EventName == EventName)
			{
				FoundEvent = &(EventContainer.at(i));
				break;
			}
		}
		return FoundEvent;
	}
	void AddArgumentToLast(string Argument)
	{
		Event* lastEvent = &EventContainer.back();
		lastEvent->AddArgument(Argument);
	}
	void AddEvent(string EventName, bool EventState)
	{
	 	Event* EventAddr = FindEvent(EventName);
		if(EventAddr == NULL)
		{
			Event NewEvent(EventName, EventState);
			EventContainer.push_back(NewEvent);
		}
		else
		{	
			EventAddr->EventState = EventState;
		}
	}
	void AddEvent(string EventName, bool EventState, string Argument)
	{
		AddEvent(EventName, EventState);
		AddArgumentToLast(Argument);	
	}
	void NullifyEvents()
	{
		for(unsigned int i=0;i<EventContainer.size();i++)
		{
			EventContainer.at(i).ClearAll();
		}
	}
	virtual bool CheckEvent(string EventName)
	{
		return CheckEventSTD(EventName);
	}
	virtual bool CheckEvent(string EventName, bool CheckState)
	{
		return CheckEventSTD(EventName, CheckState);
	}
	void ClearEvents()
	{
		EventContainer.clear();
	}
protected:
	bool CheckEventSTD(string EventName)
	{
		Event* Eve = FindEvent(EventName);
		if (Eve == NULL)
		{
			return false;
		}
		return Eve->EventState;
	}
	bool CheckEventSTD(string EventName, bool CheckState)
	{
		bool Ret = false;
		Event* Eve;
		Eve = FindEvent(EventName);
		if (Eve == NULL)
		{
			return false;
		}
		if (Eve->EventState == CheckState)
		{
			Ret = true;
		}
		return Ret;
	}

};

