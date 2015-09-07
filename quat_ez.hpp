/*
* quat_ez.hpp
* Wrap the quat.h functions to make them a bit nicer to use.
* Written by: Jérémie Bannwarth, jban039@aucklanduni.ac.nz
* University of Auckland, 2015
*/

#ifndef QUAT_EZ
#define QUAT_EZ

#include "quat.h"

struct position
{
	double x, y, z;
};

struct rotation_quat
{
	double qx, qy, qz, qw;
};

struct rotation_euler
{
	double roll, pitch, yaw;
};

extern void quat_to_euler(rotation_euler* euler, rotation_quat* quaternion);

extern void euler_to_quat(rotation_quat* quaternion, rotation_euler* euler);

extern double radian_to_degree(double angle_radian);

#endif