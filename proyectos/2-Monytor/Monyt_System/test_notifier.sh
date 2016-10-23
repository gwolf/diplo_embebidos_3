#!/bin/bash

cat "${1:-/dev/stdin}" > "${2:-/dev/stdout}"

#while (true) ; do
#	echo <&0
#	sleep 1
#done

