# makefile socket/Webserver 

src = Webserver.c Webclient.c
bin = Webserver Webclient 
save_path = ~/bin/linuxC/
CPPFLAGS = -g

all: $(bin) 

Webserver: Webserver.o
	gcc $^ -o $@ -g 
	cp $@ $(save_path)
Webclient: Webclient.o
	gcc $^ -o $@ -g 
	cp $@ $(save_path)
clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin) *.o
.PHONY: clean

