CC = gcc
CFLAGS = -g -Wall -Wextra

SRCS = $(wildcard ./*.c)
INCS = $(wildcard ./*.h)
TARGET = vzip

all: $(TARGET)

$(TARGET): $(SRCS) $(INCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS)

clean:
	rm $(TARGET)
