#include "../headers/bibliotheque.h"

/*Constructeurs*/
// Constructeur vide
Bibliotheque::Bibliotheque(){
}

// Constructeur avec le nom de la bibliotheque donnee par l'utilisateur
Bibliotheque::Bibliotheque(string nom){
    // Declaration des variables
    Json::Reader reader ;                       // Variable pour lire un fichie Json

    // Lecture du fichier et copie du contenu dans la bibliotheque
    ifstream bibliothequeFile(nom, ios::in) ;   // Chargement du fichier Json
    reader.parse(bibliothequeFile, _bibliotheque) ; 
    _cheminJson = nom;                
}                               

// Constructeur avec un objet Json
Bibliotheque::Bibliotheque(const Json::Value bibliotheque){
    setBilbiotheque(bibliotheque) ;
}

/*Getters*/
// Bibliotheque
Json::Value Bibliotheque::getBilbiotheque() const{
    return _bibliotheque ;
}

// Chemin Json
string Bibliotheque::getCheminJson() const {
    return _cheminJson; 
}

/*Setters*/
// Bibliohteque
void Bibliotheque::setBilbiotheque(const Json::Value bibliotheque){
    _bibliotheque = bibliotheque ;
}

// Chemin Json
void Bibliotheque::setCheminJson(const string cheminJson){
    _cheminJson = cheminJson ;
}

/*Methodes principales*/
// Afficher la liste des descripteurs
void Bibliotheque::AfficherDescripteurs(){
    // Declaration des variables
    Json::Value biblio = getBilbiotheque() ;        // Objet Json
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images existantes dans la bibliotheque
    int c ;                                         // Indice

    // Affichage
    for (c = 0 ; c < nbImages ; c++){
        cout << "Descipteur de l'image " << c+1 << " : " << endl ;
        cout << "Chemin d'acces : " << biblio["images"][c]["cheminAcces"].asString() << endl ;
        cout << "Source : " << biblio["images"][c]["source"].asString() << endl ;
        cout << "Titre : " << biblio["images"][c]["titre"].asString() << endl ;
        cout << "Numero : " << biblio["images"][c]["numero"].asInt() << endl ;
        cout << "Cout : " << biblio["images"][c]["cout"].asDouble() << "€" << endl ;
        cout << "Permission : " << biblio["images"][c]["acces"].asString() << endl ;
        cout << "Date d'ajout : " << biblio["images"][c]["dateAjout"].asString() << endl ;
        cout << "Date de creation : " << biblio["images"][c]["dateCreation"].asString() << endl << endl ;  
    }
}

// Afficher la liste des descripteurs d'une partie indiquee de la bibliotheque
void Bibliotheque::AfficherDescripteurs(const Json::Value bibliotheque, const int indice){
    cout << "Chemin d'acces : " << bibliotheque["images"][indice]["cheminAcces"].asString() << endl ;
    cout << "Source : " << bibliotheque["images"][indice]["source"].asString() << endl ;
    cout << "Titre : " << bibliotheque["images"][indice]["titre"].asString() << endl ;
    cout << "Numero : " << bibliotheque["images"][indice]["numero"].asInt() << endl ;
    cout << "Cout : " << bibliotheque["images"][indice]["cout"].asDouble() << "€" << endl ;
    cout << "Permission : " << bibliotheque["images"][indice]["acces"].asString() << endl ;
    cout << "Date d'ajout : " << bibliotheque["images"][indice]["dateAjout"].asString() << endl ;
    cout << "Date de creation : " << bibliotheque["images"][indice]["dateCreation"].asString() << endl << endl ;     
} 

