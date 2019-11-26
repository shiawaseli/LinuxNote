# makefile pth_mutex

src=pth_nomutex.c pth_mutex.c
bin=pth_nomutex pth_mutex 
save_path=~/bin/linuxC/

all: $(bin) 

pth_mutex: pth_mutex.c
	gcc $^ -o $@ -lpthread 
	cp $@ $(save_path)
pth_nomutex: pth_nomutex.c
	gcc $^ -o $@ -lpthread 
	cp $@ $(save_path)
clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean

