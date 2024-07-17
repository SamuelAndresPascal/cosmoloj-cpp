rm -rf bin/ lib/ CMakeFiles/ CMakeCache.txt Makefile cmake_install.cmake
cmake . -G "CodeBlocks - Unix Makefiles"
make
make test
ctest -V --output-on-failure
bin/polymorphism-demo
bin/array-demo
bin/unit-simple-ri-demo