// Affichage le cout d'une image
void Bibliotheque::AfficherCout(){
    // Declaration des variables
    int c ;                                         // Indice
    string numeroSaisi ;                            // Numero saisi par l'utilisateur
    int numero ;                                    // Numero de l'image
    Json::Value biblio = getBilbiotheque() ;        // Objet Json
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images existantes dans la bibliotheque
     
    // Choix du numero de l'image et verification 
    cout << "Veuillez donner le numero de l'image : " << endl ;
    do{
        // Saisie du numero souhaite
        numeroSaisi.clear() ;
        cin >> numeroSaisi ; 

        // Verifier le format du numero saisi
        if(VerifierNumero(numeroSaisi, numero)){
            // Verification de l'existance du numero saisi dans la bibliotheque
            if (VerifierNumero(numero, getBilbiotheque())){
                for(c = 0 ; c < nbImages ; c++){
                    // Chercher l'image ayant le numero correspondant
                    if(biblio["images"][c]["numero"].asInt() == numero){
                        // Affichage le cout correspondant
                        cout << "Cout de l'image " << numero << " : " << biblio["images"][c]["cout"].asDouble() << "€" << endl ;
                        break ;
                    }
                }
            }else{
                cout << "Ce numero n'existe pas. " ;
            }            
        }else{
            cout << "Format invalide. " ;
        }
    }while(Continuer("Voulez-vous saisir un nouveau numero ? [Y/N] : ")) ;
}


// Ajouter une image
void Bibliotheque::AjouterImage(string cheminAccesContenu,
                                string titre,int numero,double cout,string source,
                                string dateAjout,string dateCreation,string acces){

    Json::Value biblio = getBilbiotheque() ;
    int indice = biblio["images"].size() ;                            // Nombre d'images présent dans la bibliotheque avant l'ajout d'une nouvelle image

    // Saisie : Acces
    biblio["images"][indice]["acces"] = acces ;

    // Saisie : Chemin acces
    biblio["images"][indice]["cheminAcces"] = cheminAccesContenu ;

    // Saisie : Cout
    biblio["images"][indice]["cout"] = cout ;

    // Saisie : Date de creation
    biblio["images"][indice]["dateCreation"] = dateCreation ;

    // Saisie : Date d'ajout
    biblio["images"][indice]["dateAjout"] = dateAjout ;

    // Numero de l'image
    biblio["images"][indice]["numero"] = numero ;

    // Saisie : Source
    biblio["images"][indice]["source"] = source ;

    // Saisie : Titre
    biblio["images"][indice]["titre"] = titre ;
    // Incrémentation nbIamges
    biblio["nbImages"] = indice + 1 ;


    setBilbiotheque(biblio) ;
}

// Supprimer une image bibliotheque
void  Bibliotheque::SupprimerImage(int numero){
    // Declaration des variables
    Json::Value removed ;
    Json::Value biblio = getBilbiotheque() ;
    int nbImages = biblio["images"].size() ;     // Nombre d'images présent dans la bibliotheque avant la suppresion d'une nouvelle image
    int indexImage = 0 ;
    for(const auto & obj : biblio["images"]) {
        if (obj["numero"] == numero) {
            // Suppression dans le vecteur images des élèment associer à ce numéro
            biblio["images"].removeIndex(indexImage, &removed);
            // Mise à Jour sur le nombre d'image.
            biblio["nbImages"] = nbImages - 1 ;
        }
        //Incrémenter l'index Images
        indexImage++;
    }
       // Mise à jour de la bibliothèque
    setBilbiotheque(biblio);
}


// Sauvegarder une bibliotheque
void Bibliotheque::Sauvegarder(string fileName){
    // Declaration des variables
    ofstream bibliotheque_new ;                                         // Objet fichier
    Json::StyledWriter styledWriter;                                    // Writer Json
    bibliotheque_new.open(fileName) ;                             // Ouvrir le fichier
    bibliotheque_new << styledWriter.write(getBilbiotheque());  // Ecrire
    bibliotheque_new.close();                                   // Fermer le fichier
}

