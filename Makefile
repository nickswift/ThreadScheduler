# Makefile for thread scheduler
# programming assignment 2
# CS111 UCSC spring 2013

TARGET=tschedule
CC=gcc
OBJS=tschedule.o
CFLAGS=-Wall -Wextra -O2
FORMAT=indent
FORMAT_TARGET=tschedule.c
FORMAT_FLAGS=-bad -bap -bbb -bbo -br -brs -ce -i2 -cli2 -l80 -lc80 -npcs -npsl -nut

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^
	
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
format: $(FORMAT_TARGET)
	$(FORMAT) $(FORMAT_FLAGS) $@
	
clean:
	rm -f $(OBJS) $(TARGET)