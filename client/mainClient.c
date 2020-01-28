#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "client.h"
#include "../util/util.h"
#include "../util/user.h"

int monLire(char chaine[BUFSIZ]){    
	int taille;
    if(!fgets(chaine, BUFSIZ, stdin)){        
		return(-1);    
	}    
	
	//On enleve le stockage du retour à la ligne   
	taille = strlen(chaine);    
	chaine[taille - 1] = '\0';
    return taille;
}

void connexion(){
	hashMapStringString mapParameters = {.size = 0};
	char login[BUFSIZ], password[BUFSIZ];

	printf(RED "\nConnexion :\n" RESET);
	printf("Entrez votre login : ");
	monLire(login);
	printf("Entrez votre mot de passe : ");
	monLire(password);

	addToHashMapStringString(&mapParameters, "ACTION", "1");
	addToHashMapStringString(&mapParameters, "login", login);
	addToHashMapStringString(&mapParameters, "password", password);
	envoieRequeteFormatee(mapParameters);
}

void deconnexion(){
	hashMapStringString mapParameters= {.size = 0};

	printf(RED "\nDéconnexion !\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "2");
	envoieRequeteFormatee(mapParameters);
}

void ajouteUtilisateur(){
	hashMapStringString mapParameters = {.size = 0};
	char nom[BUFSIZ], prenom[BUFSIZ], mail[BUFSIZ], adressePostale[BUFSIZ], numTel[BUFSIZ], remarque[BUFSIZ], age[BUFSIZ], login[BUFSIZ], password[BUFSIZ];

	printf(RED "\nAjout d'un Utilisateur :\n" RESET);
	printf("Entrez son nom : ");
	monLire(nom);
	printf("Entrez son prénom : ");
	monLire(prenom);
	printf("Entrez son mail : ");
	monLire(mail);
	printf("Entrez son login : ");
	monLire(login);
	printf("Entrez son mot de passe : ");
	monLire(password);
	printf("Entrez son adresse (ou entrée) : ");
	monLire(adressePostale);
	printf("Entrez son numéro (ou entrée) : ");
	monLire(numTel);
	printf("Entrez une remarque (ou entrée) : ");
	monLire(remarque);
	printf("Entrez son age (ou entrée) : ");
	monLire(age);

	addToHashMapStringString(&mapParameters, "ACTION", "3");
	addToHashMapStringString(&mapParameters, "nom", nom);
	addToHashMapStringString(&mapParameters, "prenom", prenom);
	addToHashMapStringString(&mapParameters, "mail", mail);
	addToHashMapStringString(&mapParameters, "login", login);
	addToHashMapStringString(&mapParameters, "password", password);

	if(adressePostale != NULL && strlen(adressePostale) > 0){
		addToHashMapStringString(&mapParameters, "adressePostale", adressePostale);
	}
	if(numTel != NULL && strlen(numTel) > 0){
		addToHashMapStringString(&mapParameters, "numTel", numTel);
	}
	if(remarque != NULL && strlen(remarque) > 0){
		addToHashMapStringString(&mapParameters, "remarque", remarque);
	}
	if(age != NULL && strlen(age) > 0){
		addToHashMapStringString(&mapParameters, "age", age);
	}
	
	envoieRequeteFormatee(mapParameters);
}

void modifieUtilisateur(){
	hashMapStringString mapParameters = {.size = 0};
	char nom[BUFSIZ], prenom[BUFSIZ], mail[BUFSIZ], adressePostale[BUFSIZ], numTel[BUFSIZ], remarque[BUFSIZ], age[BUFSIZ], login[BUFSIZ], password[BUFSIZ];

	printf(RED "\nModification d'un Utilisateur :\n" RESET);
	printf("Entrez son nom : ");
	monLire(nom);
	printf("Entrez son prénom : ");
	monLire(prenom);
	printf("Entrez son nouveau mail (ou entrée) : ");
	monLire(mail);
	printf("Entrez son nouveau login (ou entrée) : ");
	monLire(login);
	printf("Entrez son nouveau mot de passe (ou entrée) : ");
	monLire(password);
	printf("Entrez son nouveau adresse (ou entrée) : ");
	monLire(adressePostale);
	printf("Entrez son nouveau numéro (ou entrée) : ");
	monLire(numTel);
	printf("Entrez une nouvelle remarque (ou entrée) : ");
	monLire(remarque);
	printf("Entrez son nouveau age (ou entrée) : ");
	monLire(age);

	addToHashMapStringString(&mapParameters, "ACTION", "4");
	addToHashMapStringString(&mapParameters, "nom", nom);
	addToHashMapStringString(&mapParameters, "prenom", prenom);

	if(mail != NULL && strlen(mail) > 0){
		addToHashMapStringString(&mapParameters, "mail", mail);
	}
	if(login != NULL && strlen(login) > 0){
		addToHashMapStringString(&mapParameters, "login", login);
	}
	if(password != NULL && strlen(password) > 0){
		addToHashMapStringString(&mapParameters, "password", password);
	}
	if(adressePostale != NULL && strlen(adressePostale) > 0){
		addToHashMapStringString(&mapParameters, "adressePostale", adressePostale);
	}
	if(numTel != NULL && strlen(numTel) > 0){
		addToHashMapStringString(&mapParameters, "numTel", numTel);
	}
	if(remarque != NULL && strlen(remarque) > 0){
		addToHashMapStringString(&mapParameters, "remarque", remarque);
	}
	if(age != NULL && strlen(age) > 0){
		addToHashMapStringString(&mapParameters, "age", age);
	}
	
	envoieRequeteFormatee(mapParameters);
}

void supprimeUtilisateur(){
	hashMapStringString mapParameters = {.size = 0};
	char nom[BUFSIZ], prenom[BUFSIZ];

	printf(RED "\nSuppression d'un Utilisateur :\n" RESET);
	printf("Entrez son nom : ");
	monLire(nom);
	printf("Entrez son prénom : ");
	monLire(prenom);

	addToHashMapStringString(&mapParameters, "ACTION", "5");
	addToHashMapStringString(&mapParameters, "nom", nom);
	addToHashMapStringString(&mapParameters, "prenom", prenom);
	
	envoieRequeteFormatee(mapParameters);
}

void aiguillage(int action){
	switch (action){
	case ACTION_CONNEXION:
		connexion();
		break;
	case ACTION_DECONNEXION:
		deconnexion();
		break;
	case ACTION_AJOUTE_UTILISATEUR:
		ajouteUtilisateur();
		break;
	case ACTION_MODIFIE_UTILISATEUR:
		modifieUtilisateur();
		break;
	case ACTION_SUPPRIME_UTILISATEUR:
		supprimeUtilisateur();
		break;
	}
}

int afficheMenu(int admin){
	int action;
	char stringAction[BUFSIZ];
	//On affiche le menu
	printf(RED "\nBienvenue sur le Client de Floliroy :\n" RESET);
	printf(BLU " 1. Se déconnecter\n" RESET);

	//On affiche certains l'element seulement si l'utilisateur est admin
	if(admin == 1){
		printf(BLU " 2. Ajouter un utilisateur\n" RESET);
		printf(BLU " 3. Modifier un utilisateur\n" RESET);
		printf(BLU " 4. Supprimer un utilisateur\n" RESET);
	}

	printf("\nEntrer le numéro de l'action souhaitée : ");
	//On récupère l'action souhaitée
	monLire(stringAction);
	action = atoi(stringAction);
	if((action > 1 && admin != 1) || action < 1 || action > 4){
		printf("\nERREUR : Action inconnue...\n");
		return -1;
	}

	//On renvoit l'action qui servira a l'aiguillage
	switch (action){
	case 1:
		return ACTION_DECONNEXION;
		break;
	case 2:
		return ACTION_AJOUTE_UTILISATEUR;
		break;
	case 3:
		return ACTION_MODIFIE_UTILISATEUR;
		break;
	case 4:
		return ACTION_SUPPRIME_UTILISATEUR;
		break;
	}

	return -1;
}

int main() {    
	char* message = (char*) malloc(sizeof(char));
	int retour;
	int admin = 0;
	int logged = 0;

	while(1){
		if(logged == 0){
			connexion();
		}else{
			retour = afficheMenu(admin);
			if(retour == ACTION_DECONNEXION){
				logged = 0;
				admin = 0;
			}
		}
		free(message);
		message = Reception();
		printf("J'ai recu : %s", message);
	}

	/*if(Emission("GET / HTTP/1.1\nHost: www.stri.ups-tlse.fr\n\n")!=1) {
		printf("Erreur d'Émission\n");
		return 1;
	}

	message = Reception();
	if(message == NULL){
		printf("Erreur de Réception\n");
		return 1;
	}       
	printf("Reception :\n\n");
	while(message!=NULL){
		printf("%s", message);
		free(message);
		message = Reception();
	}*/

    return 0;
}