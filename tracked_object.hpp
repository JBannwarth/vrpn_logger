/*
The MIT License (MIT)

Copyright (c) 2015 Jérémie Bannwarth

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef TRACKED_OBJECT
#define TRACKED_OBJECT

#include <iostream>
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

	double get_roll()  { return _orientations_euler.back().roll; }
	double get_pitch() { return _orientations_euler.back().pitch; }
	double get_yaw()   { return _orientations_euler.back().yaw; }
	double get_x()     { return _positions.back().x; }
	double get_y()     { return _positions.back().y; }
	double get_z()     { return _positions.back().z; }
	string get_name()  { return _name; }

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
