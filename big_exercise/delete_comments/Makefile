CROSS =
CC = $(CROSS)gcc
LD = $(CROSS)ld
AR = $(CROSS)ar
RANLIB = $(CROSS)ranlib
STRIP = $(CROSS)strip

CFLAGS = -Wall -Wshadow -Wno-trigraphs -pipe
LDFLAGS = -lm

SOURCES = delete_comments.c 
BIN = main
OBJS = $(SOURCES:.c=.o)

all: $(BIN)

$(OBJS): %.o: %.c
	$(CC) -c -g $(CFLAGS) $< -o $@

$(BIN): $(OBJS)
	$(CC) $(OBJS) $(LDLIBS) -o $(BIN)
#	$(STRIP) hic_const
			
include $(SOURCES:.c=.d)

%.d:%.c
	set -e;rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\o[ :]*,\1.o $@ :,g' < $@.$$$$ >$@; \
	rm -f $@.$$$$

clean:
	@echo "cleanning project"
	rm -rf $(BIN)
	rm -rf *.o *.d *.bak *.c.bak
	@echo "clean completed"
		
.PHONY: clean
