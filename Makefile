CXX = g++
CXXFLAGS = -Wall -Werror

main: src/**
	$(CXX) $(CXXFLAGS) -c src/platform.cpp -o target/obj/platform.o -Iinclude
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o target/obj/main.o -Iinclude
	$(CXX) $(CXXFLAGS) -c src/new.cpp -o target/obj/new.o -Iinclude
	$(CXX) $(CXXFLAGS) -c src/build/mod.cpp -o target/obj/build/mod.o -Iinclude
	$(CXX) $(CXXFLAGS) -c src/build/run.cpp -o target/obj/build/run.o -Iinclude
	$(CXX) $(CXXFLAGS) -c src/help.cpp -o target/obj/help.o -Iinclude
	$(CXX) $(CXXFLAGS) -c src/parser/mod.cpp -o target/obj/parser/mod.o -Iinclude
	$(CXX) $(CXXFLAGS) -o target/tsmmake target/obj/main.o target/obj/new.o target/obj/build/mod.o target/obj/build/run.o target/obj/help.o target/obj/parser/mod.o target/obj/platform.o

test: ./target/tsmmake
	$(CXX) $(CXXFLAGS) tests/main.cpp -o tests/main
	./tests/main
