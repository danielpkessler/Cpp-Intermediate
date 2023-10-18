/*
 
 Fichier : TP3 - A
 Auteur : Daniel Kessler
 Cours : IFT 1166
 Derniere modification : 29 juin 2023
 
 But du programme :
 
 1. Afficher le tableau des cercles en utilisant la surcharge de
 l'operateur d'affichage <<
 2. Permuter c[0] et c[4] et ensuite permuter c[1] et c[3].
 3. Determiner et ensuite afficher :
 a) Le cercle avec le plus petit rayon
 b) Le cercle avec le plus grand rayon
 Il faut utiliser une seule fonction template ainsi que la surcharge
 des operateurs > et <.
 4. Trier le tableau des cercles avec le tri rapide et donc
 reafficher le tableau trie.
 
 */

#include <iostream>
#include <iomanip>
using namespace std;

const float PI = 3.14159;

class Cercle {
private:
    float rayon;
    
public:
    Cercle(float rayon = 5.7) {
        this->rayon = rayon;
    }
    
    // fonction membre
    float perimetre() const {
        return 2 * PI * rayon;
    }
    
    // Fonction membre qui calcule et retourne la surface d'un cercle.
    float surface() const {
        return PI * rayon * rayon;
    }
    
    // Fonction membre qui retourne le rayon d'un cercle.
    float getRayon() const {
        return rayon;
    }
    
    // Fonction membre pour definir un nouveau rayon : "nouvRayon".
    void setRayon(float nouvRayon) {
        rayon = nouvRayon;
    }
    
    // Surcharge d'operateurs
    
    /* Fonction de surcharge de l'operateur '<', elle permet de
     comparer les rayons de deux objets Cercle. Elle prend une
     reference a un autre objet Cercle : "autreCercle".
     Si l'objet est strictement inferieur au rayon de "autreCercle",
     la fonction retourne faux. */
    bool operator < (const Cercle& autreCercle) const {
        return this->rayon < autreCercle.rayon;
    }
    
    /* Fonction de surcharge de l'operateur '>'.
     Meme principe que la fonction precedente mais dans
     le sens contraire : si l'objet est strictement superieur
     au rayon de "autreCercle", la fonction retourne faux. */
    bool operator > (const Cercle& autreCercle) const {
        return this->rayon > autreCercle.rayon;
    }
    
    // Fonction pour afficher l'en-tête du tableau d'informations sur les cercles
    static void enTete() {
        cout << "-------------------------------------" << endl;
        cout << setw(5) << "CERCLE No." << setw(6) << "RAYON" << setw(11) << "PERIMETRE" << setw(9) << "SURFACE" << endl;
        cout << "-------------------------------------" << endl;
        
    }
    
    // afficher un cercle avec un message pertinent
    void afficher(string message = "") {
        if (message.length() > 0) {
            cout << message << " : " << endl;
            cout << " - rayon                 : " << rayon << endl;
            cout << " - perimetre             : " << perimetre() << endl;
            cout << " - surface               : " << surface() << endl << endl;
        }
        else
            cout << setw(8) << setprecision(1) << rayon
            << setw(10) << setprecision(2) << perimetre()
            << setw(9) << setprecision(2) << surface() << endl;
    }
};

// Fonction de permutation
// La fonction permute deux objets cercle
void permutation(Cercle& a, Cercle& b) {
    /* La fonction cree une variable temporaire "temp"
     pour permuter entre les objets a et b. Les valeurs
     de a et b sont echanges. */
    Cercle temp = a;
    a = b;
    b = temp;
}

// Patron de fonction pour trouver le plus grand et le plus petit rayon
template <typename T>
/* minElement et maxElement sont une reference de pointeur
 qui vont contenir le plus petit element et le plus grand
 element (respectivement). */
void minMaxElement(T* debut, T* fin, T*& minElement, T*& maxElement) {
    if (debut == fin) return;
    
    // Les pointeurs maxElement et minElement sont initialises avec debut.
    minElement = maxElement = debut;
    
    /* La fonction itere tous les elements du debut jusqu'a la fin avec
     un pointeur x. */
    for (T* x = debut; x != fin; x++) {
        /* Pour chaque iteration elle compare de la valeur pointee par
         x avec les valeurs de minElement et maxElement.
         Si x < minElem, on assigne la valeur de x a minElement. */
        if (*x < *minElement) {
            minElement = x;
        }
        // Si x > maxElem, on assigne la valeur de *x a maxElement
        if (*x > *maxElement) {
            maxElement = x;
        }
    }
    
    cout << "\n\nINFORMATION DU CERCLE RECHERCHE :\n\n";
    minElement->afficher("Cercle avec le plus petit rayon");
    maxElement->afficher("Cercle avec le plus grand rayon");
}

