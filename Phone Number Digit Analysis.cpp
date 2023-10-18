/*
 
 Fichier : TP2 - A
 Auteur : Daniel Kessler
 Cours : IFT 1166
 Derniere modification : 14 juin 2023
 
 But du programme :
 
 1. Extraire et afficher des sous-chaines de telUdeM et telJean.
 2. Compter et afficher :
 a) Combien de fois apparait le numero 3 dans telUdeM
 b) Combien de fois apparait le numero 1 dans telUdeM
 c) Combien de fois apparait le numero 4 dans telJean
 3. Avec une fonction bool, montrer que tous les chiffres de telUdeM sont aussi presents dans telJean.
 4. Afficher les chiffres de telJean qui ne sont pas presents dans telUdeM.
 5. Trouver et afficher les chiffres impairs de telJean.
 6. Trouver et afficher les chiffres pairs de telUdeM.
 7. Determiner et afficher :
 a) Le chiffre plus petit de telUdeM
 b) Le chiffre plus petit de telJean
 
 */

#include <iostream>
#include <string>
using namespace std;


/* CHIFFRES IMPAIRS
 Cette fonction affiche les chiffres impairs contenus dans un chaine de caracteres (numero de telephone dans ce cas). La fonction utilise une boucle pour parcourir les chiffres impairs, soit : 1, 3, 5, 7, 9. Ensuite on verifie si chacun de ces chiffres est contenu dans le numero de telephone avec la methode find(). Si on retrouve le chiffre, il est ensuite affiche. */
void afficherImpairs(const string& telephone, const string& nom) { // telephone et nom sont des références vers des objets de type string
    cout << "\n5. NUMEROS IMPAIRS DU NUMERO DE TELEPHONE DE JEAN :" << endl;
    cout << "Les chiffres impairs dans " << nom << " sont :";
    for (char c = '1'; c <= '9'; c += 2) { // Boucle for qui parcourt les chiffres impairs,  elle commence à 1 et ajoute 2 à chaque itération (jusqu'a 9)
        if (telephone.find(c) != string::npos) {
            cout << " " << c;
        }
    }
}


/* CHIFFRES PAIRS
 Cette fonction est quasiment identique celle des chiffres impairs. Cependant, celle-ci cherche les chiffres pairs, soit : 0, 2, 4, 6, 8 dans le numero de telephone. */
void afficherPairs(const string& telephone, const string& nom) { // telephone et nom sont des références vers des objets de type string
    cout << "\n\n6. NUMEROS PAIRS DU NUMERO DE TELEPHONE DE L'UDEM :" << endl;
    cout << "Les chiffres pairs dans " << nom << " sont :";
    for (char c = '0'; c <= '8'; c += 2) { // Boucle for qui parcourt les chiffres pairs,  elle commence à 0 et ajoute 2 à chaque itération (jusqu'a 8)
        if (telephone.find(c) != string::npos) {
            cout << " " << c;
        }
    }
}


/* CHIFFRE PLUS PETIT :
 Cette fonction parcourt tous les caracteres dans une chaine de caracteres (String) et retourne le plus petit. Le plus petit caractere initial est nombre[0], qui est donc le premier caractere de la chaine. Si un est plus petit que chiffPetit ce caractere devient chiffPetit (chiffPetit prend la valeur de ce caractere). On fait cela pour chaque caractere dans la chaine, pour cela, le caractere le plus petit sera donc chiffPetit. */
char plusPetit(const string& nombre) { // nombre est une reference vers un string nombre, qui represente une serie de chiffres
    char chiffPetit = nombre[0];
    for (char chiffre : nombre) {
        if (chiffre < chiffPetit) {
            chiffPetit = chiffre;
        }
    }
    return chiffPetit;
}

