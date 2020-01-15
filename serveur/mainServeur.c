#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"
#include "../util/util.h"

hashMapUserString mapUtilisateurs; //creation de mapUtilisateur de type hashMapUserString en tant que variable globale

//ajout d'un utilisateur en utilisant les informations de la requête 
int ajouteUtilisateur(hashMapStringString mapParameters, char* admin){
	printf("     Entrée dans : ajouteUtilisateur\n");
	char *nom, *prenom, *mail, *adressePostale, *numTel, *remarque, *age, *login, *password;

	utilisateur newUtilisateur;
	
	//si les informations obligatoires (nom, prenom, adresse mail, login, password) sont à NULL la fonction affiche un message d'erreur
	if((nom = getFromHashMapStringString(&mapParameters, "nom")) == NULL ||
	(prenom = getFromHashMapStringString(&mapParameters, "prenom")) == NULL ||
	(mail = getFromHashMapStringString(&mapParameters, "mail")) == NULL ||
	(login = getFromHashMapStringString(&mapParameters, "login")) == NULL ||
	(password = getFromHashMapStringString(&mapParameters, "password")) == NULL){
		printf("Erreur, données manquantes pour ajouter un nouvel utilisateur.\n");
		return 0;
	}else{
		newUtilisateur.nom = nom;
		newUtilisateur.prenom = prenom;
		newUtilisateur.mail = mail;
		newUtilisateur.login = login;
		newUtilisateur.password = password;
	}
	//cérifications et affichage des messages d'erreur
	//si la fonction trouve le nom et prenom ou le login de l'utilisateur dans la hashMap, un message est retourné pour indiquer que l'utilisateur existe déja
	utilisateur* user = getUserWithNomPrenom(&mapUtilisateurs, nom, prenom);
	if(user != NULL){
		printf("Erreur, cet utilisateur existe deja.\n");
		return 0;
	}
	user = getUserWithLogin(&mapUtilisateurs, login);
	if(user != NULL){
		printf("Erreur, cet utilisateur existe deja.\n");
		return 0;
	}
	
	//si il n'y a pas le champ recherché, mettre un espace à la place
	if((adressePostale = getFromHashMapStringString(&mapParameters, "adressePostale")) == NULL){
		adressePostale = " ";
	}
	newUtilisateur.adressePostale = adressePostale;
	if((numTel = getFromHashMapStringString(&mapParameters, "numTel")) == NULL){
		numTel = " ";
	}
	newUtilisateur.numTel = numTel;
	if((remarque = getFromHashMapStringString(&mapParameters, "remarque")) == NULL){
		remarque = " ";
	}
	newUtilisateur.remarque = remarque;
	//si il n'y a pas l'age de l'utilisateur le mettre à -1 par default
	if((age = getFromHashMapStringString(&mapParameters, "age")) == NULL){
		age = "-1";
	}
	newUtilisateur.age = atoi(age); //convertir une chaine de caractère en int

	addToHashMapUserString(&mapUtilisateurs, newUtilisateur, "0");

	FILE* csv;
	if(strcmp(admin,"1") == 0){
		csv = fopen("mapUsers.csv", "w"); //création du fichier csv en écriture seule (si on crée un admin le fichier n'existe pas)
	}else{
		csv = fopen("mapUsers.csv", "r+"); //ouverture du fichier en lecture et ecriture sans écraser le fichier
	}
	fseek(csv, 0, SEEK_END); //on va a la fin du fichier
	fprintf(csv, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", nom, prenom, mail, adressePostale, numTel, remarque, age, login, password, admin);
	fclose(csv); //fermeture du fichier 

	printf(YEL "Utilisateur %s %s ajouté.\n" RESET, nom, prenom);
	printf("     Sortie de : ajouteUtilisateur\n");
	return 1;
}

//fonction permettant de modifier les informations d'un utilisateur
int modifieUtilisateur(hashMapStringString mapParameters){
	printf("     Entrée dans : modifieUtilisateur\n");
	char *nom, *prenom, *mail, *adressePostale, *numTel, *remarque, *age, *admin, *login, *password;
	
	//si le nom et prenom de l'utilisateur manquent, alors des modifications ne peuvent pas être apportées
	if((nom = getFromHashMapStringString(&mapParameters, "nom")) == NULL ||
	(prenom = getFromHashMapStringString(&mapParameters, "prenom")) == NULL){
		printf("Erreur, données manquantes pour modifier un utilisateur.\n");
		return 0;
	}
	//vérifie que l'utilisateur existe bien avant toute modification
	utilisateur* user = getUserWithNomPrenom(&mapUtilisateurs ,nom, prenom);
	if(user == NULL){
		printf("Erreur, utilisateur introuvable.\n");
		return 0;
	}
	admin = getFromHashMapUserString(&mapUtilisateurs, user);
	//modification des informations du contact
	if((mail = getFromHashMapStringString(&mapParameters, "mail")) != NULL){
		user->mail = mail;
	}else{
		mail = user->mail;
	}
	if((adressePostale = getFromHashMapStringString(&mapParameters, "adressePostale")) != NULL){
		user->adressePostale = adressePostale;
	}else{
		adressePostale = user->adressePostale;
	}
	if((numTel = getFromHashMapStringString(&mapParameters, "numTel")) != NULL){
		user->numTel = numTel;
	}else{
		numTel = user->numTel;
	}
	if((remarque = getFromHashMapStringString(&mapParameters, "remarque")) != NULL){
		user->remarque = remarque;
	}else{
		remarque = user->remarque;
	}
	if((age = getFromHashMapStringString(&mapParameters, "age")) != NULL){
		user->age = atoi(age);
	}else{
		sprintf(age,"%d",user->age);
	}
	if((login = getFromHashMapStringString(&mapParameters, "login")) != NULL){
		user->login = login;
	}else{
		login = user->login;
	}
	if((password = getFromHashMapStringString(&mapParameters, "password")) != NULL){
		user->password = password;
	}else{
		password = user->password;
	}

	int pos = getUserLineWithNomPrenom(nom, prenom);
	int cpt = 0, copie = 1;

	FILE* csv = fopen("mapUsers.csv", "r");
    	FILE* temp = fopen("temp.csv", "w"); //si on veut modifier une ligne au milieu du fichier, on réécrit le fichier entier dans un autre fichier temporaire
	char c;

	while((c = getc(csv)) != EOF){
	cpt++;
	if (cpt == pos+1)
		copie = 0;

	if(copie == 1){
		putc(c, temp);
	}else if(copie == 0){
		fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", nom, prenom, mail, adressePostale, numTel, remarque, age, login, password, admin);
		copie = -1;
	}

	if(c == '\n')
		copie = 1;
	}
	//fermeture des fichiers ouverts
	fclose(csv);
	fclose(temp);
	remove("mapUsers.csv");
	rename("temp.csv", "mapUsers.csv");

	printf(YEL "Utilisateur %s %s modifié.\n" RESET, nom, prenom);
	printf("     Sortie de : modifieUtilisateur\n");
	return 1;
}

//fonction permettant de supprimer un utilisateur
int supprimeUtilisateur(hashMapStringString mapParameters){
	printf("     Entrée dans : supprimeUtilisateur\n");
	char *nom, *prenom;

	if((nom = getFromHashMapStringString(&mapParameters, "nom")) == NULL ||
	(prenom = getFromHashMapStringString(&mapParameters, "prenom")) == NULL){
		printf("Erreur, données manquantes pour supprimer un utilisateur.\n");
		return 0;
	}
	
	utilisateur* user = getUserWithNomPrenom(&mapUtilisateurs, nom, prenom);
	user->nom = NULL;
	user->prenom = NULL;
	user->mail = NULL;
	user->adressePostale = NULL;
	user->numTel = NULL;
	user->remarque = NULL;
	user->age = -1;
	user->login = NULL;
	user->password = NULL;

	int pos = getUserLineWithNomPrenom(nom, prenom);
	int cpt = 0, copie = 1;

	FILE* csv = fopen("mapUsers.csv", "r");
    	FILE* temp = fopen("temp.csv", "w");
	char c;

	while((c = getc(csv)) != EOF){
	cpt++;
	if (cpt == pos+1)
		copie = 0;

	if(copie == 1){
		putc(c, temp);
	}

	if(c == '\n')
		copie = 1;
	}
	fclose(csv);
	fclose(temp);
	remove("mapUsers.csv");
	rename("temp.csv", "mapUsers.csv");

	printf(YEL "Utilisateur %s %s supprimé.\n" RESET, nom, prenom);
	printf("     Sortie de : supprimeUtilisateur\n");
	return 1;
}

//fonction pointant vers une fonction à laquelle l'utiisateur souhaite accéder
int aiguillageServeur(hashMapStringString mapParameters, utilisateur* userLogged){
	printf("     Entrée dans : aiguillageServeur\n");

	char* action;
	printf(BLU "ACTION = %s\n" RESET, getFromHashMapStringString(&mapParameters, "ACTION"));
	if((action = getFromHashMapStringString(&mapParameters, "ACTION")) != NULL){
		int actionCod = atoi(action);
		//choix de l'action
		switch (actionCod){
		case ACTION_DECONNEXION:
			printf("     Sortie de : aiguillageServeur\n");
			return 0;
			break;
		case ACTION_AJOUTE_UTILISATEUR:
			if(isUserAdmin(mapUtilisateurs, userLogged) == 1){
				ajouteUtilisateur(mapParameters, "0");
			}
			break;
		case ACTION_MODIFIE_UTILISATEUR:
			if(isUserAdmin(mapUtilisateurs, userLogged) == 1){
				modifieUtilisateur(mapParameters);
			}
			break;
		case ACTION_SUPPRIME_UTILISATEUR:
			if(isUserAdmin(mapUtilisateurs, userLogged) == 1){
				supprimeUtilisateur(mapParameters);
			}
			break;
		}
	}
	
	printf("     Sortie de : aiguillageServeur\n");
	return 1;
}

//fonction qui initialise la map des utilisateurs en lisant ou créant un fichier csv
void initMapUtilisateurs(){
	printf("     Entrée dans : initMapUtilisateurs\n");

	mapUtilisateurs.size = 0;

	FILE* csv;
	if((csv = fopen("mapUsers.csv", "r"))){	
		char nom[BUFSIZ], prenom[BUFSIZ], mail[BUFSIZ], adressePostale[BUFSIZ], numTel[BUFSIZ], remarque[BUFSIZ], age[BUFSIZ], admin[BUFSIZ], login[BUFSIZ], password[BUFSIZ];
		char ligne[BUFSIZ];
		int cptUser = 0;
		while(fgets(ligne, BUFSIZ, csv) != NULL){
			int cpt = 0;
			recupereString(ligne, nom, &cpt, ',');
			recupereString(ligne, prenom, &cpt, ',');
			recupereString(ligne, mail, &cpt, ',');
			recupereString(ligne, adressePostale, &cpt, ',');
			recupereString(ligne, numTel, &cpt, ',');
			recupereString(ligne, remarque, &cpt, ',');
			recupereString(ligne, age, &cpt, ',');
			recupereString(ligne, login, &cpt, ',');
			recupereString(ligne, password, &cpt, ',');
			recupereString(ligne, admin, &cpt, '\n');

			utilisateur user;
			user.nom = nom;
			user.prenom = prenom;
			user.mail = mail;
			user.adressePostale = adressePostale;
			user.numTel = numTel;
			user.remarque = remarque;
			user.age = atoi(age);
			user.login = login;
			user.password = password;
			addToHashMapUserString(&mapUtilisateurs, user, admin);

			cptUser++;
		}
		printf(YEL "%d utilisateur récupéré.\n" RESET, cptUser);
		fclose(csv);
	}else{
		hashMapStringString mapParameters = {.size = 0};
		addToHashMapStringString(&mapParameters, "nom", "Terrier");
		addToHashMapStringString(&mapParameters, "prenom", "Florian");
		addToHashMapStringString(&mapParameters, "mail", "florian.leeroy@hotmail.com");
		addToHashMapStringString(&mapParameters, "adressePostale", "7 Chemin du Semalou");
		addToHashMapStringString(&mapParameters, "numTel", "0619244208");
		addToHashMapStringString(&mapParameters, "remarque", " ");
		addToHashMapStringString(&mapParameters, "age", "21");
		addToHashMapStringString(&mapParameters, "login", "floliroy");
		addToHashMapStringString(&mapParameters, "password", "stri");

		ajouteUtilisateur(mapParameters, "1");
	}

	printf("     Sortie de : initMapUtilisateurs\n");
}

//serveur sur localhost:13214
int main() {
	char *message = NULL;
	utilisateur* userLogged;
	int logged = 0;
	int retour;

	initMapUtilisateurs();
	Initialisation();

	while(1) {
		AttenteClient();
		message = Reception();
		hashMapStringString mapParameters = {.size = 0};

		if(message != NULL && isRequeteGet(message) == 1 && extraitRequete(message, &mapParameters) == 1) {
			printf(YEL "J'ai recu: %s\n" RESET, message);

			if(logged == 1){
				retour = aiguillageServeur(mapParameters, userLogged);
				if(retour == 0){
					printf(RED "Deconnexion du login: \"%s\".\n" RESET, userLogged->login);
					logged = 0;
					free(userLogged);
				}
			}else{
				printf("Attente de connexion...\n");
				char* login = getFromHashMapStringString(&mapParameters, "login");
				char* password = getFromHashMapStringString(&mapParameters, "password");
				char* action = getFromHashMapStringString(&mapParameters, "ACTION");
				if(login != NULL && password != NULL && action != NULL &&
				strcmp(action,"1") == 0 && isMotDePasseValide(mapUtilisateurs, login, password) == 1){
					userLogged = malloc(sizeof(utilisateur));
					userLogged = getUserWithLogin(&mapUtilisateurs, login);
					logged = 1;
					printf(RED "Connexion réussie avec le login: \"%s\".\n" RESET, login);
				}
			}		

			free(message);
		}else{
			TerminaisonClient();
			//logged = 0;
			//free(userLogged);
		}
	}

	return 0;
}
