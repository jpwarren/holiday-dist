#!/bin/bash
#
# Test for the existing of a network gateway
#
TESTY=`route -n | egrep UG`
echo $?
exit $?
