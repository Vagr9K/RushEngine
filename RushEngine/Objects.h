
#include "ObjModel.h"
#include "Eventing.h"
#include <vector>


class Objects
{

	int InterfaceLayerCount;
	int PhysWorldCount;
public:
	vector<LayerHolder>* GrLayers;
	
	
public:
	Objects(int InterfaceLayerCount, int PhysWorldCount)
	{
		this->InterfaceLayerCount = InterfaceLayerCount;
		this->PhysWorldCount = PhysWorldCount;
		GrLayers = new vector<LayerHolder>[InterfaceLayerCount + PhysWorldCount];
		

	}




};