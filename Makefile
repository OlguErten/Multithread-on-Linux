CFLAGs=-w -g

all:
	gcc -w -g main.c linkedlist.c -lpthread -o multithread.a

clean:
	rm -f multithread.a