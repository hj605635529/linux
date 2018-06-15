ROOT_PATH=$(shell pwd)#处于httpd/sql目录下
 #头文件所在的目录
INCLUDE=$(ROOT_PATH)/lib/include
 #动态库所在的目录
LIB=$(ROOT_PATH)/lib/lib
 #链接的动态
LDFLAGS=-lmysqlclient

CC=g++

.PHONY:all
all:insert_cgi select_cgi

insert_cgi:insert_cgi.o sql.o
	@$(CC) -o $@ $^ -L$(LIB) $(LDFLAGS)

select_cgi:select_cgi.o sql.o
	@$(CC) -o $@ $^ -L$(LIB) $(LDFLAGS)

%.o:%.cpp
	@$(CC) -c $< -I$(INCLUDE)

.PHONY:clean
clean:
	@rm -f *.o insert_cgi select_cgi

debug:
	@echo $(INCLUDE)
	@echo $(LIB)
