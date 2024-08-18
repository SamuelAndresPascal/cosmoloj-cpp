rm -rf bin/ lib/ CMakeFiles/ CMakeCache.txt Makefile cmake_install.cmake
cmake -DCMAKE_CXX_STANDARD=17 -G "CodeBlocks - Unix Makefiles" .
make
make test
ctest -V --output-on-failure
bin/unit-simple-ri-demo
