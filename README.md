# Espressif Rom Switcher
Flips the running rom used by the default OTA Espressif ESP8266 bootloader. Useful for testing OTA upgrade processes when debugging Espressif2Arduino.
NOTE: Currently only supports the ESP8266 with 1MB of flash. Changes will be required to the ld script and boards.txt for other flash sizes

----------

# Prereqs
1. Arduino IDE with Arduino SDK 2.3.0
2. Python 2.7 / 3.4
3. ESP Tool (pip install esptool)

----------

# Building 
You can either build these images yourself of use the precompilied ones in the root of this directory.

1. From the Arduino Folder replace boards.txt and the additional ld scripts into the appropriate place for your instance of Arduino.
2. In Arduino IDE first select the Flash Size "1M (Espressif OTA Rom 1)" and build. 
3. From your build directory run the following command and save the resulting output
 
		esptool.py elf2image --version 2  EspressifRomSwitcher.ino.elf

4. Repeat for Flash Size "1M (Espressif OTA Rom 2)"

You should now have two files, one for each rom location:
- EspressifRomSwitcher.ino-0x01000.bin
- EspressifRomSwitcher.ino-0x81000.bin

----------

# Flashing / Running
Replace the port and baud speed as applicable for your system's port and possible flash speed (try 115200 if 921600 doesn't work)

1. First take a backup image of your flash by running 

		esptool.py -p COM5 read_flash 0x0 0x100000 backup-0x00000.bin (note this is slow ~2 mins)


2. To switch to rom 1 run 
		
		esptool.py -p COM5 -b 921600 write_flash 0x81000 EspressifRomSwitcher.ino-0x81000.bin

3. To switch to rom 2 run
 
		esptool.py -p COM5 -b 921600 write_flash 0x01000 EspressifRomSwitcher.ino-0x01000.bin

4. To restore your backup

		esptool.py -p COM5 -b 921600 write_flash 0x0 backup-0x00000.bin

For fun if you flash both images the ESP8266 will flip flop between the two roms