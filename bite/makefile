# makefile bite

objs=tools basicIO pctrl ipc signal pthread 
clean_objs=clean_tools clean_basicIO clean_pctrl clean_ipc clean_signal clean_pthread

all: $(objs)
clean: $(clean_objs) 

tools:
	make -C $@
clean_tools:
	make -C ./tools clean 

basicIO:
	make -C $@
clean_basicIO:
	make -C ./basicIO clean 

pctrl:
	make -C $@
clean_pctrl:
	make -C ./pctrl clean 

ipc:
	make -C $@
clean_ipc:
	make -C ./ipc clean 

signal:
	make -C $@
clean_signal:
	make -C ./signal clean 

pthread:
	make -C $@
clean_pthread:
	make -C ./pthread clean 
	``
.PHONY: $(objs) $(clean_objs) clean
