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


AMAZON WEB SERVICES
Test Box projenizde yaptığınız çalışmaları saklamanız için AWS (Amazon Web Service ) de
"CodeCommit" reposu açtık  .

Bu repoya "git" üzerinden erişebilirsiniz. Aşağıda nasıl erişebileceğinizi kısaca yazdım . Eğer bir problem yaşarsanız benimle kontağa geçin.

AWS  kullanıcı adınızı ve şifreleriniz ayrıca göndereceğim.

İyi çalışmalar

1 - AWS ye girmek için aşağıdaki web sayfasını kullanın
https://714169176372.signin.aws.amazon.com/console

Kullanıcı adınızı ve şifrenizi girin.

2- Gelen Sayfada ( AWS Management Console ) bir sürü AWS servisi var . Siz "CodeCommit" i seçin

3- Repositories linkine basınca hesaptaki repoları göreceksiniz , siz TEST_BOX reposunu seçin.

4-Böylece reponuzdaki dosyaları dizinleri ,commitleri görebilirsiniz (şu an pek bir şey yok)

Git ile repoyu bilgisayarınıza çekmek için  ve değişikliklerinizi atmanız için bir git accountu yaratmanız gerekiyor .Aşağıdaki linkteki
"To set up HTTPS Git credentials for CodeCommit" bölümündeki adımları izleyerek bu işlemi yapabilirsiniz.

https://docs.aws.amazon.com/codecommit/latest/userguide/setting-up-gc.html?icmpid=docs_acc_console_connect_np


Eğer ssh ile bu işlemi yapmak isterseniz ilgili dökümanlar :
https://docs.aws.amazon.com/codecommit/latest/userguide/setting-up-ssh-unixes.html  (LINUX)

https://docs.aws.amazon.com/codecommit/latest/userguide/setting-up-ssh-windows.html (WINDOWS)