// Fonction de partition, etape necessaire pour le tri rapide
int partitionner(Cercle cer[], int premier, int dernier) {
    
    /* Pivot qui prend la valeur du dernier element, celui-ci divisera
     le tableau en deux parties (une partie les elements inferieurs
     au pivot et une autre avec les elements superieurs au pivot). */
    Cercle pivot = cer[dernier];
    int i = premier - 1;
    
    /* Cette boucle for itere de debut jusqu'a la
     fin en comparant chaque element avec le pivot. */
    for (int j = premier; j <= dernier - 1; j++) {
        
        /* La fonction utilise la methode d'acces getRayon
         pour acceder a la valeur du rayon de chaque objet Cercle. */
        if (cer[j].getRayon() < pivot.getRayon()) {
            i++;
            
            /* Si cer[j] a un rayon inferieur au pivot, cer[j]
             et cer[i] sont permutes avec la fonction permutation. */
            permutation(cer[i], cer[j]);
        }
    }
    
    // Derniere permutation pour placer le pivot a sa position finale.
    permutation(cer[i + 1], cer[dernier]);
    return (i + 1);
}

/* Fonction de tri rapide  Si debut < fin, il y a plus d'un element,
 on peut donc faire le tri rapide. On utilise la fonction partition
 pour diviser le tableau en 2 sous tableaux le pivot se trouve
 au milieu). */
void triRapide(Cercle cer[], int debut, int fin) {
    
    /* Si debut < fin, il y a plus d'un element,
     on peut donc faire le tri rapide. */
    if (debut < fin) {
        
        /* On utilise la fonction partition pour diviser le tableau en
         2 sous tableaux (le pivot se trouve au milieu). */
        int y = partitionner(cer, debut, fin);
        triRapide(cer, debut, y - 1);
        triRapide(cer, y + 1, fin);
    }
}

int main() {
    Cercle c[] = { Cercle(6.2), Cercle(), Cercle(9.3), Cercle(6.9),
        Cercle(4.1), Cercle(12.6), Cercle(8.4) };
    int nbCercle = sizeof(c) / sizeof(Cercle);
    
    /* Boucle for qui parcourt tout le tableau. On utilise l'operateur
     de surcharge '<<' pour afficher les informations du cercle voulu. */
    cout << "TABLEAU DE CERCLES PRELIMINAIRE :\n" << endl;
    Cercle::enTete();
    for (int i = 0; i < nbCercle; i++) {
        cout << setw(5) << i + 1 << " ";
        c[i].afficher();
    }
    
    // Les deux permutations demandees
    permutation(c[0], c[4]);
    permutation(c[1], c[3]);
    
    // Reaffichage des cercles après permutation
    cout << "\n\nTABLEAU DE CERCLES APRES LES DEUX PERMUTATIONS :\n" << endl;
    Cercle::enTete();
    for (int i = 0; i < nbCercle; i++) {
        cout << setw(5) << i + 1 << " ";
        c[i].afficher();
    }
    
    /* Appel pour determiner les cercles ayant le rayon
     le plus grand et le rayon le plus petit. */
    Cercle* minCercle;
    Cercle* maxCercle;
    minMaxElement(c, c + nbCercle, minCercle, maxCercle);
    
    triRapide(c, 0, nbCercle - 1);
    
    cout << "\n\nTABLEAU DE CERCLES APRES LE TRI RAPIDE :\n" << endl;
    Cercle::enTete();
    for (int i = 0; i < nbCercle; i++) {
        cout << setw(5) << i + 1 << " ";
        c[i].afficher();
    }
    
    cout << endl;
    return 0;
}

/*
 
 EXECUTION :
 
 
 TABLEAU DE CERCLES PRELIMINAIRE :

 -------------------------------------
 CERCLE No. RAYON  PERIMETRE  SURFACE
 -------------------------------------
     1        6        39  1.2e+02
     2        6        36    1e+02
     3        9        58  2.7e+02
     4        7        43  1.5e+02
     5        4        26       53
     6    1e+01        79    5e+02
     7        8        53  2.2e+02


 TABLEAU DE CERCLES APRES LES DEUX PERMUTATIONS :

 -------------------------------------
 CERCLE No. RAYON  PERIMETRE  SURFACE
 -------------------------------------
     1        4        26       53
     2        7        43  1.5e+02
     3        9        58  2.7e+02
     4        6        36    1e+02
     5        6        39  1.2e+02
     6    1e+01        79    5e+02
     7        8        53  2.2e+02


 INFORMATION DU CERCLE RECHERCHE :

 Cercle avec le plus petit rayon :
  - rayon                 : 4.1
  - perimetre             : 26
  - surface               : 53

 Cercle avec le plus grand rayon :
  - rayon                 : 13
  - perimetre             : 79
  - surface               : 5e+02



 TABLEAU DE CERCLES APRES LE TRI RAPIDE :

 -------------------------------------
 CERCLE No. RAYON  PERIMETRE  SURFACE
 -------------------------------------
     1        4        26       53
     2        6        36    1e+02
     3        6        39  1.2e+02
     4        7        43  1.5e+02
     5        8        53  2.2e+02
     6        9        58  2.7e+02
     7    1e+01        79    5e+02

 Program ended with exit code: 0
 
 */
