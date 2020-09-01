LDFLAGS+=-lcrypt

# 目标:依赖文件
crypt:crypt_pwd.c
	gcc -o $@ $^ $(LDFLAGS)
# 伪目标
test:
	echo "are you ready?"
