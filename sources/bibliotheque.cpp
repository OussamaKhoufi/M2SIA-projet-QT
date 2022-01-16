#include "../headers/bibliotheque.h"

/*Constructeurs*/
// Constructeur vide
Bibliotheque::Bibliotheque(){
    // Declaration des variables
    string nomNew ;                                             // Nom du nouveau fichier
    bool exist ;                                                // Variable pour verifier l'existance du fichier

    // Saisie du nom du nouveau fichier
    cout << "Veuillez donner le nom de la bibliotheque : " << endl ;
    cin >> nomNew ;

    // Verifier l'extension ".json"
    VerifierExtension(nomNew) ;

    nomNew = "/home/vm/M2SIA-projet-QT/DATA/Bibliothèques/" + nomNew ;
    exist = experimental::filesystem::exists(nomNew) ;  

    // Vérifier l'existance ou non du fichier
    if(exist){                                                  // Si le nom saisi existe
        cout << "Fichier existant." << endl ;

        Json::Reader reader ;                                   // Variable pour lire un fichie Json
        ifstream bibliothequeFile(nomNew, ios::in) ;            // Chargement du fichier Json

        // Verifier l'extension ".json"
        VerifierExtension(nomNew) ;
        // Lecture du fichier et copie du contenu dans la bibliotheque
        reader.parse(bibliothequeFile, _bibliotheque) ;    

    }else{                                                      // Sinon
        cout << "Fichier inexistant. Generer une nouvelle bibliotheque." << endl ;
        AjouterImage() ;
    }
    _cheminJson = nomNew;
}

