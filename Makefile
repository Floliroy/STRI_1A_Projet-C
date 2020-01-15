mainServeur: mainServeur.o serveur.o util.o
	gcc -o mainServeur mainServeur.o serveur.o util.o; rm -f *.o core

mainServeur.o: serveur/mainServeur.c
	gcc -o mainServeur.o -c serveur/mainServeur.c -Wall -O

serveur.o: serveur/serveur.c
	gcc -o serveur.o -c serveur/serveur.c -Wall -O

util.o: util/util.c
	gcc -o util.o -c util/util.c -Wall -O

clean:
	rm -f *.o core

mrproper: clean
	rm -f mainServeur