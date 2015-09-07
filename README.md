# vrpn_logger

Written by: Jérémie Bannwarth

University of Auckland, 2015

Log data streamed by motion capture PC over VRPN to csv format.

## To-Do

- [x] Release version 1.0
- [ ] Add graphical interface (not anytime soon)

## Usage

If you are running the program on the computer that is running Vicon Tracker, simply open the command line and type:

```
vrpn_logger.exe -objectnames=name1,name2
```

Where `name1` and `name2` are the names of the objects you are tracking (the program supports any number of objects). 

Press the enter key on your keyboard to end data recording. By default the object poses will be saved in the executable's folder in a comma delimited (`,`) file called recording_YYYY_MM_DD_HH_MM.csv.

The following table describes additional command line options that can be used to change the program's behaviour:

| Command line option | Example          | Default value | Description |
| ------------------- | ---------------- | ------------- | ----------- |
| `-objectnames=` | `-objectnames=quadcopter` | No default | Choose the names of the objects to track. Should be identical to the names used in Vicon Tracker |
| `-ip=` | `-ip=10.0.0.1` | `localhost` | Choose which IP address to connect to. The motion capture PC's address is `10.0.0.1` |
| `-filename=` | `-filename=myfile.txt` | `recording_YYYY_MM_DD_HH_MM.csv` | Choose the name of the file to save data to **(does not handle spaces)** |
| `-separator=` | `-separator=;` | `,` | Choose how values are separated when saved to a file |

Make sure to separate all the options by a space. E.g.

```
vrpn_logger.exe -objectnames=quadcopter,tree -ip=10.0.0.1 -filename=myrecordingdata.csv -separator=\t
```

## Dependencies

The VRPN library needs to have been installed on your PC. It is a cross-platform library and should work on most operating systems.

### Compiling on Linux

#### Installing VRPN

First, you need to install the GUI for CMake.

```
sudo apt-get install cmake-gui
```

Then, `cd` to the directory you want to store the files in.

Download the VRPN git repository and switch to version 7.33:

```
git clone --recursive https://github.com/vrpn/vrpn.git
cd vrpn
git checkout tags/version_07.33
```

Create a build folder and use the CMake GUI to generate the build files:

```
mkdir build
cmake-gui
```

Once the CMake GUI opens, select the vrpn root folder as your source folder and the build folder you created previously as the target folder. Click "Configure" and then "Generate".

`cd` to the build directory and compile the program:

```
cd build
make
sudo make install
```

This should take a while. Once the compilation is done the generated static libraries - `libvrpn.a`, `libvrpnserver.a`, `libvrpn_timecode_generator.a`, `libvrpn_atmel.a` and `libquat.a` (a library for quarternions)- will be moved to the `/usr/local/lib/` folder, which is one of the default include folders on a Linux System.

#### Compiling vrpn_logger

First, make sure you have a C++11 compatible compiler (if in doubt, install g++-4.9 using `sudo apt-get install g++-4.9`).

Then, simply `cd` to the relevant folder and run `make`.

### Compiling the software on Windows using Visual Studio

> The following procedure was tested using Visual Studio 2013

First, `cd` to the desired folder.

First, download the vrpn library repository:

```
git clone --recursive https://github.com/vrpn/vrpn.git
cd vrpn
git checkout tags/version_07.33
```

Then, open `vrpn.sln` using Visual Studio. Update the solution files if prompted.

If you want to be able to use the program on any computer or if you are not interested in modifying the software, follow these extra steps:
> - Right click on quatlib in the Solution Explorer
> - Select Properties
> - At the top of the window, switch to the "Release" configuration
> - Click on "All Options" under the "C/C++" heading
> - Scroll down and change "Runtime Library" from "Multi-threaded Dll (/MD)" to "Multi-threaded (/MT)" - this is necessary in order to avoid having to include the visual studio DLLs along with the software
> - Click "OK" to close the window
> - Do the exact same thing for vrpn in the Solution Explorer
> - Finally, set Visual Studio to compile a "Release" build instead of a "Debug" build. The option is located in a box below the menu bars.

Once the files have been processed (and you have followed the instructions above if needed), build the following solutions (right click on the relevant solution in the solution bar and choose "build"): `quatlib` and `vrpn`.

Now, `cd` back to the root folder and download the vrpn_logger repository:

```
cd ..
git clone https://github.com/JBannwarth/vrpn_logger
cd vrpn_logger
```

Then, open `vrpn_logger.sln` using Visual Studio. The solution file should already be configured to source the vrpn libraries and include files from the folder created in the previous step. Make sure the vrpn and vrpn_logger folders are located in the same root folder, or you will have to modify the include paths manually.

> If you are not interested in modifying the software, set Visual Studio to compile a "Release" build instead of a "Debug" build. The option is located in a box below the menu bars.

Finally, simply build the software using the graphical interface (or pressing F6).
