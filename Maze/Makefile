TARGET = maze
CC = g++

CFLAGS = -lSDL2 -lSDL2_image `pkg-config --cflags --libs sdl2`

all: $(TARGET).cpp
	$(CC) $(TARGET).cpp $(CFLAGS) -o $(TARGET)
	./$(TARGET)