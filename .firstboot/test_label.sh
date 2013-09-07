#!/bin/bash
#
# Test for the presence of the label server
#
PINGY=`ping -c 10 moorescloud.local`
exit $?
