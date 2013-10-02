#
# If there is an existing iotas-app.pid, kill it.
# And wipe out the pid file
#
if [ -a /run/iotas-app.pid ]
then
	kill `cat /run/iotas-app.pid`
	rm /run/iotas-app.pid
fi

