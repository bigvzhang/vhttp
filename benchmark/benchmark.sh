#!/bin/bash
read -r -d '' DOCUMENT <<DOCUMENT
NAME
      benchmark.sh - create benchmark enviroment
SYNOPSIS
      benchmark.sh create - create media files        
      benchmark.sh [test] - test download speed        
NOTICE
      Please change the variables related to media files and server ports
DOCUMENT

# modify the following variables according your environment
MEDIA_DIR="/cygdrive/d/victour/vweb01/chat/mp3" # location of the media files
MEDIA_URL="mp3"  # the prefix url of the media files
PORT_beast=8090  # port for Beast
PORT_node=8091   # port for NodeJS
PORT_apache=8099 # port for ApacheHttp
PLATFORM="Windows7"
# end -- modify

FILE1=file_1K.mp3
FILE2=file_5M.mp3
FILE3=file_100M.mp3

function create_media_file {
	if [ ! -d "$MEDIA_DIR" ]; then
		mkdir -p "$MEDIA_DIR" || exit
	fi
	dd if=/dev/zero bs=1024c count=1      of=$MEDIA_DIR/$FILE1
	dd if=/dev/zero bs=1024c count=5120   of=$MEDIA_DIR/$FILE2
	dd if=/dev/zero bs=1024c count=102400 of=$MEDIA_DIR/$FILE3
}

function test_4_file {
	file=${1:?}
	echo "--Beast:"  && curl http://localhost:$PORT_beast/$MEDIA_URL/$file --output 1.mp3
	echo "--Node:"   && curl http://localhost:$PORT_node/$MEDIA_URL/$file --output 1.mp3
	echo "--Apache:" && curl http://localhost:$PORT_apache/$MEDIA_URL/$file --output 1.mp3
}

function test {
	echo "====Download a file whose size is 1K on $PLATFORM" && test_4_file $FILE1
	echo "====Download a file whose size is 5M on $PLATFORM" && test_4_file $FILE2
	echo "====Download a file whose size is 100M on $PLATFORM" && test_4_file $FILE3
}

if [ $# -eq 0 ]; then
	test
elif [ $# -eq 1 ]; then
	if [ $1 == "create" ]; then
		create_media_file
	elif [ $1 == "test" ]; then
		test	
	else
		echo "Invalid option($1)"
	fi
else
	echo "$DOCUMENT"
fi
