#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"
#include "../util/util.h"
#include "../util/user.h"
#include "../util/workString.h"

hashMapUserString mapUtilisateurs; //Création de la map contennant tous les utilisateurs en variable globale

void connexion(hashMapStringString mapParameters, utilisateur* userLogged, int* logged){
	printf("Attente de connexion...\n");

	char* login = getFromHashMapStringString(&mapParameters, "login");
	char* password = getFromHashMapStringString(&mapParameters, "password");
	char* action = getFromHashMapStringString(&mapParameters, "ACTION");

	//Si on a une demande de connexion et que le login et mot de passe sont valides
	if(login != NULL && password != NULL && action != NULL &&
	strcmp(action,"1") == 0 && isMotDePasseValide(mapUtilisateurs, login, password) == 1){
		//On crée alors notre utilisateur connecté
		utilisateur* user = malloc(sizeof(utilisateur));
		user = getUserWithLogin(&mapUtilisateurs, login);
		*logged = 1;
		printf(RED "Connexion réussie avec le login: \"%s\".\n" RESET, login);

		//On emet si l'utilisateur est un admin ou non
		if(isUserAdmin(mapUtilisateurs, user) == 1){
			envoieRetour(CODE_CONNEXION_REUSSI_ADMIN);
		}else{
			envoieRetour(CODE_CONNEXION_REUSSI_USER);
		}
		*userLogged = *user;
	}else{
		envoieRetour(CODE_CONNEXION_PAS_OK);
	}
}

/**
 * Permet d'ajouter un nouvel annuaire a un utilisateur s'il en a pas deja un
 * 
 * @param userLogged L'utilisateur souhaitant ajouter son annuaire
 **/
void creeAnnuaire(utilisateur* userLogged){
	printf("     Entrée dans : creeAnnuaire\n");
	char stringAnnuaire[BUFSIZ];
	//On construit le chemin de l'annuaire de l'utilisateur
	sprintf(stringAnnuaire, "util/annu%s%s.csv", userLogged->nom, userLogged->prenom);

	FILE* annuaire;
	if((annuaire = fopen(stringAnnuaire, "r"))){
		//Si on peut ouvrir le fichier c'est qu'il existe, on indique donc que l'utilisateur possède deja un annuaire
		printf("Erreur, cet utilisateur possède déjà un annuaire.\n");
		envoieRetour(CODE_USER_ANNUAIRE_EXISTANT);
	}else{
		//Sinon on lui crée un nouvel annuaire
		annuaire = fopen(stringAnnuaire, "w");
		printf(YEL "Annuaire ajouté a l'utilisateur %s %s.\n" RESET, userLogged->nom, userLogged->prenom);
		envoieRetour(CODE_ACTION_REUSSI);
	}

	fclose(annuaire);
	printf("     Sortie de : creeAnnuaire\n");
}

/**
 * Permet d'ajouter un nouvel utilisateur a l'annuaire de l'utilisateur appelant le serveur
 * 
 * @param mapParameters Les parametres de la requete recu permettant d'avoir les données de l'utilisateur à ajouter
 * @param userLogged L'utilisateur souhaitant ajouter un utilisateur dans son annuaire
 **/
