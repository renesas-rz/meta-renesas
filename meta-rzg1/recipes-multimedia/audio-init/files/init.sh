#!/bin/sh

name=`uname -a | grep iwg23s | wc -l`
if [ $name -eq 0 ]
then
	amixer set 'DVC In' 50%
	amixer set 'DVC Out' 50%
fi
