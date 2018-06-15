.PHONY:all
all:execl listparams

listparams:listparams.c
	gcc -o $@ $^
execl:execl.c
	gcc -o execl execl.c
.PHONY:clean
clean:
	rm -f execl
