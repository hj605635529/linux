.PHONY:all
all:pthread_client pthread_server

pthread_client:pthread_client.c
	gcc -o $@ $^ -lpthread

pthread_server:pthread_server.c
	gcc -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -f pthread_client pthread_server

