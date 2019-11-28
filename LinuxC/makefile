# makefile linuxC

objs=pthread socket 
clean_objs=clean_pthread clean_socket

all: $(objs)
clean: $(clean_objs)

pthread:
	make -C $@
clean_pthread:	
	make -C ./pthread clean 
socket:
	make -C $@
clean_socket:	
	make -C ./socket clean 

.PHONY: $(objs) $(clean_objs) clean
