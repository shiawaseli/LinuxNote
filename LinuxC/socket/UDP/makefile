# makefile socket/UDP 

src=server.c client.c wrap.c
bin=server client 
save_path=~/bin/linuxC/

all: $(bin) 

server: server.o wrap.o
	gcc $^ -o $@ 
	cp $@ $(save_path)
client: client.o wrap.o
	gcc $^ -o $@ 
	cp $@ $(save_path)
clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin) *.o
.PHONY: clean

