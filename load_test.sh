#!/bin/sh

max=100
ip="$1"
port="$2"
file="$3"

if [ "${#ip}" -eq 0 ]
then
    ip="127.0.0.1"
fi

if [ "${#port}" -eq 0 ]
then
    port="6000"
fi

if [ "${#file}" -eq 0 ]
then
    file="1MB"
fi

for i in `seq 1 $max`
do
    nc "$ip" "$port" < $file &#> /dev/null &
done
