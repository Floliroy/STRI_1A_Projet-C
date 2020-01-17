#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../serveur/serveur.h"
#include "util.h"
#include "user.h"

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
	FILE* csv = fopen("util/mapUsers.csv", "r");
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

int isUserAdminWithNomPrenomInCsvFile(char* nomParam, char* prenomParam){
	printf("     Entrée dans : isUserAdminWithNomPrenomInCsvFile\n");
	
	//Ouverture du fichier en lecture
	FILE* csv = fopen("util/mapUsers.csv", "r");
	char nom[BUFSIZ], prenom[BUFSIZ], admin[BUFSIZ], champ[BUFSIZ];
	char ligne[BUFSIZ];

	//On lit ligne par ligne
	while(fgets(ligne, BUFSIZ, csv) != NULL){
		int cpt = 0;
		//On récupère le nom et le prenom qui sont les premieres valeurs stockées dans le csv
		recupereString(ligne, nom, &cpt, ',');
		recupereString(ligne, prenom, &cpt, ',');
		
		//On regarde si le nom et le prenom de l'utilisateur correspondent
		if(nom != NULL && prenom != NULL && strcmp(nom,nomParam) == 0 && strcmp(prenom,prenomParam) == 0){				
			//On récupère les autres champs
			for(int i=0 ; i<7 ; i++){
				recupereString(ligne, champ, &cpt, ',');
			}
			recupereString(ligne, admin, &cpt, '\n');
			
			//On renvoit la bonne valeur
			printf("     Sortie de : isUserAdminWithNomPrenomInCsvFile\n");
			if(admin != NULL && strcmp(admin, "1") != 0){
				return 1;
			}else{
				return 0;
			}
		}else{
			//Sinon on passe a la ligne suivante
			while(ligne[cpt] != '\n'){
				cpt++;
			}
		}		
	}
	//On ferme le fichier ouvert
	fclose(csv);

	return 0; //Retourne null si on ne trouve aucune correspondance
}