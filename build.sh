#!/bin/bash

PROJECT_ROOT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd ) # want to call the script from anywhere
BUILD_DIR=./build
SOURCE_DIR=.
BUILD_TYPE=$1
MYFLAGS="-j10"

cd "$PROJECT_ROOT_DIR" || exit 1
cmake "$2" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -S $SOURCE_DIR -B $BUILD_DIR && cmake --build $BUILD_DIR $MYFLAGS "--config=$BUILD_TYPE" 
