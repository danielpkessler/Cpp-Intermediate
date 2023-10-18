#include <iostream>
#include <iomanip>
using namespace std;

    
  void afficher(int age[], int nbCafe[], char sexe[], float taille[], int nbPers,
                   const char message[])
  {
     cout.setf(ios::fixed);
     cout.setf(ios::showpoint);
     
     cout << "\n\nContenu des 4 tableaux " << message << " :\n\n";
     cout << "indice      age     cafe   sexe   taille  " << endl ;
     
     for(int i = 0; i < nbPers; i++)
       cout << setw(3) << i << ") " << setw(10) << age[i] << setw(8) << nbCafe[i]
            << setw(6) << sexe[i] << setw(10) << setprecision(2) << taille[i]
            << endl;
     cout << endl;
        
  }
  
  
  template <class T>
  float moyenne(T tab[], int nbElem)
  { float somme = 0.0 ;
    for(int i = 0; i < nbElem ; i++)
       somme += tab[i];
  
    return somme / nbElem ;
  }


// 1. Fonction pour compter le nombre d'hommes et de femmes

void compteurSexe(char sexe[], int nbPers, int& nbHommes, int& nbFemmes)
{
    nbHommes = 0;
    nbFemmes = 0;
    for(int i = 0; i < nbPers; i++) {
        if(sexe[i] == 'M')
            nbHommes++;
        else if(sexe[i] == 'F')
            nbFemmes++;
    }
}


// 2. Patron de fonction pour determiner le nombre d'elements superieure a une borne specifique

template <class T>
void patronCompteur(T tab[], int nbElem, T borne, const char* mess)
{
    int compteur = 0;
    for(int i = 0; i < nbElem; i++) {
        if(tab[i] > borne)
            compteur++;
    }
    cout << "Le nombre de personnes " << mess << " : " << compteur << endl;
}


// 3. Patron de fonction pour determiner l'element "maximal" de chaque tableau

template <class T>
T max(T tab[], int nbElem, const char* message)
{
    T max = tab[0];
    for(int i = 1; i < nbElem; i++) {
        if(tab[i] > max)
            max = tab[i];
    }
    cout << message << " : " << max << endl;
    return max;
}


// 4. Fonction pour trier les quatre tableaux

template <class T>
void triTaille(T &x, T &y)
{
    T tempo = x;
    x = y ;
    y = tempo;
}

void trier(int age[], float taille[], int nbCafe[], char sexe[], int nbPers)
{
    for(int i = 0; i < nbPers - 1; i++) {
        int indMax = i;
        for(int j = i + 1; j < nbPers; j++)
        if (taille[j] < taille[indMax])
            indMax = j;
      if (indMax != i) {
          triTaille(taille[i], taille[indMax]);
          triTaille(age[i], age[indMax]);
          triTaille(nbCafe[i], nbCafe[indMax]);
          triTaille(sexe[i], sexe[indMax]);
      }
    }
}


int main()
{
  int age[] = { 25, 19, 41, 37, 20, 37 },
      nbCafe[] = { 3, 4, 0, 6, 3, 2 } ;
  char sexe[] = { 'F', 'M', 'F', 'F', 'M', 'F' };
  float taille[] = { 1.72, 1.84, 1.65, 1.57, 1.93, 1.85 };
  
  int nbPers = sizeof(age) / sizeof(int);
      
  afficher(age, nbCafe, sexe, taille, nbPers, " au debut");
  
  cout << "Age moyen : " << setw(6)
       << setprecision(2) << moyenne(age, nbPers) << " an(s) " << endl ;
  cout << "Consommation moyenne de cafe : " << setw(6)
       << setprecision(2) << moyenne(nbCafe, nbPers)
       << " tasse(s) par jour" << endl ;
       
  cout << "Taille moyenne : " << setprecision(2)
       << moyenne(taille, nbPers) << " metre" << endl;

// Appels pour trouver le nombre d'hommes et femmes
int nbH, nbF;
compteurSexe(sexe, nbPers, nbH, nbF);
cout << "\nLe nombre d'hommes est de     : " << nbH << endl;
cout << "Le nombre de femmes est de    : " << nbF << "\n" << endl;
    
// Appels pour trouver le nombre de personnes ayant un age superieur a 29 ans, une consommation superieure a 2 cafes par jour et dont la taille est superieure a 1.80 metre
patronCompteur(age, nbPers, 29, "dont l’âge est supérieur à 29 ans                ");
patronCompteur(nbCafe, nbPers, 2, "qui consomment plus de 2 tasses de café par jour ");
patronCompteur(taille, nbPers, 1.80f, "dont la taille est supérieure à 1.80 mètre       ");
    
// Appels pour trouver l'age maximal, la consommation de cafe par jour maximale et la taille maximale
max(age, nbPers, "\nL'age maximal est de                                   ");
max(nbCafe, nbPers, "La consommation maximale de tasses café par jour est de");
max(taille, nbPers, "La plus grande taille est de                           ");
    
// Appel pour trier les quatre tableaux en fonction de la taille
trier(age, taille, nbCafe, sexe, nbPers);
afficher(age, nbCafe, sexe, taille, nbPers, "à la suite du tri");
                                                       
  return 0;
    
}
