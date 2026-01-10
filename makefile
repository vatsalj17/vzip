CC = gcc
CFLAGS = -g -Wall -Wextra

SRCDIR = src
INCDIR = include
OBJ = obj
CFLAGS += -I$(INCDIR)

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJ)/%.o, $(SRCS))

TARGET = vzip

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)

$(OBJ)/%.o: $(SRCDIR)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ):
	mkdir -p $(OBJ)

clean:
	rm -rf $(TARGET) $(OBJ)
