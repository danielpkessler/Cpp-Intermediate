/*
 
 Fichier : TP2 - C
 Auteur : Daniel Kessler
 Cours : IFT 1166
 Date de derniere modification : 14 juin 2023
 
 But du programme :
 1. Afficher les personnes lues avec des fonctions appropriees.
 2. Determiner et afficher l'information de la personne ayant la plus grande taille.
 3. Determiner et afficher l'information de :
 a) La femme ayant le poids le plus leger
 b) L'homme ayant la plus petite taille
 4. Calculer + Afficher :
 a) Le poids moyen des femmes
 b) La taille moyenne des hommes
 5. Faire un tri rapide des personnes selon leurs numeros et afficher le contenu du tableau pers en suite.
 
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <float.h>


using namespace std; // librairie standard

class Personne
{
    private :
    char sexe ;
    float taille, poids ;
    int numero;
    public :
    
    // constructeur avec dÈfinition reportÈe
    Personne(char sexe, int numero, float taille, float poids);
    
    
    // constructeur sans paramËtre dont le corps est VIDE
    Personne()
    {
    }
    
    // Methodes d'acces
    
    int getNumero();
    char getSexe();
    float getPoids();
    void afficher();
    float getTaille();
    
};

// Fonction pour afficher les informations des personnes
void Personne::afficher()
{
    cout << "Sexe : " << (sexe == 'M' ? "Homme" : "Femme") << ", Numero : " << numero
    << ", Taille : " << taille << "m, Poids : " << poids << "kg" << endl;
}

// METHODES "GETTER"

// Implementation de la methode getTaille
float Personne::getTaille()
{
    return taille;
}

// Implementation de la methode getNumero
int Personne::getNumero()
{
    return numero;
}

// Implementation de la methode getSexe
char Personne::getSexe()
{
    return sexe;
}

// Implementation de la methode getPoids
float Personne::getPoids()
{
    return poids;
}


Personne::Personne(char sexe, int numero, float taille, float poids)
{
    this->sexe = sexe;
    this->numero = numero;
    this->taille = taille;
    this->poids = poids;
}


void lireRemplir(string nomALire, Personne pers[], int & n)
{
    const float PIED_EN_METRE = 0.3048,
    LIVRE_EN_KG = 0.454;
    int numero, nbPieds, nbPouces, nbLivres;
    float taille, poids;
    char sexe;
    
    ifstream  aLire (nomALire, ios::in); // localiser et ouvrir pour la lecture
    
    n = 0;
    while (aLire >> sexe >> numero >> nbPieds >> nbPouces >> nbLivres)
    {
        taille = (nbPieds + nbPouces /12.0) * PIED_EN_METRE;
        poids  = nbLivres * LIVRE_EN_KG ;
        pers[n++] = Personne(sexe, numero, taille, poids);
    }
    aLire.close();
}


// Fonction pour trouver la femme ayant le poids le plus leger
void femmeLeger(Personne pers[], int nbPers) {
    float poidsMin = FLT_MAX;
    int leger = -1;
    
    // On parcourt le tableau de personnes. Pour chaque iteration, la boucle for verifie si le sexe de la personne est feminin et aussi, si le poids de la personne est inferieur a poidsMin. Si ces deux crieteres sont satisfaits, la personne est une femme qui est plus legere que le reste des femmes.
    for (int i = 0; i < nbPers; i++) {
        if (pers[i].getSexe() == 'F' && pers[i].getPoids() < poidsMin) {
            poidsMin = pers[i].getPoids();
            leger = i;
        }
    }
    
    if (leger != -1) {
        // Si la femme a ete trouve, ses informations sont affichees.
        cout << "\na) Les informations de la femme ayant le poids le plus leger :\n";
        pers[leger].afficher();
    }
}


// Fonction pour trouver l'homme ayant la plus petite taille
void hommePetit(Personne pers[], int nbPers) {
    float tailleMin = FLT_MAX;
    int petit = -1;
    
    // Meme principe que la fonction precedente. Cependant, dans cette fonction, la boucle for verifie si la personne a une taille inferieure a tailleMin. Si la personne est un homme et a un poids inferieur a tailleMin, la personne trouve est l'homme avec la plus petite taille.
    for (int i = 0; i < nbPers; i++) {
        if (pers[i].getSexe() == 'M' && pers[i].getTaille() < tailleMin) {
            tailleMin = pers[i].getTaille();
            petit = i;
        }
    }
    
    if (petit != -1) {
        // Si l'homme a ete trouve, ses informations sont affichees.
        cout << "b) Les informations de l'homme ayant la plus petite taille :\n";
        pers[petit].afficher();
    }
}


// Patron de fonction pour trouver l'homme avec la plus petite taille et la femme avec la plus grande taille.
template<class T>
float moyenne(Personne pers[], int nbPers, char sexe, T Personne::*crctrstq) { // Le pointeur crctrstq pointe vers la caracteristique de la personne dont on veut calculer la moyenne. Puisque qu'on utilise la classe T, on peut evaluer tout type (int, float, char, const). Ce pointeur peut pointer vers la taille ou le poids d'une personne.
    float somme = 0.0; // Somme des valeurs de la caracteristique voulue pour toutes les personnes du sexe voulu
    int compteur = 0; // On compte le nombre de personnes du sexe voulu
    // Boucle for pour parcourir le tableau de personnes. Pour toute personne dans le tableau, on verifie si le sexe de celle-ci est le meme que le sexe voulu. Si le sexe voulu est le meme que celui de la personne, le coompteur est incremente.
    for (int i = 0; i < nbPers; i++) {
        if (pers[i].getSexe() == sexe) {
            somme += (pers[i].*crctrstq)();
            compteur++;
        }
    }
    return somme / compteur; // A la fin de la boucle, avec un return on calcule la moyenne : somme divisee par le nombre de personnes qui correspondent aux sexe voulu.
}


/* Patron de fonction
 La fonction permuter prend deux références à des objets (A et B) de type T. La fonction crée une variable temporaire (tempo) pour garder la valeur de A, puis elle accorde a A la valeur de B. Ensuite la fonction accorde à B la valeur gardee dans tempo. À la fin, on a echange les valeurs de A et B. */
