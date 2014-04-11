#!/bin/sh

mkdir vendor
svn checkout http://googletest.googlecode.com/svn/trunk/ vendor/googletest

mkdir build
pushd build
cmake ..
popd
