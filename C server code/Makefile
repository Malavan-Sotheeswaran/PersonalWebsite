PORT = 57769
CC = gcc
CFLAGS =  -DPORT=${PORT} -g -Wall -std=gnu99

all: server

server: server.o response.o request.o socket.o
	${CC} ${CFLAGS} -o $@ $^


.c.o: response.h request.h socket.h
	${CC} ${CFLAGS}  -c $<

clean:
	rm *.o server
