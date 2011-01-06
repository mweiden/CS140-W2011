#!/bin/sh

HOSTFILE="mpihosts"

for i in `cat $HOSTFILE` ; do
    echo $i | grep 'slots=' > /dev/null
    if [ $? == 0 ]
    then
        continue
    fi
    if [ $i == "localhost" ]
    then
        echo "killall orted"
        killall orted
    else
        echo "ssh $i \"killall orted\""
        ssh $i "killall orted"
    fi
done