// Creer une sous-bibliotheque avec les images correspondantes au droit d'utilisateur
void Bibliotheque::majBiblioSuivantDroitAcces(const bool droitAcces){
    // Declaration des variables
    int c, k ;                                      // Indices
    Json::Value biblio = getBilbiotheque() ;        // Bibliotheque originale
    Json::Value biblioAcces ;                       // Bibliotheque correspondante au droit de l'utilisateur
    Json::Value removed ;                           // Parametre pour mettre a jour la bibliotheque apres l'enlevement d'un element
    vector<int> numero ;                            // Vecteur des numeros des images a enlever

    // Initialisation
    biblioAcces = biblio ;
    numero.clear() ;

    // Si l'utilisateur n'a pas de droit d'acces
    if(droitAcces == false){
        // Determiner les numeros des images a enlever
        for(c = 0 ; c < biblio["nbImages"].asInt() ; c++){
            // Sauvegarder le numero des images a enlever dans le vecteur des numeros
            if(biblio["images"][c]["acces"].asString() == "R"){
                numero.push_back(biblio["images"][c]["numero"].asInt()) ;
            }
        }
    }

    // Enlever les images pour lesquelles leurs numeros sont ecrits dans le vecteur des numeros
    for(c = 0 ; c < (int)numero.size() ; c++){
        for(k = 0 ; k < biblioAcces["nbImages"].asInt() ; k++){
            if(biblioAcces["images"][k]["numero"].asInt() == numero[c]){
                biblioAcces["images"].removeIndex(k,  &removed) ;             
                biblioAcces["nbImages"] = biblioAcces["nbImages"].asInt() - 1 ;
            }
        }
    }

    
    _bibliotheque = biblioAcces ;
}                     

/*Methodes supplementaires*/
// Construire et afficher une sous-liste en fonction du cout (4 premieres options)
Json::Value Bibliotheque::ConstruireAfficherSousListeCout(const int choix){
    // Declaration des variables
    int c ;                                         // Indice
    int compteur = 0 ;                              // Compteur des images dans la sous liste
    Json::Value biblio = getBilbiotheque() ;        // Bibliotheque
    Json::Value sousListeBiblio ;                  // Sous-liste de la bibliothèque
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images dans la bibliotheque

    switch (choix){
        // Sous-critere : Cout gratuit
        case 1 :
            // Affichage conditionnelle
            for (c = 0 ; c < nbImages ; c++){
                if (biblio["images"][c]["cout"].asDouble() == 0.0){
                    // Ajouter Image
                    sousListeBiblio["images"][compteur]["cheminAcces"]  = biblio["images"][c]["cheminAcces"];
                    sousListeBiblio["images"][compteur]["source"]       = biblio["images"][c]["source"];
                    sousListeBiblio["images"][compteur]["titre"]        = biblio["images"][c]["titre"];
                    sousListeBiblio["images"][compteur]["numero"]       = biblio["images"][c]["numero"];
                    sousListeBiblio["images"][compteur]["cout"]         = biblio["images"][c]["cout"];
                    sousListeBiblio["images"][compteur]["acces"]        = biblio["images"][c]["acces"];
                    sousListeBiblio["images"][compteur]["dateAjout"]    = biblio["images"][c]["dateAjout"];
                    sousListeBiblio["images"][compteur]["dateCreation"] = biblio["images"][c]["dateCreation"];
                    // Incrementation du compteur 
                    compteur++ ;
                    sousListeBiblio["nbImages"] = compteur;
                }
            }
            break ;

        // Sous-critere : Cout ≤ 99,99 €
        case 2 :
            // Affichage conditionnelle
            for (c = 0 ; c < nbImages ; c++){
                if (biblio["images"][c]["cout"].asDouble() <= 99.99){
                    // Ajouter Image
                    sousListeBiblio["images"][compteur]["cheminAcces"]  = biblio["images"][c]["cheminAcces"];
                    sousListeBiblio["images"][compteur]["source"]       = biblio["images"][c]["source"];
                    sousListeBiblio["images"][compteur]["titre"]        = biblio["images"][c]["titre"];
                    sousListeBiblio["images"][compteur]["numero"]       = biblio["images"][c]["numero"];
                    sousListeBiblio["images"][compteur]["cout"]         = biblio["images"][c]["cout"];
                    sousListeBiblio["images"][compteur]["acces"]        = biblio["images"][c]["acces"];
                    sousListeBiblio["images"][compteur]["dateAjout"]    = biblio["images"][c]["dateAjout"];
                    sousListeBiblio["images"][compteur]["dateCreation"] = biblio["images"][c]["dateCreation"];
                    // Incrementation du compteur
                    compteur++ ;
                    sousListeBiblio["nbImages"] = compteur;
                }
            }
            break ;  

        // Sous-critere : 100 ≤ Cout ≤ 999,99 €
        case 3 :
            // Affichage conditionnelle
            for (c = 0 ; c < nbImages ; c++){
                if ((biblio["images"][c]["cout"].asDouble() >= 100) && (biblio["images"][c]["cout"].asDouble() <= 999.99)){
                    // Ajouter Image
                    sousListeBiblio["images"][compteur]["cheminAcces"]  = biblio["images"][c]["cheminAcces"];
                    sousListeBiblio["images"][compteur]["source"]       = biblio["images"][c]["source"];
                    sousListeBiblio["images"][compteur]["titre"]        = biblio["images"][c]["titre"];
                    sousListeBiblio["images"][compteur]["numero"]       = biblio["images"][c]["numero"];
                    sousListeBiblio["images"][compteur]["cout"]         = biblio["images"][c]["cout"];
                    sousListeBiblio["images"][compteur]["acces"]        = biblio["images"][c]["acces"];
                    sousListeBiblio["images"][compteur]["dateAjout"]    = biblio["images"][c]["dateAjout"];
                    sousListeBiblio["images"][compteur]["dateCreation"] = biblio["images"][c]["dateCreation"];
                    // Incrementation du compteur
                    compteur++ ;
                    sousListeBiblio["nbImages"] = compteur;
                }
            }
            break ;  

        // Sous-critere : Cout > 1000 €
        case 4 :
            // Affichage conditionnelle
            for (c = 0 ; c < nbImages ; c++){
                if (biblio["images"][c]["cout"].asDouble() >= 1000){
                    // Ajouter Image
                    sousListeBiblio["images"][compteur]["cheminAcces"]  = biblio["images"][c]["cheminAcces"];
                    sousListeBiblio["images"][compteur]["source"]       = biblio["images"][c]["source"];
                    sousListeBiblio["images"][compteur]["titre"]        = biblio["images"][c]["titre"];
                    sousListeBiblio["images"][compteur]["numero"]       = biblio["images"][c]["numero"];
                    sousListeBiblio["images"][compteur]["cout"]         = biblio["images"][c]["cout"];
                    sousListeBiblio["images"][compteur]["acces"]        = biblio["images"][c]["acces"];
                    sousListeBiblio["images"][compteur]["dateAjout"]    = biblio["images"][c]["dateAjout"];
                    sousListeBiblio["images"][compteur]["dateCreation"] = biblio["images"][c]["dateCreation"];
                    // Incrementation du compteur
                    compteur++ ;
                    sousListeBiblio["nbImages"] = compteur;
                }
            }
            break ;  
        default :
            break ;
    }
    // Retour
    return sousListeBiblio ;
}

