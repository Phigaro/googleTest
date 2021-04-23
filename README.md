# googleTest

# gtest-all build
g++ ./googletest/googletest/src/gtest-all.cc -c -I ./googletest/googletest/include/ -I ./googletest/googletest/

# make libgtest.a (static) 
ar -rcv libgtest.a gtest-all.o

# build main.cpp
g++ main.cpp -lgtest -L. -I ./googletest/googletest/include/ -pthread

# make gtest
./fuse_gtest_files.py ~/jinha.hwang/

# makegtest-all.o
g++ -c gtest/gtest-all.cc -I.
=> and run make libgtest.a

# new main.cpp build
g++ main.cpp -lgtest -L. -I. -pthread

# make gtest_main.o
g++ ./googletest/googletest/src/gtest_main.cc -c -I.

# add archive to gtest_main.o to libgtest.a
ar rcv libgtest.a gtest_main.o

# make gmock
./googletest/googlemock/scripts/fuse_gmock_files.py .

# make gmock-gtest-all
g++ -c gmock-gtest-all.cc -I.

# make gmock_main.o
g++ -c ./googletest/googlemock/src/gmock_main.cc -I.

# add archive to (gmock-gtest-all.o gmock_main.o) to libgtest.a
ar rcv libgtest.a gmock-gtest-all.o gmock_main.o

# DloggerTarget gmock gen
./googletest/googlemock/scripts/generator/gmock_gen.py DLoggerTarget.h