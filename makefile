# makefile workdir

objs=bite linuxC GNUmake 
clean_objs=clean_bite clean_linuxC clean_GNUmake 	

all: $(objs)
clean: $(clean_objs)

bite:
	make -C $@
clean_bite:
	make -C ./bite clean 

linuxC:
	make -C $@
clean_linuxC:
	make -C ./linuxC clean 

GNUmake:
	make -C $@
clean_GNUmake:
	make -C ./GNUmake clean 

.PHONY: $(objs) $(clean_objs) clean 
