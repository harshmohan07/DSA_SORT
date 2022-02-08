s: main.o file_functions.o sort_functions.o
	cc main.o file_functions.o sort_functions.o
main.o: main.c
	cc -c main.c
file_functions.o: file_functions.c file_functions.h
	cc -c file_functions.c
sort_functions.o: sort_functions.c sort_functions.h
	cc -c sort_functions.c
c:
	rm *.o
ct:
	rm -f ./*.txt
t:
	gcc -o test test.c
	./test
r:
	./a.out text.txt