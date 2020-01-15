#ifndef __UTIL_H__
#define __UTIL_H__

//Constantes correspondants aux différents actions possible
#define ACTION_CONNEXION 1
#define ACTION_DECONNEXION 2
#define ACTION_AJOUTE_UTILISATEUR 3
#define ACTION_MODIFIE_UTILISATEUR 4
#define ACTION_SUPPRIME_UTILISATEUR 5

//Couleurs pour les printf en console
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

//Structure utilisateur
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

//Element d'une structure HashMap<String,String>
typedef struct{
	char* key;
	char* value;
}elementStringString;

//HashMap<String,String>
typedef struct{
	int size;
	elementStringString elem[BUFSIZ];
}hashMapStringString;

/**
 * Ajoute à la HashMap<String,String> passé en paramètre une clé et une valeur.
 * 
 * @param map La HashMap dans laquelle on ajoutera le nouvel élément
 * @param key La clé pour cet élément de la HashMap
 * @param value La valeur pour cet élément de la HashMap
 **/
void addToHashMapStringString(hashMapStringString* map, char* key, char* value);

/**
 * Recupère une valeur de la HashMap<String,String> passé en paramètre en fonction de la clé passée.
 * 
 * @param map La HashMap dans laquelle on cherche la valeur
 * @param key La clé de l'élément recherché
 * @return Renvoit la valeur correspondante à la clé, NULL si on ne trouve rien
 **/
char* getFromHashMapStringString(hashMapStringString* map, char* key);

//Element d'une structure HashMap<utilisateur,String>
typedef struct{
	utilisateur* key;
	char* value;
}elementUserString;

//HashMap<utilisateur,String>
typedef struct{
	int size; //nombre d'éléments de la structure 
	elementUserString elem[BUFSIZ];
}hashMapUserString;

/**
 * Ajoute à la HashMap<utilisateur,String> passé en paramètre une clé et une valeur.
 * 
 * @param map La HashMap dans laquelle on ajoutera le nouvel élément
 * @param key La clé pour cet élément de la HashMap
 * @param value La valeur pour cet élément de la HashMap
 **/
void addToHashMapUserString(hashMapUserString* map, utilisateur key, char* value);

/**
 * Recupère une HashMap<utilisateur,String> de la HashMap passé en paramètre en fonction de la clé passée.
 * 
 * @param map La HashMap dans laquelle on cherche la valeur
 * @param key La clé de l'élément recherché
 * @return Renvoit la valeur correspondante à la clé, NULL si on ne trouve rien
 **/
char* getFromHashMapUserString(hashMapUserString* map, utilisateur* key);


/**
 * Parcours le string ligne et extrait un sous string entre l'indice de départ et un délimiteur.
 * 
 * @param ligne String dans lequelle on va extraire notre sous string
 * @param string String que l'on souhaite extraire de ligne
 * @param start Indice de départ (on le renvoit pour pouvoir revenir dans la fonction avec un autre sous string a extraire)
 * @param delimiteur Le caractere a partir duquel on arrete d'extraire notre sous string
 **/
void recupereString(char ligne[BUFSIZ], char string[BUFSIZ], int* start, char delimiteur);

#endif