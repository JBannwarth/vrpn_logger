#ifndef TRACKING_REGISTER
#define TRACKING_REGISTER

#include <vector>
#include "tracked_object.hpp"

class tracking_register
{
private:
	vector<tracked_object> _tracked_objects;

public:
	tracking_register();
	~tracking_register();

	int add_tracked_object(string object_name, string ip_address);
};

#endif