# makefile socket 

objs = TCP UDP UNIXDomainSocketIPC Webserver
clean_objs=clean_TCP clean_UDP clean_UNIXDomainSocketIPC clean_Webserver

all: $(objs)
clean: $(clean_objs)

TCP:
	make -C $@
clean_TCP:	
	make -C ./TCP clean 
UDP:
	make -C $@
clean_UDP:	
	make -C ./UDP clean 
UNIXDomainSocketIPC:
	make -C $@
clean_UNIXDomainSocketIPC:	
	make -C ./UNIXDomainSocketIPC clean 
Webserver:
	make -C $@
clean_Webserver:	
	make -C ./Webserver clean 

.PHONY: $(objs) $(clean_objs) clean