// Construire et afficher une sous-liste en fonction du cout (derniere option)
Json::Value Bibliotheque::ConstruireAfficherSousListeCout(double coutMin, double coutMax){
    // Declaration des variables
    int c ;                                         // Indice
    int compteur = 0 ;                              // Compteur des images dans la sous liste
    Json::Value biblio = getBilbiotheque() ;        // Bibliotheque
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images dans la bibliotheque
    Json::Value sousListeBiblio;                  // Sous-liste de la bibliothèque

    for (c = 0 ; c < nbImages ; c++){
        if ((biblio["images"][c]["cout"].asDouble() >= coutMin) && (biblio["images"][c]["cout"].asDouble() <= coutMax)){
            // Ajouter Image
            sousListeBiblio["images"][compteur]["cheminAcces"]  = biblio["images"][c]["cheminAcces"];
            sousListeBiblio["images"][compteur]["source"]       = biblio["images"][c]["source"];
            sousListeBiblio["images"][compteur]["titre"]        = biblio["images"][c]["titre"];
            sousListeBiblio["images"][compteur]["numero"]       = biblio["images"][c]["numero"];
            sousListeBiblio["images"][compteur]["cout"]         = biblio["images"][c]["cout"];
            sousListeBiblio["images"][compteur]["acces"]        = biblio["images"][c]["acces"];
            sousListeBiblio["images"][compteur]["dateAjout"]    = biblio["images"][c]["dateAjout"];
            sousListeBiblio["images"][compteur]["dateCreation"] = biblio["images"][c]["dateCreation"];
            // Incrementation du compteur
            compteur++ ;
            sousListeBiblio["nbImages"] = compteur;
        }
    }    

    // Retour
    return sousListeBiblio ;
} 

