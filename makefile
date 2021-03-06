TARGET = main
CC = g++
# -w is used to suppress the warnings
CFLAGS = -std=c++17 -w -lSDL2 -lSDL2_image -lSDL2_mixer `pkg-config --cflags --libs sdl2`

all: clean build run clean

build:
	@echo "Building Project ... "
	$(CC) $(TARGET).cpp $(CFLAGS) -o $(TARGET)

run:
	./$(TARGET)

clean:
	$(RM) -r $(TARGET)
	$(RM) -r "assets/Maze.txt"
	@echo
