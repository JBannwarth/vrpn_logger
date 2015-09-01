#include "vrpn_Tracker.h"
#include "quat.h"

#include "tracked_object.hpp"
#include "quat_ez.hpp"

#include <iostream>
#include <ctime>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

// Command line arguments tags
string TAG_IP_ADDRESS = "-ip=";
string TAG_FILE_NAME =  "-filename=";
string TAG_SEPARATOR =  "-separator=";
string TAG_OBJECT_NAMES = "-objectnames=";

bool stop = false;

vector<tracked_object*> objects;
vector<vrpn_Tracker_Remote*> vrpn_trackers;

vector<double> start_time_s;
vector<double> start_time_us;

struct tracking_info
{
	vector<string> object_names;
	string ip_address;
	string logging_filename;
	string logging_extension;
	string separator;
};

void save_data(tracking_info tracking_setup);
int parse_inputs(int argc, char* argv[], tracking_info* tracking_setup);

void VRPN_CALLBACK handle_tracker(void* object_pointer, const vrpn_TRACKERCB t)
{
	rotation_quat tracked_quat;
	tracked_quat.qx = t.quat[0];
	tracked_quat.qy = t.quat[1];
	tracked_quat.qz = t.quat[2];
	tracked_quat.qw = t.quat[3];

	position tracked_pos;
	tracked_pos.x = t.pos[0];
	tracked_pos.y = t.pos[1];
	tracked_pos.z = t.pos[2];

	tracked_object* object = (tracked_object*)object_pointer;
	object->update_pose(tracked_pos, tracked_quat, t.msg_time.tv_sec, t.msg_time.tv_usec);
}

void logging_thread(tracking_info& tracking_setup)
{

	for (int i = 0; i < (int)tracking_setup.object_names.size(); i++)
	{
		objects.push_back(new tracked_object(tracking_setup.object_names.at(i)));
	}

	// Initiate callback for each object
	
	for (int i = 0; i < (int)objects.size(); i++)
	{
		string vrpn_address = tracking_setup.object_names.at(i) + "@" + tracking_setup.ip_address;

		vrpn_trackers.push_back(new vrpn_Tracker_Remote(vrpn_address.c_str()));

		vrpn_trackers.at(i)->register_change_handler((void*)objects.at(i), handle_tracker);
	}

	while( !stop )
	{
		for (int i = 0; i < (int)vrpn_trackers.size(); i++)
		{
			vrpn_trackers.at(i)->mainloop();
		}
	}

	save_data(tracking_setup);
}

int main(int argc, char* argv[])
{
	tracking_info tracking_setup;

	int valid_input = parse_inputs(argc, argv, &tracking_setup);

	if (valid_input != 0)
	{
		thread log_t(logging_thread, ref(tracking_setup));

		// Wait for user to press the enter key
		cin.get();

		stop = true;

		// Wait for thread to close
		log_t.join();
	}

	return 0;
}

void save_data(tracking_info tracking_setup)
{
	// Log each object as filename_objectname.extension
	string filename = tracking_setup.logging_filename + "." + tracking_setup.logging_extension;
	string sep = tracking_setup.separator;
	ofstream logging_file;
	logging_file.open(filename.c_str());


	// Find object with the most saved data
	int max_data_index = 0;
	for (int i = 1; i < (int)objects.size(); i++)
	{
		if (objects.at(i)->size() > objects.at(max_data_index)->size())
		{
			max_data_index = i;
		}
	}

	// Create headers
	int max_data_length = objects.at(max_data_index)->size();

	for (int j = 0; j < (int)objects.size(); j++)
	{
		string name = objects.at(j)->get_name();
		logging_file << "time_" << name << sep << "x_" << name << sep << "y_" << name << sep <<
			"z_" << name << sep << "roll_" << name << sep << "pitch_" << name << sep << "yaw_" <<
			name << sep;
	}
	logging_file << endl;

	// Save data
	for (int i = 0; i < max_data_length; i++)
	{
		for (int j = 0; j < (int)objects.size(); j++)
		{
			if (i < (int)objects.at(j)->size())
			{
				logging_file << objects.at(j)->get_time(i) << sep <<
					objects.at(j)->get_position(i).x << sep <<
					objects.at(j)->get_position(i).y << sep <<
					objects.at(j)->get_position(i).z << sep <<
					objects.at(j)->get_euler(i).roll << sep <<
					objects.at(j)->get_euler(i).pitch << sep <<
					objects.at(j)->get_euler(i).yaw << sep;
			}
			else
			{
				// There's no more data to save for this object
				logging_file << sep << sep << sep << sep << sep << sep << sep;
			}
		}
		logging_file << endl;
	}

	logging_file.close();
}