// Construire et afficher une sous-liste en fonction de la date d'ajout
Json::Value Bibliotheque::ConstruireAfficherSousListeDateAjout(const int choix){
    // Declaration des variables
    int c ;                                         // Indice
    int compteur = 0 ;                              // Compteur des images dans la sous liste
    Json::Value biblio = getBilbiotheque() ;        // Bibliotheque
    Json::Value sousListeBiblio ;                  // Sous-liste de la bibliothèque
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images dans la bibliotheque
    //QDate dateAjout;
    string dateStr;
    string jour,mois,annee;

    switch (choix){
        // Sous-critere : Date d'Ajout Aujourd'hui
        case 1 :
        // Affichage conditionnelle
        for (c = 0 ; c < nbImages ; c++){
            ExtraireDate(dateStr = biblio["images"][c]["dateAjout"].asString(),jour,mois,annee);
            QDate dateAjout(stoi(annee),stoi(mois),stoi(jour));
            if (dateAjout==QDate::currentDate()){
                // Ajouter Image
                sousListeBiblio["images"][compteur]["cheminAcces"]  = biblio["images"][c]["cheminAcces"];
                sousListeBiblio["images"][compteur]["source"]       = biblio["images"][c]["source"];
                sousListeBiblio["images"][compteur]["titre"]        = biblio["images"][c]["titre"];
                sousListeBiblio["images"][compteur]["numero"]       = biblio["images"][c]["numero"];
                sousListeBiblio["images"][compteur]["cout"]         = biblio["images"][c]["cout"];
                sousListeBiblio["images"][compteur]["acces"]        = biblio["images"][c]["acces"];
                sousListeBiblio["images"][compteur]["dateAjout"]    = biblio["images"][c]["dateAjout"];
                sousListeBiblio["images"][compteur]["dateCreation"] = biblio["images"][c]["dateCreation"];
                // Incrementation du compteur
                compteur++ ;
                sousListeBiblio["nbImages"] = compteur;
            }
        }
        break ;
        // Sous-critere : Date d'Ajout : il y a moins d'une semaine
        case 2 :
        // Affichage conditionnelle
        for (c = 0 ; c < nbImages ; c++){
            ExtraireDate(dateStr = biblio["images"][c]["dateAjout"].asString(),jour,mois,annee);
            QDate dateAjout(stoi(annee),stoi(mois),stoi(jour));
            if ((dateAjout.month()==QDate::currentDate().month())&&(dateAjout.year()==QDate::currentDate().year())&&(dateAjout.daysTo(QDate::currentDate())<7)){
                // Ajouter Image
                sousListeBiblio["images"][compteur]["cheminAcces"]  = biblio["images"][c]["cheminAcces"];
                sousListeBiblio["images"][compteur]["source"]       = biblio["images"][c]["source"];
                sousListeBiblio["images"][compteur]["titre"]        = biblio["images"][c]["titre"];
                sousListeBiblio["images"][compteur]["numero"]       = biblio["images"][c]["numero"];
                sousListeBiblio["images"][compteur]["cout"]         = biblio["images"][c]["cout"];
                sousListeBiblio["images"][compteur]["acces"]        = biblio["images"][c]["acces"];
                sousListeBiblio["images"][compteur]["dateAjout"]    = biblio["images"][c]["dateAjout"];
                sousListeBiblio["images"][compteur]["dateCreation"] = biblio["images"][c]["dateCreation"];
                // Incrementation du compteur
                compteur++ ;
                sousListeBiblio["nbImages"] = compteur;
            }
        }
        break ;
        // Sous-critere : Date d'Ajout : ce mois
    case 3 :
        // Affichage conditionnelle
        for (c = 0 ; c < nbImages ; c++){
            ExtraireDate(dateStr = biblio["images"][c]["dateAjout"].asString(),jour,mois,annee);
            QDate dateAjout(stoi(annee),stoi(mois),stoi(jour));
            if ((dateAjout.month()==QDate::currentDate().month())&&(dateAjout.year()==QDate::currentDate().year())){
                // Ajouter Image
                sousListeBiblio["images"][compteur]["cheminAcces"]  = biblio["images"][c]["cheminAcces"];
                sousListeBiblio["images"][compteur]["source"]       = biblio["images"][c]["source"];
                sousListeBiblio["images"][compteur]["titre"]        = biblio["images"][c]["titre"];
                sousListeBiblio["images"][compteur]["numero"]       = biblio["images"][c]["numero"];
                sousListeBiblio["images"][compteur]["cout"]         = biblio["images"][c]["cout"];
                sousListeBiblio["images"][compteur]["acces"]        = biblio["images"][c]["acces"];
                sousListeBiblio["images"][compteur]["dateAjout"]    = biblio["images"][c]["dateAjout"];
                sousListeBiblio["images"][compteur]["dateCreation"] = biblio["images"][c]["dateCreation"];
                // Incrementation du compteur
                compteur++ ;
                sousListeBiblio["nbImages"] = compteur;
            }
        }
        break ;
        // Sous-critere : Date d'Ajout : cette année
    case 4 :
        // Affichage conditionnelle
        for (c = 0 ; c < nbImages ; c++){
            ExtraireDate(dateStr = biblio["images"][c]["dateAjout"].asString(),jour,mois,annee);
            QDate dateAjout(stoi(annee),stoi(mois),stoi(jour));
            if (dateAjout.year()==QDate::currentDate().year()){
                // Ajouter Image
                sousListeBiblio["images"][compteur]["cheminAcces"]  = biblio["images"][c]["cheminAcces"];
                sousListeBiblio["images"][compteur]["source"]       = biblio["images"][c]["source"];
                sousListeBiblio["images"][compteur]["titre"]        = biblio["images"][c]["titre"];
                sousListeBiblio["images"][compteur]["numero"]       = biblio["images"][c]["numero"];
                sousListeBiblio["images"][compteur]["cout"]         = biblio["images"][c]["cout"];
                sousListeBiblio["images"][compteur]["acces"]        = biblio["images"][c]["acces"];
                sousListeBiblio["images"][compteur]["dateAjout"]    = biblio["images"][c]["dateAjout"];
                sousListeBiblio["images"][compteur]["dateCreation"] = biblio["images"][c]["dateCreation"];
                // Incrementation du compteur
                compteur++ ;
                sousListeBiblio["nbImages"] = compteur;
            }
        }
        break ;
    default :
        break ;
    }
    // Retour
    return sousListeBiblio ;
}

