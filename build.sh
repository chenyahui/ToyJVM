#!/bin/sh

set -x
ulimit -c unlimited 

BUILD_DIR=${BUILD_DIR:-./build}
BUILD_TYPE=${BUILD_TYPE:-debug}
INSTALL_DIR=${INSTALL_DIR:-${BUILD_DIR}/${BUILD_TYPE}}

mkdir -p $INSTALL_DIR \
	&& cd $BUILD_DIR \
	&& rm -rf ./* \
	&& mkdir $BUILD_TYPE \
	&& cmake .. \
	-DCMAKE_BUILD_TYPE=$BUILD_TYPE \
	&& make
