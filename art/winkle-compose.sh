#!/bin/bash
#
# Randomly twinkle, we hope
#
secs=$1
pid=$$
pidx=`printf '0x%06X' $pid` 
while [ $secs -gt "0" ]
do
    twstr="0x000000
$pidx"
    for i in {1..50}
    do
       twstr=$twstr$'\n'
       brite=$(($RANDOM%9))
       britestr="0x0"$brite"0"$brite"0"$brite
       twstr=$twstr$britestr
    done
    #echo "$twstr" > winkle.out
    echo "$twstr" > /run/compose.fifo
    secs=$((secs-1))
    env sleep .1
done
