# makefile socket/UNIX Domain socket 

src = client.c server.c
bin = client server 
save_path = ~/bin/linuxC/
CPPFLAGS = -L. -lmyIPC

all: $(bin) 

server: libmyIPC.so server.c
	gcc -o $@ $^ 
	cp $@ $(save_path)
client: libmyIPC.so client.c
	gcc -o $@ $^
	cp $@ $(save_path)
libmyIPC.so: cli_conn.o serv_listen.o serv_accept.o serv_bind.o
	gcc -shared -o $@ $?
%.o: %.c
	gcc -fPIC -c $< -g
clean:
	cd $(save_path) && rm -f $(bin)
	rm -f *.o $(bin)
.PHONY: clean