template <class T>
void permuter(T& A, T& B) {
    T tempo = A;
    A = B;
    B = tempo;
}


// Fonction pour partitionner le tableau. Cela est necessaire pour faire le tri rapide.
int partitionner(Personne tableau[], int debut, int fin) {
    int g = debut, d = fin;
    int valPivot = tableau[debut].getNumero(); // On choisit une valeur pivot (valeur du numero de la premiere personne du tableau)
    
    // On deplace les indices de g et d. g est deplace vers la droite lorsque la valeur du numero de la personne ayant la position g est <= a la valeur du pivot. d est deplace vers la gauche lorsque la valeur du numero de la personne ayant la position d est > a la valeur du pivot.
    do {
        while (g <= d && tableau[g].getNumero() <= valPivot) g++;
        while (tableau[d].getNumero() > valPivot) d--;
        
        if (g < d) // Si g < d, on utilise la fonction permuter pour echanger les personnes ayant la position g avec les personnes ayant la posititon d du tableau.
            permuter(tableau[g], tableau[d]);
        
    } while (g <= d);
    
    permuter(tableau[d], tableau[debut]); // On utilise la fonction permuter pour echanger la personne ayant la position d avec la premiere personne au debut.
    return d;
    // A la fin de l'execution de cette fonction, le tableau est partitionne : les personnes ayant un numero inferieur a celui du pivot sont a gauche de d. Les personnes ayant un numero superieur au pivot sont a droite de d. Le pivot se retrouve a la position de d.
}


