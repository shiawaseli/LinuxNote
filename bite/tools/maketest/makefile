# makefile maketest 

src=mysum.c 
bin=mysum
save_path=~/bin/bite/

all: $(bin)

mysum: mysum.c
	gcc $^ -o $@
	cp $@ $(save_path)

clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clear