// Tri elementaire
Json::Value Bibliotheque::Trier(const int choix){
    // Declaration des variables
    Json::Value biblioTrie ;                                // Initialiser la bibliotheque triee
    Json::Value biblioNonTrie = getBilbiotheque() ;         // Initialiser la bibliotheque non triee
    int nbImages = biblioNonTrie["nbImages"].asInt() ;      // Nombre d'images existantes dans la bibliotheque
    int c ;                                                 // Indices
    vector<int> indice ;                                    // Vecteur des indices pour le tri de la bibliotheque
    vector<string> valeurTemp ;                             // Vecteur des valeurs temporaires
    string jour, mois, annee ;                              // Jour, mois, annee pour le tri des dates
    // Vecteurs des valeurs triees 
    vector<string> texteTri ;                               // Type chaine de caracteres                     
    vector<int> entierTri ;                                 // Type entier
    vector<double> reelTri ;                                // Type reel
    // Vecteurs des valeurs non triees 
    vector<string> texteNonTri ;                            // Type chaine de caracteres
    vector<int> entierNonTri ;                              // Type entier
    vector<double> reelNonTri ;                             // Type reel

    // Initialisation
    indice.clear() ;
    valeurTemp.clear() ;
    texteTri.clear() ;
    entierTri.clear() ;
    reelTri.clear() ;
    texteNonTri.clear() ;
    entierNonTri.clear() ;
    reelNonTri.clear() ;

    // Trier suivant le choix
    switch(choix){
       /* // Titre
    case  :
        // Initialiser vecteur des titres
        for (c = 0 ; c < nbImages ; c++){
            texteNonTri.push_back(biblioNonTrie["images"][c]["titre"].asString()) ;
        }
        indice = Trier(texteNonTri) ;
        break ;*/
        // Cout
    case 1 :
        // Initialiser vecteur des couts
        for (c = 0 ; c < nbImages ; c++){
            reelNonTri.push_back(biblioNonTrie["images"][c]["cout"].asDouble()) ;
        }
        indice = Trier(reelNonTri) ;
        break ;
        // Numero
    case 2 :
        // Initialiser vecteur des numeros
        for (c = 0 ; c < nbImages ; c++){
            entierNonTri.push_back(biblioNonTrie["images"][c]["numero"].asInt()) ;
        }
        indice = Trier(entierNonTri) ;
        break ;
/*
        // Source
    case 4 :
        // Initialiser vecteur des sources
        for (c = 0 ; c < nbImages ; c++){
            texteNonTri.push_back(biblioNonTrie["images"][c]["titre"].asString()) ;
        }
        indice = Trier(texteNonTri) ;
        break ;
        // Date de creation
    case 5 :
        // Initialiser vecteur des dates de creation
        for (c = 0 ; c < nbImages ; c++){
            valeurTemp.push_back(biblioNonTrie["images"][c]["dateCreation"].asString()) ;
        }
        // Inverser la position des elements de la date pour trier
        for(c = 0 ; c < nbImages ; c++){
            ExtraireDate(valeurTemp[nbImages -1 - c], jour, mois, annee) ;
            entierNonTri.push_back(stoi(annee + mois + jour)) ;
        }
        indice = Trier(entierNonTri) ;
        break ;
        // Date d'ajout
    case 6 :
        // Initialiser vecteur des dates d'ajout
        for (c = 0 ; c < nbImages ; c++){
            valeurTemp.push_back(biblioNonTrie["images"][c]["dateAjout"].asString()) ;
        }
        // Inverser la position des elements de la date pour trier
        for(c = 0 ; c < nbImages ; c++){
            ExtraireDate(valeurTemp[nbImages - 1 - c], jour, mois, annee) ;
            entierNonTri.push_back(stoi(annee + mois + jour)) ;
        }
        indice = Trier(entierNonTri) ;
        break ;
*/
        // Permission (acces)
    case 3 :
        // Initialiser vecteur des permissions
        for (c = 0 ; c < nbImages ; c++){
            texteNonTri.push_back(biblioNonTrie["images"][c]["acces"].asString()) ;
        }
        indice = Trier(texteNonTri) ;
        break ;
    default :
        break ;
    }
    if (choix){
        // Tri de la bibliotheque
        biblioTrie = biblioNonTrie ;                                                // Initialisation
        for (c = 0 ; c < nbImages ; c++){                                           // Remplir la bibliotheque triee
            biblioTrie["images"][c] = biblioNonTrie["images"][indice[c]] ;
        }
        _bibliotheque = biblioTrie;
        // Retour
        return biblioTrie ;
    }else {
        // Retour
        return biblioNonTrie ;
    }


}

