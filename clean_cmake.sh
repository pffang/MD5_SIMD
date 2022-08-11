#!/bin/bash
if [ -f "build.ninja" ]; then
    ninja clean
fi
if [ -f "Makefile" ]; then
    make clean
fi

if [ -f "build/build.ninja" ]; then
    ninja -C build/ clean
    rm -rf build/
fi
if [ -f "build/Makefile" ]; then
    make -C build/ clean
    rm -rf build/
fi

for fld in $(find -name "CMakeLists.txt" -printf '%h ')
do
    for cmakefile in CMakeCache.txt cmake_install.cmake CTestTestfile.cmake CMakeFiles Makefile *.moc_parameters moc_* *.ninja
    do
        rm -rf $fld/$cmakefile
    done
done