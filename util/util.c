#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "../serveur/serveur.h"

void addToHashMapStringString(hashMapStringString* map, char* key, char* value){
	//Allocation dynamique de la clé et de la valeur
	char* newKey = malloc(strlen(key) * sizeof(char));
	char* newValue = malloc(strlen(value) * sizeof(char));
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
	char* newValue = malloc(strlen(value) * sizeof(char));
	newKey->nom = malloc(strlen(key.nom) * sizeof(char));
	strcpy(newKey->nom,key.nom);
	newKey->prenom = malloc(strlen(key.prenom) * sizeof(char));
	strcpy(newKey->prenom,key.prenom);
	newKey->mail = malloc(strlen(key.mail) * sizeof(char));
	strcpy(newKey->mail,key.mail);
	newKey->adressePostale = malloc(strlen(key.adressePostale) * sizeof(char));
	strcpy(newKey->adressePostale,key.adressePostale);
	newKey->numTel = malloc(strlen(key.numTel) * sizeof(char));
	strcpy(newKey->numTel,key.numTel);
	newKey->remarque = malloc(strlen(key.remarque) * sizeof(char));
	strcpy(newKey->remarque,key.remarque);
	newKey->age = key.age;
	strcpy(newValue, value);
	newKey->login = malloc(strlen(key.login) * sizeof(char));
	strcpy(newKey->login,key.login);
	newKey->password = malloc(strlen(key.password) * sizeof(char));
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

void recupereString(char ligne[BUFSIZ], char string[BUFSIZ], int* start, char delimiteur){
	int i = 0;
	int cpt = *start;

	//Tant qu'on a pas le caractere de fin
	while(ligne[cpt] != delimiteur){
		string[i] = ligne[cpt];
		cpt++;
		i++;
	}

	//On ferme notre string
	string[i] = '\0';
	cpt++;

	//On incremente pour passer au caractere après le delimiteur
	*start = cpt;
}

utilisateur* getUserWithNomPrenom(hashMapUserString* map, char* nom, char* prenom){
	printf("     Entrée dans : getUserWithNomPrenom\n");

	for(int i=0 ; i<map->size ; i++){
		//On regarde si le nom et le prenom de l'utilisateur correspondent
		if(map->elem[i].key->nom != NULL && map->elem[i].key->prenom != NULL && 
		strcmp(map->elem[i].key->nom,nom) == 0 && strcmp(map->elem[i].key->prenom,prenom) == 0){
			
			printf("     Sortie de : getUserWithNomPrenom\n");
			return map->elem[i].key;
		}
	}
	return NULL; //Retourne null si on ne trouve aucune correspondance
}

utilisateur* getUserWithLogin(hashMapUserString* map, char* login){
	printf("     Entrée dans : getUserWithLogin\n");

	for(int i=0 ; i<map->size ; i++){
		//On regarde si le login de l'utilisateur correspondent
		if(map->elem[i].key->login != NULL && strcmp(map->elem[i].key->login,login) == 0){
			
			printf("     Sortie de : getUserWithLogin\n");
			return map->elem[i].key;
		}
	}
	return NULL; //Retourne null si on ne trouve aucune correspondance
}

int getUserLineWithNomPrenom(char* nomParam, char* prenomParam){
	printf("     Entrée dans : getUserLineWithNomPrenom\n");
	
	//Ouverture du fichier en lecture
	FILE* csv = fopen("mapUsers.csv", "r");
	char nom[BUFSIZ], prenom[BUFSIZ];
	char ligne[BUFSIZ];
	int retour = 0;

	//On lit ligne par ligne
	while(fgets(ligne, BUFSIZ, csv) != NULL){
		int cpt = 0;
		//On récupère le nom et le prenom qui sont les premieres valeurs stockées dans le csv
		recupereString(ligne, nom, &cpt, ',');
		recupereString(ligne, prenom, &cpt, ',');
		while(ligne[cpt] != '\n'){
			cpt++;
		}
		
		//On regarde si le nom et le prenom de l'utilisateur correspondent
		if(nom != NULL && prenom != NULL && strcmp(nom,nomParam) == 0 && strcmp(prenom,prenomParam) == 0){				
			fclose(csv);
			
			printf("     Sortie de : getUserLineWithNomPrenom\n");
			return retour;
		}
		//On récupère la position du curseur a la fin de la ligne pour avoir le début de la ligne suivante
		retour = ftell(csv);
	}

	//On ferme le fichier ouvert
	fclose(csv);

	return -1; //Retourne -1 si on ne trouve aucune correspondance
}

int isUserAdmin(hashMapUserString mapUtilisateurs, utilisateur* user){
	//Dans mapUtilisateurs la 'value' correspond a si l'utilisateur est admin
	if(strcmp(getFromHashMapUserString(&mapUtilisateurs, user),"1") != 0){
		return 0;
	}else{
		return 1;
	}
}

int isMotDePasseValide(hashMapUserString mapUtilisateurs, char* login, char* password){
	//On cherche l'utilisateur par son login
	utilisateur* user = getUserWithLogin(&mapUtilisateurs, login);

	//Si l'utilisateur existe on regarde si le mot de passe correspond
	if(user != NULL && strcmp(password, user->password) == 0){
		return 1;
	}else{
		return 0;
	}
}