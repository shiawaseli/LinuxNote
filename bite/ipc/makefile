# makefile ipc
src = pipe.c pipe2.c fifo_read.c fifo_write.c shm_read.c shm_write.c
bin = pipe pipe2 fifo_read fifo_write shm_read shm_write 
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
shm_read: shm_read.c
	gcc $^ -o $@
	cp $@ $(save_path)
shm_write: shm_write.c
	gcc $^ -o $@
	cp $@ $(save_path)

clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean
