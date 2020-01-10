# makefile thread

src = create.c tout.c cond.c pro_con.cpp con_pro.cpp 
bin = create tout cond pro_con con_pro 
save_path = ~/bin/bite/
CPPFLAGS += -lpthread # or -pthread

all: $(bin) 

create: create.c
	gcc $(CPPFLAGS) -o $@ $^
	cp $@ $(save_path)
tout: tout.c
	gcc $(CPPFLAGS) -o $@ $^
	cp $@ $(save_path)
cond: cond.c
	gcc $(CPPFLAGS) -o $@ $^
	cp $@ $(save_path)
pro_con: pro_con.cpp
	g++ $(CPPFLAGS) -o $@ $^
	cp $@ $(save_path)
con_pro: con_pro.cpp
	g++ $(CPPFLAGS) -o $@ $^
	cp $@ $(save_path)

clean:
	cd $(save_path) && rm -f $(bin)
	rm -f $(bin)
.PHONY: clean
