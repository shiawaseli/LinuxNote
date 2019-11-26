# makefile pthread_create

src=pth_create.c
bin=pth_create
save_path=~/bin/linuxC/

all: $(bin) 

pth_create: pth_create.c
	gcc $^ -o $@ -lpthread 
	cp $@ $(save_path)
clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean

