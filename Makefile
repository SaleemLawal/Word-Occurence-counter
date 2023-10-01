CXX = g++
CXXFLAGS = -g
IODIR =../../proj5_IO

main: main.cpp Bar.o LL.cpp
	$(CXX) $(CXXFLAGS) main.cpp Bar.o LL.cpp -o main

Bar.o: Bar.h Bar.cpp LL.cpp
	$(CXX) $(CXXFLAGS) -c Bar.cpp

LL_test: LL.cpp LL_test.cpp
	$(CXX) $(CXXFLAGS) LL.cpp LL_test.cpp -o LL_test

valLL:
	valgrind ./LL_test

clean:
	rm *.o
	rm *~
	rm *output*

run1:
	./main

