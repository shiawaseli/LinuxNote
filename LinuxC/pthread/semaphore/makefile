# makefile pth_semaphore

src=pth_sem.c sem_test.c
bin=pth_sem sem_test 
save_path=~/bin/linuxC/

objs=my_sem
clean_objs=clean_my_sem

all: $(objs) $(bin)

sem_test: sem_test.c
	gcc $^ -o $@ -lpthread
	cp $@ $(save_path)
pth_sem: pth_sem.c
	gcc $^ -o $@ -lpthread
	cp $@ $(save_path)

clean: $(clean_objs)
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)

my_sem:
	make -C ./sem_by_mutex 
clean_my_sem:
	make -C ./sem_by_mutex clean 

.PHONY: clean

