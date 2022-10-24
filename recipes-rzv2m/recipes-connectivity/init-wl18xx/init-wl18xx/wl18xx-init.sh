#!/bin/sh

#This script is used to disable Extreme Low Power (ELP) mode as a workaround
# for using Wifi on RZ/G2M and RZ/G2N boards.

#Check if machine is RZ/G2M or RZ/G2N.
if [ `uname -n` != rzv2m ] && [ `uname -n` != rzv2ma ]
then
        #Change directory to the directory containing wlconf binary to start the configuration.
        cd /usr/sbin/wlconf

        #Get value of core.conn.sta_sleep_auth in /lib/firmware/ti-connectivity/wl18xx-conf.bin.
        wl18xx_sleep_auth_conf=`./wlconf -i /lib/firmware/ti-connectivity/wl18xx-conf.bin -g | egrep "core.conn.sta_sleep_auth" | awk '{print $3}'`

        #If wl18xx_sleep_auth_conf has already been 0x00, then no need to change value
        if [ $wl18xx_sleep_auth_conf == 0x00 ]
        then
            echo "Extreme Low Power mode has already been disabled."
        else
                #Remove the old wlcore_sdio.ko.
                rmmod wlcore_sdio

                #Setting core.conn.sta_sleep_auth to 0x00 to disable ELP mode.
                if [ $wl18xx_sleep_auth_conf == 0xff ]
                then
                        ./wlconf -i /lib/firmware/ti-connectivity/wl18xx-conf.bin -s core.conn.sta_sleep_auth=0x00 -o /lib/firmware/ti-connectivity/wl18xx-conf.bin
                fi

                #Confirm the value of core.conn.sta_sleep_auth is 0x00 then print the current state of ELP mode.
                wl18xx_sleep_auth_conf=`./wlconf -i /lib/firmware/ti-connectivity/wl18xx-conf.bin -g | egrep "core.conn.sta_sleep_auth" | awk '{print $3}'`
                if [ $wl18xx_sleep_auth_conf == 0x00 ]
                then
                        echo "Extreme Low Power mode is disabled."
                fi

                #Re-insert wlcore_sdio.ko to load the updated firmware.
                modprobe wlcore_sdio
        fi

        #Change back to the current directory
        cd /home/root
fi
