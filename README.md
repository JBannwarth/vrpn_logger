# vrpn_logger

Log data streamed by motion capture PC over VRPN to csv format

## To-Do

Create Windows makefile

## Usage

Simply open the command line and type:

```
./vrpn_logger 192.168.20.4 object_name filename.csv
```

Press the enter key on your keyboard to end data recording.

## Dependencies

The VRPN library needs to have been installed on your PC. It is a cross-platform library and should work on most operating systems.

### Installing VRPN on Linux

First, you need to install the GUI for CMake.

```
sudo apt-get install cmake-gui
```

Then, `cd` to the directory you want to store the files in.

Download the VRPN git repository and switch to version 7.33:

```
git clone https://github.com/vrpn/vrpn.git
git checkout tags/version_7.33
```

Create a build folder and use the CMake GUI to generate the build files:

```
cd vrpn
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

## Compiling vrpn_logger

Simply run

```
make
```
