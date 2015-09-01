#include <string>
#include <sstream>

#include "tracked_object.hpp"

using namespace std;

// -----------------------------------------------------------------------------
// ----------------------------------- UTILITY ---------------------------------
// -----------------------------------------------------------------------------

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

// -----------------------------------------------------------------------------
// -------------------------------- CONSTRUCTORS -------------------------------
// -----------------------------------------------------------------------------

tracked_object::tracked_object(string name, string filename)
{
    _name = name;
    _logging_filename = filename;

    clear_pose();
    _logging = false;

	_start_time_s = -1;
	_start_time_us = -1;
	//vrpn_tracker = new vrpn_Tracker_Remote(name.c_str());
	//vrpn_tracker->register_change_handler(0, handle_tracker);
}

tracked_object::tracked_object(string name)
{
    _name = name;

    // Generate filename in format recording_yyyy_mm_dd_hh_mm.txt
    time_t t = time(0);
    struct tm * now = localtime (& t);

    string year    = to_string(now->tm_year + 1900);
    string month   = to_string(now->tm_mon + 1);
    string day     = to_string(now->tm_mday);
    string hours   = to_string(now->tm_hour);
    string minutes = to_string(now->tm_min);

    _logging_filename = "recording_" + _name + "_" + year + "_" + month + "_" +
        day + "_" + hours + "_" + minutes + ".csv";

    clear_pose();
    _logging = false;

	_start_time_s = -1;
	_start_time_us = -1;

	//vrpn_tracker = new vrpn_Tracker_Remote(name.c_str());
	//vrpn_tracker->register_change_handler(0, handle_tracker);
}


// -----------------------------------------------------------------------------
// ------------------------------ LOGGING FUNCTIONS ----------------------------
// -----------------------------------------------------------------------------

void tracked_object::start_logging()
{
    _logging = true;
    _logging_file.open(_logging_filename.c_str());

	_logging_file << "time;x;y;z;roll;pitch;yaw\n";
}

void tracked_object::stop_logging()
{
    _logging = false;
    _logging_file.close();
}

void tracked_object::log_data()
{
    if (_logging)
    {
 		_logging_file << _time << ";" << get_x() << ";" << get_y() <<
			";" << get_z() << ";" << get_roll() << ";" << get_pitch() << ";" <<
            get_yaw() << "\n";
    }
    else
    {
        cout << "Err: logging not initialised, use start_logging() first" << endl;
    }
}

// -----------------------------------------------------------------------------
// ------------------------------ UPDATE FUNCTIONS -----------------------------
// -----------------------------------------------------------------------------

//void VRPN_CALLBACK tracked_object::handle_tracker(void* userData, const vrpn_TRACKERCB t)
//{
//	_x = t.pos[0];
//	_y = t.pos[1];
//	_z = t.pos[2];
//
//	_orientation_quat[Q_X] = t.quat[0];
//	_orientation_quat[Q_Y] = t.quat[1];
//	_orientation_quat[Q_Z] = t.quat[2];
//	_orientation_quat[Q_W] = t.quat[3];
//
//	q_to_euler(_orientation_euler, _orientation_quat);
//}

void tracked_object::update_pose(double x, double y, double z, q_vec_type orientation_quat,
	double time_s, double time_us)
{
	update_position(x, y, z);
	update_orientation(orientation_quat);
	update_time(time_s, time_us);
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
}

void tracked_object::update_time(double time_s, double time_us)
{
	if (_start_time_s == -1)
	{
		_start_time_s = time_s;
		_start_time_us = time_us;
	}

	_time = (time_s - _start_time_s) + (time_us - _start_time_us) / 1000000;
}

void tracked_object::clear_pose()
{
    _x = 0;
    _y = 0;
    _z = 0;

    for (int i = 0; i < 4; i++)
    {
        _orientation_quat[i] = 0;
    }

    for (int i = 0; i < 3; i++)
    {
        _orientation_euler[i] = 0;
    }
}

//void tracked_object::update()
//{
//	vrpn_tracker->mainloop();
//}

// -----------------------------------------------------------------------------
// ------------------------------ PRINT FUNCTIONS ------------------------------
// -----------------------------------------------------------------------------

void tracked_object::print_orientation_euler()
{
    cout << "roll: " << Q_RAD_TO_DEG(_orientation_euler[Q_ROLL]) <<
        " pitch: " << Q_RAD_TO_DEG(_orientation_euler[Q_PITCH]) <<
        " yaw: " << Q_RAD_TO_DEG(_orientation_euler[Q_YAW]);
}

void tracked_object::print_orientation_quat()
{
    cout << "quat_x: " << Q_RAD_TO_DEG(_orientation_quat[Q_X]) <<
        " quat_y: " << Q_RAD_TO_DEG(_orientation_quat[Q_Y]) <<
        " quat_z: " << Q_RAD_TO_DEG(_orientation_quat[Q_Z]) <<
        " quat_w: " << Q_RAD_TO_DEG(_orientation_quat[Q_W]);
}

void tracked_object::print_position()
{
    cout << "pos_x: " << _x << " pos_y: " << _y << " pos_z: " << _z;
}

void tracked_object::print_pose()
{
    print_position();
    cout << ", ";
    print_orientation_euler();
}
