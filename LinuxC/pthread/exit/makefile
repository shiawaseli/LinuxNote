# makefile pthread_exit

src=pth_exit.c
bin=pth_exit
save_path=~/bin/linuxC/

all: $(bin)

pth_exit: pth_exit.c
	gcc $^ -o $@ -lpthread 
	cp $@ $(save_path)
clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean

