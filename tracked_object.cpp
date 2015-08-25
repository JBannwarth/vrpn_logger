#include <string>
#include <sstream>

#include "tracked_object.hpp"

using namespace std;

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

tracked_object::tracked_object(string filename)
{
    clear_orientation();
    _logging_filename = filename;
    start_logging();
}

tracked_object::tracked_object()
{
    clear_orientation();

    // Generate filename in format recording_yyyy_mm_dd_hh_mm.txt
    time_t t = time(0);
    struct tm * now = localtime (& t);

    string year    = to_string(now->tm_year + 1900);
    string month   = to_string(now->tm_mon + 1);
    string day     = to_string(now->tm_mday);
    string hours   = to_string(now->tm_hour);
    string minutes = to_string(now->tm_min);

    _logging_filename = "recording_" + year + "_" + month + "_" + day + "_" +
        hours + "_" + minutes + ".txt";
    _logging = false;
}

void tracked_object::start_logging()
{
    _logging = true;
    _logging_file.open(_logging_filename.c_str());

    _logging_file << "time,x,y,z,roll,pitch,yaw\n";
    _time_start = (double)clock() / CLOCKS_PER_SEC;
}

void tracked_object::stop_logging()
{
    _logging = false;
    _logging_file.close();
}

void tracked_object::save_data()
{
    double elapsed_time = (double)(clock() - _time_start) / CLOCKS_PER_SEC;

    _logging_file << elapsed_time << "," << get_x() << "," << get_y() << "," << get_z() << "," <<
        get_roll() << "," << get_pitch() << "," << get_yaw() << "\n";
}

void tracked_object::clear_orientation()
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

void tracked_object::update_position(double x, double y, double z)
{
    _x = x;
    _y = y;
    _z = z;
}

void tracked_object::update_orientation(q_vec_type orientation_quat)
{
    q_copy(_orientation_quat, orientation_quat);
    q_to_euler(_orientation_euler, _orientation_quat);

    if (_logging)
    {
        save_data();
    }
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
