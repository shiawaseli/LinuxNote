# makefile GNUmake 

objs=1 2 3
clean_objs=clean_1 clean_2 clean_3

all: $(objs)
clean: $(clean_objs)

1:
	make -C 1_easymakefile 
clean_1:
	make -C ./1_easymakefile clean
2:
	make -C 2_rule 
clean_2:
	make -C ./2_rule  clean
3:
	make -C 3_variables  
clean_3:
	make -C ./3_variables clean

.PHONY: $(objs) $(clean_objs) clean
