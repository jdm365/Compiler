CC = gcc
CFLAGS = -Wall -g -O3 -march=native
SRCS = src/*.c
INCLUDES = src/*.h
OBJS = $(patsubst %.c, %.o, $(wildcard $(SRCS)))
TARGET = ./bin/compile

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

run: all
	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
