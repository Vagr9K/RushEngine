#include <vector>
#include <string>
using namespace std;


struct Event
{
  string EventName;
  bool EventState;
  vector <string> EventArgs;
  Event (string Name, bool State);
  void AddArgument (string Argument);
  void ClearArguments ();
  void AddArgumentFromZero (string Argument);
  void ClearAll ();
};
struct Events
{
  vector <Event> EventContainer;
  Events ();
  Event * FindEvent (string EventName);
  void AddArgumentToLast (string Argument);
  void AddEvent (string EventName, bool EventState);
  void AddEvent (string EventName, bool EventState, string Argument);
  void NullifyEvents ();
  virtual bool CheckEvent (string EventName);
  virtual bool CheckEvent (string EventName, bool CheckState);
  void ClearEvents ();
protected:
  bool CheckEventSTD (string EventName);
  bool CheckEventSTD (string EventName, bool CheckState);
};
enum MouseButton
{
  LEFT,
  RIGHT
};
