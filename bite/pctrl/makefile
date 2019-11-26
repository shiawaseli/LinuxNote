# makefile process_control

src = pc_wait.c pc_err.c pc_exec.c mini_shell.c Myshell.c
bin = pc_wait pc_err pc_exec mini_shell Myshell
save_path = ~/bin/bite/

all: $(bin) 

Myshell: Myshell.c
	gcc $^ -o $@
	cp $@ $(save_path)
mini_shell: mini_shell.c
	gcc $^ -o $@
	cp $@ $(save_path)
pc_exec: pc_exec.c
	gcc $^ -o $@
	cp $@ $(save_path)
pc_wait: pc_wait.c
	gcc $^ -o $@
	cp $@ $(save_path)
pc_err: pc_err.c
	gcc $^ -o $@
	cp $@ $(save_path)

clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean
