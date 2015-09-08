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
