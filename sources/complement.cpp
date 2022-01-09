#include "../headers/complement.h"

using namespace std ;
using namespace rapidjson ;

/*Date*/
// Saisie et validation de la date
string SaisirDate(string& jour, string& mois, string& annee){
    // Declaration de variable
    int c ;                             // Indice
    string date ;                       // Date saisie
    vector<int> erreur ;                // Liste des erreurs

    // Saisie et verification
    do{
        // Saisie de la date
        cin >> date ;
        // Verification
        erreur = VerifierDate(date, jour, mois, annee) ;

        // S'il n'y a aucune erreur
        if((int)erreur.size() == 0){
            break ;
        }

        // Affichage des erreurs 
        for(c = 0 ; c < (int)erreur.size() ; c++){
            switch(erreur[c]){
                case 0 :
                    cout << "Format invalide." << endl ;
                    break ;
                case 1 :
                    cout << "Annee dois etre entre 1800 et 2022." << endl ;
                    break ;
                case 2 :
                    cout << "Mois doit etre entre 1 et 12." << endl ;
                    break ;
                case 3 :
                    cout << "Jour doit etre entre 1 et 31." << endl ;
                    break ;
                case 4 :
                    cout << "Jour doit etre < 29." << endl ;
                    break ;
                case 5 :
                    cout << "Jour doit etre < 31." << endl ;
                    break ;
                default :
                    break ;
            }
        }
        cout << "Veuillez resaisir une nouvelle date (dd/mm/yyyy) : " ;
    }while((int)erreur.size() != 0) ;

    // Retour
    return date ;
}

// Verifier le format de la date
bool VerifierDate(const string date){
    // Si la longueur de la date saisie est incorrecte
    if(date.size() != 10){
        return false ;
    // Si le format d'une ou des caracteres est incorrect
    }else if((isdigit(date[0]) == false) || (isdigit(date[1]) == false) || (isdigit(date[3]) == false) || (isdigit(date[4]) == false) || (isdigit(date[6]) == false) || (isdigit(date[7]) == false) || (isdigit(date[8]) == false) || (isdigit(date[9]) == false)){
        return false ;
    // Sinon
    }else{
        return true ;
    }
}         

// Valider la date et remplir les champs requis
vector<int> VerifierDate(const string date, string& jour, string& mois, string& annee){
    // Declaration de variable
    vector<int> erreur ;        // Vecteur des erreurs

    // Initialisation
    jour.clear() ;              // Jour
    mois.clear() ;              // Mois
    annee.clear() ;             // Annee

    if(VerifierDate(date)){
        // Remplir du jour
        jour.push_back(date[0]) ;
        jour.push_back(date[1]) ;
        // Remplir du mois
        mois.push_back(date[3]) ;
        mois.push_back(date[4]) ;
        // Remplir de l'annee
        annee.push_back(date[6]) ;
        annee.push_back(date[7]) ;
        annee.push_back(date[8]) ;
        annee.push_back(date[9]) ;

        // Verification - Annee
        // Si l'annee saisie est hors intervalle [1800, 2022]
        if((stoi(annee) > 2022) || (stoi(annee) < 1800)){                                                                       
            erreur.push_back(1) ;
        }

        // Verification - Mois
        // Si le mois saisi est hors intervalle [1, 12]
        if((stoi(mois) < 1) || (stoi(mois) > 12)){                                                                              
            erreur.push_back(2) ;
        }

        // Verification - Jour
        // Si le jour saisi est hors intervalle [1, 31]
        if((stoi(jour) > 31) || (stoi(jour) < 1)){                                                                              
            erreur.push_back(3) ;
        // Mois = 2, Jour > 28
        }else if((stoi(mois) == 2) && (stoi(jour) > 28)){    
            // Mois = 2, Jour > 29 ou jour = 29 mais annee % 4 != 0                                                                   
            if((stoi(jour) > 29) || ((stoi(jour) == 29) && ((stoi(annee) % 4) != 0))){                                          
                erreur.push_back(4) ;
            }
        // Si Jour = 31 mais Mois = 4, 6, 9, 11
        }else if((stoi(jour) == 31) && ((stoi(mois) == 4) || (stoi(mois) == 6) || (stoi(mois) == 9) || (stoi(mois) == 11))){    
            erreur.push_back(5) ;
        }          
    // Erreur de format
    }else{
        erreur.push_back(0) ;
    }

    // Retour
    return erreur ;
}  

