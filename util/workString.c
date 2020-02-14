#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "user.h"
#include "workString.h"

int monLire(char chaine[BUFSIZ]){
	int taille;
    if(!fgets(chaine, BUFSIZ, stdin)){        
		return(-1);    
	}    
	
	//On enleve le stockage du retour à la ligne   
	taille = strlen(chaine); 
	if(chaine[taille - 1] == '\n'){
		chaine[taille - 1] = '\0';
	}   
    return taille;
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

void demandeParam(char* nomParam, hashMapStringString* mapParameters, int appartenance, int nullable){
    char param[BUFSIZ];

    //On cherche le bon mot de liaison
    char* liaison;
    if(appartenance == 1){
        liaison = malloc(6 * sizeof(char));
        liaison = "votre";
    }else if(appartenance == 2){
        liaison = malloc(4 * sizeof(char));
        liaison = "une";
    }else if(appartenance == -1){
        liaison = malloc(4 * sizeof(char));
        liaison = "ses";
    }else{
        liaison = malloc(4 * sizeof(char));
        liaison = "son";
    }

    //On regarde si le paramètre est optionnel
    char* entree = "";
    if(nullable == 1){
        entree = malloc(13 * sizeof(char));
        entree = "(ou entrée) ";
    }

    //On demande a l'utilisateur de rentrer la valeur de son paramètre
    printf("Entrez %s %s %s: ", liaison, nomParam, entree);
	monLire(param);
    //On remplace les virgules par des espaces pour ne pas casser le csv du serveur
    for(int i=0 ; i<=strlen(param) ; i++){
        if(param[i] == ',' || param[i] == '=' || param[i] == '&')  {
            param[i] = ' ';
        }
    }

    //On ajoute le paramètre à la HashMap
    if(nullable == 1){
        if(param != NULL && strlen(param) > 0){
            addToHashMapStringString(mapParameters, nomParam, param);
        }
    }else{
	    addToHashMapStringString(mapParameters, nomParam, param);
    }
}