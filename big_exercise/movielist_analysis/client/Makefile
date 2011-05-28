objs = movielist_client.o wrap.o analysis.o
movielist_client: $(objs)
	$(CC) $^ -o $@

sources = movielist_client.c wrap.c analysis.c

include $(sources:.c=.d)

%.d:%.c
	set -e;rm -f $@; \
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\o[ :]*,\1.o $@ :,g' < $@.$$$$ >$@; \
	rm -f $@.$$$$

clean:
	@echo "cleanning project"
	-rm  movielist_client *.o *.d
	@echo "clean completed"

.PHONY: clean
