# Makefile
  
FLAGS = -std=c99 -O1 -Wall -Werror -g -D_POSIX_C_SOURCE=200809L -Wextra -pedantic


all: server client

server: server.c
	gcc ${FLAGS} -o server server.c 

client: client.c
	gcc ${FLAGS} -o client client.c

clean:
	rm -f server

