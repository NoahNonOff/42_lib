#!/bin/bash

binName=webServer
pid=`pidof $binName`

if [ $? -eq 1 ]; then
	echo "error: webServer isn't running"
else
	kill $pid
fi