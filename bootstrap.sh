#!/bin/sh

mkdir vendor
svn checkout http://googlemock.googlecode.com/svn/trunk/ vendor/googlemock

mkdir build
pushd build
cmake ..
popd
