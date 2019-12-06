# makefile ipc
src = pipe.c pipe2.c fifo_read.c fifo_write.c
bin = pipe pipe2 fifo_read fifo_write
save_path = ~/bin/bite/

all: $(bin) 

pipe: pipe.c
	gcc $^ -o $@
	cp $@ $(save_path)
pipe2: pipe2.c
	gcc $^ -o $@
	cp $@ $(save_path)
fifo_read: fifo_read.c
	gcc $^ -o $@
	cp $@ $(save_path)
fifo_write: fifo_write.c
	gcc $^ -o $@
	cp $@ $(save_path)

clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean
