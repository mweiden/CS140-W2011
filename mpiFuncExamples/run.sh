#!/bin/sh

source "targets"

which --tty-only 'orted' 2>&1 > /dev/null
if [ $? -ne 0 ]
then
    echo "Your system does not appear able to run MPI."
    echo "Make sure you run this on a system which is"
    echo "capable of running MPI jobs."
    exit
fi

if [ $# -gt 0 ]
then
    if [ $1 == "-h" ] || [ $1 == "--help" ]
    then
        echo "./run.sh [number-of-jobs-per-system]"
        exit
    fi
    SINGLEHOSTPROCS=$1
    PROCPERHOST=$1
else
    SINGLEHOSTPROCS=10 # for single-host usage
    PROCPERHOST=2 # assuming that all machines are dual-core
fi

HOSTFILE="mpihosts"
HOSTS=`wc -l $HOSTFILE | cut -d' ' -f1`
CWD=`pwd`

hostname | grep 'csil\.cs\.ucsb\.edu' > /dev/null
if [ $? == 0 ]
then
    echo "Don't run this script on CSIL; use one of the lab machines instead."
    exit
fi

PROCS=$(($PROCPERHOST * $HOSTS))
if [ $HOSTS == 1 ]
then
    grep localhost $HOSTFILE > /dev/null
    if [ $? == 0 ]
    then
        PROCS=$SINGLEHOSTPROCS
    fi
fi

for i in $TARGETS ; do
    echo "mpirun --no-daemonize -hostfile $HOSTFILE -np $PROCS $CWD/$i"
    mpirun --no-daemonize -hostfile $HOSTFILE -np $PROCS $CWD/$i > $i-output 2> $i-error
    if [ $? == 0 ]
    then
        echo "$i succeeded"
    else
        echo "$i failed"
    fi
done
