#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "client.h"
#include "../util/util.h"
#include "../util/user.h"

/**
 * Permet de lire une chaine tapée dans la console
 **/
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

/**
 * Permet de se connecter au serveur en demandant le login et le mdp utilisateur
 **/
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

/**
 * Permet de déconnecter l'utilisateur actuellement connecté sur le serveur
 **/
void deconnexion(){
	hashMapStringString mapParameters= {.size = 0};

	printf(RED "\nDéconnexion !\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "2");
	envoieRequeteFormatee(mapParameters);
}

/**
 * Permet d'ajouter un annuaire
 **/
void creeAnnuaire(){
	hashMapStringString mapParameters= {.size = 0};

	printf(RED "\nAjout Annuaire !\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "6");
	envoieRequeteFormatee(mapParameters);
}

/**
 * Permet d'ajouter un utilisateur a son annuaire
 **/
void ajouteDansAnnuaire(){
	hashMapStringString mapParameters= {.size = 0};
	char nom[BUFSIZ], prenom[BUFSIZ], droits[BUFSIZ];

	printf(RED "\nAjout d'un Utilisateur à l'Annuaire !\n" RESET);

	printf("Entrez son nom : ");
	monLire(nom);
	printf("Entrez son prénom : ");
	monLire(prenom);
	printf("Entrez ses droits (0/1) : ");
	monLire(droits);

	addToHashMapStringString(&mapParameters, "ACTION", "7");
	addToHashMapStringString(&mapParameters, "nom", nom);
	addToHashMapStringString(&mapParameters, "prenom", prenom);
	addToHashMapStringString(&mapParameters, "droits", droits);
	envoieRequeteFormatee(mapParameters);
}

/**
 * Permet de supprimer un utilisateur de son annuaire
 **/
void supprimeDeAnnuaire(){
	hashMapStringString mapParameters= {.size = 0};
	char nom[BUFSIZ], prenom[BUFSIZ];

	printf(RED "\nSuppression d'un Utilisateur de l'Annuaire !\n" RESET);

	printf("Entrez son nom : ");
	monLire(nom);
	printf("Entrez son prénom : ");
	monLire(prenom);

	addToHashMapStringString(&mapParameters, "ACTION", "8");
	addToHashMapStringString(&mapParameters, "nom", nom);
	addToHashMapStringString(&mapParameters, "prenom", prenom);
	envoieRequeteFormatee(mapParameters);
}

/**
 * Permet d'ajouter un nouvel utilisateur en demandant les champs nécessaires
 **/
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

/**
 * Permet de modifier un utilisateur en demandant son nom et son prénom ainsi que les infos a modifier
 **/
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

/**
 * Permet de supprimer un utilisateur en demandant son nom et son prénom 
 **/
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

/**
 * Aiguille vers la bonne fonction suivant l'action souhaitée
 * 
 * @param action Le numéro de l'action souhaitée
 **/
void aiguillageAction(int action){
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
	case ACTION_CREE_ANNUAIRE:
		creeAnnuaire();
		break;
	case ACTION_AJOUTE_DANS_ANNUAIRE:
		ajouteDansAnnuaire();
		break;
	case ACTION_SUPPRIME_DE_ANNUAIRE:
		supprimeDeAnnuaire();
		break;
	}
}

/**
 * Affiche différenntes chaines suivant le code de retour recu, peut aussi changer l'état de logged et admin
 * 
 * @param code Le code de retour
 * @param logged L'état de connexion de l'utilisateur
 * @param admin L'état administrateur de l'utilisateur 
 **/
void aiguillageRetour(char* message, int* logged, int* admin){
	
	char stringCode[BUFSIZ];
	int cpt = 0;
	recupereString(message, stringCode, &cpt, ' ');

	int code = atoi(stringCode);

	switch (code){
	case CODE_CONNEXION_REUSSI_ADMIN:
		printf("	Vous vous êtes bien connecté en tant qu'admin.\n");
		*logged = 1;
		*admin = 1;
		break;
	case CODE_CONNEXION_REUSSI_USER:
		printf("	Vous vous êtes bien connecté.\n");
		*logged = 1;
		*admin = 0;
		break;
	case CODE_DECONNEXION:
		printf("	Vous vous êtes bien déconnecté.\n");
		*logged = 0;
		*admin = 0;
		break;
	case CODE_CONNEXION_PAS_OK:
		printf("	Votre mot de passe ou login sont incorrects.\n");
		break;
	case CODE_ACTION_INCONNU:
		printf("	L'action que vous souhaitez effectuer est inconnue.\n");
		break;
	case CODE_ACTION_REUSSI:
		printf("	L'action a bien été effectuée.\n");
		break;
	case CODE_ACTION_IMPOSSIBLE:
		printf("	Vous n'avez pas les droits pour effectuer cette action.\n");
		break;
	case CODE_CHAMPS_MANQUANTS_INVALIDES:
		printf("	Vous n'avez pas bien renseigner les champs nécessaire a cette action.\n");
		break;
	case CODE_USER_ANNUAIRE_EXISTANT:
		printf("	La ressouce que vous souhaitez ajouter existe déjà.\n");
		break;
	case CODE_USER_ANNUAIRE_INTROUVABLE:
		printf("	La ressouce a laquelle vous souhaitez accéder est introuvable.\n");
		break;
	}
}

/**
 * Affiche le menu du client avec les différentes actions possibles
 * 
 * @param admin Indique si l'utilisateur est un admin et donc s'il a accés aux actions réservés aux admins
 * @return Retourne l'action souhaitée
 **/
int afficheMenu(int admin){
	int action;
	char stringAction[BUFSIZ];
	//On affiche le menu
	printf(RED "\nBienvenue sur le Client de Floliroy :\n" RESET);
	printf(BLU " 1. Se déconnecter\n" RESET);
	printf(BLU " 2. Créer un annuraire\n" RESET);
	printf(BLU " 3. Ajouter utilisateur à son annuaire\n" RESET);
	printf(BLU " 4. Supprimer utilisateur de son annuaire\n" RESET);

	//On affiche certains l'element seulement si l'utilisateur est admin
	if(admin == 1){
		printf(BLU " 5. Ajouter un utilisateur\n" RESET);
		printf(BLU " 6. Modifier un utilisateur\n" RESET);
		printf(BLU " 7. Supprimer un utilisateur\n" RESET);
	}

	printf("\nEntrer le numéro de l'action souhaitée : ");
	//On récupère l'action souhaitée
	monLire(stringAction);
	action = atoi(stringAction);
	if((action > 4 && admin != 1) || action < 1 || action > 7){
		printf("\nERREUR : Action inconnue...\n");
		return -1;
	}

	//On renvoit l'action qui servira a l'aiguillage
	switch (action){
	case 1:
		return ACTION_DECONNEXION;
		break;
	case 2:
		return ACTION_CREE_ANNUAIRE;
		break;
	case 3:
		return ACTION_AJOUTE_DANS_ANNUAIRE;
		break;
	case 4:
		return ACTION_SUPPRIME_DE_ANNUAIRE;
		break;
	case 5:
		return ACTION_AJOUTE_UTILISATEUR;
		break;
	case 6:
		return ACTION_MODIFIE_UTILISATEUR;
		break;
	case 7:
		return ACTION_SUPPRIME_UTILISATEUR;
		break;
	}

	return -1;
}

/**
 * Main du client
 **/
int main() {    
	char* message = (char*) malloc(sizeof(char));
	int admin = 0;
	int logged = 0;

	while(1){
		if(logged == 0){
			//Si on est pas connecté alors on essaye de se connecter
			connexion();
		}else{
			//Sinon on va vers le menu du client
			aiguillageAction(afficheMenu(admin));
		}

		free(message);
		message = Reception();
		//On affiche des messages suivant le code de retour recu
		aiguillageRetour(message, &logged, &admin);
	}

    return 0;
}