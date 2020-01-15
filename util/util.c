#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "../serveur/serveur.h"

//fonction pour ajouter à la hash map une valeur et sa clé
void addToHashMapStringString(hashMapStringString* map, char* key, char* value){
	//allocation dynamique de la clé et de la valeur
	char* newKey = malloc(strlen(key) * sizeof(char));
	char* newValue = malloc(strlen(value) * sizeof(char));
	
	//strcpy copie la chaîne pointée par key dans la chaîne pointée par newKey pour que la chaine passé en parametre puisse etre modifié par la suite
	strcpy(newKey, key);
	strcpy(newValue, value);

	map->elem[map->size].key = newKey;
	map->elem[map->size].value = newValue;

	//incrémentation de la taille de la Hash map aprés ajout de la valeur 
	map->size = map->size + 1;
}

//fonction pour obtenir une valeur de la HashMap à partir de sa clé
char* getFromHashMapStringString(hashMapStringString* map, char* key){
	for(int i=0 ; i<map->size ; i++){
		//strcmp va comparer les clés de la map avec la clé passé en paramètre
		if(map->elem[i].key != NULL && strcmp(map->elem[i].key,key) == 0){
			return map->elem[i].value;
		}
	}
	return NULL; //retourne null si on ne trouve aucune correspondance
}

/* ajoute un utilisateur à la HashMap des utilisateurs du serveur. 
 * Cette fonction consiste à faire des allocation dynamiques pour les différents 
 * pour que l'utilisateur passé en parametre puisse être modifié par la suite */
void addToHashMapUserString(hashMapUserString* map, utilisateur key, char* value){
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

	map->elem[map->size].key = newKey;
	map->elem[map->size].value = newValue;
	map->size = map->size + 1;
	
}

//fonction pour obtenir de la HashMap la valeur du string associé à un utilisateur (pour le moment ce string correspond a si il est admin ou non) 
char* getFromHashMapUserString(hashMapUserString* map, utilisateur* key){
	for(int i=0 ; i<map->size ; i++){
		if(map->elem[i].key == key){
			return map->elem[i].value;
		}
	}
	return NULL;
}

//cette fonction permet de parcourir un string en d'en extraire en sous string entre l'indice de départ et un delimiteur
void recupereString(char ligne[BUFSIZ], char string[BUFSIZ], int* start, char delimiteur){
	int i = 0;
	int cpt = *start;
	while(ligne[cpt] != delimiteur){
		string[i] = ligne[cpt];
		cpt++;
		i++;
	}
	string[i] = '\0';
	cpt++;
	*start = cpt;
}

//fonction qui cherche un utilisateur par son nom et son prenom
utilisateur* getUserWithNomPrenom(hashMapUserString* map, char* nom, char* prenom){
	printf("     Entrée dans : getUserWithNomPrenom\n");

	for(int i=0 ; i<map->size ; i++){
		if(map->elem[i].key->nom != NULL && map->elem[i].key->prenom != NULL && 
		strcmp(map->elem[i].key->nom,nom) == 0 && strcmp(map->elem[i].key->prenom,prenom) == 0){
			
			printf("     Sortie de : getUserWithNomPrenom\n");
			return map->elem[i].key;
		}
	}
	return NULL;
}

//fonction qui cherche un utilisateur par son login
utilisateur* getUserWithLogin(hashMapUserString* map, char* login){
	printf("     Entrée dans : getUserWithLogin\n");

	for(int i=0 ; i<map->size ; i++){
		if(map->elem[i].key->login != NULL && strcmp(map->elem[i].key->login,login) == 0){
			
			printf("     Sortie de : getUserWithLogin\n");
			return map->elem[i].key;
		}
	}
	return NULL;
}

//retourne la position du curseur pour être au debut de la ligne de l'utilisateur recherché dans le fichier csv
int getUserLineWithNomPrenom(char* nomParam, char* prenomParam){
	printf("     Entrée dans : getUserLineWithNomPrenom\n");
	
	//ouverture du fichier en lecture
	FILE* csv = fopen("mapUsers.csv", "r");
	char nom[BUFSIZ], prenom[BUFSIZ];
	char ligne[BUFSIZ];
	int retour = 0;
	while(fgets(ligne, BUFSIZ, csv) != NULL){
		int cpt = 0;
		recupereString(ligne, nom, &cpt, ',');
		recupereString(ligne, prenom, &cpt, ',');
		while(ligne[cpt] != '\n'){
			cpt++;
		}
		if(nom != NULL && prenom != NULL && strcmp(nom,nomParam) == 0 && strcmp(prenom,prenomParam) == 0){				
			fclose(csv);
			
			printf("     Sortie de : getUserLineWithNomPrenom\n");
			return retour;
		}
		//la fonction ftell permet de connaitre la position du pointeur de fichier csv
		retour = ftell(csv);
	}

	fclose(csv);
	return -1;
}

//fonction pour savoir si l'utilisateur est administrateur
int isUserAdmin(hashMapUserString mapUtilisateurs, utilisateur* user){
	if(strcmp(getFromHashMapUserString(&mapUtilisateurs, user),"1") != 0){
		return 0;
	}else{
		return 1;
	}
}

/* fonction pour savoir si le mot de passe est valide. En faisant appel à la fonction getUserWithLogin
 * strcmp compare le mot de passe passé en paramètre avec le mot de passe de l'utilisateur. */
int isMotDePasseValide(hashMapUserString mapUtilisateurs, char* login, char* password){
	utilisateur* user = getUserWithLogin(&mapUtilisateurs, login);
	if(user != NULL && strcmp(password, user->password) == 0){
		return 1;
	}else{
		return 0;
	}
}