// Determiner les indices des elements avant le tri (chaine de caracteres)
vector<int> Bibliotheque::Trier(vector<double>valeurNonTri){
    // Declaration des variables
    int c, k ;                      // Indices
    vector<double> valeurTri ;      // Vecteur des valeurs triees
    vector<int> indice ;            // Vecteur des indices pour le tri de la bibliotheque

    // Initialiser le vecteur des titres tries 
    valeurTri = valeurNonTri ;     

    // Trier les titres dans l'ordre decroissant
    sort(valeurTri.begin(), valeurTri.end(), greater<double>()) ; 

    // Initialiser la premiere valeur du vecteur des indices du tri par l'indice du cout maximum
    for (c = 0 ; c < (int)valeurTri.size() ; c++){
        if(valeurNonTri[c] == valeurTri[0]){
            indice.push_back(c) ;
            break ;
        }
    }

    // Remplir le vecteur des indice du tri
    for (c = 1 ; c < (int)valeurTri.size() ; c++){                      // Pour chaque element du vecteur des indices du vecteur des couts trie
        for (k = 0 ; k < (int)valeurTri.size() ; k++){                  // Pour chaque element du vecteur des indices du vecteur des couts non trie
            if ((valeurTri[c] == valeurNonTri[k])){                     // Si on retrouve le meme cout dans le vecteur trie que dans le vecteur non trie     
                if ((*find(indice.begin(), indice.end(), k)) != k){     // Si l'indice correspondant n'est pas encore ecrit dans le vecteur des indices de tri                         
                    indice.push_back(k) ;                               // Ajouter cet indice
                }
            }
        }
    }    

    // Retour
    return indice ;
}

