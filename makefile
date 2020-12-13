english_dictionary: dic.o
	gcc -o english_dictionary dic.o
dic.o: dic.c
	gcc -c dic.c
