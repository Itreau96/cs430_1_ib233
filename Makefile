# Simple makefile

CC = gcc
CFLAGS = -g -Wall

all: ppmrw

# Create ppmrw
ppmrw: main_program.c
	$(CC) $(CFLAGS) main_program.c -o ppmrw

# Create clean
clean:
	-rm -rf ppmrw *~
