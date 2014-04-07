#!/bin/bash

cp ./src/.libs/* ./file-tests
cd file-tests
LD_LIBRARY_PATH=. python fast-regression-check.py ./file exact
ret=$?
cd ..

exit $ret
