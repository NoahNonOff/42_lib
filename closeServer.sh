#!/bin/bash

binName=webserver
pid=`pidof $binName`

if [ $? -eq 1 ]; then
	echo "error: webServer isn't running"
else
	kill $pid
fi