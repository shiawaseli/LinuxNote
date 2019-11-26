# makefile my_sem

src=pth_mysem.c  sem_by_mutex.c
bin=my_sem
save_path=~/bin/linuxC/

$(bin): $(src)
	gcc $^ -o $@ -lpthread -g
	cp $@ $(save_path)
clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean

