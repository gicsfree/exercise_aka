objs = main.o d2b.o multi.o encryption.o exchange.o 
main: $(objs)
	$(CC) $^ -o $@

sources = main.c d2b.c multi.c encryption.c exchange.c

include $(sources:.c=.d)

%.d:%.c
	set -e;rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\o[ :]*,\1.o $@ :,g' < $@.$$$$ >$@; \
	rm -f $@.$$$$

clean:
	@echo "cleanning project"
	-rm *.o *.d
	@echo "clean completed"

.PHONY: clean
