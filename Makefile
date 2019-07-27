all: aes

aes: aes_const.o aes_func.o aes_kexp_func.o aes_math.o aes_misc.o main.o
	gcc -o aes aes_const.o aes_func.o aes_kexp_func.o aes_math.o aes_misc.o main.o

aes_const.o: aes_const.c
	gcc -o aes_const.o -c aes_const.c -W -Wall -ansi -pedantic

aes_func.o: aes_func.c
	gcc -o aes_func.o -c aes_func.c -W -Wall -ansi -pedantic

aes_kexp_func.o: aes_kexp_func.c
	gcc -o aes_kexp_func.o -c aes_kexp_func.c -W -Wall -ansi -pedantic

aes_math.o: aes_math.c
	gcc -o aes_math.o -c aes_math.c -W -Wall -ansi -pedantic

aes_misc.o: aes_misc.c
	gcc -o aes_misc.o -c aes_misc.c -W -Wall -ansi -pedantic

main.o : main.c
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic

clean: rm -rf *.o

mrproper: clean
	rm -rf aes
