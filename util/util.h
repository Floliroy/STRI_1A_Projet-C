#ifndef __UTIL_H__
#define __UTIL_H__

//Constantes correspondants aux différents actions possible
#define ACTION_CONNEXION 1
#define ACTION_DECONNEXION 2
#define ACTION_AJOUTE_UTILISATEUR 3
#define ACTION_MODIFIE_UTILISATEUR 4
#define ACTION_SUPPRIME_UTILISATEUR 5
#define ACTION_CREE_ANNUAIRE 6
#define ACTION_AJOUTE_DANS_ANNUAIRE 7
#define ACTION_SUPPRIME_DE_ANNUAIRE 8
#define ACTION_SUPPRIME_ANNUAIRE 9
#define ACTION_CONSULTE_ANNUAIRE 10
#define ACTION_CONSULTE_AUTRE_ANNUAIRE 11

//Constantes concernant les codes de retour / d'erreur
#define CODE_CONNEXION_REUSSI_USER 10
#define CODE_CONNEXION_REUSSI_ADMIN 11
#define CODE_CONNEXION_PAS_OK 12
#define CODE_DECONNEXION 13

#define CODE_ACTION_INCONNU 20
#define CODE_ACTION_REUSSI 21
#define CODE_ACTION_IMPOSSIBLE 22

#define CODE_CHAMPS_MANQUANTS_INVALIDES 30
#define CODE_USER_ANNUAIRE_EXISTANT 31
#define CODE_USER_ANNUAIRE_INTROUVABLE 32

#define CODE_CONSULTE_ANNUAIRE 40

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

/** (Florian)
 * Ajoute à la HashMap<String,String> passé en paramètre une clé et une valeur.
 * 
 * @param map La HashMap dans laquelle on ajoutera le nouvel élément
 * @param key La clé pour cet élément de la HashMap
 * @param value La valeur pour cet élément de la HashMap
 **/
void addToHashMapStringString(hashMapStringString* map, char* key, char* value);

/** (Florian)
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

/** (Florian)
 * Ajoute à la HashMap<utilisateur,String> passé en paramètre une clé et une valeur.
 * 
 * @param map La HashMap dans laquelle on ajoutera le nouvel élément
 * @param key La clé pour cet élément de la HashMap
 * @param value La valeur pour cet élément de la HashMap
 **/
void addToHashMapUserString(hashMapUserString* map, utilisateur key, char* value);

/** (Florian)
 * Recupère une HashMap<utilisateur,String> de la HashMap passé en paramètre en fonction de la clé passée.
 * 
 * @param map La HashMap dans laquelle on cherche la valeur
 * @param key La clé de l'élément recherché
 * @return Renvoit la valeur correspondante à la clé, NULL si on ne trouve rien
 **/
char* getFromHashMapUserString(hashMapUserString* map, utilisateur* key);

/** (Florian)
 * Permet de copier un fichier dans un autre sauf une ligne
 * 
 * @param fileBase Le fichier a copier
 * @param fileNew Le fichier de destination
 * @param ligne La position du curseur de la ligne a ne pas copier
 **/
void copieSaufLigne(FILE* fileBase, FILE* fileNew, int ligne);

#endif