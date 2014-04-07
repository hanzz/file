#!/bin/bash

cp ./src/.libs/* ./file-tests
cd file-tests
LD_LIBRARY_PATH=. python ./fast-regression-test.py "./file -m ../magic/magic.mgc" exact
ret=$?
cd ..

exit $ret
