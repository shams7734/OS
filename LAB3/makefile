#make file for square root code

CC := gcc
CFLAGS := -fopenmp -Wall
SOURCES := make.c make.h -lm
OUT_FILE := a.out

build: $(SOURCES)
	$(CC) $(CFLAGS) -o $(OUT_FILE) $(SOURCES)

clean:
	rm -f $(OUT_FILE)

rebuild: clean build

all: build

