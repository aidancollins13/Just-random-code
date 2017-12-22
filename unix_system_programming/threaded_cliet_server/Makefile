# Makefile
  
FLAGS = -std=c99 -O1 -Wall -Werror -g -D_POSIX_C_SOURCE=200809L -Wextra -pedantic -lpthread


all: server client

server: multi_server.c
	gcc ${FLAGS} -o server multi_server.c 

client: client.c
	gcc ${FLAGS} -o client client.c

clean:
	rm -f server client

