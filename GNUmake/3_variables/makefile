# makefile 3_variables 

# 常数
CC := gcc
MKDIR := mkdir -p

# 内部变量
source = *.c
objects = $(subst .c,.o,$(source))

# 函数
maybe-make-dir = $(if $(wildcard $1),,$(MKDIR) $1)
assert-not-null = $(if $1,,$(error Illegal null value.))


# 当 include 了一个 makefile 文件后，make 会重新读取当前 makefile，之前未能创建的目标此时就可以创建了
# 这个简单的 makefile 引入了一个自动产生的文件
foo.mk: bar.mk 
	m4 --define=FILENAME=$@ bar.mk > $@
include foo.mk 
$(warning Finished include)

#.PHONY: dummy
#makefile: dummy
#	touch $@
# make 执行时会看到 makefile 尚未更新(.PHONY工作目标dummy尚未更新)，此时会执行 touch 命令，这样做会重新读进 makefile 的时间戳。
# make 将无限循环

# 使用 -include foo1.mk 忽略未找到 foo1.mk 的情况
-include foo1.mk
sinclude foo2.mk 
# 为了兼容其它版本的 make，GNU make 为 -inlcude 提供了别名 sinclude

LIBRARY = libio.a # LIBRARY 的值包含了一个跟在后面的空格
missing_file:
	touch $(LIBRARY) # 创建文件'libio.a'
	ls -l | grep '$(LIBRARY)' # 此时找不到文件'libio.a '

# 下面的设定可用来汇报尚未使用的磁盘空间
# DF = df 
# AWK = awk 
# free-space := $(DF) . | $(AWK) 'NR == 2 { print $$4 }'
# free: 
#	$(free-space)

#
# 赋值类型:
# 	=	创建递归变量，每次使用时都重新取值
# 	:= 	创建简单变量，处理到时立即进行赋值
# 	?= 	条件赋值，当变量的值不存在时才进行赋值
# 	+=	不加赋值，将新的值附加到原来的变量中
# 		对于简单变量相当于:
# 		simple := $(simple) new stuff
# 		但对于递归变量有特别的实现，使的不会出现无穷递归
#

#
# 变量: 赋值运算符定义的量
# 宏: 由 define 定义的量
#
define creater-jar
	@echo Creating $@...
	$(RM) $(TMP_JAR_DIR)
	$(MKDIR) $(TMP_JAR_DIR)
	$(CP) -r $^ $(TMP_JAR_DIR)
	cd $(TMP_JAR_DIR) && $(JAR) $(JARFLAGS) $@ .
	$(JAR) -ufm $@ $(MANIFEST)
	$(RM) $(TMP_JAR_DIR)
endef
# 执行命令脚本时，前置 @ 的命令不会被 make 输出，只输出执行的结果
# 用到命令行时，只影响本行命令
# 用到宏主体时，整个宏的命令都只输出结果
$(UI_JAR): $(UI_CLASSES)
	@$(create_jar)
# 输出:
# $ make 
# Creatint ui.jar...
#

# make 运行阶段:
# 	1、读取所有被引入的 makefile，将定义的变量和规则加载进 make 内部的数据库并建立依存图
# 	2、分析依存图并且判断需要更新的工作目标，接着执行相应的脚本
#
# makefile 中元素扩展的规则:
# 	1、对变量赋值，make 会在第一阶段立即扩展赋值运算符左边的部分
# 	2、= 和 ?= 右边部分会被延后到第二阶段使用的时候
#   3、:=的右边部分会立即扩展
#   4、+=左边如果是简单变量会立即进行扩展，否则会延后扩展
#   5、对宏定义，宏的变量名会立即进行扩展，主体会延后到使用时进行扩展
#   6、规则、工作目标和必要条件会立即扩展，命令的扩展会被延后
#
BIN := /usr/bin 
PRINTF := $(BIN)/printf 
DF := $(BIN)/df 
AWK := $(BIN)/awk 

define free-space 
	$(PRINTF) "Free disk space "
	$(DF) . | $(AWK) 'NR == 2 { print $$4 }'
endef 

OUTPUT_DIR := /tmp 
$(OUTPUT_DIR)/very_big_file:
	$(free-space) 
# 只有 := 和工作目标会在第一阶段进行扩展，所以只有使用 = 时，以上命令无论何时定义，make 的结果才会符合预期

# 使用赋值运算符，创建工作目标的专属变量(格式如下)
# target...: variable = value    { = := += ?= }
# 当有个别工作对象的某些选项有额外项时，可以建立其独有的临时新变量
gui.o: CPPFLAGS += -DUSE_NEW_MALLOC=1
gui.o: gui.h
	$(COMPLIE.c) $(OUTPUT_OPTION) $< # 可以删去

# 变量来源:
# 	1、文件中定义
# 		定义在 makefile 中或通过 include 引入指定文件的定义
# 	2、make 命令行上定义
# 		例:
# 			$ make CFLASS=-g CPPFLAGS='-DBSD -DDEBUG'
# 		命令行上变量的结果会覆盖环境变量和 makefile 中定义的变量(使用 override 要求采用 makefile 中的定义，特定情况下使用)
# 			override LDFLAGS = -EB
#	3、环境变量
#		优先度最低，使用(--environment-overrides/-e)命令行选项，使环境变量覆盖 makefile 
#		导出变量使用: export
#		避免环境变量被导出到子进程使用: unexport
#	4、自动创建
#		make 会在执行一个规则的命令脚本之前自动创建自动变量

# 设置可以轻易被用户修改的变量的方法: 
# 1、使用 ifndef 或 ifdef 条件指令
ifndef OUTPUT_DIR 
	# 假设输出目录为 $(PROJECT_DIR)/out 
	OUTPUT_DIR = $(PROJECT_DIR)/out
endif
# 2、使用 ?= 条件赋值运算符
OUTPUT_DIR ?= $(PROJECT_DIR)/out

# 条件指令
# 使用条件指令能够使需要的指令被执行而忽略不满足条件的指令
# ifdef : 如果定义了
# ifndef : 如果没定义
# ifeq : 如果相等
# ifneq : 如果不相等
# else : 条件未满足的情况
# endif : 条件指令的结束

# ifdef variable-name
# ifndef variable-name
# ifeq test
# ifneq test
# variable-name -> 不用 $() 括住 variable-name
# test -> 'a' 'b'  or  "a" "b"  or  (a,b)

# 例:
# COMSPEC 只会在Windows上被定义
ifdef COMPLIE 
	PATH_SEP := ;
	EXE_EXT := .exe 
else
	PATH_SEP := :
	EXE_EXT := 
endif 

ifeq (a, a)
	# equal
endif 
ifeq ( b, b )
	# 逗号之后的空格会被忽略
	# not equal --> ' b' != 'b '
endif 
ifeq "a" "a"
	# equal
endif 
ifeq 'b' 'b'
	# equal
endif 

# 注意变量扩展后可能会包含非预期的空格符号
# 使用 strip 函数来解决这种情况
ifeq "$(strip $(OPTIONS))" "-d"
	COMPILATION_FLAGS += -DDEBUG
endif 

