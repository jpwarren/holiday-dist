#/bin/bash
#
# Turn off the Holiday's WiFi Access Point
#
# If the Access point isn't running, don't do this.
#
if [ -e /run/ap-on.pid ]
then
# Kill off the monomanaical DNS server
#
echo ":: Shutting down fake DNS Server"
if [ -e /run/monodns.pid ]
then
    kill -9 `cat /run/monodns.pid`
    rm /run/monodns.pid
fi
#
# Kill of DHCP Server if running
echo ":: DHCP Server shutting down"
if [ -e /run/dhcpd.pid ]
then
    kill `cat /run/dhcpd.pid`
    rm /run/dhcpd.pid
fi
#
# Kill hostapd
echo ":: Hostapd Server shutting down"
if [ -e /run/hostapd.pid ]
then
        kill `cat /run/hostapd.pid`
        # rm /run/hostapd.pid # apparently this happens automagically
fi
#
# Kill off wpa_supplicant
#
if [ -e /run/wpa_supplicant.pid ]
then
    echo ":: WPA_Supplicant shutting down"
    kill `cat /run/wpa_supplicant.pid`
    rm /run/wpa_supplicant.pid
fi
#
# Turn the link off
#
echo ":: wlan0 going down"
ip link set down wlan0
sleep 1
#
# Reconfigure the link
#
#echo ":: Reconfiguring wlan0"
#
ip addr del 192.168.23.254/24 dev wlan0
ip route del default via 192.168.23.254
#
ip link set up wlan0
sleep 1
rm /run/ap-on.pid
echo ":: Access Point stopped"
fi
exit 0