// Determiner les indices des elements avant le tri (reel)
vector<int> Bibliotheque::Trier(vector<string>valeurNonTri){
    // Declaration des variables
    int c, k ;                      // Indices
    vector<string> valeurTri ;      // Vecteur des valeurs triees
    vector<int> indice ;            // Vecteur des indices pour le tri de la bibliotheque

    // Initialiser le vecteur des titres tries 
    valeurTri = valeurNonTri ;     
             
    // Trier les titres dans l'ordre decroissant
    sort(valeurTri.begin(), valeurTri.end(), greater<string>()) ; 

    // Initialiser la premiere valeur du vecteur des indices du tri par l'indice du cout maximum
    for (c = 0 ; c < (int)valeurTri.size() ; c++){
        if(valeurNonTri[c] == valeurTri[0]){
            indice.push_back(c) ;
            break ;
        }
    }

    // Remplir le vecteur des indice du tri
    for (c = 1 ; c < (int)valeurTri.size() ; c++){                      // Pour chaque element du vecteur des indices du vecteur des couts trie
        for (k = 0 ; k < (int)valeurTri.size() ; k++){                  // Pour chaque element du vecteur des indices du vecteur des couts non trie
            if ((valeurTri[c] == valeurNonTri[k])){                     // Si on retrouve le meme cout dans le vecteur trie que dans le vecteur non trie     
                if ((*find(indice.begin(), indice.end(), k)) != k){     // Si l'indice correspondant n'est pas encore ecrit dans le vecteur des indices de tri                         
                    indice.push_back(k) ;                               // Ajouter cet indice
                }
            }
        }
    }    

    // Retour
    return indice ;
}

// Determiner les indices des elements avant le tri (entier)
vector<int> Bibliotheque::Trier(vector<int>valeurNonTri){
    // Declaration des variables
    int c, k ;                      // Indices
    vector<int> valeurTri ;         // Vecteur des valeurs triees
    vector<int> indice ;            // Vecteur des indices pour le tri de la bibliotheque

    // Initialiser le vecteur des titres tries 
    valeurTri = valeurNonTri ;     

    // Trier les titres dans l'ordre decroissant
    sort(valeurTri.begin(), valeurTri.end(), greater<int>()) ;

    // Initialiser la premiere valeur du vecteur des indices du tri par l'indice du cout maximum
    for (c = 0 ; c < (int)valeurTri.size() ; c++){
        if(valeurNonTri[c] == valeurTri[0]){
            indice.push_back(c) ;
            break ;
        }
    }

    // Remplir le vecteur des indice du tri
    for (c = 0 ; c < (int)valeurTri.size() ; c++){                      // Pour chaque element du vecteur des indices du vecteur des couts trie
        for (k = 0 ; k < (int)valeurTri.size() ; k++){                  // Pour chaque element du vecteur des indices du vecteur des couts non trie
            if ((valeurTri[c] == valeurNonTri[k])){                     // Si on retrouve le meme cout dans le vecteur trie que dans le vecteur non trie     
                if ((*find(indice.begin(), indice.end(), k)) != k){     // Si l'indice correspondant n'est pas encore ecrit dans le vecteur des indices de tri                         
                    indice.push_back(k) ;                               // Ajouter cet indice
                }
            }
        }
    }    

    // Retour
    return indice ;
}

// Veriffier bibliotheque vide ou invalide
bool Bibliotheque::VerifierBibliotheque(){
    // Si la biliotheque ne contient aucune image
    if(getBilbiotheque()["nbImages"].asInt() == 0){
        cout << "Bibliotheque vide" << endl ;
        return false ;
    // Si le nombre d'images est negatif
    }else if(getBilbiotheque()["nbImages"].asInt() < 0){
        cout << "Bibliotheque invalide." << endl ;
        return false ;
    // Bibliotheque valide
    }else{
        return true ;
    }
}
