# Makefile for thread scheduler
# programming assignment 2
# CS111 UCSC spring 2013

TARGET=scheduler
CC=gcc
OBJS=the_app.o scheduler.o thread_list.o
CFLAGS=-Wall -Wextra -O2
GCC_IGNORE_STRUCT_INIT=-Wno-missing-field-initializers -Wno-missing-braces
FORMAT=indent
FORMAT_TARGET=tschedule.c scheduler.o thread_list.o
FORMAT_FLAGS=-bad -bap -bbb -bbo -br -brs -ce -i2 -cli2 -l80 -lc80 -npcs -npsl -nut

main: $(TARGET)

testlist: thread_list.o
	$(CC) -o $@ $^
    
$(TARGET): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(GCC_IGNORE_STRUCT_INIT)
	
format: $(FORMAT_TARGET)
	$(FORMAT) $(FORMAT_FLAGS) $@
	
clean:
	rm -f $(OBJS) $(TARGET) test
