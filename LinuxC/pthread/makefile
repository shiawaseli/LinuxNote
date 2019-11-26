# makefile pthread

objs=create exit cond mutex sem phil 
clean_objs=clean_create clean_exit clean_cond clean_mutex clean_sem clean_phil

all: $(objs)
clean: $(clean_objs)

create:
	make -C $@
clean_create:
	make -C ./create clean

exit:
	make -C $@
clean_exit:
	make -C ./exit clean

cond:
	make -C conditionVariable 
clean_cond:
	make -C ./conditionVariable clean

mutex:
	make -C $@
clean_mutex:
	make -C ./mutex clean

sem:
	make -C semaphore 
clean_sem:
	make -C ./semaphore clean

phil:
	make -C TheDinningPhilosophersProblem 
clean_phil:
	make -C ./TheDinningPhilosophersProblem clean

.PHONY: $(objs) $(clean_objs) clean
