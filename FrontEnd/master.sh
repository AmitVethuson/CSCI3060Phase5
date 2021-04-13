#!/bin/sh
make
sh runTests.sh
sh convert.sh
sh comp.sh