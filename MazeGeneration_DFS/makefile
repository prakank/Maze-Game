TARGET = MazeGeneration
CC = g++
# -w is used to suppress the warnings
CFLAGS = -w -lSDL2 -lSDL2_image `pkg-config --cflags --libs sdl2`

all: clean build run clean

build:
	@echo "Building Project ... "
	$(CC) $(TARGET).cpp $(CFLAGS) -o $(TARGET)

run:
	./$(TARGET)

clean:
	$(RM) -r $(TARGET)