// Fonction pour effectuer le tri rapide, on veut trier les personnes en fonction de leur numero (ordre ascendant).
void quickSort(Personne tableau[], int gauche, int droite) {
    if (droite > gauche) { // Si droite > gauche, on tri le tableau
        int indPivot = partitionner(tableau, gauche, droite); // On utilise la fonction partitionner pour partitionner le tableau en fonction d'un pivot (le numero de la premiere personne du tableau)
        quickSort(tableau, gauche, indPivot - 1); // On partitionne la partie tableau qui est a gauche du pivot
        quickSort(tableau, indPivot + 1, droite); // On partitionne la partie tableau qui est a droite du pivot
    }
}


// Fonction pour effectuer la recherche dichotomique, on divise le tableau dans deux sous-tableaux (milieu).
int rechDicho(Personne tableau[], int taille, int numero) {
    int debut = 0;
    int fin = taille - 1;
    
    while (debut <= fin) { // boucle while se poursuit lorsque debut <= fin.
        int milieu = (debut + fin) / 2; // a chaque iteration l'indice milieu est calcule comme la moyenne de debut et de fin.
        
        if (tableau[milieu].getNumero() == numero) { // Si le numero de la personne a l'indice milieu = au numero cherche, le numero a ete trouve.
            return milieu;
        } else if (tableau[milieu].getNumero() < numero) { // Si le numero de la personne a l'indice milieu est < au numero cherche, debut est deplace avant milieu.
            debut = milieu + 1;
        } else { // Si le numero de la personne a l'indice milieu est > au numero cherche, fin est deplace avant milieu.
            fin = milieu - 1; // Si le numero n'est pas toruve, -1 est retourne
        }
    }
    return -1; // On retourne -1 si la clé n'est pas trouvée
}



int main() {
    
    const int MAX_PERS = 30 ;
    Personne pers[MAX_PERS];
    int nbPers;
    int empVoulu[] = {4433, 2879, 9876};
    
    // APPELS
    
    lireRemplir("/Users/dpkessler/Desktop/TP2C/imp_e23.txt",pers, nbPers);
    
    cout << "On a lu l'information de " << nbPers << " personnes.\n\n";
    
    cout << "\n1. AFFICHAGE DU TABLEAU PERS :\n\n";
    for (int i = 0; i < nbPers; ++i) {
        cout << i+1 << ") ";
        pers[i].afficher();
    }
    
    // Personne avec la plus grande taille
    Personne* plusGrandePers = &pers[0]; // On initialise un pointeur vers la premiere personne du tableau. Personne* = pointeur et &pers[0] = garde l'adresse de la premiere personne du tableau
    for (int i = 1; i < nbPers; ++i) { // Boucle for qui parcourt le reste du tableau a partir de la deuxieme personne (indice 1)
        if (pers[i].getTaille() > plusGrandePers->getTaille()) { // On verifie si la taille de la personne voulue est plus grande que celle de la plus grande (plusGrandePers). On utilise -> pour acceder aux membres d'un objet a travers un pointeur qui pointe vers cet objet.
            plusGrandePers = &pers[i]; // La personne actuelle est la plus grande, donc le pointeur plusGrandPers pointe cette personne maintenant.
        }
    }
    
    // Afficher les informations de la personne avec la plus grande taille
    cout << "\n\n2. LA PERSONNE AYANT LA PLUS GRANDE TAILLE A LES INFORMATIONS SUIVANTES : \n" << endl;
    plusGrandePers->afficher();
    
    
    // Appel des fonctions pour trouver et afficher la femme ayant le poids le plus leger et l'homme ayant la plus petite taille
    cout << "\n\n3. VARIABLES MINIMALES :" << endl;
    femmeLeger(pers, nbPers);
    hommePetit(pers, nbPers);
    
    
    // Calculer et afficher le poids moyen des femmes et la taille moyenne des hommes
    cout << "\n\n4. MOYENNE DES VARIABLES :" << endl;
    float poidsMoyH = moyenne(pers, nbPers, 'F', &Personne::getPoids);
    cout << "\na) Le poids moyen des femmes est de : " << poidsMoyH << " kg" << endl;
    
    float tailleMoyF = moyenne(pers, nbPers, 'M', &Personne::getTaille);
    cout << "b) La taille moyenne des hommes est de : " << tailleMoyF << " m\n" << endl;
    
    // Tri du tableau pers en fonction du numéro
    quickSort(pers, 0, nbPers - 1);
    
    // Reaffichage du tableau pers après le tri
    cout << "\n5. REAFFICHAGE DU TABLEAU APRES LE TRI RAPIDE : \n" << endl;
    for(int i = 0; i < nbPers; i++) {
        cout << i+1 << ") ";
        pers[i].afficher();
    }
    
    // Recherche dichotomique des personnes ayant les numeros : 4433, 2879 et 9876.
    cout << "\n\n6. RECHERCHE DICHOTOMIQUE DES PERSONNES VOULUES, EN FONCTION DE LEUR NUMERO :\n" << endl;
    for (int i = 0; i < 3; i++) { // Boucle for qui parcourt les 3 premiers elements du tableau empVoulu.
        int indice = rechDicho(pers, nbPers, empVoulu[i]);
        if (indice != -1) { // La fonction rechDicho retourne l'indice de l'element trouve, si l'element n'est pas trouve, elle retourne -1 (si l'indice est different de -1, la personne a ete trouvee).
            cout << " - La personne avec le numero " << empVoulu[i] << " se trouve à l'indice : " << indice << endl;
            cout << "   Informations sur l'employe : " << endl;
            pers[indice].afficher();
        } else { // Si l'indice est egal a -1, la personne n'a pas ete trouvee.
            cout << " - La personne avec le numéro " << empVoulu[i] << " n'a pas ete trouvé dans le tableau.\n" << endl;
        }
    }
    
    
    return 0;
    
    
}

