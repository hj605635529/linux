.PHONY:all
all:fork_server fork_client

fork_server:fork_server.c
	gcc -o $@ $^
fork_client:fork_client.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f fork_server fork_client