int parse_inputs(int argc, char* argv[], tracking_info* tracking_setup)
{

	if (argc < 1)
	{
		// Needs at least the tracked object's name
		cout << "Err: not enough input arguments\n";
		cout << "Err: example syntax: vrpn_logger -ip=192.168.20.4 -filename=data.csv "
			<< "-objectnames=quadcopter0,quadcopter1\n";

		return 0;
	}
	else
	{
		// Default settings
		// Generate filename in format recording_yyyy_mm_dd_hh_mm.txt
		time_t t = time(0);
		struct tm * now = localtime(&t);

		string year = to_string(now->tm_year + 1900);
		string month = to_string(now->tm_mon + 1);
		string day = to_string(now->tm_mday);
		string hours = to_string(now->tm_hour);
		string minutes = to_string(now->tm_min);

		tracking_setup->logging_filename = "recording_" + year + "_" + month + "_" +
			day + "_" + hours + "_" + minutes;
		tracking_setup->logging_extension = "csv";
		tracking_setup->separator = ';';
		tracking_setup->ip_address = "localhost";		

		bool found_object_name = false;

		for (int i = 1; i < argc; i++)
		{
			string argument = argv[i];

			if (argument.compare(0, TAG_IP_ADDRESS.size(), TAG_IP_ADDRESS) == 0)
			{
				// Check validity of ip address
				string ip_address_str = argument.substr(TAG_IP_ADDRESS.size());
				
				bool valid_ip_address = false;

				if (ip_address_str.compare("localhost") == 0)
				{
					valid_ip_address = true;
				}
				else
				{
					// Look for address in format xxx.xxx.xxx.xxx, e.g. 192.168.20.4
					string ip_address_tmp = ip_address_str;

					// Find location of first dot from beginning of string, remove
					// everything up to and including that dot from the string
					// Repeat and count occurences
					// Dot can't be the first or last element of the string as that 
					// would mean the ip address is in the form xxx..xxx.xxx or xxx.xxx.xxx.
					// which aren't valid
					int dot_index = ip_address_tmp.find('.');
					int dot_count = 1;

					while ( (dot_index != string::npos) && (dot_index != 0) )
					{
						ip_address_tmp = ip_address_tmp.substr(dot_index + 1);

						dot_index = ip_address_tmp.find('.');

						dot_count++;
					}

					if (dot_count == 4)
					{
						valid_ip_address = true;
					}
				}

				if (valid_ip_address)
				{
					tracking_setup->ip_address = ip_address_str;
				}
				else
				{
					cout << "Err: invalid ip address\n";
					cout << "Err: make sure it is in one of two following formats:\n";
					cout << "Err: localhost if vicon tracker runs on the same machine\n";
					cout << "Err: xxx.xxx.xxx.xxx (e.g. 10.0.0.1 or 192.168.20.4) if" <<
						"vicon tracker runs on another machine on the network\n";
					return 0;
				}
			}
			else if (argument.compare(0, TAG_FILE_NAME.size(), TAG_FILE_NAME) == 0)
			{
				int tag_length = TAG_FILE_NAME.size();

				// Find and separate extension
				int dot_index = argument.find('.');

				if (dot_index != string::npos)
				{
					int filename_length = dot_index - tag_length;
					tracking_setup->logging_filename = argument.substr(tag_length, filename_length);
					tracking_setup->logging_extension = argument.substr(dot_index + 1, string::npos);
				}
				else
				{
					// No extension entered, keep default
					tracking_setup->logging_filename = argument.substr(tag_length);
				}
				
			}
			else if (argument.compare(0, TAG_SEPARATOR.size(), TAG_SEPARATOR) == 0)
			{
				string separator_str = argument.substr(TAG_FILE_NAME.size());
				if (separator_str.size() == 1)
				{
					tracking_setup->separator = argument.at(TAG_SEPARATOR.size());
				}
				else if ( (separator_str.size() > 1) && separator_str.compare("\t") )
				{
					tracking_setup->separator = '\t';
				}
				else
				{
					cout << "Err: invalid separator argument\n";
					cout << "Err: acceptable separators:\n";
					cout << "Err: \t (for tabulation character)\n";
					cout << "Err: any single character, e.g. ; or ,\n";

					return 0;
				}
				
			}
			else if (argument.compare(0, TAG_OBJECT_NAMES.size(), TAG_OBJECT_NAMES) == 0)
			{
				// Make sure the user has entered a name after the tag
				if (argument.size() > TAG_OBJECT_NAMES.size())
				{
					// Remove the tag
					string names_str = argument.substr(TAG_OBJECT_NAMES.size());

					// Separate the names and save them separately
					int comma_index = names_str.find(',');
					
					tracking_setup->object_names.push_back(names_str.substr(0, comma_index));

					while (comma_index != string::npos)
					{
						names_str = names_str.substr(comma_index + 1);

						comma_index = names_str.find(',');

						tracking_setup->object_names.push_back(names_str.substr(0, comma_index));
					}

					found_object_name = true;
				}
			}
			else
			{
				cout << "Err: invalid input argument\n";
				cout << "Err: recognised arguments:\n";
				cout << "Err: " << TAG_IP_ADDRESS << " " << TAG_FILE_NAME << " " <<
					TAG_SEPARATOR << " " << TAG_OBJECT_NAMES << endl;

				return 0;
			}
		}

		if (!found_object_name)
		{
			cout << "Err: missing object name\n";
			cout << "Err: please enter the name of the object being tracked\n";
			cout << "Err: Example syntax: vrpn_logger -objectnames=quadcopter\n";

			return 0;
		}

		return -1;
	}
}