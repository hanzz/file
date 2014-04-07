#!/bin/bash

cp ./src/.libs/* ./file-tests
cd file-tests
export TZ="Europe/Prague"
LD_LIBRARY_PATH=. python ./fast-regression-test.py "./lt-file -m ../magic/magic.mgc" exact
ret=$?
cd ..

exit $ret
