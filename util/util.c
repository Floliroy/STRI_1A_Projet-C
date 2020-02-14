#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "user.h"
#include "workString.h"

void addToHashMapStringString(hashMapStringString* map, char* key, char* value){
	//Allocation dynamique de la clé et de la valeur
	char* newKey = malloc((strlen(key) + 1) * sizeof(char));
	char* newValue = malloc((strlen(value) + 1) * sizeof(char));
	strcpy(newKey, key);
	strcpy(newValue, value);

	//On stocke les valeurs dans la map
	map->elem[map->size].key = newKey;
	map->elem[map->size].value = newValue;

	//Incrémentation de la taille de la map 
	map->size = map->size + 1;
}

char* getFromHashMapStringString(hashMapStringString* map, char* key){
	for(int i=0 ; i<map->size ; i++){
		//On regarde si la clé correspond à la valeur passé en parametre
		if(map->elem[i].key != NULL && strcmp(map->elem[i].key,key) == 0){
			return map->elem[i].value;
		}
	}
	return NULL; //Retourne null si on ne trouve aucune correspondance
}

void addToHashMapUserString(hashMapUserString* map, utilisateur key, char* value){
	//Allocation dynamique des differents champs de l'utilisateur
	utilisateur* newKey = malloc(sizeof(key));
	char* newValue = malloc((strlen(value) + 1) * sizeof(char));
	newKey->nom = malloc((strlen(key.nom) + 1) * sizeof(char));
	strcpy(newKey->nom,key.nom);
	newKey->prenom = malloc((strlen(key.prenom) + 1) * sizeof(char));
	strcpy(newKey->prenom,key.prenom);
	newKey->mail = malloc((strlen(key.mail) + 1) * sizeof(char));
	strcpy(newKey->mail,key.mail);
	newKey->adressePostale = malloc((strlen(key.adressePostale) + 1) * sizeof(char));
	strcpy(newKey->adressePostale,key.adressePostale);
	newKey->numTel = malloc((strlen(key.numTel) + 1) * sizeof(char));
	strcpy(newKey->numTel,key.numTel);
	newKey->remarque = malloc((strlen(key.remarque) + 1) * sizeof(char));
	strcpy(newKey->remarque,key.remarque);
	newKey->age = key.age;
	strcpy(newValue, value);
	newKey->login = malloc((strlen(key.login) + 1) * sizeof(char));
	strcpy(newKey->login,key.login);
	newKey->password = malloc((strlen(key.password) + 1) * sizeof(char));
	strcpy(newKey->password,key.password);

	//On stocke les valeurs dans la map
	map->elem[map->size].key = newKey;
	map->elem[map->size].value = newValue;

	//Incrémentation de la taille de la map 
	map->size = map->size + 1;
}

char* getFromHashMapUserString(hashMapUserString* map, utilisateur* key){
	for(int i=0 ; i<map->size ; i++){
		//On regarde si la clé correspond à la valeur passé en parametre
		if(map->elem[i].key == key){
			return map->elem[i].value;
		}
	}
	return NULL; //Retourne null si on ne trouve aucune correspondance
}

void copieSaufLigne(FILE* fileBase, FILE* fileNew, int ligne){
	int cpt = 0, copie = 1;
	char c;

	//Tant qu'on est pas a la fin du fichier
	while((c = getc(fileBase)) != EOF){
		cpt++;
		//Si on arrive a la ligne de l'utilisateur a supprimer on arrete de copier jusqu'a ...
		if (cpt == ligne+1)
			copie = 0;

		if(copie == 1){
			putc(c, fileNew);
		}

		//... on arrete de copier jusqu'a avoir un retour a la ligne (marquant la fin des données de l'utilisateur)
		if(c == '\n')
			copie = 1;
	}
}