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
