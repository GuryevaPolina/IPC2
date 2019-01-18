CCH=gcc 
CFLAGS=-Wall -Werror 
LIBS=-lpthread
HOST=host.c
CLIENT=client.c 
EXECHOST=$(ALL_TARGETS:./conn_%.c=host_%)
EXECCLIENT=$(ALL_TARGETS:./conn_%.c=client_%)

ALL_TARGETS=$(shell find . -name "conn_*.c")

all: $(EXECHOST) $(EXECCLIENT)
	
host_%: conn_%.o $(HOST:.c=.o)
	$(CC) -o $@ $^ $(LIBS)

client_%: conn_%.o $(CLIENT:.c=.o)
	$(CC) -o $@ $^ $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean

clean:
	rm -rf `find . -maxdepth 1 -executable -type f`