// Constructeur avec le nom de la bibliotheque donnee par l'utilisateur
Bibliotheque::Bibliotheque(string nom){
    // Declaration des variables
    Json::Reader reader ;                       // Variable pour lire un fichie Json

    // Verifier l'extension ".json"
    VerifierExtension(nom) ;
    nom = "/home/vm/M2SIA-projet-QT/DATA/Bibliothèques/" + nom ;

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

// Construire et afficher une sous-liste
void Bibliotheque::ConstruireAfficherSousListe(){
    // Declaration des variables
    Json::Value biblio = getBilbiotheque() ;        // Objet Json
    int choix ;                                     // Choix du critere
    int choixPlage ;                                // Choix de la plage de cout
    int c ;                                         // Indice
    int compteur ;                                  // Compteur du nombre d'images choisies par critere
    string choixSource ;                            // Choix de la source
    double plageMin, plageMax ;                     // Plage de cout personalisee
    vector <string> listeSource ;                   // Liste des sources

    cout << "Veuillez choisir un critere : " << endl ;
    cout << "1. Cout" << endl << "2. Source" << endl ;
    cout << "Votre choix : " ;
    // Saisie du critere et verification
    do{
        // Saisie le choix
        cin >> choix ;
        // Validation du choix
        if ((choix != 1) && (choix != 2)){
            cout << "Choix invalide. Veuillez saisir '1' ou '2' : " ;
        }
    }while((choix != 1) && (choix != 2)) ;
    switch (choix){
        // Critere choisi : Cout
        case 1 :
            do{
                // Remise a zero le compteur
                compteur = 0 ;

                // Choix de la plage de cout
                cout << "Veuillez choisir une plage de cout :" << endl ;
                cout << "1. Gratuit" << endl << "2. Cout ≤ 99,99 €" << endl << "3. 100 ≤ Cout ≤ 999,99 €" << endl << "4. Cout > 1000 €" << endl << "5. Plage personnalisee" << endl ;
                cout << "Votre choix : " ; 
                // Saisie de la plage et validation
                do{
                    cin >> choixPlage ;
                    if ((choixPlage != 1) && (choixPlage != 2) && (choixPlage != 3) && (choixPlage != 4) && (choixPlage != 5)){
                        cout << "Choix invalide. Veuillez saisir '1', '2', '3', '4' ou '5' : " ;
                    }
                }while((choixPlage != 1) && (choixPlage != 2) && (choixPlage != 3) && (choixPlage != 4) && (choixPlage != 5)) ;  

                // Consitions personnalisee
                if(choixPlage == 5){
                    // Saisie de la plage de cout souhaitee
                    cout << "Veuillez saisir la plage de cout souhaitee : " << endl ; 
                    // Cout minimum
                    cout << "Min : " ;
                    do{
                        cin >> plageMin ;
                        if (plageMin < 0){
                            cout << "Veuillez choisir une valeur positive ou nulle." << endl ;
                        }
                    }while(plageMin < 0) ;
                    // Cout maximum
                    cout << "Max : " ;
                    do{
                        cin >> plageMax ;
                        if (plageMax < plageMin){
                            cout << "Veuillez choisir une valeur > " << plageMin << endl ;
                        }
                    }while(plageMax < plageMin) ;
                    cout << "Sous liste cree : " << endl ;
                    compteur = ConstruireAfficherSousListeCout(plageMin, plageMax) ;
                // Conditions standards
                }else{
                    cout << "Sous liste cree : " << endl ;
                    compteur = ConstruireAfficherSousListeCout(choixPlage) ;
                }
                cout << "Il y a " << compteur << " images dans la plage de cout personnalisee" << endl << endl ;
            }while(Continuer()) ;                
            break ;

        // Critere choisi : Source
        case 2 :
            // Creer la liste des sources
            listeSource.clear() ;
            listeSource = ListerSource(biblio) ;
            // Affichage des sources existantes
            cout << "Les sources existantes dans la bibliotheque : " << endl ;
            for(c = 0 ; c < (int)listeSource.size() ; c++){
                cout << listeSource[c] << endl ;
            }

            // Saisie et verification de la source souhaitee
            do{
                // Remise a zero le compteur
                compteur = 0 ;
                // Saisie
                cout << "Veuillez saisir une source souhaitee : " << endl ;
                cin >> choixSource ;
                // Si la source saisie est invalide
                if(VerifierExistance(listeSource, choixSource) == false){
                    cout << "Source invalide. Veuillez saisir une autre source." << endl ;
                // Affichage conditionnelle
                }else{
                    cout << "Sous liste cree : " << endl ;
                    compteur = ConstruireAfficherSousListeSource(choixSource) ;
                }
            }while(Continuer()) ;

            cout << "Il y a " << compteur << " images correspondates a cette source." << endl << endl ;
            break ;
        default :
            break ;
    }
}

// Trier la bibliotheque suivant une critere choisie 
void Bibliotheque::Trier(){
    // Declaration des variables
    Json::Value biblioTrie ;                                // Bibliotheque trie
    int choix ;                                             // Choix du critere pour trier la bibliotheque

    // Saisie et validation du choix de la critere pour trier
    //do{
        // Choix du critere de tri
        cout << "Tri dans l'ordre decroissant" << endl ; 
        cout << "1. Permission (acces)" << endl << "2. Chemin d'acces" << endl ;
        cout << "3. Cout" << endl ;
        // cout << "4. Date d'ajout" << endl << "5. Date de creation" << endl ;
        cout << "4. Numero" << endl << "5. Source" << endl << "6. Titre" << endl ;
        cout << "Votre choix : " ; 
        do{
            // Saisie le choix
            cin >> choix ;
            // Validation du choix
            if ((choix != 1) && (choix != 2) && (choix != 3) && (choix != 4) && (choix != 5) && (choix != 6)){
                cout << "Choix invalide. Veuillez saisir '1', '2', '3', '4', '5', '6' : " ;
            }
        }while((choix != 1) && (choix != 2) && (choix != 3) && (choix != 4) && (choix != 5) && (choix != 6)) ;

    // Affirmation du choix
    switch(choix){
            // Permission (acces)
            case 1 : 
                cout << "Critere choisi : Permission (acces) dans l'ordre decroissant" << endl ;
                biblioTrie = Trier(1) ;
                break ;
            // Chemin d'acces   
            case 2 : 
                cout << "Critere choisi : Chemin d'acces dans l'ordre decroissant" << endl ;
                biblioTrie = Trier(2) ;
                break ;     
            // Cout
            case 3 : 
                cout << "Critere choisi : Cout dans l'ordre decroissant" << endl ;
                biblioTrie = Trier(3) ;
                break ;
            // Date d'ajout
            /*case 4 :
                cout << "Critere choisi : Date d'ajout dans l'ordre decroissant" << endl ;
                break ;
            // Date de creation
            case 5 : 
                cout << "Critere choisi : Date de creation dans l'ordre decroissant" << endl ;
                break ;*/
            // Numero
            case 4 : 
                cout << "Critere choisi : Numero dans l'ordre decroissant" << endl ;
                biblioTrie = Trier(6) ;
                break ;
            // Source
            case 5 : 
                cout << "Critere choisi : Source dans l'ordre decroissant" << endl ;
                biblioTrie = Trier(7) ;
                break ;   
            // Titre    
            case 6 :
                cout << "Critere choisi : Titre dans l'ordre decroissant" << endl ;
                biblioTrie = Trier(8) ;
                break ;
            default : 
                break ;
        }

        // Affichage
        setBilbiotheque(biblioTrie) ;
        AfficherDescripteurs() ;

        /*// Sauvegardement
        if (Continuer("Voulez-vous sauvegarder ce resultat ? [Y/N] : ")){
            Sauvegarder() ;
        }*/
    //}while(Continuer("Voulez-vous continuer le tri ? [Y/N] : ")) ;
}

// Ajouter une image
void Bibliotheque::AjouterImage(){ 
    Json::Value biblio = getBilbiotheque() ; 
    int nbImages = biblio["images"].size() ;                            // Nombre d'images présent dans la bibliotheque avant l'ajout d'une nouvelle image  
    int indice = nbImages ;
    bool exist ;
    char decision ;
    bool valideDate ;                                                   // Variable pour valider la date d'ajout
    string jourAjout, moisAjout, anneeAjout ;                           // Variables pour la saisie de la date d'ajout de l'image
    string jourCreation, moisCreation, anneeCreation ;                  // Variables pour la saisie de la date d'ajout de l'image
    float nbReel ;                                                      // Variable pour la saisie en nombre reel
    string texte ;                                                      // Variable pour la saisie en texte

    // Boucle de saisir
    do{
        // Saisie : Acces
        cout << "Acces (P : Publique, R : Restreint) : " ;
        do{
            cin >> texte ;
            // Verification
            if ((texte != "P") && (texte != "R")){
                cout << "Sasie incorrecte. Veuillez saisir 'P' ou 'R' : " ;
            }
        }while((texte != "P") && (texte != "R")) ;
        biblio["images"][indice]["acces"] = texte ;

        // Saisie : Chemin acces
        cout << "Chemin d'acces : ./DATA/Images/" ;
        do{
            cin >> texte ;
            texte = "./DATA/Images/" + texte ;
            // Verifier l'existance du fichier
            exist = experimental::filesystem::exists(texte) ; 
            // Si le fichier n'existe pas
            if(exist == false){
                cout << "Ce fichier n'existe pas. Veuillez saisir un nom valide : ./DATA/Images/" ;
            }
        }while (exist == false) ;
        biblio["images"][indice]["cheminAcces"] = texte ;

        // Saisie : Cout
        cout << "Cout : " ;
        cin >> nbReel ;           
        biblio["images"][indice]["cout"] = nbReel ;

        // Saisie : Date de creation
        cout << "Date de creation (dd/mm/yyyy) : " ;
        texte = SaisirDate(jourCreation, moisCreation, anneeCreation) ;
        biblio["images"][indice]["dateCreation"] = texte ;

        // Saisie : Date d'ajout
        do{  
            cout << "Date d'ajout (dd/mm/yyyy) : " ;
            texte = SaisirDate(jourAjout, moisAjout, anneeAjout) ;
            // Si la date d'ajout est superieure ou egale a la date de creation
            if((stoi(anneeAjout + moisAjout + jourAjout) - stoi(anneeCreation + moisCreation + jourCreation)) < 0){
                cout << "La date d'ajout doit etre superieure ou egale a la date de creation. Veuillez reessayer." << endl ;
                valideDate = false ;
            }else{                      
                valideDate = true ;
            }
        }while(valideDate == false) ;
        
        biblio["images"][indice]["dateAjout"] = texte ;

        // Numero de l'image
        biblio["images"][indice]["numero"] = indice + 1 ;

        // Saisie : Source
        cout << "Source : " ;
        cin >> texte ;
        biblio["images"][indice]["source"] = texte ;

        // Saisie : Titre
        cout << "Titre : " ;
        cin >> texte ;
        biblio["images"][indice]["titre"] = texte ;
        biblio["nbImages"] = indice + 1 ;

        // Incrementation de l'indice de la boucle
        indice++ ;

    }while(Continuer()) ;

    setBilbiotheque(biblio) ;

    // Decision de sauvegarder
    cout << "Voulez-vous sauvegarder ce resultat ? [Y/N]" << endl ;
    do{
        cin >> decision ;
        if ((decision != 'Y') && (decision != 'N')){
            cout << "Choix invalide. Veuillez saisir 'Y' ou 'N'." << endl ;
        }
    } while((decision != 'Y') && (decision != 'N')) ;

    // Sauvegardement
    if (decision == 'Y'){
        Sauvegarder() ;
    }    
}

// Supprimer une image bibliotheque
void  Bibliotheque::SupprimerImage(){
    // Declaration des variables
    Json::Value removed ;
    Json::Value biblio = getBilbiotheque() ;
    string numeroSaisi ;
    int numero ;
    int nbImages = biblio["images"].size() ;     // Nombre d'images présent dans la bibliotheque avant la suppresion d'une nouvelle image
    

    do{
        // Saisir du numéro de l'image à supprimer
        cout << "Entrez le numero de l'image a supprimer"<< endl ;
        cin >> numeroSaisi ;

        // Verifier le format du numero saisi
        if(VerifierNumero(numeroSaisi, numero)){
            // Verifier l'existance du numero saisi
            if(VerifierNumero(numero, getBilbiotheque())){
                int indexImage = 0 ;
                for(const auto & obj : biblio["images"]) {
                    if (obj["numero"] == numero) {
                        // Supprésion dans le vecteur images des élèment associer à ce numéro
                        biblio["images"].removeIndex(indexImage, &removed);
                        // Mise à Jour sur le nombre d'image.
                        biblio["nbImages"] = nbImages - 1 ;
                    }
                    //Incrémenter l'index Images
                    indexImage++;
                }
                
                // Mise à jour de la bibliothèque
                setBilbiotheque(biblio);
            }else{
                cout << "Ce numero n'existe pas. " ;
            }
        }else{
            cout << "Format invalide. " ;
        }
    }while(Continuer("Voulez-vous saisir un autre numero ? [Y/N] : ") && VerifierBibliotheque()) ;
}

// Sauvegarder une bibliotheque
void Bibliotheque::Sauvegarder(){
    // Declaration des variables
    string nomNew ;                                                     // Nom du nouveau fichier
    bool exist ;                                                        // Variable pour verifier l'existance du fichier
    ofstream bibliotheque_new ;                                         // Objet fichier
    Json::StyledWriter styledWriter;                                    // Writer Json
    
    // Verifier l'existance ou non du fichier
    cout << "Veuillez donner un nom au fichier de resultat : " << endl ;
 
    cin >> nomNew ; 
    VerifierExtension(nomNew) ;
    nomNew = "./DATA/Bibliothèques/" + nomNew ;
    exist = experimental::filesystem::exists(nomNew) ;
    if(exist){
        cout << "Ce fichier existe deja. Le sauvegardement va ecraser le fichier existant." << endl ;
        if(Continuer()){
            bibliotheque_new.open(nomNew) ;                             // Ouvrir le fichier
            bibliotheque_new << styledWriter.write(getBilbiotheque());  // Ecrire
            bibliotheque_new.close();                                   // Fermer le fichier
        }
    }else{
        bibliotheque_new.open(nomNew) ;                                 // Ouvrir le fichier
        bibliotheque_new << styledWriter.write(getBilbiotheque());      // Ecrire
        bibliotheque_new.close();                                       // Fermer le fichier        
    }
    cout << "Bibliotheque sauvegardee." << endl ;
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
int Bibliotheque::ConstruireAfficherSousListeCout(const int choix){
    // Declaration des variables
    int c ;                                         // Indice
    int compteur = 0 ;                              // Compteur des images dans la sous liste
    Json::Value biblio = getBilbiotheque() ;        // Bibliotheque
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images dans la bibliotheque

    switch (choix){
        // Sous-critere : Cout gratuit
        case 1 :
            // Affichage conditionnelle
            for (c = 0 ; c < nbImages ; c++){
                if (biblio["images"][c]["cout"].asDouble() == 0.0){
                    // Affichage des descripteur
                    AfficherDescripteurs(biblio, c) ;
                    // Incrementation du compteur 
                    compteur++ ;
                }
            }
            break ;

        // Sous-critere : Cout ≤ 99,99 €
        case 2 :
            // Affichage conditionnelle
            for (c = 0 ; c < nbImages ; c++){
                if (biblio["images"][c]["cout"].asDouble() <= 99.99){
                    // Affichage des descripteur
                    AfficherDescripteurs(biblio, c) ;
                    // Incrementation du compteur 
                    compteur++ ;
                }
            }
            break ;  

        // Sous-critere : 100 ≤ Cout ≤ 999,99 €
        case 3 :
            // Affichage conditionnelle
            for (c = 0 ; c < nbImages ; c++){
                if ((biblio["images"][c]["cout"].asDouble() >= 100) && (biblio["images"][c]["cout"].asDouble() <= 999.99)){
                    // Affichage des descripteur
                    AfficherDescripteurs(biblio, c) ;
                    // Incrementation du compteur 
                    compteur++ ;
                }
            }
            break ;  

        // Sous-critere : Cout > 1000 €
        case 4 :
            // Affichage conditionnelle
            for (c = 0 ; c < nbImages ; c++){
                if (biblio["images"][c]["cout"].asDouble() > 1000){
                    // Affichage des descripteur
                    AfficherDescripteurs(biblio, c) ;
                    // Incrementation du compteur 
                    compteur++ ;
                }
            }
            break ;  
        default :
            break ;
    }

    // Retour
    return compteur ;
}

// Construire et afficher une sous-liste en fonction du cout (derniere option)
int Bibliotheque::ConstruireAfficherSousListeCout(double coutMin, double coutMax){
    // Declaration des variables
    int c ;                                         // Indice
    int compteur = 0 ;                              // Compteur des images dans la sous liste
    Json::Value biblio = getBilbiotheque() ;        // Bibliotheque
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images dans la bibliotheque

    for (c = 0 ; c < nbImages ; c++){
        if ((biblio["images"][c]["cout"].asDouble() >= coutMin) && (biblio["images"][c]["cout"].asDouble() <= coutMax)){
            // Affichage des descripteur
            AfficherDescripteurs(biblio, c) ;
            // Incrementation du compteur 
            compteur++ ;
        }
    }    

    // Retour
    return compteur ;
} 

// Construire et afficher une sous-liste en fonction de la source
int Bibliotheque::ConstruireAfficherSousListeSource(const string source){
    // Declaration des variables
    int c ;                                         // Indice
    int compteur = 0 ;                              // Compteur des images dans la sous liste
    Json::Value biblio = getBilbiotheque() ;        // Bibliotheque
    int nbImages = biblio["nbImages"].asInt() ;     // Nombre d'images dans la bibliotheque

    for (c = 0 ; c < nbImages ; c++){
        if (biblio["images"][c]["source"].asString() == source){
           // Affichage des descripteur
            AfficherDescripteurs(biblio, c) ;
            // Incrementation du compteur 
            compteur++ ;
        }
    }

    // Retour
    return compteur ;
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
        // Permission (acces)
        case 1 : 
            // Initialiser vecteur des permissions
            for (c = 0 ; c < nbImages ; c++){
                texteNonTri.push_back(biblioNonTrie["images"][c]["acces"].asString()) ;
            }
            indice = Trier(texteNonTri) ;        
            break ;

        // Chemin d'acces   
        case 2 : 
            // Initialiser vecteur des chemins d'acces
            for (c = 0 ; c < nbImages ; c++){
                texteNonTri.push_back(biblioNonTrie["images"][c]["cheminAcces"].asString()) ;
            }
            indice = Trier(texteNonTri) ;        
            break ;     

        // Cout
        case 3 : 
            // Initialiser vecteur des couts
            for (c = 0 ; c < nbImages ; c++){
                reelNonTri.push_back(biblioNonTrie["images"][c]["cout"].asDouble()) ;
            }
            indice = Trier(reelNonTri) ;
            break ;

        // Date d'ajout
        case 4 :
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

        // Date de creation
        case 5 : 
            // Initialiser vecteur des dates de creation
            for (c = 0 ; c < nbImages ; c++){
                valeurTemp.push_back(biblioNonTrie["images"][c]["dateCreation"].asString()) ;
            }
            // Inverser la position des elements de la date pour trier
            for(c = 0 ; c < nbImages ; c++){
                ExtraireDate(valeurTemp[nbImages - 1 - c], jour, mois, annee) ;
                cout << stoi(annee + mois + jour) << endl ;
                entierNonTri.push_back(stoi(annee + mois + jour)) ;
            }
            indice = Trier(entierNonTri) ; 
            break ;

        // Numero
        case 6 : 
            // Initialiser vecteur des numeros
            for (c = 0 ; c < nbImages ; c++){
                entierNonTri.push_back(biblioNonTrie["images"][c]["numero"].asInt()) ;
            }
            indice = Trier(entierNonTri) ;          
            break ;

        // Source
        case 7 : 
            // Initialiser vecteur des sources
            for (c = 0 ; c < nbImages ; c++){
                texteNonTri.push_back(biblioNonTrie["images"][c]["titre"].asString()) ;
            }
            indice = Trier(texteNonTri) ;        
            break ;   

        // Titre    
        case 8 :
            // Initialiser vecteur des titres
            for (c = 0 ; c < nbImages ; c++){
                texteNonTri.push_back(biblioNonTrie["images"][c]["titre"].asString()) ;
            }
            indice = Trier(texteNonTri) ;
            break ;

        default : 
            break ;
    }

    // Tri de la bibliotheque
    biblioTrie = biblioNonTrie ;                                                // Initialisation
    for (c = 0 ; c < nbImages ; c++){                                           // Remplir la bibliotheque triee
        biblioTrie["images"][c] = biblioNonTrie["images"][indice[c]] ;      
    }

    // Retour
    return biblioTrie ;
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
