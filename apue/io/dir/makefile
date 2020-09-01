LDFLAGS+=-lcrypt
CFLAGS+=-D_GNU_SOURCE

# 目标:依赖文件
crypt:crypt_pwd.c
	gcc -o $@ $^ $(LDFLAGS) $(CFLAGS)
# 伪目标
test:
	echo "are you ready?"

clean:
	rm crypt