// Extraire jour, mois, annee a partir d'une date
void ExtraireDate(const string date, string& jour, string& mois, string& annee){
    // Initialisation
    jour.clear() ;
    mois.clear() ;
    annee.clear() ;

    // Jour de creation : caracteres aux indices 0 et 1
    jour.push_back(date[0]) ; 
    jour.push_back(date[1]) ;

    // Mois de creation : caracteres aux indices 3 et 4
    mois.push_back(date[3]) ;
    mois.push_back(date[4]) ;

    // Annee de creation : 4 dernieres caracteres
    annee.push_back(date[6]) ;
    annee.push_back(date[7]) ;
    annee.push_back(date[8]) ;
    annee.push_back(date[9]) ;    
}

/*Verification*/
// Verifier le format du cout saisie
bool VerifierCout(const string saisie, double& chiffre){                        	
    // Declaration des variables
    bool validation = true ;
    int c ;

    // Verifier le format du numero saisi
    for(c = 0 ; c < (int)saisie.size() ; c++){
        if(isdigit(saisie[c]) == false){
            validation = false ;
            break ;
        }
    }

    // Si le format est valide
    if(validation){
        chiffre = stod(saisie) ;
    }

    // Si le cout est invalide
    if(chiffre < 0){
        validation = false ;
    }

    // Retour 
    return validation ;
}                      	

// Verifier l'extension ".json"
void VerifierExtension(string& nom){
    if (nom.length() < 6){                                          // Si la longueur du nom est < 6 (".json" = 5 caracteres)
        nom += ".json" ;                                            // Ajouter l'extension
    }else{                                                          // Sinon
        if(nom.find(".json", nom.length()-5) != nom.length()-5){    // Si ".json" n'existe pas dans le nom saisi
            nom += ".json" ;                                        // Ajouter l'extension
        }
    }    
}

// Verifier l'existance d'un numero de l'image
bool VerifierNumero(const int numero, const Json::Value biblio){
    // Declaration des variables
    int c ;                                         // Indice
    bool exist = false ;                            // Verificaiton de l'existance du numero saisi
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images existantes dans la bibliotheque
     
    // Verification de l'existance du numero saisi dans la bibliotheque
    for (c = 0 ; c < nbImages ; c++){
        // Si le numero existe
        if (numero == biblio["images"][c]["numero"].asInt()){
            exist = true ;
            break ;
        }
    }

    // Retour
    return exist ;
}

// Verifier le format du numero (entier)
bool VerifierNumero(const string saisie, int& numero){
    // Declaration des variables
    bool validation = true ;
    int c ;

    // Verifier le format du numero saisi
    for(c = 0 ; c < (int)saisie.size() ; c++){
        if(isdigit(saisie[c]) == false){
            validation = false ;
            break ;
        }
    }

    // Si le format est valide
    if(validation){
        numero = stoi(saisie) ;
    }

    // Retour 
    return validation ;
}    

// Verifier le format du numero (reel)
bool VerifierNumero(const string saisie, double& numero){
    // Declaration des variables
    bool validation = true ;
    int c ;
    int s = 0 ;

    // Verifier le format de chaque caractere du numero 
    for(c = 0 ; c < (int)saisie.size() ; c++){
        // Si le caractere n'est pas un chiffre
        if(isdigit(saisie[c]) == false){
            // Si ce caractere ne se trouve pas dans la premiere position et si c'est le separateur du reel
            if((c > 0) && (saisie[c] == '.')){
                // S'il y a plus d'un separateur
                if(s++ > 1){
                    validation = false ;
                    break ;
                }
            // Si ce n'est pas le separateur du reel
            }else{
                validation = false ;
                break ;
            }
        }
    }

    // Si le format est valide
    if(validation){
        numero = stod(saisie) ;
    }

    // Retour 
    return validation ;
}                      	       

