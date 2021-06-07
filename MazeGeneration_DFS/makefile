TARGET = Kruskal_Maze
CC = g++
# -w is used to suppress the warnings
CFLAGS = -std=c++17 -w -lSDL2 -lSDL2_image `pkg-config --cflags --libs sdl2`

all: clean build run clean

build:
	@echo "Building Project ... "
	$(CC) $(TARGET).cpp $(CFLAGS) -o maze

run:
	./maze

clean:
	$(RM) -r maze
