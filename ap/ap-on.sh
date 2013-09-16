#/bin/bash
#
# Turn this Holiday into a WiFi Access Point
# SSID: "MooresCloud"  PSK: "Holidays"
# 
# Routing enabled
# 192.168.23/24, with Holiday at 192.168.23.254
# DHCP server enabled
# DNS catcher enabled
#
# If the access point is already running, don't do this.
#
if [ -e /run/ap-on.pid ]
then
    exit 0
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
# Kill DHCP Client if running
#
echo ":: Shutting down DHCP Client"
if [ -e /run/dhcpcd-wlan0.pid ]
then
    dhcpcd -k wlan0
fi 
#
#
# Kill of DHCP Server if running
echo ":: DHCP Server shutting down"
if [ -e /run/dhcpd.pid ]
then
    kill `cat /run/dhcpd.pid`
fi
#
# Turn the link off
#
echo ":: wlan0 going down"
ip link set down wlan0
sleep 1
#
# Configure the link
#
echo ":: Configuring wlan0"
#iwconfig wlan0 mode Ad-Hoc
#sudo iwconfig wlan0 nickname "Holiday Network"
#iwconfig wlan0 essid MooresCloud
#iwconfig wlan0 key off
#iwconfig wlan0 channel 7
#sudo iwconfig wlan0 commit
ip addr add 192.168.23.254/24 dev wlan0
ip route add default via 192.168.23.254
#
ip link set up wlan0
sleep 1
#
echo ":: Establishing access point..."
/home/holiday/bin/hostapd -B -P/run/hostapd.pid /home/holiday/ap/hostapd.conf
echo ":: Access point configured"
#
# Ok, now setup the DHCP server
#
echo ":: DHCP server starting"
dhcpd -4 -cf /etc/dhcpd.conf wlan0
#
# And start the fake, monomaniacal DNS server
#
echo ":: DNS server starting"
nohup python /home/holiday/ap/monodns.py >> /dev/null &
MONOPID=$!
echo ":: DNS server started as process "$MONOPID
touch /run/monodns.pid
chmod a+w /run/monodns.pid
echo $MONOPID>/run/monodns.pid
#
# And restart avahi-daemon
#
/etc/rc.d/avahi-daemon restart
#
echo ":: Access Point established"
echo $$ > /run/ap-on.pid