/*
 
 EXECUTION :
 
 On a lu l'information de 20 personnes.
 
 
 1. AFFICHAGE DU TABLEAU PERS :
 
 1) Sexe : Femme, Numero : 2187, Taille : 1.6764m, Poids : 81.72kg
 2) Sexe : Homme, Numero : 4148, Taille : 1.8034m, Poids : 83.99kg
 3) Sexe : Homme, Numero : 2233, Taille : 1.8542m, Poids : 85.352kg
 4) Sexe : Femme, Numero : 4433, Taille : 1.4732m, Poids : 57.658kg
 5) Sexe : Femme, Numero : 2108, Taille : 1.8034m, Poids : 74.91kg
 6) Sexe : Femme, Numero : 4100, Taille : 1.651m, Poids : 54.026kg
 7) Sexe : Femme, Numero : 2176, Taille : 1.8796m, Poids : 84.898kg
 8) Sexe : Homme, Numero : 5423, Taille : 1.7526m, Poids : 66.738kg
 9) Sexe : Homme, Numero : 4169, Taille : 1.6764m, Poids : 55.842kg
 10) Sexe : Femme, Numero : 4177, Taille : 1.7526m, Poids : 62.652kg
 11) Sexe : Homme, Numero : 2879, Taille : 1.8796m, Poids : 86.714kg
 12) Sexe : Femme, Numero : 5477, Taille : 1.8034m, Poids : 66.738kg
 13) Sexe : Homme, Numero : 4869, Taille : 1.6002m, Poids : 73.548kg
 14) Sexe : Femme, Numero : 4354, Taille : 1.6764m, Poids : 76.726kg
 15) Sexe : Homme, Numero : 2235, Taille : 1.8796m, Poids : 85.806kg
 16) Sexe : Homme, Numero : 5444, Taille : 1.778m, Poids : 68.554kg
 17) Sexe : Femme, Numero : 4198, Taille : 1.7526m, Poids : 56.75kg
 18) Sexe : Femme, Numero : 5678, Taille : 2.0066m, Poids : 86.26kg
 19) Sexe : Femme, Numero : 1357, Taille : 1.6764m, Poids : 70.37kg
 20) Sexe : Femme, Numero : 3498, Taille : 1.4986m, Poids : 61.29kg
 
 
 2. LA PERSONNE AYANT LA PLUS GRANDE TAILLE A LES INFORMATIONS SUIVANTES :
 
 Sexe : Femme, Numero : 5678, Taille : 2.0066m, Poids : 86.26kg
 
 
 3. VARIABLES MINIMALES :
 
 a) Les informations de la femme ayant le poids le plus leger :
 Sexe : Femme, Numero : 4100, Taille : 1.651m, Poids : 54.026kg
 b) Les informations de l'homme ayant la plus petite taille :
 Sexe : Homme, Numero : 4869, Taille : 1.6002m, Poids : 73.548kg
 
 
 4. MOYENNE DES VARIABLES :
 
 a) Le poids moyen des femmes est de : 69.4998 kg
 b) La taille moyenne des hommes est de : 1.778 m
 
 
 5. REAFFICHAGE DU TABLEAU APRES LE TRI RAPIDE :
 
 1) Sexe : Femme, Numero : 1357, Taille : 1.6764m, Poids : 70.37kg
 2) Sexe : Femme, Numero : 2108, Taille : 1.8034m, Poids : 74.91kg
 3) Sexe : Femme, Numero : 2176, Taille : 1.8796m, Poids : 84.898kg
 4) Sexe : Femme, Numero : 2187, Taille : 1.6764m, Poids : 81.72kg
 5) Sexe : Homme, Numero : 2233, Taille : 1.8542m, Poids : 85.352kg
 6) Sexe : Homme, Numero : 2235, Taille : 1.8796m, Poids : 85.806kg
 7) Sexe : Homme, Numero : 2879, Taille : 1.8796m, Poids : 86.714kg
 8) Sexe : Femme, Numero : 3498, Taille : 1.4986m, Poids : 61.29kg
 9) Sexe : Femme, Numero : 4100, Taille : 1.651m, Poids : 54.026kg
 10) Sexe : Homme, Numero : 4148, Taille : 1.8034m, Poids : 83.99kg
 11) Sexe : Homme, Numero : 4169, Taille : 1.6764m, Poids : 55.842kg
 12) Sexe : Femme, Numero : 4177, Taille : 1.7526m, Poids : 62.652kg
 13) Sexe : Femme, Numero : 4198, Taille : 1.7526m, Poids : 56.75kg
 14) Sexe : Femme, Numero : 4354, Taille : 1.6764m, Poids : 76.726kg
 15) Sexe : Femme, Numero : 4433, Taille : 1.4732m, Poids : 57.658kg
 16) Sexe : Homme, Numero : 4869, Taille : 1.6002m, Poids : 73.548kg
 17) Sexe : Homme, Numero : 5423, Taille : 1.7526m, Poids : 66.738kg
 18) Sexe : Homme, Numero : 5444, Taille : 1.778m, Poids : 68.554kg
 19) Sexe : Femme, Numero : 5477, Taille : 1.8034m, Poids : 66.738kg
 20) Sexe : Femme, Numero : 5678, Taille : 2.0066m, Poids : 86.26kg
 
 
 6. RECHERCHE DICHOTOMIQUE DES PERSONNES VOULUES, EN FONCTION DE LEUR NUMERO :
 
 - La personne avec le numero 4433 se trouve à l'indice : 14
 Informations sur l'employe :
 Sexe : Femme, Numero : 4433, Taille : 1.4732m, Poids : 57.658kg
 - La personne avec le numero 2879 se trouve à l'indice : 6
 Informations sur l'employe :
 Sexe : Homme, Numero : 2879, Taille : 1.8796m, Poids : 86.714kg
 - La personne avec le numéro 9876 n'a pas ete trouvé dans le tableau.
 
 Program ended with exit code: 0
 
 */
