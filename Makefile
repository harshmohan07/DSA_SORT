sort: main.o file_functions.o sort_functions.o
	cc main.o file_functions.o sort_functions.o
main.o: main.c
	cc -c main.c
file_functions.o: file_functions.c file_functions.h
	cc -c file_functions.c
sort_functions.o: sort_functions.c sort_functions.h
	cc -c sort_functions.c
clean:
	rm *.o
cleantxt:
	rm *.txt
text:
	gcc -o test test.c
	./test
run:
	./a.out text.txt