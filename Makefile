all: map1 map2

map2: map2.o list.o bst.o
	gcc -Wall -o map2 map2.o list.o bst.o -g -lm
    
map1: map1.o list.o bst.o
	gcc -Wall -o map1 map1.o list.o bst.o -g -lm
    
    
    
map1.o: map1.c list.h bst.h
	gcc -Wall -c -o map1.o map1.c -g -lm

map2.o: map2.c list.h bst.h
	gcc -Wall -c -o map2.o map2.c -g -lm
    
    
    
list.o: list.c list.h
	gcc -Wall -c -o list.o list.c -g -lm
    
bst.o: bst.c list.h bst.h 
	gcc -Wall -c -o bst.o bst.c -g -lm
    
clean: 
	rm -f *.o map1 map2 