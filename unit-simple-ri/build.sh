rm -rf bin/ lib/ CMakeFiles/ CMakeCache.txt Makefile cmake_install.cmake
cmake . -G "CodeBlocks - Unix Makefiles"
make
bin/test
bin/unit-simple-ri-test
