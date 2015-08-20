#ifndef TRACKED_OBJECT
#define TRACKED_OBJECT

#include "quat.h"
#include <iostream>

using namespace std;

class tracked_object
{
    protected:
        q_type     _orientation_quat;
        q_vec_type _orientation_euler;

    public:
        tracked_object();

        double get_roll()  { return _orientation_euler[Q_ROLL]; }
        double get_yaw()   { return _orientation_euler[Q_YAW]; }
        double get_pitch() { return _orientation_euler[Q_PITCH]; }

        void set_orientation(q_vec_type orientation_quat);
        void print_orientation_euler();
        void print_orientation_quat();
};

#endif
