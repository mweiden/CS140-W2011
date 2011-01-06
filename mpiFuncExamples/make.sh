#!/bin/sh

source 'targets'

which 'mpicc' 2>&1 > /dev/null
if [ $? -ne 0 ]
then
    echo "Your system does not appear to have mpicc installed."
    echo "Make sure it is in your path and run this script again."
    exit
fi

for i in $TARGETS ; do
    echo "mpicc -Wall -o $i $i.c"
    mpicc -Wall -o $i $i.c
done
