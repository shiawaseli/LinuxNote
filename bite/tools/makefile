# makefile tools

objs=maketest 
clean_objs=clean_maketest

all: $(objs)
clean: $(clean_objs)

maketest:
	make -C $@
clean_maketest:
	make -C ./maketest clean 

.PHONY: $(objs) $(clean_objs) clean
