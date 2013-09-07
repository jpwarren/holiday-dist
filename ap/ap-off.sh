#/bin/bash
#
# Turn off the Holiday's WiFi Access Point
#
# Kill off the monomanaical DNS server
#
echo ":: Shutting down fake DNS Server"
kill -9 `cat /run/monodns.pid`
rm /run/monodns.pid
#
echo ":: Shutting down DHCP Server"
killall dhcpd

#
# Kill off wpa_supplicant
#
echo ":: WPA_Supplicant shutting down"
killall wpa_supplicant
#
# Kill of DHCP Server if running
echo ":: DHCP Server shutting down"
killall dhcpd
#
# Turn the link off
#
echo ":: wlan0 going down"
ip link set down wlan0
sleep 1
#
# Reconfigure the link
#
echo ":: Reconfiguring wlan0"
iwconfig wlan0 mode Managed
ip addr del 192.168.23.254/24 dev wlan0
ip route del default via 192.168.23.254
#
ip link set up wlan0
sleep 1
echo ":: Access Point stopped"

