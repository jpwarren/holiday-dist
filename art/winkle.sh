#!/bin/bash
#
# Randomly twinkle, we hope
#
secs=$1
while [ $secs -gt 0 ]
do
    twstr=""
    for i in {1..50}
    do
       brite=$(($RANDOM%9))
       britestr="0x0"$brite"0"$brite"0"$brite$'\n'
       twstr=$twstr$britestr
    done
    #echo "$twstr"
    echo "$twstr" > /run/pipelights.fifo
    secs=$((secs-1))
    env sleep .05
done
