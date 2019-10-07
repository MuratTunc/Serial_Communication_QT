# Serial_Communication_QT_C++
Serial Communication in QT IDE

1-ENVIRONMENT SET UP

HW:Raspberrypi3
sw:Qt-C++
OPERATİNG SYSTEM:Linux Debian.

Install QT on Raspberry Pi:
From Shell insert these shell command step by step:
   sudo apt-get update
   sudo apt-get upgrade
   sudo apt-get install qt5-default
   sudo apt-get install qtcreator
   sudo apt-get install libqt5serialport5
   sudo apt-get install libqt5serialport5-dev
   
Open Qtcreator and go to Help > about plugins and and untick Remote Linux
Restart your raspberry pi
Again open Qt creator, go to "Tools > Options > Build and Run" and go to Compilers. Add "GCC" set compiler path as /usr/bin/gcc
Normally Qt version and Debugger will be automatically set, but you can also set them
Then go to Kits (Still inside the Build and Run) and check whether Compiler, Debugger and Qt version are set

[https://www.raspberrypi.org/forums/viewtopic.php?t=69163]


   

