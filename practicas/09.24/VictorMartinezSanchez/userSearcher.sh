#!/bin/ash

# Get the first parameter and store it in the variable user
USER="$1"

# Pipe the content of the file /etc/passwd to a grep to show if the user exists
FOUND=$(cat /etc/passwd |\
	grep -e "^$USER")

# Verify if the last command was successfull or not
# if it is return just the name of the user if not
# return failed
if [ "$?" -eq 0 ]; then
	echo $FOUND |\
		sed 's/:.*//'
	exit 0
fi
exit 1

