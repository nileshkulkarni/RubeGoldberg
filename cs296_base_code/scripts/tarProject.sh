#!bin/bash

rm -rf cs296_g28_project
mkdir cs296_g28_project
cp src cs296_g28_project/ -r
cp doc cs296_g28_project/ -r
cp resources cs296_g28_project/ -r
cp Makefile cs296_g28_project/
mkdir -p cs296_g28_project/external/src
cp external/src/Box2D.tgz external/src/cs296_README.txt cs296_g28_project/external/src
cp scripts cs296_g28_project/ -r
tar zcvf ../cs296_g28_project.tar.gz cs296_g28_project/
rm -r cs296_g28_project



