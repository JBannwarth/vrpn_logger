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

#include "tracked_object.hpp"

using namespace std;

// -----------------------------------------------------------------------------
// -------------------------------- CONSTRUCTORS -------------------------------
// -----------------------------------------------------------------------------

tracked_object::tracked_object(string name)
{
    _name = name;

	_start_time_s = -1;
	_start_time_us = -1;
}

// -----------------------------------------------------------------------------
// ------------------------------ UPDATE FUNCTIONS -----------------------------
// -----------------------------------------------------------------------------

void tracked_object::update_pose(position current_position,
	rotation_quat current_orientation, double time_s, double time_us)
{
	update_position(current_position);
	update_orientation(current_orientation);
	update_time(time_s, time_us);
}

void tracked_object::update_position(position current_position)
{
	_positions.push_back(current_position);
}

void tracked_object::update_orientation(rotation_quat current_orientation)
{
	_orientations_quat.push_back(current_orientation);

	rotation_euler orientation_euler;

	quat_to_euler(&orientation_euler, &current_orientation);

	_orientations_euler.push_back(orientation_euler);
}

void tracked_object::update_time(double time_s, double time_us)
{
	if (_start_time_s == -1)
	{
		_start_time_s = time_s;
		_start_time_us = time_us;
	}

	double time_temp = (time_s - _start_time_s) +
		(time_us - _start_time_us) / 1000000;

	_time.push_back(time_temp);
}

// -----------------------------------------------------------------------------
// ------------------------------ PRINT FUNCTIONS ------------------------------
// -----------------------------------------------------------------------------

void tracked_object::print_orientation_euler()
{
	cout << "roll: " << radian_to_degree(_orientations_euler.back().roll) <<
		" pitch: " << radian_to_degree(_orientations_euler.back().pitch) <<
		" yaw: " << radian_to_degree(_orientations_euler.back().yaw);
}

void tracked_object::print_orientation_quat()
{
	cout << "quat_x: " << _orientations_quat.back().qx <<
		" quat_y: " << _orientations_quat.back().qy <<
		" quat_z: " << _orientations_quat.back().qz <<
		" quat_w: " << radian_to_degree(_orientations_quat.back().qw);
}

void tracked_object::print_position()
{
	cout << "pos_x: " << _positions.back().x <<
		" pos_y: " <<_positions.back().y <<
		" pos_z: " << _positions.back().z;
}

void tracked_object::print_pose()
{
    print_position();
    cout << ", ";
    print_orientation_euler();
}
