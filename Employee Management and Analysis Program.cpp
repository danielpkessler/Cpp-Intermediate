/*
 
 Fichier : TP3 - C
 Auteur : Daniel Kessler
 Cours : IFT 1166
 Derniere modification : 28 juin 2023
 
 But du programme :
 
 1. Lire le fichier txt, creer une conteneur de liste
 des employes dans l'ordre FIFO (premier rentre, premier sorti).
 2. Afficher le premier et le dernier employe
 en surchargeant l'operateur d'affichage.
 3. Modifier le sexe de l'employe numero 542
 (sexe feminin) avec la recherche sequentielle.
 4. Trier la liste selon les numeros des employes.
 5. Modifier le salaire de l'employe numero 270
 (1234.50) avec la recherche sequentielle.
 6. Supprimer le premier et le dernier employe.
 7. Compter et afficher : le nombre de femmes
 et le nombre d'hommes.
 8. Calculer la salaire hebdomadaire moyen des hommes.
 9. Determiner et afficher les informations de employes
 ayant du sexe feminin ayant le plus haut salaire.
 10. Afficher les cinq premiers employes dans la liste.
 
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
using namespace std;

class Employe {
private:
    char sexe;     // Sexe de l'employe
    int numero;    // Numéro de l'employe
    double heures; // Nombre d'heures travaillees par semaine
    float tauxHor; // Taux horaire (salaire par heure)
    
public:
    
    /* Constructeur de la classe Employe qui
     initialise les attributs de l'employe. */
    Employe(char sexe, int numero, double heures, float tauxHor);
    
    // Methodes "getter".
    int getNumero() const { return numero; }
    char getSexe() const { return sexe; }
    double getHeures() const { return heures; }
    float getTauxHor() const { return tauxHor; }
    double getSalaireHebdo() const { return heures * tauxHor; }
    
    // Methodes "setter".
    void setSexe(char sexe) { this->sexe = sexe; }
    void setHeures(double heures) { this->heures = heures; }
    void setTauxHor(float tauxHor) { this->tauxHor = tauxHor; }
    
    // Cette fonction surcharge l'operateur << pour afficher un objet Employe.
    friend ostream& operator<<(ostream& os, const Employe& employe);
    
    // Cette fonction surcharge l'operateur < pour comparer deux objets Employe.
    bool operator<(const Employe& autre) const {
        return numero < autre.numero;
    }
};

// Constructeur de la classe Employe.
Employe::Employe(char sexe, int numero, double heures, float tauxHor) {
    this->sexe = sexe;
    this->numero = numero;
    this->heures = heures;
    this->tauxHor = tauxHor;
}

// Definition de la surcharge de l'operateur << de la classe Employe.
ostream& operator<<(ostream& os, const Employe& employe) {
    os << "    - Sexe             : " << (employe.sexe == 'F' ? "Feminin" : "Masculin") << "\n"
    << "    - Numero d'Employe : " << employe.numero << "\n"
    << "    - Heures / Semaine : " << setprecision(1) << fixed << employe.heures << "\n"
    << "    - Taux Horaire     : " << setprecision(2) << fixed << employe.tauxHor << endl;
    return os;
}

// Fonction d'affichage des informations des employes.
void afficher(const list<Employe>& liste, const string& message, bool entete = false) {
    if (entete) {
        cout << "-----------------------------------------------------" << endl;
        cout << setw(10) << "No. PERS" << setw(7) << "SEXE" << setw(12) << "NUMERO" << setw(8) << "HEURES" << setw(15) << "TAUX HORAIRE" << endl;
        cout << "-----------------------------------------------------" << endl;
    }
    
    int index = 1;
    for (const Employe& employe : liste) {
        cout << setw(6) << index++
        << setw(14) << (employe.getSexe() == 'F' ? "Feminin" : "Masculin")
        << setw(8) << employe.getNumero()
        << setw(8) << setprecision(1) << fixed << employe.getHeures()
        << setw(12) << setprecision(2) << fixed << employe.getTauxHor()
        << endl;
    }
    cout << endl;
}

