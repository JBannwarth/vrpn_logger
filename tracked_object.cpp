/*
* tracked_object.cpp
* Written by: Jérémie Bannwarth, jban039@aucklanduni.ac.nz
* University of Auckland, 2015
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
