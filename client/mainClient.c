#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include "client.h"
#include "../util/util.h"
#include "../util/user.h"

int afficheMenu(int admin){
	int action;
	//On affiche le menu
	printf(RED "\nBienvenue sur le Client de Floliroy :\n" RESET);
	printf(BLU " 1. Se déconnecter\n" RESET);

	//On affiche certains l'element seulement si l'utilisateur est admin
	if(admin == 1){
		printf(BLU " 2. Ajouter un utilisateur\n" RESET);
		printf(BLU " 3. Modifier un utilisateur\n" RESET);
		printf(BLU " 4. Supprimer un utilisateur\n" RESET);
	}

	printf("\nEntrer le numéro de l'action souhaitée: ");
	//On récupère l'action souhaitée
	scanf("%d", &action);
	if(action > 1 && admin != 1){
		printf("\nERREUR : Action inconnue...\n");
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
}

int main() {    
	//char* message;
	int retour;
	int admin = 0;
	int logged = 1;

	if(Initialisation("localhost") != 1) {
		printf("Erreur d'initialisation\n");
		return 1;
	}

	while(1){
		if(logged == 0){

		}else{
			retour = afficheMenu(admin);
			if(retour == ACTION_DECONNEXION){
				logged = 0;
				admin = 0;
			}else{

			}
		}
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