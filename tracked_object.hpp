#ifndef TRACKED_OBJECT
#define TRACKED_OBJECT

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "vrpn_Tracker.h"
#include "quat_ez.hpp"

using namespace std;
class tracked_object
{
protected:
	vector<rotation_quat>  _orientations_quat;
	vector<rotation_euler> _orientations_euler;
	vector<position>       _positions;
	vector<double>         _time;

	double _start_time_s, _start_time_us;
	string _name;
	
public:
    tracked_object(string name);

	int size() { return _time.size(); }

	position       get_position(int i) { return _positions.at(i); }
	rotation_euler get_euler(int i)    { return _orientations_euler.at(i); }
	rotation_quat  get_quat(int i)     { return _orientations_quat.at(i); }
	double         get_time(int i)     { return _time.at(i); }
	string         get_name()          { return _name; }

	double get_roll()  { return _orientations_euler.back().roll; }
	double get_pitch() { return _orientations_euler.back().pitch; }
	double get_yaw()   { return _orientations_euler.back().yaw; }
	double get_x()     { return _positions.back().x; }
	double get_y()     { return _positions.back().y; }
	double get_z()     { return _positions.back().z; }

	void update_pose(position current_position, rotation_quat current_orientation, double time_s, double time_us);
	void update_orientation(rotation_quat current_orientation);
	void update_position(position current_position);
	void update_time(double time_s, double time_us);

    void print_orientation_euler();
    void print_orientation_quat();
    void print_position();
    void print_pose();
};

#endif