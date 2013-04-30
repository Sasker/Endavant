#!/bin/bash
#

VALIDOPTION=0
CLEAN=0
DEBUG=0
RELEASE=0
BUILD_DIR=''
BUILD_STR=''
CMAKE_OPTS=''
HELP=0

function print_usage()
{
    echo -e "uso: $1 [-c] [-d] [-r]\n"
    echo "-c clean"
    echo "-d debug"
    echo "-r release"
    echo "-a all (debug&release)"
    echo "-h esta ayuda"
}

function parse_param()
{
    if [ "$1" == "-c" ]; then
		CLEAN=1
		VALIDOPTION=1
	fi
	if [ "$1" == "-d" ]; then
		DEBUG=1
		VALIDOPTION=1
	fi
	if [ "$1" == "-r" ]; then
		RELEASE=1
		VALIDOPTION=1
	fi				
	if [ "$1" == "-a" ]; then
		DEBUG=1
		RELEASE=1
		VALIDOPTION=1
	fi				
	if [ "$1" == "-h" ]; then
		HELP=1
		VALIDOPTION=1
	fi	
}

if [ $# -gt 2 ]; then
  print_usage "$0"
  exit 1
fi

for item in `seq 1 $#`; do
    parse_param "${!item}"
done

if [ $# -ge 1 -a "$1" == "-h" ]; then
    print_usage "$0"
    exit 0
fi

if [ $VALIDOPTION -eq 0 ]; then
    print_usage "$0"
    exit 0
fi

UNAMESTR="uname -s"
UNAMECONFIGTMP=$(echo $(eval "$UNAMESTR"))
UNAMECONFIG=$(echo ${UNAMECONFIGTMP:0:7})

if [ $UNAMECONFIG == "MINGW32" ]; then
	echo "Windows MinGW32, MSys detected!"
else
	if [ $UNAMECONFIG == "Darwin" ]; then
		echo "Apple, Darwin detected!"
	else
		echo "Linux detected!"
	fi
fi

if [ $CLEAN -eq 1 ]; then
	BUILD_STR="cd build/debug && rm -rf * && cd ../release && rm -rf * && cd ../../ && "
	echo "Clean OK!"
else
	BUILD_STR=""
	CMAKE_THREADS='-j4 '
	if [ $DEBUG -eq 1 ]; then
		BUILD_DIR='build/debug'
		CMAKE_OPTS='-DCMAKE_BUILD_TYPE=debug'
		if [ $UNAMECONFIG == "MINGW32" ]; then
			CMAKE_OPTS="${CMAKE_OPTS} -G 'MSYS Makefiles'"
			CMAKE_THREADS=''
		fi				
		BUILD_STR="${BUILD_STR}cd $BUILD_DIR && "
		BUILD_STR="${BUILD_STR}cmake ${CMAKE_OPTS} ../.. && make ${CMAKE_THREADS} && cd ../.. && "		
	fi
	
	if [ $RELEASE -eq 1 ]; then
		BUILD_DIR='build/release'
		CMAKE_OPTS='-DCMAKE_BUILD_TYPE=release'
		if [ $UNAMECONFIG == "MINGW32" ]; then
			CMAKE_OPTS="${CMAKE_OPTS} -G 'MSYS Makefiles'"
			CMAKE_THREADS=''
		fi				
		BUILD_STR="${BUILD_STR}cd $BUILD_DIR && "
		BUILD_STR="${BUILD_STR}cmake ${CMAKE_OPTS} ../.. && make ${CMAKE_THREADS} && cd ../.. && "		
	fi

fi

BUILD_STR="${BUILD_STR}cd ."		

eval "$BUILD_STR"
