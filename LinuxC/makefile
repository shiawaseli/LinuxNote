# makefile linuxC

objs=pthread 
clean_objs=clean_pthread 

all: $(objs)
clean: $(clean_objs)

pthread:
	make -C $@
clean_pthread:	
	make -C ./pthread clean 

.PHONY: $(objs) $(clean_objs) clean
