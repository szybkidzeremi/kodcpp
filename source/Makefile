CXX = g++
CXXFLAGS = -std=c++14 -Wall
SRC = arguments.cpp finder.cpp filehandler.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = kodcpp

all: $(EXEC)

$(EXEC): $(OBJ)
    $(CXX) $(OBJ) -o $(EXEC)

%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(EXEC)
