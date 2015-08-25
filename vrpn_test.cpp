#include "vrpn_Tracker.h"
#include "vrpn_Button.h"
#include "vrpn_Analog.h"
#include "quat.h"

#include "tracked_object.hpp"

#include <iostream>
#include <ctime>

using namespace std;

tracked_object quadcopter;

clock_t start = 0;

void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t )
{
	cout << "dT: " << (double)(clock() - start)/CLOCKS_PER_SEC*1000 << " ";
	start = clock();

	q_type tracked_quat;

	// Put quaternion in format used by quat library
	tracked_quat[Q_X] = t.quat[0];
	tracked_quat[Q_Y] = t.quat[1];
	tracked_quat[Q_Z] = t.quat[2];
	tracked_quat[Q_W] = t.quat[3];

	quadcopter.update_orientation(tracked_quat);
	quadcopter.update_position(t.pos[0], t.pos[1], t.pos[2]);

	quadcopter.print_orientation_euler();
}


int main(int argc, char* argv[])
{
	vrpn_Tracker_Remote* vrpnTracker = new vrpn_Tracker_Remote("quadcopter@192.168.20.4");

	vrpnTracker->register_change_handler( 0, handle_tracker );

	quadcopter.start_logging();

	clock_t t_start = time(0);

	while( (time(0) - t_start) < 20 )
	{
		vrpnTracker->mainloop();
	}

	quadcopter.stop_logging();

	return 0;
}
