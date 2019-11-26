# makefile 1_easymakefile 

save_path=~/bin/GNUmake/

count_words_1: count_words_1.o lexer_1.o 
	gcc -o $@ $^ -lfl
	cp $@ $(save_path)
count_words_1.o: count_words_1.c
	gcc -c $<
lexer_1.o: lexer_1.c
	gcc -c $<
lexer_1.c: lexer_1.l
	flex -t $< > $@

clean:
	cd $(save_path) && rm -f count_words_1 
	rm -f *.o lexer_1.c count_words_1 
.PHONY: clean