/* 1. Fonction pour lire et remplire une liste
 d'objets Employe en fonction d'un fichier txt. */
void lireRemplir(const string& nomFichier, list<Employe>& liste) {
    ifstream aLire(nomFichier);
    if (!aLire) {
        
        // Si on n'a pas reussi a lire le fichier le message suivant sera affiche.
        cout << "Erreur lors de l'ouverture du fichier: " << nomFichier << endl;
        return;
    }
    
    string ligneLue;
    
    /* On utilise une boucle while pour lire chaque ligne du fichier txt.
     On utilise la fonction getLine pour extrire une ligne du fichier
     et la stocker dans ligneLue. */
    while (getline(aLire, ligneLue)) {
        
        /* Les substrings suivants sont utilises pour extraire
         les chaines de caracteres necessaires pour faire la
         lecture de chaque composante du fichier txt. */
        char sexe = ligneLue[0];
        int numero = stoi(ligneLue.substr(5, 4));
        float heures = stof(ligneLue.substr(14, 5));
        float tauxHor = stof(ligneLue.substr(22, 6));
        
        /* Un objet Employe est genere avec l'extraction des informations
         et ajoute a la liste grace a la fonction push_back. */
        liste.push_back(Employe(sexe, numero, heures, tauxHor));
    }
    
    aLire.close();
}

/* 2. Fonction pour determiner et afficher les informations
 du premier et dernier employe dans une liste. */
// La fonction prend reference a une liste d'employes.
void premierDernier(const list<Employe>& liste) {
    if (liste.empty()) {
        
        // On verifie que la liste ne soit pas vide.
        cout << "La liste est vide." << endl;
        return;
    }
    
    /* liste.front() renvoie un iterateur qui pointe vers le premier element
     de la liste et liste.back() pour le dernier element de la liste. */
    cout << "\nINFORMATION DU PREMIER EMPLOYE : \n" << liste.front() << endl;
    cout << "INFORMATION DU DERNIER EMPLOYE : \n" << liste.back() << endl;
}

/* 3. Fonction pour modifier le sexe d'un employe dans une liste
 (en fonction du numero d'employe) - utilise la recherche sequentielle */
// La fonction prend reference a une liste d'employes et au numero d'employe

void modifierSexe(list<Employe>& liste, int numero) {
    
    /* La fonction utilise un iterateur il, pour chaque iteration
     on verifie si le numero de l'employe est le meme que celui du
     numero choisi. */
    for (list<Employe>::iterator il = liste.begin(); il != liste.end(); ++il) {
        
        /* Si le numero correspond au numero voulu, on utilise la
         methode getSexe pour changer le sexe de l'employe voulu. */
        if (il->getNumero() == numero) {
            il->setSexe('F');
            break;
        }
    }
}


/* 5. Fonction de recherche sequentielle dans une liste d'employes
 pour trouver un employe voulu en fonction de son numero d'employe. */
// La fonction prend reference a une liste d'employes et au numero d'employe.
list<Employe>::iterator rechSeq(list<Employe>& liste, int numero) {
    
    // On utilise une boucle for pour parcourir la liste avec un iterateur il.
    for (list<Employe>::iterator il = liste.begin(); il != liste.end(); ++il) {
        
        /* On verifie si l'employe a le numero qui correpond au numero
         d'employe voulu. Si l'employe est trouve l'iterateur pointe
         vers l'employe. */
        if (il->getNumero() == numero) {
            return il;
        }
    }
    return liste.end();
}

// 6. Fonction pour supprimer le premier et dernier employe dans une liste.
// La fonction prend reference a une liste d'employes.
void suppPremDern(list<Employe>& liste) {
    
    // On verifie si la liste est vide ou non
    if (!liste.empty()) {
        
        /* On utilise la methode erase pour effacer le premier
         element avec l'iterateur liste.begin(). */
        liste.erase(liste.begin());
        
        /* On utilise la methode erase pour effacer le dernier
         element avec l'iterateur --liste.end(). */
        liste.erase(--liste.end());
    }
}

