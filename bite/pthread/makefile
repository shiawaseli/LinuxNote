# makefile thread

src = create.c
bin = create 
save_path = ~/bin/bite/
CPPFLAGS += -lpthread # or -pthread

all: $(bin) 

create: create.c
	gcc $(CPPFLAGS) -o $@ $^
	cp $@ $(save_path)

clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean
