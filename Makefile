CXX = g++
CXXFLAGS = -Wall -Werror

main: src/**
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o target/obj/main.o -Iinclude
	$(CXX) $(CXXFLAGS) -c src/new.cpp -o target/obj/new.o -Iinclude
	$(CXX) $(CXXFLAGS) -c src/build/mod.cpp -o target/obj/build/mod.o -Iinclude
	$(CXX) $(CXXFLAGS) -c src/build/toml.cpp -o target/obj/build/toml.o -Iinclude
	$(CXX) $(CXXFLAGS) -o target/ccreate target/obj/main.o target/obj/new.o target/obj/build/mod.o target/obj/build/toml.o

run: target/ccreate
	cd dev && ../target/ccreate build 