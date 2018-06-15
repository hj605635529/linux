.PHONY:all
all:my_daemon my_daemon2

my_daemon:my_daemon.c
	gcc -o my_daemon my_daemon.c

my_daemon2:my_daemon2.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f my_daemon
