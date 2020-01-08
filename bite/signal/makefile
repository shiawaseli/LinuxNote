# makefile signal
src = loop.c signal.c signal2.c mask.c main.c test.c zombie.c
bin = loop signal signal2 mask main test zombie
save_path = ~/bin/bite/

all: $(bin) 

loop: loop.c
	gcc $^ -o $@
	cp $@ $(save_path)
signal: signal.c
	gcc $^ -o $@
	cp $@ $(save_path)
signal2: signal2.c
	gcc $^ -o $@
	cp $@ $(save_path)
mask: mask.c
	gcc $^ -o $@
	cp $@ $(save_path)
main: main.c
	gcc $^ -o $@
	cp $@ $(save_path)
test: test.c
	gcc $^ -o $@
	cp $@ $(save_path)
zombie: zombie.c
	gcc $^ -o $@
	cp $@ $(save_path)

clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean
