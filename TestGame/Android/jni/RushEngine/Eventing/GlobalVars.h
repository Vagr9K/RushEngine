#include "../Graphics/Components.h"

class GlobalVars
{
public:
	WindowInfo* WindowData;
	GlobalVars()
	{

	}
	~GlobalVars()
	{
		delete WindowData;
	}
};