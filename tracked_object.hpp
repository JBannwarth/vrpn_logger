#ifndef TRACKED_OBJECT
#define TRACKED_OBJECT

#include "quat.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "vrpn_Tracker.h"

using namespace std;

class tracked_object
{
protected:
    string     _name;
    q_type     _orientation_quat;
    q_vec_type _orientation_euler;
    string     _logging_filename;
    ofstream   _logging_file;
    bool       _logging;
	double     _time;
	double     _start_time_s, _start_time_us;
    double     _x, _y, _z;

    void clear_pose();

	vrpn_Tracker_Remote* vrpn_tracker;

public:
    tracked_object(string name, string filename);
    tracked_object(string name);

    double get_roll()  { return _orientation_euler[Q_ROLL]; }
    double get_pitch() { return _orientation_euler[Q_PITCH]; }
    double get_yaw()   { return _orientation_euler[Q_YAW]; }
    double get_x()     { return _x; }
    double get_y()     { return _y; }
    double get_z()     { return _z; }

    void start_logging();
    void stop_logging();
    void log_data();

    void update_pose(double x, double y, double z, q_vec_type orientation_quat, double time_s, double time_us);
    void update_orientation(q_vec_type orientation_quat);
    void update_position(double x, double y, double z);
	void update_time(double time_s, double time_us);

    void print_orientation_euler();
    void print_orientation_quat();
    void print_position();
    void print_pose();
};

#endif
