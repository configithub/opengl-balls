CC=g++
#CFLAGS=-g -O3 -std=c99 --float-store 
CFLAGS=-g -std=c99 --float-store --debug
INCLUDES=-I/usr/include
LDFLAGS=-lm -lSDLmain -lSDL -lSDL_image -lGL -L/usr/lib/x86_64-linux-gnu   
SRC_DIR=src
SOURCES=src/main.cpp src/render_tools.cpp src/position.cpp src/rectangle.cpp src/aabb_collision.cpp src/entity.cpp src/component.cpp
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(SOURCES:.c=.h)
MAIN=bin/app

all: $(MAIN)
	
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES) 

$(MAIN): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.PHONY: clean

clean:
	rm -rf bin/app src/*.o


