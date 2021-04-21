# googleTest

# gtest-all build
g++ ./googletest/googletest/src/gtest-all.cc -c -I ./googletest/googletest/include/ -I ./googletest/googletest/

# make libgtest.a (static) 
ar -rcv libgtest.a gtest-all.o

# build main.cpp
g++ main.cpp -lgtest -L. -I ./googletest/googletest/include/ -pthread
