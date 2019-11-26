# makefile bite

objs=tools basicIO pctrl 
clean_objs=clean_tools clean_basicIO clean_pctrl 

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

.PHONY: $(objs) $(clean_objs) clean
