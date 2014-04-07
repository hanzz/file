#!/bin/bash

cp ./src/.libs/* ./file-tests
cd file-tests
LD_LIBRARY_PATH=. python ./fast-regression-test.py "./file -m ../magic/magic.mgc" exact
echo "EXECUTING:"
LD_LIBRARY_PATH=. ./file -m ../magic/magic.mgc -b db/wav/send.wav
LD_LIBRARY_PATH=. ./file -m ../magic/magic.mgc -bi db/wav/send.wav
ret=$?
cd ..

exit $ret