// 7. Fonction pour compter le nombre de hommes et femmes dans une liste.
// La fonction prend reference a une liste d'employes,
void compteurGenre(const list<Employe>& liste) {
    int femmes = 0;
    int hommes = 0;
    for (const Employe& employe : liste) {
        
        /* On utilise la methode getSexe pour verifier si l'employe
         est une femme ('F'). Si ceci est le cas, le compteur des
         femmes (femmes++) augmente. Dans le cas contraire (else),
         le compteur des hommes (hommes++) augmente. */
        if (employe.getSexe() == 'F') {
            femmes++;
        } else {
            hommes++;
        }
    }
    cout << "\nOn trouve " << femmes << " femmes dans le fichier." << endl;
    cout << "On trouve " << hommes << " hommes dans le fichier." << endl;
}

/* 8. Fonction pour calculer le salaire hebdomadaire moyen des
 hommes dans une liste.
 La fonction prend reference a une liste d'employes. */
double salMoyH(list<Employe> &liste) {
    double sommeSalaireH = 0.0;
    int compteur = 0;
    
    // On itere tous les employes de la liste avec une iterateur il.
    for (list<Employe>::iterator il = liste.begin(); il != liste.end(); ++il) {
        
        /* On verifie le sexe de l'employe avec la methode getSexe.
         Si l'employe est un homme ('M'), on ajoute le salaire
         hebdomadaire de cet employe a la somme du salaire des hommes
         (sommeSalaireH). Aussi le compteur augmente. */
        if (il->getSexe() == 'M') {
            sommeSalaireH += il->getSalaireHebdo();
            compteur++;
        }
    }
    if (compteur == 0) {
        return 0.0;
    } else {
        
        /* On retourne la moyenne du salaire des hommes en divisant
         la somme des salaires des hommes par le nomnbre d'hommes
         (compteur). */
        return sommeSalaireH / compteur;
    }
}

// 9. Fonction pour trouver la femme ayant le salaire hebdomadaire le plus eleve.
// La fonction prend reference a une liste d'employes.
void salFem(list<Employe>& liste) {
    double salaireEleve = 0.0;
    
    // Creation d'objet empRiche, avec des parametres definis.
    Employe empRiche('F', 0, 0.0, 0.0);
    
    // On itere tous les employes de la liste avec une iterateur il.
    for (list<Employe>::iterator il = liste.begin(); il != liste.end(); ++il) {
        
        /* On verifie le sexe de l'employe avec la methode getSexe et on
         verifie aussi si le salaire hebdomadaire est superieur a tous
         les autres salaires toruves precedemment.
         Une fois que la fonction parcourt toute la liste, la femme
         avec le salaire plus eleve sera retournee (il faut que les
         deux conditions precedentes soient satisfaites). */
        if (il->getSexe() == 'F' && il->getSalaireHebdo() > salaireEleve) {
            salaireEleve = il->getSalaireHebdo();
            empRiche = *il;
        }
    }
    
    if (salaireEleve > 0.0) {
        cout << "\nL'employée du sexe féminin avec le salaire hebdomadaire le plus élevé a les informations suivantes : \n";
        cout << empRiche << endl;
    }
    else {
        cout << "\nAucune employée du sexe féminin trouvée.\n";
    }
}

/* 10. Fonction pour trouver et afficher les informatons des 5 premieres
 personnes dans une liste.
 La fonction prend reference a une liste d'employes. */
void cinq(const list<Employe>& liste) {
    
    // Liste vide pour stocker les informatiosn des 5 premiers employes de la liste.
    list<Employe> cinq;
    int compteur = 0;
    
    /* Parcourt la liste d'employes jusqu'à la fin de la liste ou
     jusqu'au point ou on a trouve les 5 employes. */
    for (list<Employe>::const_iterator il = liste.begin(); il != liste.end(); ++il) {
        
        // Ajoute l'employe courant à la liste.
        cinq.push_back(*il);
        compteur++;
        
        /* Verifie si le nombre d'employés ajoutés est egal à 5,
         pour arreter la boucle. */
        if (compteur >= 5) {
            break;
        }
    }
    
    // Affiche la liste des 5 premiers employés.
    afficher(cinq, "Cinq premiers employés", true);
}


