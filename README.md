# Serial_Communication_QT_C++
Serial Communication in QT IDE


1-BURN RASP4 image to SD CARD on Lİnux Platform
https://raspberrypi.stackexchange.com/questions/931/how-do-i-install-an-os-image-onto-an-sd-card

2-DISABLE SCREEN SAVER
   sudo apt-get update
   sudo apt-get install xscreensaver
After install, went to Rpi's desktop "Menu" (left top corner)
Went to preference ---> screensaver.
Then In mode : section, selected "disable screensaver" and closed.
   reboot
   
https://stackoverflow.com/questions/30985964/how-to-disable-sleeping-on-raspberry-pi

3-Change keyboard to Turkey
http://www.tarikakbay.com/blog/raspberry-pi-turkce-klavye-ve-saat-ayarlari/

4-HDMI Picture Setting
    tvservice -d edid.dat
    sudo cp edid.dat /boot/

Edit /boot/config.txt and add
    sudo nano /boot/config.txt
    hdmi_edid_file:1=1
    hdmi_edid_filename:1=edid.dat
    hdmi_force_hotplug:1=1
    hdmi_force_hotplug=1
    hdmi_drive=2

https://www.raspberrypi.org/forums/viewtopic.php?t=244558
https://blog.mivia.dk/solved-hdmi-working-raspberry-pi/



5-ENVIRONMENT SET UP

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
