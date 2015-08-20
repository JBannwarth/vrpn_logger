#include "tracked_object.hpp"

using namespace std;

tracked_object::tracked_object()
{
    for (int i = 0; i < 4; i++)
    {
        _orientation_quat[i] = 0;
    }

    for (int i = 0; i < 3; i++)
    {
        _orientation_euler[i] = 0;
    }
}

void tracked_object::set_orientation(q_vec_type orientation_quat)
{
    q_copy(_orientation_quat, orientation_quat);
    q_to_euler(_orientation_euler, _orientation_quat);
}

void tracked_object::print_orientation_euler()
{
    cout << "roll: " << Q_RAD_TO_DEG(_orientation_euler[Q_ROLL]) <<
        " pitch: " << Q_RAD_TO_DEG(_orientation_euler[Q_PITCH]) <<
        " yaw: " << Q_RAD_TO_DEG(_orientation_euler[Q_YAW]) << endl;
}

void tracked_object::print_orientation_quat()
{
    cout << "X: " << Q_RAD_TO_DEG(_orientation_quat[Q_X]) <<
        " Y: " << Q_RAD_TO_DEG(_orientation_quat[Q_Y]) <<
        " Z: " << Q_RAD_TO_DEG(_orientation_quat[Q_Z]) <<
        " W: " << Q_RAD_TO_DEG(_orientation_quat[Q_W]) << endl;
}
