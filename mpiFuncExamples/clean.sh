#!/bin/sh

source "targets"

for i in $TARGETS ; do
    echo "rm -f $i $i-output $i-error"
    rm -f $i $i-output $i-error
done
