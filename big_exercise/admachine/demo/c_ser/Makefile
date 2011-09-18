src = $(wildcard *.c)
objs = $(patsubst %.c,%.o,$(src))

CC = gcc
CFLAGS = -Wall -g -O2 -I.
LDFLAGS = -L.

TARGET = server

all:$(TARGET) 

$(TARGET):$(objs)
	$(CC) $(LDFLAGS) $^ -o $@ 

%.o:%.c 
	$(CC) $(CFLAGS) -c $< -o $@ -g

clean:
	-rm -f $(TARGET)
	-rm -f $(objs)
	-rm -f *~