int main(int argc, const char * argv[]) {
    
    string telUdeM = "5143436111";
    string telJean = "4501237654";
    
    /* 1. Extraire et afficher des sous-chaines de telUdeM et telJean
     Nous utilisons la methode substr() qui est utilisee pour extraire des sous-chaînes (substring) du numero de telephone. Le premier argument de substr(), qui est donc 0, est l'index de debut, et le deuxieme est la longueur de la sous-chaîne, qui est donc de 3 caracteres (on extrait donc les trois premiers caracteres). La meme loguique s'applique au reste du code.
     
     a) Le telephone de l'Universite de Montreal : (514) 343-6111 */
    string codeRegionUdeM = telUdeM.substr(0, 3), echangeUdeM = telUdeM.substr(3, 3), numeroUdeM = telUdeM.substr(6);
    cout << "1. AFFICHAGE DES DEUX TELEPHONES AVEC UN FORMAT SPECIFIQUE :" << endl;
    cout << "a) Le telephone de l'Universite de Montreal : " "(" << codeRegionUdeM << ") " << echangeUdeM << "-" << numeroUdeM << endl;
    
    // b) Le telephone de Jean : (450) 123-7654
    string codeRegionJean = telJean.substr(0, 3), echangeJean = telJean.substr(3, 3), numeroJean = telJean.substr(6);
    cout << "b) Le telephone de Jean : " "(" << codeRegionJean << ") " << echangeJean << "-" << numeroJean << "\n" << endl;
    
    
    //  2. Compter et afficher :
    // a) Cette partie du code compte combien de fois les chiffres 3 et 1 apparaissent dans le numero de telephone de l'UdeM.
    int chiff3 = 0, chiff1 = 0, chiff4 = 0;
    
    for (char digit : telUdeM) {
        if (digit == '3')
            chiff3++;
        
        else if (digit == '1')
            chiff1++;
    }
    
    // b) Cette partie du code compte combien de fois le chiffre 4 apparaissent dans le telephone de Jean
    for (char digit : telJean) {
        if (digit == '4')
            chiff4++;
    }
    
    cout << "2. AFFICHAGE DE COMBIEN DE FOIS APPARAISSENT DES CHIFFRES VOULUS DANS UN NUMERO :" << endl;
    cout << "a) Le chiffre 3 apparait " << chiff3 << " fois dans le telephone de l'UdeM." << endl;
    cout << "b) Le chiffre 1 apparait " << chiff1 << " fois dans le telephone de l'UdeM." << endl;
    cout << "c) Le chiffre 4 apparait " << chiff4 << " fois dans le telephone de Jean." << endl;
    
    
    // 3. Verifier si tous les chiffres dans telUdeM sont presents dans telJean
    bool chiffUdeM = true;
    for (char chiff : telUdeM) {
        if (telJean.find(chiff) == string::npos) {
            chiffUdeM = false;
            break;
        }
    }
    
    cout << "\n3. PROUVER SI LES CHIFFRES DU TELEPHONE DE L'UDEM SONT PRESENTS DANS CELUI DE JEAN :" << endl;
    cout << "Tous les chiffres dans le telphone de l'UdeM sont presents dans le telephone de Jean : " << (chiffUdeM ? "VRAI" : "FAUX") << endl;
    
    
    // 4. Verifier quels sont les chiffres dans le telephone de Jean qui ne sont pas presents dans le telephone de l'UdeM
    cout << "\n4. AFFICHAGE DES CHIFFRES DU NUMERO DE JEAN QUI NE SONT PAS PRESENTS DANS CELUI DE L'UDEM :" << endl;
    cout << "Les chiffres dans telJean qui ne sont pas presents dans telUdeM sont : ";
    for (char chiff : telJean) { // Cette boucle parcourt tous les chiffres (char chiff) dans le string telJean
        if (telUdeM.find(chiff) == string::npos) // On utilise la methode find sur le string telUdeM. Si on ne trouve pas le chiffre dans telUdeM, la methode find indique que le chiffre n'a pas ete trouve, que sa position n'a pas ete trouve (string::npos)
            cout << chiff << " ";
    }
    cout << endl;
    
    
    // 5. Affichage des chiffres impairs du telephone de Jean
    string Jean = "telJean";
    afficherImpairs(telJean, Jean);
    
    
    // 6. Affichage des chiffres pairs du telephone de l'UdeM
    string UdeM = "telUdeM";
    afficherPairs(telUdeM, UdeM);
    
    
    // 7. Affichage du chiffre plus petit dans les deux numeros de telephone :
    // a) Chiffre plus petit dans le telephone de l'UdeM
    cout << "\n\n7. DETERMINER LES PLUS PETITS CHIFFRES DANS CHAQUE NUMERO :" << endl;
    char plusPetitUdeM = plusPetit(telUdeM);
    cout << "a) Le plus petit chiffre du numero de telephone de l'UdeM est " << plusPetitUdeM << "." << endl;
    
    // b) Chiffre plus petit dans le telephone de Jean
    char plusPetitJean = plusPetit(telJean);
    cout << "b) Le plus petit chiffre du numero de telephone de Jean est " << plusPetitJean << "." << endl;
    
    cout << "\n";
    
    return 0;
}

/*
 
 EXECUTION :
 
 
 1. AFFICHAGE DES DEUX TELEPHONES AVEC UN FORMAT SPECIFIQUE :
 a) Le telephone de l'Universite de Montreal : (514) 343-6111
 b) Le telephone de Jean : (450) 123-7654
 
 2. AFFICHAGE DE COMBIEN DE FOIS APPARAISSENT DES CHIFFRES VOULUS DANS UN NUMERO :
 a) Le chiffre 3 apparait 2 fois dans le telephone de l'UdeM.
 b) Le chiffre 1 apparait 4 fois dans le telephone de l'UdeM.
 c) Le chiffre 4 apparait 2 fois dans le telephone de Jean.
 
 3. PROUVER SI LES CHIFFRES DU TELEPHONE DE L'UDEM SONT PRESENTS DANS CELUI DE JEAN :
 Tous les chiffres dans le telphone de l'UdeM sont presents dans le telephone de Jean : VRAI
 
 4. AFFICHAGE DES CHIFFRES DU NUMERO DE JEAN QUI NE SONT PAS PRESENTS DANS CELUI DE L'UDEM :
 Les chiffres dans telJean qui ne sont pas presents dans telUdeM sont : 0 2 7
 
 5. NUMEROS IMPAIRS DU NUMERO DE TELEPHONE DE JEAN :
 Les chiffres impairs dans telJean sont : 1 3 5 7
 
 6. NUMEROS PAIRS DU NUMERO DE TELEPHONE DE L'UDEM :
 Les chiffres pairs dans telUdeM sont : 4 6
 
 7. DETERMINER LES PLUS PETITS CHIFFRES DANS CHAQUE NUMERO :
 a) Le plus petit chiffre du numero de telephone de l'UdeM est 1.
 b) Le plus petit chiffre du numero de telephone de Jean est 0.
 
 Program ended with exit code: 0
 
 */
