#include <iostream>
using namespace std;


// 2. Patron de Fonction
template <class T>
void compteur(T tableau[], int nbPers, T borne, int &n) {
    n = 0;
    for(int i = 0; i < nbPers; i++) {
        if(tableau[i] >= borne) {
            n++;
        }
    }
}


// 3. Fonction dont deux parametres sont transmis par pointeurs
template <class T>
void minMax(T tableau[], int nbPers, T *ptrMin, T *ptrMax) {
    *ptrMin = tableau[0];
    *ptrMax = tableau[0];
    for (int i = 1; i < nbPers; i++) {
        if (tableau[i] < *ptrMin) {
            *ptrMin = tableau[i];
        }
        if (tableau[i] > *ptrMax) {
            *ptrMax = tableau[i];
        }
    }
}


// 4. Fonction dont un des parametres est transmis par reference
template <class T>
void moyenne(T tableau[], int nbPers, float &moy) {
    float somme = 0.0;
    
    for(int i = 0; i < nbPers; i++) {
        somme += tableau[i];
    }
    moy = somme / nbPers;
}


int main(int argc, const char * argv[]) {
    
    int age[] = {27, 35, 41, 18, 25, 30, 54, 50};
    float taille[] = {1.72, 1.65, 1.58, 1.76, 1.69, 1.54, 1.83, 1.71};
    float poids[] = {65.3, 67.1, 74.8, 60.7, 72.3, 56.4, 66.9, 72.1};
    int nbPers = sizeof(age)/sizeof(int);
    
    
    // 1. Affichage des trois tableaux
    cout << "1. Contenu des trois tableaux\n\n";
    cout << "Age |  Taille | Poids\n";
    cout << "---------------------\n";
    for(int i = 0; i < nbPers; i++) {
        cout << age[i] << "  |  " << taille[i] << "   |  " << poids[i] << "\n";
    }
    
    
    // 2. Affichage du nombre de personnes depassant les bornes des variables voulues
    int nbAdultes, borneTaille, bornePoids;
    
    int ageVoulu = 18;
    cout << "\n\n2. Affichage des personnes depassant les bornes (18 ans, 1.73 metres et 70 kg)\n\n";
    compteur(age, nbPers, ageVoulu, nbAdultes);
    cout << "a. Nombre d'adultes ayant " << ageVoulu << " ans ou plus : " << nbAdultes << endl;
    
    float tailleVoulue = 1.73;
    compteur(taille, nbPers, tailleVoulue, borneTaille);
    cout << "b. Nombre de personnes ayant une taille superieure ou egale a " << tailleVoulue << " metre(s) : " << borneTaille << endl;
    
    float poidsVoulu = 70.00;
    compteur(poids, nbPers, poidsVoulu, bornePoids);
    cout << "c. Nombre de personnes ayant un poids superieur ou egal a " << poidsVoulu << " kg : " << bornePoids << endl;
    
    
    // 3. Affichage des variables maximales et miminales
    cout << "\n\n3. Variables minimales et maximales (age, taille et poids)\n\n";
    int ageMin, ageMax;
    float tailleMin, tailleMax, poidsMin, poidsMax;

    minMax(age, nbPers, &ageMin, &ageMax);
    cout << "a. L'age minimal est de " << ageMin << " ans et l'age maximal est de " << ageMax << " ans " << endl;

    minMax(taille, nbPers, &tailleMin, &tailleMax);
    cout << "b. La taille minimale est de " << tailleMin << " metre(s) et la taille maximale est de " << tailleMax << " metre(s) " << endl;

    minMax(poids, nbPers, &poidsMin, &poidsMax);
    cout << "c. Le poids minimal est de " << poidsMin << " kg et le poids maximal est de " << poidsMax << " kg " << endl;
    
    
    // 4. Affichage des moyennes des variables
    cout << "\n\n4. Moyennes des variables (age, taille et poids)\n";
    float ageMoyen, tailleMoyenne, poidsMoyen;
    moyenne(age, nbPers, ageMoyen);
    moyenne(taille, nbPers, tailleMoyenne);
    moyenne(poids, nbPers, poidsMoyen);

    cout << "\na. L'age moyen est de " << ageMoyen << " ans " << endl;
    cout << "b. La taille moyenne est de " << tailleMoyenne << " metre(s) " << endl;
    cout << "c. Poids moyen est de " << poidsMoyen << " kg \n" << endl;

    return 0;
}
