CXX = g++
CXXFLAGS = -std=c++2a -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++2a -Ih -pthread
OBJECTS = ./obj/main.o ./obj/maze.o
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/main.o: ./cpp/main.cpp ./h/maze.h
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
./obj/maze.o: ./cpp/maze.cpp
	$(CXX) $(CXXFLAGS) ./cpp/maze.cpp -o ./obj/maze.o
clean:
	rm -fv $(TARGET) $(OBJECTS)