void ajouteDansAnnuaire(hashMapStringString mapParameters, utilisateur* userLogged){
	printf("     Entrée dans : ajouteDansAnnuaire\n");
	char stringAnnuaire[BUFSIZ];
	//On construit le chemin de l'annuaire de l'utilisateur
	sprintf(stringAnnuaire, "util/annu%s%s.csv", userLogged->nom, userLogged->prenom);

	FILE* annuaire;
	if((annuaire = fopen(stringAnnuaire, "r+"))){
		//Si on peut ouvrir le fichier c'est qu'il existe, on ajoute donc le champ nécessaire
		char *nom, *prenom, *droits;
		if((nom = getFromHashMapStringString(&mapParameters, "nom")) == NULL ||
		(prenom = getFromHashMapStringString(&mapParameters, "prenom")) == NULL ||
		(droits = getFromHashMapStringString(&mapParameters, "droits")) == NULL){
			printf("Erreur, données manquantes pour ajouter utilisateur à l'agenda.\n");
			envoieRetour(CODE_CHAMPS_MANQUANTS_INVALIDES);
		}else{
			utilisateur* user = getUserWithNomPrenom(&mapUtilisateurs, nom, prenom);
			if(user == NULL){
				//Si l'utilisateur n'existe pas
				printf("Erreur, utilisateur introuvable.\n");
				envoieRetour(CODE_USER_ANNUAIRE_INTROUVABLE);
			}else if (getUserLineWithNomPrenom(nom, prenom, stringAnnuaire) != -1){
				//Si l'utilisateur fait deja partie du fichier
				printf("Erreur, utilisateur deja present.\n");
				envoieRetour(CODE_USER_ANNUAIRE_EXISTANT);
			}else{
				//Sinon on se place a la fin du fichier
				fseek(annuaire, 0, SEEK_END);
				//On écrit la ligne d'ajout de l'utilisateur
				fprintf(annuaire, "%s,%s,%s\n", nom, prenom, droits);
				printf(YEL "Utilisateur %s %s ajouté à l'annuaire de %s %s.\n" RESET, nom, prenom, userLogged->nom, userLogged->prenom);
				envoieRetour(CODE_ACTION_REUSSI);
			}
		}
		fclose(annuaire);
	}else{
		//Sinon on indique a l'utilisateur qu'il doit d'abord créer un son annuaire
		printf("Erreur, l'annuaire de cet utilisateur n'existe pas.\n");
		envoieRetour(CODE_USER_ANNUAIRE_INTROUVABLE);
	}

	printf("     Sortie de : ajouteDansAnnuaire\n");
}

/**
 * Permet de supprimer utilisateur de l'annuaire de l'utilisateur appelant le serveur
 * 
 * @param mapParameters Les parametres de la requete recu permettant d'avoir les données de l'utilisateur à supprime
 * @param userLogged L'utilisateur souhaitant supprime un utilisateur dans son annuaire
 **/
void supprimeDeAnnuaire(hashMapStringString mapParameters, utilisateur* userLogged){
	printf("     Entrée dans : supprimeDeAnnuaire\n");
	char stringAnnuaire[BUFSIZ];
	//On construit le chemin de l'annuaire de l'utilisateur
	sprintf(stringAnnuaire, "util/annu%s%s.csv", userLogged->nom, userLogged->prenom);

	FILE* annuaire;
	if((annuaire = fopen(stringAnnuaire, "r"))){
		//Si on peut ouvrir le fichier c'est qu'il existe, on ajoute donc le champ nécessaire
		char *nom, *prenom;
		if((nom = getFromHashMapStringString(&mapParameters, "nom")) == NULL ||
		(prenom = getFromHashMapStringString(&mapParameters, "prenom")) == NULL){
			fclose(annuaire);
			printf("Erreur, données manquantes pour supprimer l'utilisateur de l'agenda.\n");
			envoieRetour(CODE_CHAMPS_MANQUANTS_INVALIDES);
		}else{
			int pos = getUserLineWithNomPrenom(nom, prenom, stringAnnuaire);

			//On crée un fichier temporaire pour copier tout le fichier actuel sauf la ligne de l'utilisateur a supprimer
			FILE* temp = fopen("util/temp.csv", "w");
			//On copie notre fichier sauf la ligne de l'utilisateur
			copieSaufLigne(annuaire, temp, pos);

			//On ferme les fichiers ouvert
			fclose(annuaire);
			fclose(temp);
			//On supprime notre précédent fichier
			remove(stringAnnuaire);
			//On renomme notre fichier temporaire
			rename("util/temp.csv", stringAnnuaire);
			printf(YEL "Utilisateur %s %s supprimé de l'annuaire de %s %s.\n" RESET, nom, prenom, userLogged->nom, userLogged->prenom);
			envoieRetour(CODE_ACTION_REUSSI);
		}
	}else{
		//Sinon on indique a l'utilisateur qu'il doit d'abord créer un son annuaire
		printf("Erreur, l'annuaire de cet utilisateur n'existe pas.\n");
		envoieRetour(CODE_USER_ANNUAIRE_INTROUVABLE);
	}

	printf("     Sortie de : supprimeDeAnnuaire\n");
}

/**
 * Permet de supprime un annuaire a un utilisateur
 * 
 * @param userLogged L'utilisateur souhaitant ajouter son annuaire
 **/
void supprimeAnnuaire(utilisateur* userLogged){
	printf("     Entrée dans : supprimeAnnuaire\n");
	char stringAnnuaire[BUFSIZ];
	//On construit le chemin de l'annuaire de l'utilisateur
	sprintf(stringAnnuaire, "util/annu%s%s.csv", userLogged->nom, userLogged->prenom);

	remove(stringAnnuaire);
	printf(YEL "Annuaire de l'utilisateur %s %s supprimé.\n" RESET, userLogged->nom, userLogged->prenom);
	envoieRetour(CODE_ACTION_REUSSI);

	printf("     Sortie de : supprimeAnnuaire\n");
}

