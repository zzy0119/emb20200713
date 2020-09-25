LDFLAGS+=-lsqlite3

rgsServer:rgs_server.c
	gcc -o $@ $^ $(LDFLAGS)

loginServer:login_server.c
	gcc -o $@ $^ $(LDFLAGS)

clean:
	rm rgsServer