int main() {
    
    // Creation d'une liste vide d'employes.
    list<Employe> liste;
    
    /* 1. On appelle la fonction lireRemplir pour lire le contenu du
     fichier txt ainsi que pour remplir la liste avec les employes. */
    lireRemplir("/Users/dpkessler/Documents/Academic/E23/IFT 1166/TP3/emp_e23.txt", liste);
    
    /* 2. Appelle la foncton premierDernier pour afficher
     l'information du premier et dernier employe de la liste. */
    premierDernier(liste);
    
    /* 3. Appelle la fonction modifierSexe pour modifier le sexe de
     l'employe avec le numero 542. */
    modifierSexe(liste, 542);
    
    /* 4. Tri de la liste d'employes en fonction du numero des
     employes avec la methode sort(). */
    liste.sort();
    
    /* Appelle la fonction rechSeq pour faire une recherche
     sequentielle de l'employe avec le numero 270 et retourne
     un iterateur qui pointe vers l'employe 270. */
    list<Employe>::iterator it = rechSeq(liste, 270);
    
    /* 5. On modifie le taux horaire de l'employe 270 pour
     obtenir le nouveau salaire hebdomadaire. */
    if (it != liste.end()) {
        float newSalaire = 1234.50;
        it->setTauxHor(newSalaire / it->getHeures());
    }
    
    /* 6. Appelle la fonction suppPremDern pour eliminer le
     premier et le dernier employe de la liste. */
    suppPremDern(liste);
    
    /* 7. Appelle la fonction compteurGenre pour compter et afficher
     combien de femmes et d'hommes sont trouves dans le fichier
     (et donc, dans la liste). */
    compteurGenre(liste);
    
    /* 8. On calcule la moyenne des salaires des hommes trouves
     dans la liste. */
    double moyenne = salMoyH(liste);
    cout << "\nLe salaire hebdomadaire moyen des hommes est de : " << moyenne << "\n" << endl;
    
    /* 9. On appelle la fonction salFem pour determiner et afficher
     la femme ayant le salaire le plus eleve. */
    salFem(liste);
    
    /* 10. On affiche les informations des cinq premiers employes
     dans la liste apres toutes les modifications de la liste
     (suppressions, tri, ...) */
    cout << "\nVoici l'information des cinq premières personnes trouvées dans la liste après le tri :\n\n";
    cinq(liste);
    
    return 0;
    
}


/*
 
 EXECUTION :
 
 
 INFORMATION DU PREMIER EMPLOYE :
 - Sexe             : Masculin
 - Numero d'Employe : 357
 - Heures / Semaine : 39.0
 - Taux Horaire     : 20.25
 
 INFORMATION DU DERNIER EMPLOYE :
 - Sexe             : Masculin
 - Numero d'Employe : 1067
 - Heures / Semaine : 42.0
 - Taux Horaire     : 32.25
 
 
 On trouve 43 femmes dans le fichier.
 On trouve 47 hommes dans le fichier.
 
 Le salaire hebdomadaire moyen des hommes est de : 654.19
 
 
 L'employée du sexe féminin avec le salaire hebdomadaire le plus élevé a les informations suivantes :
 - Sexe             : Feminin
 - Numero d'Employe : 270
 - Heures / Semaine : 38.0
 - Taux Horaire     : 32.49
 
 
 Voici l'information des cinq premières personnes trouvées dans la liste après le tri :
 
 -----------------------------------------------------
 No. PERS   SEXE      NUMERO  HEURES   TAUX HORAIRE
 -----------------------------------------------------
 1      Masculin      45    40.0       20.25
 2      Masculin      50    38.0       10.25
 3      Masculin      67    42.0       15.75
 4      Masculin      71    37.0       20.25
 5      Masculin      87    25.2       37.00
 
 Program ended with exit code: 0
 
 */
