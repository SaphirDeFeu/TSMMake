CXX = g++
CXXFLAGS = -Wall -Werror

main: src/*
	cd target/obj && $(CXX) $(CXXFLAGS) -c ../../src/main.cpp
	$(CXX) $(CXXFLAGS) -o target/main target/obj/main.o

run: target/main
	./target/main