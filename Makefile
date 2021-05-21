CXX = g++
CXXFLAGS = -std=c++2a -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++2a -Ih -pthread
OBJECTS = ./obj/main.o ./obj/cell.o
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/main.o: ./cpp/main.cpp ./h/cell.h ./cpp/
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
./obj/cell.o: ./cpp/cell.cpp
	$(CXX) $(CXXFLAGS) ./cpp/cell.cpp -o ./obj/cell.o
clean:
	rm -fv $(TARGET) $(OBJECTS)