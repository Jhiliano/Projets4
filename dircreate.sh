#!/bin/sh
obj="obj"
bin="bin"
bint="tests/bin"

if [ ! -n $obj ]; then
 mkdir $obj
fi
if [ ! -n $bin ]; then
 mkdir $bin
fi
if [ ! -n $bint ]; then
 mkdir $bint
fi
