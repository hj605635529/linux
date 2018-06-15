.PHONY:all
all:serv clie

serv:serv.c
	gcc -o $@ $^
clie:clie.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f serv clie
