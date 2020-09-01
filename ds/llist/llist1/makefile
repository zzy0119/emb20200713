# LDFLAGS 指定链接动态库-l
# CFLAGS 指定头文件路径-I 宏-D

# 目标:依赖文件
llist:llist.o main.o
	# 规则
	gcc -o $@ $^

#llist.o:llist.c
#	gcc -c -o $@ $^

#main.o:main.c
#	gcc -c -o $@ $^


# 伪目标
clean:
	@rm llist llist.o main.o

