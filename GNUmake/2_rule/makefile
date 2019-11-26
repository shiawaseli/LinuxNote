# makefile 2_rule 

VPATH = src include
CPPFLAGS = -I include
save_path = ~/bin/GNUmake/

SOURCES = count_words.c \
		  lexer.c 		\
		  counter.c

count_words: count_words.o counter.o lexer.o
	gcc $^ -lfl -o $@
	cp $@ $(save_path)
count_words.o: counter.h
counter.o: counter.h lexer.h
lexer.o: lexer.h

# 自动生成依赖关系方法2
-include $(subst .c,.d,$(SOURCES))

%.d: %.c
	$(CC) -M $(CPPFLAGS) $< > $@.$$$$;			\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;		\
	rm -f $@.$$$$
# 方法2利用了模式规则更方便的解决依赖关系问题

# 自动生成依赖关系方法1
depend: count_words.c lexer.c counter.c
	$(CC) -M $(CPPFLAGS) $^ > $@
# 然后使用 
# include depend
# 导入生成的依赖

clean:
	cd $(save_path) && rm -f count_words 
	rm -f *.o *.d lexer.c count_words  
.PHONY: clean help 
