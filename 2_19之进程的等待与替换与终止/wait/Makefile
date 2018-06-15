.PHONY:all
all:waitmany waitofWNOHANG wait1

waitmany:waitmany.c
	gcc -o $@ $^

waitofWNOHANG:waitofWNOHANG.c
	gcc -o $@ $^

wait1:wait1.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f wait1
