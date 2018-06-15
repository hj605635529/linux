.PHONY:all
all:client server

client:client.c
	gcc -o $@ $^
#gcc -0 client client.c

server:server.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -f client server fifo有名管道
