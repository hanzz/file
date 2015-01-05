git fetch upstream
git checkout master
git merge -s ours upstream/master -m "merge with upstream"
git diff -R upstream/master src/ magic/ configure.ac > x.patch
patch -p1 < x.patch
git add ./magic/Magdir/*
git commit -a -m 'merge with upstream'
git push
