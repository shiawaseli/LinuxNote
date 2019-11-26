#  makefile The_Dinning_Philosophers_Problem

src=phil_pro.c phil_pro_mutex.c
bin=phil_pro phil_pro_mutex 
save_path=~/bin/linuxC/

all: $(bin)

phil_pro_mutex: phil_pro_mutex.c
	gcc $^ -o $@ -lpthread -g 
	cp $@ $(save_path)
phil_pro: phil_pro.c
	gcc $^ -o $@ -lpthread -g
	cp $@ $(save_path)
clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean

