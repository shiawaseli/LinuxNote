# makefile socket
src = servUDP.c cliUDP.cpp
bin = servUDP cliUDP 
save_path = ~/bin/bite/

all: $(bin) 

servUDP: servUDP.c
	gcc $^ -o $@
	cp $@ $(save_path)
cliUDP: cliUDP.cpp
	g++ $^ -o $@ -std=c++11
	cp $@ $(save_path)

clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean
