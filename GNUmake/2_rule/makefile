# makefile 2_rule 

VPATH = src include
CPPFLAGS = -I include
save_path = ~/bin/GNUmake/

SOURCES = count_words.c \
		  lexer.c 		\
		  counter.c

count_words: count_words.o libcounter.a 
	gcc $^ -lfl -o $@
	cp $@ $(save_path)
count_words.o: counter.h
counter.o: counter.h lexer.h
lexer.o: lexer.h


# 使用一种更精致 $< 的方式更新静态库中函数，为每一个更新项创建一个子进程
# 旧版的 ar 不会更新新成员的索引，需要使用 ranlib 手动更新
libcounter.a: libcounter.a(lexer.o) libcounter.a(counter.o)
	$(RANLIB) $@
libcounter.a(lexer.o): lexer.o
	$(AR) $(ARFLAGS) $@ $<
libcounter.a(counter.o): counter.o
	$(AR) $(ARFLAGS) $@ $<
# $? 能够只更新必要条件中更新的项，但当修改的项超过十个时，-r 替换的速度可能不如重新创建新的静态库快
# ARFLAGS 默认为 rv
#
# libcounter.a: counter.o lexer.o
# $(AR) $(ARFLAGS) $@ $?
#

# 对于大型的静态库:
# libcounter.a: counter.o lexer.o
# 	$(RM) $@
# 	$(AR) $(ARFLAGS) $@ $^
# 	$(RANLIB) $@

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
