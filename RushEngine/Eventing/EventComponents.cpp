#include "EventComponents.h"

Event::Event (string Name, bool State)
        {
		EventName = Name;
		EventState = State;
	}
void Event::AddArgument (string Argument)
        {
		EventArgs.push_back(Argument);
	}
void Event::ClearArguments ()
        {
		EventArgs.clear();
	}
void Event::AddArgumentFromZero (string Argument)
        {
		ClearArguments();
		AddArgument(Argument);
		
	}
void Event::ClearAll ()
        {
		EventState = false;
		ClearArguments();
	}
Events::Events ()
        {
		
	}
Event * Events::FindEvent (string EventName)
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
void Events::AddArgumentToLast (string Argument)
        {
		Event* lastEvent = &EventContainer.back();
		lastEvent->AddArgument(Argument);
	}
void Events::AddEvent (string EventName, bool EventState)
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
void Events::AddEvent (string EventName, bool EventState, string Argument)
        {
		AddEvent(EventName, EventState);
		AddArgumentToLast(Argument);	
	}
void Events::NullifyEvents ()
        {
		for(unsigned int i=0;i<EventContainer.size();i++)
		{
			EventContainer.at(i).ClearAll();
		}
	}
bool Events::CheckEvent (string EventName)
        {
		return CheckEventSTD(EventName);
	}
bool Events::CheckEvent (string EventName, bool CheckState)
        {
		return CheckEventSTD(EventName, CheckState);
	}
void Events::ClearEvents ()
        {
		EventContainer.clear();
	}
bool Events::CheckEventSTD (string EventName)
        {
		Event* Eve = FindEvent(EventName);
		if (Eve == NULL)
		{
			return false;
		}
		return Eve->EventState;
	}
bool Events::CheckEventSTD (string EventName, bool CheckState)
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

