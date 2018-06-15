sem_=sem
cc=gcc

semSrc=main.c sem.c

$(sem_):$(semSrc)
	$(cc) -o $@ $^
.PHONY:clean
clean:
	rm -f $(sem_)
