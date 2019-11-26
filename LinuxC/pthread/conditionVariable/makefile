# makefile pth_condition_variable

src=pth_cond.c pth_cond_test.c 
bin=pth_cond pth_cond_test 
save_path=~/bin/linuxC/

all: $(bin) 

pth_cond_test: pth_cond_test.c
	gcc $^ -o $@ -lpthread 
	cp $@ $(save_path)
pth_cond: pth_cond.c
	gcc $^ -o $@ -lpthread 
	cp $@ $(save_path)
clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean

