mainServeur: mainServeur.o serveur.o util.o user.o workString.o
	gcc -o mainServeur mainServeur.o serveur.o util.o user.o workString.o; rm -f *.o core

mainServeur.o: serveur/mainServeur.c
	gcc -o mainServeur.o -c serveur/mainServeur.c -Wall -O

serveur.o: serveur/serveur.c
	gcc -o serveur.o -c serveur/serveur.c -Wall -O


mainClient: mainClient.o client.o util.o user.o workString.o
	gcc -o mainClient mainClient.o client.o util.o user.o workString.o; rm -f *.o core

mainClient.o: client/mainClient.c
	gcc -o mainClient.o -c client/mainClient.c -Wall -O

client.o: client/client.c
	gcc -o client.o -c client/client.c -Wall -O


util.o: util/util.c
	gcc -o util.o -c util/util.c -Wall -O

user.o: util/user.c
	gcc -o user.o -c util/user.c -Wall -O

workString.o: util/workString.c
	gcc -o workString.o -c util/workString.c -Wall -O


clean:
	rm -f *.o core