/**
 * Permet de consulter son annuaire
 * 
 * @param userLogged L'utilisateur souhaitant consulter son annuaire
 **/
void consulteAnnuaire(utilisateur* userLogged){
	printf("     Entrée dans : consulteAnnuaire\n");
	char stringAnnuaire[BUFSIZ], retour[BUFSIZ];
	//On construit le chemin de l'annuaire de l'utilisateur
	sprintf(stringAnnuaire, "util/annu%s%s.csv", userLogged->nom, userLogged->prenom);

	FILE* annuaire;
	if((annuaire = fopen(stringAnnuaire, "r"))){
		sprintf(retour, "%d ,", CODE_CONSULTE_ANNUAIRE);

		//Si on peut ouvrir le fichier c'est qu'il existe on va donc renvoyer la liste des utilisateurs
		char nom[BUFSIZ], prenom[BUFSIZ], finLigne[BUFSIZ];
		char ligne[BUFSIZ];

		//On récupère les valeurs ligne par ligne (donc utilisateur par utilisateur)
		while(fgets(ligne, BUFSIZ, annuaire) != NULL){
			int cpt = 0;
			//On extrait les deux champs de la ligne
			recupereString(ligne, nom, &cpt, ',');
			recupereString(ligne, prenom, &cpt, ',');
			recupereString(ligne, finLigne, &cpt, '\n');

			//On stocke les valeurs dans les champs de l'utilisateur
			utilisateur* user = getUserWithNomPrenom(&mapUtilisateurs, nom, prenom);
			char champsUtilisateur[BUFSIZ];
			//sprintf(champsUtilisateur, "%s %s %s %s %s %s %d %s %s\n", user->nom, user->prenom, user->mail, user->adressePostale, user->numTel, user->remarque, user->age, user->login, user->password);
			sprintf(champsUtilisateur, "%s %s %s,", user->nom, user->prenom, user->mail);
			strcat(retour, champsUtilisateur);
		}
		strcat(retour, "\n");
		printf(YEL "Consultation de l'annuaire de %s %s terminé.\n" RESET, userLogged->nom, userLogged->prenom);
		//On ferme le fichier precedemment ouvert
		fclose(annuaire);
		
		Emission(retour);
	}else{
		//Sinon on indique a l'utilisateur qu'il doit d'abord créer un son annuaire
		printf("Erreur, l'annuaire de cet utilisateur n'existe pas.\n");
		envoieRetour(CODE_USER_ANNUAIRE_INTROUVABLE);
	}

	printf("     Sortie de : consulteAnnuaire\n");
}

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
		envoieRetour(CODE_CHAMPS_MANQUANTS_INVALIDES);
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
		envoieRetour(CODE_USER_ANNUAIRE_EXISTANT);
		return 0;
	}
	user = getUserWithLogin(&mapUtilisateurs, login);
	if(user != NULL){
		printf("Erreur, cet utilisateur existe deja.\n");
		envoieRetour(CODE_USER_ANNUAIRE_EXISTANT);
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
		csv = fopen("util/mapUsers.csv", "w");
	}else{
		//Ouverture du fichier en lecture et ecriture sans écraser le fichier
		csv = fopen("util/mapUsers.csv", "r+");
	}

	//On se place a la fin du fichier
	fseek(csv, 0, SEEK_END);
	//On écrit la ligne des données de l'utilisateur
	fprintf(csv, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n", nom, prenom, mail, adressePostale, numTel, remarque, age, login, password, admin);
	//On ferme le fichier
	fclose(csv);

	printf(YEL "Utilisateur %s %s ajouté.\n" RESET, nom, prenom);
	envoieRetour(CODE_ACTION_REUSSI);

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
		envoieRetour(CODE_CHAMPS_MANQUANTS_INVALIDES);
		return 0;
	}

	//On vérifie que l'utilisateur existe bien avant toute modification
	utilisateur* user = getUserWithNomPrenom(&mapUtilisateurs ,nom, prenom);
	if(user == NULL){
		printf("Erreur, utilisateur introuvable.\n");
		envoieRetour(CODE_USER_ANNUAIRE_INTROUVABLE);
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
		age = (char*) malloc(4 * sizeof(char));
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

	printf("%s\n", adressePostale);

	//On modifie ensuite le fichier csv avec les nouvelles données
	int pos = getUserLineWithNomPrenom(nom, prenom, "util/mapUsers.csv");
	int cpt = 0, copie = 1;


	//On crée un fichier temporaire pour copier tout le fichier actuel sauf la ligne de l'utilisateur a modifier
	FILE* csv = fopen("util/mapUsers.csv", "r");
    FILE* temp = fopen("util/temp.csv", "w");
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
	remove("util/mapUsers.csv");
	//On renomme notre fichier temporaire
	rename("util/temp.csv", "util/mapUsers.csv");

	printf(YEL "Utilisateur %s %s modifié.\n" RESET, nom, prenom);
	envoieRetour(CODE_ACTION_REUSSI);

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
		envoieRetour(CODE_CHAMPS_MANQUANTS_INVALIDES);
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
	int pos = getUserLineWithNomPrenom(nom, prenom, "util/mapUsers.csv");
	//On crée un fichier temporaire pour copier tout le fichier actuel sauf la ligne de l'utilisateur a supprimer
	FILE* csv = fopen("util/mapUsers.csv", "r");
    FILE* temp = fopen("util/temp.csv", "w");

	//On copie tout notre fichier sauf la ligne de l'utilisateur
	copieSaufLigne(csv, temp, pos);

	//On ferme les fichiers ouvert
	fclose(csv);
	fclose(temp);
	//On supprime notre précédent fichier
	remove("util/mapUsers.csv");
	//On renomme notre fichier temporaire
	rename("util/temp.csv", "util/mapUsers.csv");

	printf(YEL "Utilisateur %s %s supprimé.\n" RESET, nom, prenom);
	envoieRetour(CODE_ACTION_REUSSI);

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
			}else{
				envoieRetour(CODE_ACTION_IMPOSSIBLE);
			}
			break;
		case ACTION_MODIFIE_UTILISATEUR:
			//Accessible seulement par l'administrateur
			if(isUserAdmin(mapUtilisateurs, userLogged) == 1){
				modifieUtilisateur(mapParameters);
			}else{
				envoieRetour(CODE_ACTION_IMPOSSIBLE);
			}
			break;
		case ACTION_SUPPRIME_UTILISATEUR:
			//Accessible seulement par l'administrateur
			if(isUserAdmin(mapUtilisateurs, userLogged) == 1){
				supprimeUtilisateur(mapParameters);
			}else{
				envoieRetour(CODE_ACTION_IMPOSSIBLE);
			}
			break;
		case ACTION_CREE_ANNUAIRE:
			creeAnnuaire(userLogged);
			break;
		case ACTION_AJOUTE_DANS_ANNUAIRE:
			ajouteDansAnnuaire(mapParameters, userLogged);
			break;
		case ACTION_SUPPRIME_DE_ANNUAIRE:
			supprimeDeAnnuaire(mapParameters, userLogged);
			break;
		case ACTION_SUPPRIME_ANNUAIRE:
			supprimeAnnuaire(userLogged);
			break;
		case ACTION_CONSULTE_ANNUAIRE:
			consulteAnnuaire(userLogged);
			break;
		}

		//Si on ne connait pas l'action souhaitée
		if(actionCod < 2 || actionCod > 10){
			envoieRetour(CODE_ACTION_INCONNU);
		}
	}else{
		//Si l'action est a NULL
		envoieRetour(CODE_ACTION_INCONNU);
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
	if((csv = fopen("util/mapUsers.csv", "r"))){	
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
	utilisateur* userLogged = malloc(sizeof(utilisateur));
	int logged = 0;
	int aiguillage;

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
			printf(YEL "\nJ'ai recu: %s\n" RESET, message);

			//Si l'utilisateur est connecté
			if(logged == 1){
				//On pointe alors sur nnotre aiguillage
				aiguillage = aiguillageServeur(mapParameters, userLogged);
				//Un aiguillage à 0 indique un souhait de déconnexion
				if(aiguillage == 0){
					printf(RED "Deconnexion du login: \"%s\".\n" RESET, userLogged->login);
					logged = 0;

					//On indique qu'on c'est bien déconnecté
					envoieRetour(CODE_DECONNEXION);
				}
			}else{
				connexion(mapParameters, userLogged, &logged);
			}		

			//On libère l'espace mémoire alloué au message recu
			free(message);
		}else{
			TerminaisonClient();
			logged = 0;
		}
	}

	return 0;
}
