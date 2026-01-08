CXX = clang++
CXXFLAGS = -std=c++17 -I/opt/homebrew/opt/sfml/include -I./include
LDFLAGS = -L/opt/homebrew/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

SRC = ./src/*.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = sfml-app

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o
