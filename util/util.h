#ifndef __UTIL_H__
#define __UTIL_H__

//constantes permettant d'associer les variables à des valeurs
#define ACTION_CONNEXION 1
#define ACTION_DECONNEXION 2
#define ACTION_AJOUTE_UTILISATEUR 3
#define ACTION_MODIFIE_UTILISATEUR 4
#define ACTION_SUPPRIME_UTILISATEUR 5

//couleurs pour les printf
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef struct {
	char* nom; // champ obligatoire 
	char* prenom; //champ obligatoire
	char* mail; //champ obligatoire
	char* adressePostale; 
	char* numTel; 
	char* remarque;
	int age;
	char* login; //obligatoire
	char* password; //obligatoire
}utilisateur;

//hashMap entre deux strings, structure de donnée entre deux strings permettant l'association clé-valeur
typedef struct{
	char* key;
	char* value;
}elementStringString;

typedef struct{
	int size; //nombre d'éléments de la structure 
	elementStringString elem[BUFSIZ];
}hashMapStringString;

//fonction pour ajouter à la hash map une valeur et sa clé
void addToHashMapStringString(hashMapStringString* map, char* key, char* value);

//fonction pour obtenir une valeur de la HashMap à partir de sa clé
char* getFromHashMapStringString(hashMapStringString* map, char* key);

//hashMap entre user et string: clé utilisateur qui permet d'avoir une valeur String 
typedef struct{
	utilisateur* key;
	char* value;
}elementUserString;

typedef struct{
	int size; //nombre d'éléments de la structure 
	elementUserString elem[BUFSIZ];
}hashMapUserString;

/* ajoute un utilisateur à la HashMap des utilisateurs du serveur. 
 * Cette fonction consiste à faire des allocation dynamiques pour les différents 
 * pour que l'utilisateur passé en parametre puisse être modifié par la suite */
void addToHashMapUserString(hashMapUserString* map, utilisateur key, char* value);

//fonction pour obtenir de la HashMap la valeur du string associé à un utilisateur (pour le moment ce string correspond a si il est admin ou non) 
char* getFromHashMapUserString(hashMapUserString* map, utilisateur* key);

//cette fonction permet de parcourir un string en d'en extraire en sous string entre l'indice de départ et un delimiteur
void recupereString(char ligne[BUFSIZ], char string[BUFSIZ], int* start, char delimiteur);

//fonction qui cherche un utilisateur par son nom et son prenom
utilisateur* getUserWithNomPrenom(hashMapUserString* map, char* nom, char* prenom);

//fonction qui cherche un utilisateur par son login
utilisateur* getUserWithLogin(hashMapUserString* map, char* login);

//retourne la position du curseur pour être au debut de la ligne de l'utilisateur recherché dans le fichier csv
int getUserLineWithNomPrenom(char* nomParam, char* prenomParam);

//fonction pour savoir si l'utilisateur est administrateur
int isUserAdmin(hashMapUserString mapUtilisateurs, utilisateur* user);

/* fonction pour savoir si le mot de passe est valide. En faisant appel à la fonction getUserWithLogin
 * strcmp compare le mot de passe passé en paramètre avec le mot de passe de l'utilisateur. */
int isMotDePasseValide(hashMapUserString mapUtilisateurs, char* login, char* password);

#endif