#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "client.h"
#include "../util/util.h"
#include "../util/user.h"
#include "../util/workString.h"

/** (Florian)
 * Permet de se connecter au serveur en demandant le login et le mdp utilisateur
 **/
void connexion(){
	hashMapStringString mapParameters = {.size = 0};
	printf(RED "\nConnexion :\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "1");
	demandeParam("login", &mapParameters, 1, 0);
	demandeParam("password", &mapParameters, 1, 0);
	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
 * Permet de déconnecter l'utilisateur actuellement connecté sur le serveur
 * 
 * @param show Permet de montrer ou non le message de déconnexion
 **/
void deconnexion(int show){
	hashMapStringString mapParameters= {.size = 0};
	if(show != 0){
		printf(RED "\nDéconnexion !\n" RESET);
	}

	addToHashMapStringString(&mapParameters, "ACTION", "2");
	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
 * Permet d'ajouter un annuaire
 **/
void creeAnnuaire(){
	hashMapStringString mapParameters= {.size = 0};

	printf(RED "\nAjout d'Annuaire !\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "6");
	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
 * Permet d'ajouter un utilisateur a son annuaire
 **/
void ajouteDansAnnuaire(){
	hashMapStringString mapParameters= {.size = 0};
	printf(RED "\nAjout d'un Utilisateur à l'Annuaire !\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "7");
	demandeParam("nom", &mapParameters, 0, 0);
	demandeParam("prenom", &mapParameters, 0, 0);
	printf(RED "\nDroits (0 ou 1) ...\n" RESET);
	demandeParam("droits", &mapParameters, -1, 0);
	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
 * Permet de supprimer un utilisateur de son annuaire
 **/
void supprimeDeAnnuaire(){
	hashMapStringString mapParameters= {.size = 0};
	printf(RED "\nSuppression d'un Utilisateur de l'Annuaire !\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "8");
	demandeParam("nom", &mapParameters, 0, 0);
	demandeParam("prenom", &mapParameters, 0, 0);
	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
 * Permet de supprimer un annuaire
 **/
void supprimeAnnuaire(){
	hashMapStringString mapParameters= {.size = 0};
	printf(RED "\nSuppresion d'Annuaire !\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "9");
	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
 * Permet de consulter un annuaire
 **/
void consulterAnnuaire(){
	hashMapStringString mapParameters= {.size = 0};
	printf(RED "\nConsulter son Annuaire !\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "10");
	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
 * Permet de consulter l'annuaire d'un autre utilisateur
 **/
void consulterAutreAnnuaire(){
	hashMapStringString mapParameters= {.size = 0};
	printf(RED "\nConsulter Annuaire d'un Utilisateur :\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "10");
	demandeParam("nom", &mapParameters, 0, 0);
	demandeParam("prenom", &mapParameters, 0, 0);
	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
 * Permet d'ajouter un nouvel utilisateur en demandant les champs nécessaires
 **/
void ajouteUtilisateur(){
	hashMapStringString mapParameters = {.size = 0};
	printf(RED "\nAjout d'un Utilisateur :\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "3");
	demandeParam("nom", &mapParameters, 0, 0);
	demandeParam("prenom", &mapParameters, 0, 0);
	demandeParam("mail", &mapParameters, 0, 0);
	demandeParam("login", &mapParameters, 0, 0);
	demandeParam("password", &mapParameters, 0, 0);

	printf(RED "\nChamps optionnels :\n" RESET);
	demandeParam("adressePostale", &mapParameters, 0, 1);
	demandeParam("numTel", &mapParameters, 0, 1);
	demandeParam("remarque", &mapParameters, 2, 1);
	demandeParam("age", &mapParameters, 0, 1);	

	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
 * Permet de modifier un utilisateur en demandant son nom et son prénom ainsi que les infos a modifier
 **/
void modifieUtilisateur(){
	hashMapStringString mapParameters = {.size = 0};
	printf(RED "\nModification d'un Utilisateur :\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "4");
	demandeParam("nom", &mapParameters, 0, 0);
	demandeParam("prenom", &mapParameters, 0, 0);

	printf(RED "\nChamps à modifier :\n" RESET);
	demandeParam("mail", &mapParameters, 0, 1);
	demandeParam("login", &mapParameters, 0, 1);
	demandeParam("password", &mapParameters, 0, 1);
	demandeParam("adressePostale", &mapParameters, 0, 1);
	demandeParam("numTel", &mapParameters, 0, 1);
	demandeParam("remarque", &mapParameters, 2, 1);
	demandeParam("age", &mapParameters, 0, 1);	

	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
 * Permet de supprimer un utilisateur en demandant son nom et son prénom 
 **/
void supprimeUtilisateur(){
	hashMapStringString mapParameters = {.size = 0};
	printf(RED "\nSuppression d'un Utilisateur :\n" RESET);

	addToHashMapStringString(&mapParameters, "ACTION", "5");
	demandeParam("nom", &mapParameters, 0, 0);
	demandeParam("prenom", &mapParameters, 0, 0);	
	envoieRequeteFormatee(mapParameters);
}

/** (Florian)
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
		deconnexion(1);
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
	case ACTION_SUPPRIME_ANNUAIRE:
		supprimeAnnuaire();
		break;
	case ACTION_CONSULTE_ANNUAIRE:
		consulterAnnuaire();
		break;
	case ACTION_CONSULTE_AUTRE_ANNUAIRE:
		consulterAutreAnnuaire();
		break;
	}
}

/** (Katia & Duncan)
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

	//On efface ce qu'il y a dans la console
	if(system("clear")){}

	switch (code){
	case CODE_CONNEXION_REUSSI_ADMIN:
		printf("\n	Vous vous êtes bien connecté en tant qu'admin.\n");
		*logged = 1;
		*admin = 1;
		break;
	case CODE_CONNEXION_REUSSI_USER:
		printf("\n	Vous vous êtes bien connecté.\n");
		*logged = 1;
		*admin = 0;
		break;
	case CODE_DECONNEXION:
		printf("\n	Vous vous êtes bien déconnecté.\n");
		*logged = 0;
		*admin = 0;
		break;
	case CODE_CONNEXION_PAS_OK:
		printf("\n	Votre mot de passe ou login sont incorrects.\n");
		break;
	case CODE_ACTION_INCONNU:
		printf("\n	L'action que vous souhaitez effectuer est inconnue.\n");
		break;
	case CODE_ACTION_REUSSI:
		printf("\n	L'action a bien été effectuée.\n");
		break;
	case CODE_ACTION_IMPOSSIBLE:
		printf("\n	Vous n'avez pas les droits pour effectuer cette action.\n");
		break;
	case CODE_CHAMPS_MANQUANTS_INVALIDES:
		printf("\n	Vous n'avez pas bien renseigner les champs nécessaire a cette action.\n");
		break;
	case CODE_USER_ANNUAIRE_EXISTANT:
		printf("\n	La ressource que vous souhaitez ajouter existe déjà.\n");
		break;
	case CODE_USER_ANNUAIRE_INTROUVABLE:
		printf("\n	La ressource a laquelle vous souhaitez accéder est introuvable.\n");
		break;
	case CODE_CONSULTE_ANNUAIRE:
		printf("\n	Voici les utilisateurs présents dans l'annuaire :\n");
		for(int i=0 ; i<=strlen(message) ; i++){
			if(message[i] == ',')  {
				message[i] = '\n';
			}
		}
		char* retourAffichage = message;
		retourAffichage += 3;
		printf("%s", retourAffichage);
		break;
	}
}

/** (Katia & Duncan)
 * Affiche le menu du client avec les différentes actions possibles
 * 
 * @param admin Indique si l'utilisateur est un admin et donc s'il a accés aux actions réservés aux admins
 * @return Retourne l'action souhaitée
 **/
int afficheMenu(int admin){
	int action;
	char stringAction[BUFSIZ];
	//On affiche le menu
	do{
		printf(RED "\nBienvenue sur le Client de Floliroy :\n" RESET);
		printf(BLU " 1. Se déconnecter\n" RESET);
		printf(BLU " 2. Créer un annuaire\n" RESET);
		printf(BLU " 3. Supprimer son annuaire\n" RESET);
		printf(BLU " 4. Ajouter utilisateur à son annuaire\n" RESET);
		printf(BLU " 5. Supprimer utilisateur de son annuaire\n" RESET);
		printf(BLU " 6. Consulter son annuaire\n" RESET);
		printf(BLU " 7. Consulter l'annuaire d'un utilisateur\n" RESET);

		//On affiche certains l'element seulement si l'utilisateur est admin
		if(admin == 1){
			printf(BLU " 8. Ajouter un utilisateur\n" RESET);
			printf(BLU " 9. Modifier un utilisateur\n" RESET);
			printf(BLU " 10. Supprimer un utilisateur\n" RESET);
		}

		printf("\nEntrer le numéro de l'action souhaitée : ");
		//On récupère l'action souhaitée
		monLire(stringAction);
		action = atoi(stringAction);

		if((action > 7 && admin != 1) || action < 1 || action > 10){
			printf("\nERREUR : Action inconnue...\n");
		}
	}while((action > 7 && admin != 1) || action < 1 || action > 10);

	//On renvoit l'action qui servira a l'aiguillage
	switch (action){
	case 1:
		return ACTION_DECONNEXION;
		break;
	case 2:
		return ACTION_CREE_ANNUAIRE;
		break;
	case 3:
		return ACTION_SUPPRIME_ANNUAIRE;
		break;
	case 4:
		return ACTION_AJOUTE_DANS_ANNUAIRE;
		break;
	case 5:
		return ACTION_SUPPRIME_DE_ANNUAIRE;
		break;
	case 6:
		return ACTION_CONSULTE_ANNUAIRE;
		break;
	case 7:
		return ACTION_CONSULTE_AUTRE_ANNUAIRE;
		break;
	case 8:
		return ACTION_AJOUTE_UTILISATEUR;
		break;
	case 9:
		return ACTION_MODIFIE_UTILISATEUR;
		break;
	case 10:
		return ACTION_SUPPRIME_UTILISATEUR;
		break;
	}

	return -1;
}

/** (Florian)
 * Main du client
 **/
int main() {    
	char* message = (char*) malloc(sizeof(char));
	int admin = 0;
	int logged = 0;

	if(system("clear")){}
	deconnexion(0);

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