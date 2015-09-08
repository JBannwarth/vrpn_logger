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
