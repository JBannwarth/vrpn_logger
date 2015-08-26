#include "vrpn_Tracker.h"
#include "vrpn_Button.h"
#include "vrpn_Analog.h"
#include "quat.h"

#include "tracked_object.hpp"

#include <iostream>
#include <ctime>
#include <sstream>
#include <pthread.h>

using namespace std;

tracked_object* quadcopter;

bool stop = false;

string ip_address;
string object_name;
string logging_filename;

void VRPN_CALLBACK handle_tracker(void* userData, const vrpn_TRACKERCB t )
{
	q_type tracked_quat;

	// Put quaternion in format used by quat library
	tracked_quat[Q_X] = t.quat[0];
	tracked_quat[Q_Y] = t.quat[1];
	tracked_quat[Q_Z] = t.quat[2];
	tracked_quat[Q_W] = t.quat[3];

	quadcopter->update_pose(t.pos[0], t.pos[1], t.pos[2], tracked_quat);
	quadcopter->log_data();
	quadcopter->print_pose();
	cout << endl;
}

void *logging_thread(void*)
{
	string vrpn_address = object_name + "@" + ip_address;
	// ostringstream address;
	// address << argv[2] << "@" << argv[1];
	// cout << "Connecting to: " << address.str().c_str() << endl;
	// address.str().c_str()
	vrpn_Tracker_Remote* vrpnTracker = new vrpn_Tracker_Remote(vrpn_address.c_str());

	vrpnTracker->register_change_handler( 0, handle_tracker );

	if ( logging_filename.compare("") == 0 )
	{
		// Use default file name
		quadcopter = new tracked_object(object_name);
	}
	else
	{
		quadcopter = new tracked_object(object_name, logging_filename);
	}

		quadcopter->start_logging();

	while( !stop )
	{
		vrpnTracker->mainloop();
	}

	quadcopter->stop_logging();
}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Err: not enough input arguments\n";
		cout << "Err: example syntax: vrpn_logger 192.168.20.4 quadcopter data.csv\n";
		cout << "Err: i.e. vrpn_logger <broadcaster_ip_address> " <<
			"<tracked_object_name> <file_name>\n";
	}
	else
	{
		if (argc == 3)
		{
			ip_address = argv[1];
			object_name = argv[2];
			logging_filename = "";
		}
		else
		{
			ip_address = argv[1];
			object_name = argv[2];
			logging_filename = argv[3];
		}
		pthread_t log_t;

		pthread_create(&log_t, NULL, &logging_thread, NULL);

		cin.get();

		stop = true;

		// Wait for thread to close
		void* result;
		pthread_join(log_t, &result);

	}

	return 0;
}
