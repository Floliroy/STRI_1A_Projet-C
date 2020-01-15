#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"
#include "../util/util.h"

hashMapUserString mapUtilisateurs; //Création de la map contennant tous les utilisateurs en variable globale

/**
 * Permet d'ajouter un nouvel utilisateur a mapUtilisateurs et au fichier csv (pour la sauvegarde)
 * 
 * @param mapParameters Les parametres de la requete recu permettant d'avoir les données de l'utilisateur à ajouter
 * @param admin Savoir si l'utilisateur doit etre defini comme admin ou non
 * @return Renvoit 1 si tout c'est bien passé, 0 sinon
 **/
int ajouteUtilisateur(hashMapStringString mapParameters, char* admin){
	printf("     Entrée dans : ajouteUtilisateur\n");
	char *nom, *prenom, *mail, *adressePostale, *numTel, *remarque, *age, *login, *password;

	utilisateur newUtilisateur;
	
	//Si les informations obligatoires (nom, prenom, adresse mail, login, password) sont nulles alors on ne peut pas ajouter un nouvel utilisateur
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

	//Si on l'utilisateur existe deja par son nom/prenom ou par son login alors on ne le réajoute pas
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

	//Si dans les parametres on trouve des valeurs non nulles alors on les ajoute a l'utilisateur sinon on met un espace
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
	//Pour l'age s'il n'est pas renseigné on stockera -1
	if((age = getFromHashMapStringString(&mapParameters, "age")) == NULL){
		age = "-1";
	}
	newUtilisateur.age = atoi(age); //convertir une chaine de caractère en int

	//On ajoute l'utilisateur a la map
	addToHashMapUserString(&mapUtilisateurs, newUtilisateur, "0");

	//Puis au fichier csv
	FILE* csv;
	if(strcmp(admin,"1") == 0){
		//Création du fichier csv en écriture seule (si on crée un admin le fichier n'existe pas encore)
		csv = fopen("mapUsers.csv", "w");
	}else{
		//Ouverture du fichier en lecture et ecriture sans écraser le fichier
		csv = fopen("mapUsers.csv", "r+");
	}

	//On se place a la fin du fichier
	fseek(csv, 0, SEEK_END);
	//On écrit la ligne des données de l'utilisateur
	fprintf(csv, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", nom, prenom, mail, adressePostale, numTel, remarque, age, login, password, admin);
	//On ferme le fichier
	fclose(csv);

	printf(YEL "Utilisateur %s %s ajouté.\n" RESET, nom, prenom);
	printf("     Sortie de : ajouteUtilisateur\n");
	return 1;
}

/**
 * Permet de modifier un utilisateur dans mapUtilisateurs et dans le fichier csv
 * 
 * @param mapParameters Les parametres de la requete recu permettant d'avoir les données de l'utilisateur à modifier
 * @return Renvoit 1 si tout c'est bien passé, 0 sinon
 **/
int modifieUtilisateur(hashMapStringString mapParameters){
	printf("     Entrée dans : modifieUtilisateur\n");
	char *nom, *prenom, *mail, *adressePostale, *numTel, *remarque, *age, *admin, *login, *password;
	
	//Si on n'a ni le nom ni le prenom alors on ne peut pas savoir quel utilisateur modifier
	if((nom = getFromHashMapStringString(&mapParameters, "nom")) == NULL ||
	(prenom = getFromHashMapStringString(&mapParameters, "prenom")) == NULL){
		printf("Erreur, données manquantes pour modifier un utilisateur.\n");
		return 0;
	}

	//On vérifie que l'utilisateur existe bien avant toute modification
	utilisateur* user = getUserWithNomPrenom(&mapUtilisateurs ,nom, prenom);
	if(user == NULL){
		printf("Erreur, utilisateur introuvable.\n");
		return 0;
	}
	admin = getFromHashMapUserString(&mapUtilisateurs, user);
	
	//Si dans les parametres on trouve des valeurs non nulles alors on les modifie pour l'utilisateur
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

	//On modifie ensuite le fichier csv avec les nouvelles données
	int pos = getUserLineWithNomPrenom(nom, prenom);
	int cpt = 0, copie = 1;

	//On crée un fichier temporaire pour copier tout le fichier actuel sauf la ligne de l'utilisateur a modifier
	FILE* csv = fopen("mapUsers.csv", "r");
    FILE* temp = fopen("temp.csv", "w");
	char c;

	while((c = getc(csv)) != EOF){
		cpt++;

		//Si on arrive a la ligne de l'utilisateur a modifier on arrete de copier jusqu'a ...
		if (cpt == pos+1)
			copie = 0;

		if(copie == 1){
			putc(c, temp);
		}else if(copie == 0){
			//Si on ne copie pas depuis notre fichier alors on écrit a la place la nouvelle ligne pour cet utilisateur
			fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", nom, prenom, mail, adressePostale, numTel, remarque, age, login, password, admin);
			copie = -1;
		}

		//... on arrete de copier jusqu'a avoir un retour a la ligne (marquant la fin des données de l'utilisateur)
		if(c == '\n')
			copie = 1;
	}
	//On ferme les fichiers ouvert
	fclose(csv);
	fclose(temp);
	//On supprime notre précédent fichier
	remove("mapUsers.csv");
	//On renomme notre fichier temporaire
	rename("temp.csv", "mapUsers.csv");

	printf(YEL "Utilisateur %s %s modifié.\n" RESET, nom, prenom);
	printf("     Sortie de : modifieUtilisateur\n");
	return 1;
}

/**
 * Permet de supprimer un utilisateur de mapUtilisateurs et dans le fichier csv
 * 
 * @param mapParameters Les parametres de la requete recu permettant d'avoir les données de l'utilisateur à supprimer
 * @return Renvoit 1 si tout c'est bien passé, 0 sinon
 **/
int supprimeUtilisateur(hashMapStringString mapParameters){
	printf("     Entrée dans : supprimeUtilisateur\n");
	char *nom, *prenom;

	//Si on n'a ni le nom ni le prenom alors on ne peut pas savoir quel utilisateur supprimer
	if((nom = getFromHashMapStringString(&mapParameters, "nom")) == NULL ||
	(prenom = getFromHashMapStringString(&mapParameters, "prenom")) == NULL){
		printf("Erreur, données manquantes pour supprimer un utilisateur.\n");
		return 0;
	}
	
	//On supprime l'utilisateur de la structure
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

	//Puis on le supprime du fichier csv
	int pos = getUserLineWithNomPrenom(nom, prenom);
	int cpt = 0, copie = 1;

	//On crée un fichier temporaire pour copier tout le fichier actuel sauf la ligne de l'utilisateur a supprimer
	FILE* csv = fopen("mapUsers.csv", "r");
    FILE* temp = fopen("temp.csv", "w");
	char c;

	//Tant qu'on est pas a la fin du fichier
	while((c = getc(csv)) != EOF){
		cpt++;
		//Si on arrive a la ligne de l'utilisateur a supprimer on arrete de copier jusqu'a ...
		if (cpt == pos+1)
			copie = 0;

		if(copie == 1){
			putc(c, temp);
		}

		//... on arrete de copier jusqu'a avoir un retour a la ligne (marquant la fin des données de l'utilisateur)
		if(c == '\n')
			copie = 1;
	}
	//On ferme les fichiers ouvert
	fclose(csv);
	fclose(temp);
	//On supprime notre précédent fichier
	remove("mapUsers.csv");
	//On renomme notre fichier temporaire
	rename("temp.csv", "mapUsers.csv");

	printf(YEL "Utilisateur %s %s supprimé.\n" RESET, nom, prenom);
	printf("     Sortie de : supprimeUtilisateur\n");
	return 1;
}

/**
 * Fonction qui permet de pointer vers l'action à laquelle le client souhaite accéder
 * 
 * @param mapParameters Les parametres de la requete recu permettant d'avoir les données de l'utilisateur à supprimer
 * @param userLogged L'utilisateur connecté au serveur
 * @return Retourne 0 si l'utilisateur souhaite se déconnecter, 1 sinon
 **/
int aiguillageServeur(hashMapStringString mapParameters, utilisateur* userLogged){
	printf("     Entrée dans : aiguillageServeur\n");

	char* action;
	printf(BLU "ACTION = %s\n" RESET, getFromHashMapStringString(&mapParameters, "ACTION"));

	//On récupère l'action souhaité par le client
	if((action = getFromHashMapStringString(&mapParameters, "ACTION")) != NULL){
		int actionCod = atoi(action);
		
		//On pointe vers la bonne fonction
		switch (actionCod){
		case ACTION_DECONNEXION:
			printf("     Sortie de : aiguillageServeur\n");
			return 0;
			break;
		case ACTION_AJOUTE_UTILISATEUR:
			//Accessible seulement par l'administrateur
			if(isUserAdmin(mapUtilisateurs, userLogged) == 1){
				ajouteUtilisateur(mapParameters, "0");
			}
			break;
		case ACTION_MODIFIE_UTILISATEUR:
			//Accessible seulement par l'administrateur
			if(isUserAdmin(mapUtilisateurs, userLogged) == 1){
				modifieUtilisateur(mapParameters);
			}
			break;
		case ACTION_SUPPRIME_UTILISATEUR:
			//Accessible seulement par l'administrateur
			if(isUserAdmin(mapUtilisateurs, userLogged) == 1){
				supprimeUtilisateur(mapParameters);
			}
			break;
		}
	}
	
	printf("     Sortie de : aiguillageServeur\n");
	return 1;
}

/**
 * Fonction qui permet d'initialiser la mapUtilisateurs en créant le fichier csv ou en le lisant
 **/
void initMapUtilisateurs(){
	printf("     Entrée dans : initMapUtilisateurs\n");

	mapUtilisateurs.size = 0;

	FILE* csv;
	//Si on peut ouvrir le fichier c'est qu'il existe, on le lire donc
	if((csv = fopen("mapUsers.csv", "r"))){	
		char nom[BUFSIZ], prenom[BUFSIZ], mail[BUFSIZ], adressePostale[BUFSIZ], numTel[BUFSIZ], remarque[BUFSIZ], age[BUFSIZ], admin[BUFSIZ], login[BUFSIZ], password[BUFSIZ];
		char ligne[BUFSIZ];
		int cptUser = 0;

		//On récupère les valeurs ligne par ligne (donc utilisateur par utilisateur)
		while(fgets(ligne, BUFSIZ, csv) != NULL){
			int cpt = 0;
			//On extrait les differents champs de la ligne
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

			//On stocke les valeurs dans les champs de l'utilisateur
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

			//On ajoute l'utilisateur a la map
			addToHashMapUserString(&mapUtilisateurs, user, admin);
			cptUser++;
		}
		printf(YEL "%d utilisateur récupéré.\n" RESET, cptUser);
		//On ferme le fichier precedemment ouvert
		fclose(csv);
	}else{
		//On crée des "faux" parametres de requete pour pouvoir pointer vers ajouteUtilisateur()
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

		//On envoit notre map a ajouteUtilisateur()
		ajouteUtilisateur(mapParameters, "1");
	}

	printf("     Sortie de : initMapUtilisateurs\n");
}

/**
 * Main du serveur
 **/
int main() {
	char *message = NULL;
	utilisateur* userLogged;
	int logged = 0;
	int retour;

	//On initialise notre map d'utilisateurs et le serveur
	initMapUtilisateurs();
	Initialisation();

	while(1) {
		//On attends un message du client
		AttenteClient();
		message = Reception();
		//On 'reset' notre map des paramètres de la requête
		hashMapStringString mapParameters = {.size = 0};

		//Si on a une requete GET et qu'on peut en récupérer des paramètres
		if(message != NULL && isRequeteGet(message) == 1 && extraitRequete(message, &mapParameters) == 1) {
			printf(YEL "J'ai recu: %s\n" RESET, message);

			//Si l'utilisateur est connecté
			if(logged == 1){
				//On pointe alors sur nnotre aiguillage
				retour = aiguillageServeur(mapParameters, userLogged);
				//Un retour à 0 indique un souhait de déconnexion
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

				//Si on a une demande de connexion et que le login et mot de passe sont valides
				if(login != NULL && password != NULL && action != NULL &&
				strcmp(action,"1") == 0 && isMotDePasseValide(mapUtilisateurs, login, password) == 1){
					//On crée alors notre utilisateur connecté
					userLogged = malloc(sizeof(utilisateur));
					userLogged = getUserWithLogin(&mapUtilisateurs, login);
					logged = 1;
					printf(RED "Connexion réussie avec le login: \"%s\".\n" RESET, login);
				}
			}		

			//On libère l'espace mémoire alloué au message recu
			free(message);
		}else{
			TerminaisonClient();
			//logged = 0;
			//free(userLogged);
		}
	}

	return 0;
}