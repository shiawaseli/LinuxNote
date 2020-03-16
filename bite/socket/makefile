# makefile socket
src = servUDP.cpp cliUDP.cpp servTCP.cpp cliTCP.cpp processServTCP.cpp threadServTCP.cpp 
bin = servUDP cliUDP servTCP cliTCP processServTCP threadServTCP 
save_path = ~/bin/bite/

all: $(bin) 

threadServTCP: threadServTCP.cpp 
	g++ $^ -o $@ -std=c++11 -pthread
	cp $@ $(save_path)
processServTCP: processServTCP.cpp 
	g++ $^ -o $@ -std=c++11
	cp $@ $(save_path)
servTCP: servTCP.cpp 
	g++ $^ -o $@ -std=c++11
	cp $@ $(save_path)
cliTCP: cliTCP.cpp
	g++ $^ -o $@ -std=c++11
	cp $@ $(save_path)
servUDP: servUDP.cpp 
	g++ $^ -o $@ -std=c++11
	cp $@ $(save_path)
cliUDP: cliUDP.cpp
	g++ $^ -o $@ -std=c++11
	cp $@ $(save_path)
#不再使用C版的UDP服务器
#servUDP: servUDP.c
#	gcc $^ -o $@
#	cp $@ $(save_path)

clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean
