#!/bin/bash
#
# Test for global Internet connectivity
#
PINGY=`ping -c 10 8.8.8.8`
exit $?
