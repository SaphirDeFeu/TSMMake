CXX = g++
CXXFLAGS = -Wall -Werror

main: src/*
	$(CXX) $(CXXFLAGS) -o target/ccreate src/main.cpp