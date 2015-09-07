/*
* quat_ez.cpp
* Written by: Jérémie Bannwarth, jban039@aucklanduni.ac.nz
* University of Auckland, 2015
*/

#include "quat_ez.hpp"

extern void quat_to_euler(rotation_euler* euler, rotation_quat* quaternion)
{
	// rotation_quat -> q_vec
	q_type quat_temp;
	quat_temp[Q_X] = quaternion->qx;
	quat_temp[Q_Y] = quaternion->qy;
	quat_temp[Q_Z] = quaternion->qz;
	quat_temp[Q_W] = quaternion->qw;

	q_vec_type euler_temp;
	q_to_euler(euler_temp, quat_temp);

	// q_vec_type -> rotation_euler
	euler->roll = euler_temp[Q_ROLL];
	euler->pitch = euler_temp[Q_PITCH];
	euler->yaw = euler_temp[Q_YAW];
}

extern void euler_to_quat(rotation_quat* quaternion, rotation_euler* euler)
{
	// To-Do: Implement
}

extern double radian_to_degree(double angle_radian)
{
	return (angle_radian * 3.14159265358979323846) / 180.0;
}