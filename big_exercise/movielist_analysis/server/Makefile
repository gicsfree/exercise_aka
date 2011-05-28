objs = movielist_server.o wrap.o -lpthread
movielist_server: $(objs)
	$(CC) $^ -o $@

sources = movielist_server.c wrap.c

include $(sources:.c=.d)

%.d:%.c
	set -e;rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\o[ :]*,\1.o $@ :,g' < $@.$$$$ >$@; \
	rm -f $@.$$$$

clean:
	@echo "cleanning project"
	-rm  movielist_server *.o *.d
	@echo "clean completed"

.PHONY: clean
