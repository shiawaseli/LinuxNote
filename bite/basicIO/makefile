# makefile basicIO

src = io_review.c io_sysio.c 
bin = io_review io_sysio
save_path = ~/bin/bite/

all: $(bin) 

io_sysio: io_sysio.c
	gcc $^ -o $@
	cp $@ $(save_path)
io_review: io_review.c
	gcc $^ -o $@
	cp $@ $(save_path)

clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean
