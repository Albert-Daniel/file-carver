CC = gcc # C Compiler
CFLAGS = -Wall -Wextra -std=c11 -Iinclude # Compiler options (shows warnings) (extra warnings) (uses the standard C11) (searches for include/ headers)

SRC = src/main.c src/jpeg_carver.c # Source files (the files that will be compiled)

TARGET = carver # Output's name (./carver ...)

all: $(TARGET) # What to do when you type make

$(TARGET): $(SRC) # If SRC files change, recompile
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) # it actually is; gcc -Wall -Wextra -std=c11 -Iinclude src/main.c src/jpeg_carver.c -o carver

clean: # If you say: make clean
	rm -f $(TARGET) # deletes 'carver'