// Verifier l'existance d'un element dans un vecteur
bool VerifierExistance(vector<string> vecteur, string valeur){
    // Declaration des variables
    bool exist = false ;    // Existance de la valeur dans le vecteur
    int c ;                 // Indice

    // Verifier l'existance de la valeur dans le vecteur
    for(c = 0 ; c < (int)vecteur.size() ; c++){
        if(vecteur[c] == valeur){
            exist = true ;
            break ;
        }
    }

    return exist ;
}

/*Continuement*/
// Continuer [Y/N]
bool Continuer(){
    // Declaration de variable
    char decision ;

    cout << "Voulez-vous continuer ? [Y/N] : " ;
    do{
        // Saisie
        cin >> decision ;

        // Verification
        if ((decision != 'Y') && (decision != 'N')){
            cout << "Choix invalide. Veuillez saisir 'Y' ou 'N': " ;
        }
    } while((decision != 'Y') && (decision != 'N')) ;

    // Retour
    return (decision == 'Y') ;
}

// Continuer [Y/N] avec message personnalisee
bool Continuer(const string message){
    // Declaration de variable
    char decision ;

    cout << message ;
    do{
        // Saisie
        cin >> decision ;

        // Verification
        if ((decision != 'Y') && (decision != 'N')){
            cout << "Choix invalide. Veuillez saisir 'Y' ou 'N' : " ;
        }
    } while((decision != 'Y') && (decision != 'N')) ;

    // Retour
    return (decision == 'Y') ;    
}                           

/*Liste*/
// Creer une liste des sources des images contenues dans une bibliotheque
vector<string> ListerSource(Json::Value biliotheque){
    // Declarations des variables
    int c ;                             // Indice
    vector<string> listeSource ;        // Liste des sources

    // Remplir la liste des sources
    listeSource.push_back(biliotheque["images"][0]["source"].asString()) ;
    for(c = 1 ; c < biliotheque["nbImages"].asInt() ; c++){
        if(VerifierExistance(listeSource, biliotheque["images"][c]["source"].asString()) == false){
            listeSource.push_back(biliotheque["images"][c]["source"].asString()) ;
        }
    }

    // Retour
    return listeSource ;
}

// Creer une liste des noms des fichiers des images dans la base de donnees
vector<string> ListerImage(){
    DIR* dossier ;
    dirent* fichier ;
    vector<string> listeImage ;

    // Ouvrir le dossier des images
    dossier = opendir("./DATA/Images");
    // Si le dossier n'est pas vide
    if (dossier != NULL){
        // Tant qu'on n'a pas lu tous les fichiers dans le dossier
        while ((fichier = readdir(dossier))){
            // Eviter les cas des non-fichiers
            if(strcmp((fichier->d_name), ".") && strcmp((fichier->d_name), "..")){
                // Remplir le vecteur
                listeImage.push_back(fichier->d_name);
            }
        }
    }    
    // Fermer le dossier
    closedir(dossier) ;

    // Retour
    return listeImage ;
}                                                           

// Creer une liste des numeros des images contenues dans une bibliotheque
vector<int> ListerNumero(Json::Value biliotheque){
    // Declarations des variables
    int c ;                             // Indice
    vector<int> listeNumero ;        // Liste des sources

    // Remplir la liste des sources
    listeNumero.push_back(biliotheque["images"][0]["numero"].asInt()) ;
    for(c = 1 ; c < biliotheque["nbImages"].asInt() ; c++){
        listeNumero.push_back(biliotheque["images"][c]["numero"].asInt()) ;
    }

    // Retour
    return listeNumero ;    
}                                       




