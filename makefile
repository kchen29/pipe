all: pipe.o
	gcc pipe.o

pipe.o: pipe.c
	gcc -c pipe.c

clean:
	rm -f *o *~ a.out

run: all
	./a.out
