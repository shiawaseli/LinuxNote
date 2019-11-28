# makefile socket 

src=server.c client.c
bin=server client 
save_path=~/bin/linuxC/

all: $(bin) 

server: server.c
	gcc $^ -o $@ -lpthread 
	cp $@ $(save_path)
client: client.c
	gcc $^ -o $@ -lpthread 
	cp $@ $(save_path)
clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean

