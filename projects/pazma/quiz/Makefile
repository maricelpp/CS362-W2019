runtest: testme.exe
	./testme.exe

all: testme.exe

testme.exe: testme.o
	gcc -Wall -fprofile-arcs -ftest-coverage -std=c99 -o testme.exe testme.o

testme.o: testme.c
	gcc -Wall -fprofile-arcs -ftest-coverage -std=c99 -c testme.c

clean:
	rm testme.o testme.exe
