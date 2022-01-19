#include "headers/image.h"

/*Constructeurs*/
// Constructeur vide
Image::Image()
{
    bool validation ;                                                                   // Validation du numero saisi
    int numero ;                                                                        // Numero de l'image
    int c ;                                                                             // Indice
    string nbSaisi ;                                                                    // Numero saisi par l'utilisateur
    Json::Value biblio ;                                                                // Objet Json
    Json::Reader reader ;                                                               // Variable pour la lecture d'un fichier Json

    ifstream bibliotheque_file("/home/vm/M2SIA-projet-QT/DATA/Bibliothèques/bibliotheque.json", ios::in) ;     // Charger le contenu du fichier json
    reader.parse(bibliotheque_file, biblio) ;                                           // Importer le contenu a l'objet Json

    // Saisir et valider le numero de l'image
    cout << "Veuillez saisir le numero de l'image souhaitee : " ;
    do{
        // Saisie
        cin >> nbSaisi ;
        // Validation du format
        validation = VerifierNumero(nbSaisi, numero) ;
        cout << "Here" << endl ;
        if(validation){
            // Validation du numero
            validation = VerifierNumero(numero, biblio) ;
            if(validation == false){
                cout << "Ce numero n'existe pas. Veuillez saisir un autre numero : " ;
            }
        }else{
            cout << "Format invalide. Veuillez saisir un autre numero : " ;
        }
    }while(validation == false) ;

    // Affectuer des attributs
    for(c = 0 ; c < biblio["nbImages"].asInt() ; c++){
        if(biblio["images"][c]["numero"].asInt() == numero){
            _cheminAccesContenu = biblio["images"][c]["cheminAcces"].asString() ;
            _source = biblio["images"][c]["source"].asString() ;
            _titre = biblio["images"][c]["titre"].asString() ;
            _numero = biblio["images"][c]["numero"].asInt() ;
            _cout = biblio["images"][c]["cout"].asDouble() ;
            _acces = biblio["images"][c]["acces"].asString() ;
            _dateAjout = biblio["images"][c]["dateAjout"].asString() ;
            _dateCreation = biblio["images"][c]["dateCreation"].asString() ;
            _cheminJson = "./DATA/bibliotheque.json" ;
            _numeroJson = c ;
            break ;
        }
    }

}

// Constructeur avec le chemin vers la bibliotheque connu
Image::Image(string chemin)
{
    bool validation ;                                                           // Validation du numero saisi
    int numero ;                                                                // Numero de l'image
    int c ;                                                                     // Indice
    bool exist ;                                                                // Variable pour verifier l'existance du fichier
    char decision ;                                                             // Condition d'arret de la boucle
    string nbSaisi ;                                                            // Numero saisi par l'utilisateur
    Json::Value biblio ;                                                        // Objet Json
    Json::Reader reader ;                                                       // Variable pour la lecture du fichier Json

    VerifierExtension(chemin) ;                                                 // Verifier l'existance de l'xension ".json"
    exist = experimental::filesystem::exists(chemin) ;                          // Verifier l'existace du fichier
    do{
        decision = 'N' ;
        // Verifier l'existance du fichier
        if (exist){                                                             // Si le fichier existe
            ifstream bibliotheque_file(chemin, ios::in) ;                       // Charger le contenu du fichier json
            reader.parse(bibliotheque_file, biblio) ;                           // Importer le contenu a l'objet Json

            // Saisir et valider le numero de l'image
            cout << "Veuillez saisir le numero de l'image souhaitee : " << endl ;
            do{
                // Saisie
                cin >> nbSaisi ;
                // Validation du format
                validation = VerifierNumero(nbSaisi, numero) ;
                if(validation){
                    // Validation du numero
                    validation = VerifierNumero(numero, biblio) ;
                    if(validation == false){
                        cout << "Ce numero n'existe pas. Veuillez saisir un autre numero : " ;
                    }
                }else{
                    cout << "Format invalide. Veuillez saisir un autre numero : " ;
                }
            }while(validation == false) ;

            // Affectuer des attributs
            for(c = 0 ; c < biblio["nbImages"].asInt() ; c++){
                if(biblio["images"][c]["numero"].asInt() == numero){
                    _cheminAccesContenu = biblio["images"][c]["cheminAcces"].asString() ;
                    _source = biblio["images"][c]["source"].asString() ;
                    _titre = biblio["images"][c]["titre"].asString() ;
                    _numero = biblio["images"][c]["numero"].asInt() ;
                    _cout = biblio["images"][c]["cout"].asDouble() ;
                    _acces = biblio["images"][c]["acces"].asString() ;
                    _dateAjout = biblio["images"][c]["dateAjout"].asString() ;
                    _dateCreation = biblio["images"][c]["dateCreation"].asString() ;
                    _cheminJson = chemin ;
                    _numeroJson = c ;
                    break ;
                }
            }
        // Si le fichier n'existe pas
        }else{
            cout << "Fichier non exist" << endl ;
            // Si l'utilisateur veut continuer
            if (Continuer("Voulez-vous saisir un autre chemin ? [Y/N] : ")){
                cout << "Nouveau chemin : ./DATA/Bibliothèques/" ;
                // Saisir un autre chemin
                cin >> chemin ;
                // Completer le chemin
                chemin = "./DATA/Bibliothèques/" + chemin ;
                decision = 'Y' ;
            }
        }
    }while(decision == 'Y') ;
}

// Constructeur avec le chemin vers la bibliotheque et le numero de l'image connus
Image::Image(string chemin, int numero){
    // Declaration des variables
    bool exist ;                                                                // Variable pour verifier l'existance du fichier
    char decision ;                                                             // Condition d'arret de la boucle
    int c ;                                                                     // Indice
    string numeroSaisi ;                                                        // Numero saisi par l'utilisateur
    Json::Value biblio ;                                                        // Objet Json
    Json::Reader reader ;                                                       // Variable pour la lecture du fichier Json

    VerifierExtension(chemin) ;                                                 // Verifier l'existance de l'xension ".json"
    exist = experimental::filesystem::exists(chemin) ;                          // Verifier l'existace du fichier

    do{
        decision = 'N' ;
        if (exist){                                                             // Si le fichier existe
            ifstream bibliotheque_file(chemin, ios::in) ;                       // Charger le contenu du fichier json
            reader.parse(bibliotheque_file, biblio) ;                           // Importer le contenu a l'objet Json

            // Verifier le numero de l'image et saisir un autre numero en cas d'erreur
            while(VerifierNumero(numero, biblio) == false){
                cout << "Ce numero n'existe pas. Veuillez saisir un autre numero : " ;
                do{
                    cin >> numeroSaisi ;
                    if(VerifierNumero(numeroSaisi, numero) == false){
                        cout << "Format invalide. Veuillez saisir un autre numero : " ;
                    }
                }while(VerifierNumero(numeroSaisi, numero) == false) ;
            }

            // Affectuer des attributs
            for(c = 0 ; c < biblio["nbImages"].asInt() ; c++){
                if(biblio["images"][c]["numero"].asInt() == numero){
                    _cheminAccesContenu = biblio["images"][c]["cheminAcces"].asString() ;
                    _source = biblio["images"][c]["source"].asString() ;
                    _titre = biblio["images"][c]["titre"].asString() ;
                    _numero = biblio["images"][c]["numero"].asInt() ;
                    _cout = biblio["images"][c]["cout"].asDouble() ;
                    _acces = biblio["images"][c]["acces"].asString() ;
                    _dateAjout = biblio["images"][c]["dateAjout"].asString() ;
                    _dateCreation = biblio["images"][c]["dateCreation"].asString() ;
                    _cheminJson = chemin ;
                    _numeroJson = c ;
                    break ;
                }
            }
        // Si le fichier n'existe pas
        }else{
            cout << "Fichier non exist" << endl ;
            // Si l'utilisateur veut continuer
            if (Continuer("Voulez-vous saisir un autre chemin ? [Y/N] : ")){
                cout << "Nouveau chemin : ./DATA/Bibliothèques/" ;
                // Saisir un autre chemin
                cin >> chemin ;
                // Completer le chemin
                chemin = "./DATA/Bibliothèques/" + chemin ;
                decision = 'Y' ;
            }
        }
    }while(decision == 'Y') ;
}

// Constructeur avec un objet bibliotheque et le numero de l'image connu
Image::Image(Bibliotheque objBiblio, int numImage){
    // Declaration des variables
    int c  ;                                                    // Indice
    Json::Value biblioJson = objBiblio.getBilbiotheque();       // Bibliotheque

    // Affectuer des attributs
    for(c = 0 ; c < biblioJson["nbImages"].asInt() ; c++){
        if(biblioJson["images"][c]["numero"].asInt() == numImage){
            _cheminAccesContenu = biblioJson["images"][c]["cheminAcces"].asString() ;
            _source = biblioJson["images"][c]["source"].asString() ;
            _titre = biblioJson["images"][c]["titre"].asString() ;
            _numero = biblioJson["images"][c]["numero"].asInt() ;
            _cout = biblioJson["images"][c]["cout"].asDouble() ;
            _acces = biblioJson["images"][c]["acces"].asString() ;
            _dateAjout = biblioJson["images"][c]["dateAjout"].asString() ;
            _dateCreation = biblioJson["images"][c]["dateCreation"].asString() ;
            _cheminJson = objBiblio.getCheminJson() ;
            _numeroJson = c ;
            break ;
        }
    }
}

/*Getters*/
// Chemin d'acces
string Image::getCheminAccesContenu() const {
    return _cheminAccesContenu ;
}
// Source
string Image::getSource() const {
    return _source ;
}
// Titre
string Image::getTitre() const {
    return _titre ;
}
// Numero
int Image::getNumero() const {
    return _numero ;
}
// Cout
double Image::getCout() const {
    return _cout ;
}
// Permission
string Image::getAcces() const {
    return _acces ;
}
// Date d'ajout
string Image::getDateAjout() const {
    return _dateAjout ;
}
// Date de creation
string Image::getDateCreation() const {
    return _dateCreation ;
}
// Chemin Json
string Image::getCheminJson() const {
    return _cheminJson ;
}
// Numero Json
int Image::getNumeroJson() const {
    return _numeroJson ;
}

/*Setters*/
// Chemin d'acces
void Image::setCheminAccesContenu(const string cheminAccesContenu){
    _cheminAccesContenu = cheminAccesContenu ;
}
// Source
void Image::setSource(const string source){
    _source = source ;
}
// Titre
void Image::setTitre(const string titre){
    _titre = titre ;
}
// Numero
void Image::setNumero(const int numero){
    _numero = numero ;
}
// Cout
void Image::setCout(const double cout){
    _cout = cout ;
}
// Permission
void Image::setAcces(const string acces){
    _acces = acces ;
}
// Date d'ajout
void Image::setDateAjout(const string dateAjout){
    _dateAjout = dateAjout ;
}
// Date de creation
void Image::setDateCreation(const string dateCreation){
    _dateCreation = dateCreation ;
}
// Chemin Json
void Image::setCheminJson(const string cheminJson){
    _cheminJson = cheminJson ;
}
// Numero Json
void Image::setNumeroJson(const int numeroJson){
    _numeroJson = numeroJson ;
}

/*Methodes principales*/
// Afficher le contenu de l'image
void Image::AfficherContenuImage(){
    // Declaration des variables
    Mat image = imread(getCheminAccesContenu()) ;   // Charger l'image
    string windowName = getTitre() ;                // Nom de la fenetre d'affichage

    // Affichage
    namedWindow(windowName, WINDOW_NORMAL) ;
    imshow(windowName, image);
    waitKey(0) ;
    destroyWindow(windowName) ;
}

// Afficher les descripteurs de l'image
void Image::AfficherDescripteurImage(){
    // Afficher les descripteurs de l'image
    cout << "Chemin :" << getCheminAccesContenu() << endl ;
    cout << "Source :" << getSource() << endl ;
    cout << "Titre :" << getTitre() << endl ;
    cout << "Numero :" << getNumero() << endl ;
    cout << "Cout :" << getCout() << endl ;
    cout << "Acces :" << getAcces() << endl ;
    cout << "Date d'ajout :" << getDateAjout() << endl ;
    cout << "Date de creation :" << getDateCreation() << endl ;
}

// Modifier les descripteurs de l'image (saisie & affichage)
void Image::ModifierDescripteurImage(){
    // Declaration des variables
    bool validation ;                                                               // Variable booleenne pour valider les conditions
    int choix ;                                                                     // Choix des actions (entier)
    string saisie ;                                                                 // Choix des actions (chaine de caracteres)
    string nouveauTexte ;                                                           // Variable pour la saisie des chaines de caractere
    string jourAjout, moisAjout, anneeAjout ;                                       // Jour, Mois, Annee d'ajout
    string jourCreation, moisCreation, anneeCreation ;                              // Jour, Mois, Annee de creation
    string dateAjout, dateCreation ;                                                // Date d'ajout, date de creation
    vector<int> erreur ;                                                            // Vecteur des erreurs
    Json::StyledWriter styledWriter;                                                // Writer Json
    Json::Value biblio ;                                                            // Objet Json
    Json::Reader reader ;                                                           // Variable pour la lecture du fichier Json

    ifstream bibliotheque_file(getCheminJson(), ios::in) ;                          // Charger le contenu du fichier json
    reader.parse(bibliotheque_file, biblio) ;                                       // Importer le contenu a l'objet Json

    do{
        // Afficher les choix
        cout << "Liste des descripteurs : " << endl ;
        cout << "1.Chemin" << endl << "2.Source" << endl << "3.Titre" << endl ;
        cout << "4.Numero" << endl << "5.Cout" << endl << "6.Acces" << endl ;
        cout << "7.Date d'ajout" << endl << "8.Date de Creation" << endl ;
        cout << "Veuillez saisir un choix : " ;
        do{
            validation = true ;
            // Saisir le choix
            cin >> saisie ;
            if(VerifierNumero(saisie, choix)){
                // Verifier le choix
                if(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 && choix != 8){
                    cout << "Veuillez saisir un choix compris entre 1 et 8 : " ;
                    validation = false ;
                }
            }else{
                cout << "Le choix doit etre un entier. Veuillez saisir un choix valide : " ;
                validation = false ;
            }
        }while(validation == false) ;

        // Modification des descripteurs
        do{
            erreur.clear() ;
            switch (choix){
            // Chemin d'acces
            case 1 :
                cout << "Veuillez saisir le nouveau chemin d'acces : ./DATA/Images/" ;
                break ;
            // Source
            case 2 :
                cout << "Veuillez saisir la nouvelle source : " ;
                break ;
            // Titre
            case 3 :
                cout << "Veuillez saisir le nouveau titre : " ;
                break ;
            // Numero
            case 4 :
                cout << "Veuillez saisir le nouveau numero : " ;
                break ;
            // Cout
            case 5 :
                cout << "Veuillez saisir le nouveau cout : " ;
                break ;
            // Acces (Permission)
            case 6 :
                cout << "Veuillez saisir le nouveua acces : " ;
                break ;
            // Date d'ajout
            case 7 :
                cout << "Veuillez saisir la nouvelle date d'ajout : " ;
                break ;
            //Date de creation
            case 8 :
                cout << "Veuillez saisir la nouvelle date de creation : " ;
            default:
                break;
            }
            cin >> nouveauTexte ;
            erreur = ModifierDescripteurImage(choix, nouveauTexte, biblio) ;
            ModifierDescripteurImage(erreur) ;
        }while((int)erreur.size() != 0) ;

    }while(Continuer("Voulez-vous effectuer autres modifications ? [Y/N] : ")) ;
}

// Modifier un descripteur de l'image (verification et affectation)
vector<int> Image::ModifierDescripteurImage(const int choix, const string saisie, Json::Value& biblio){
    // Declaration des variables
    int c ;                                                 // Indice
    int nouveauEntier ;                                     // Nouvelle valeur (entiere)
    double nouveauReel ;                                    // Nouvelle valeur (reelle)
    string nouveauTexte ;                                   // Nouvelle valeur (chaine de caractere)
    string jourAjout, moisAjout, anneeAjout ;               // Date d'ajout
    string jourCreation, moisCreation, anneeCreation ;      // Date de creation
    vector<int> erreur ;                                    // Vecteur des erreurs : 0-format, 1...8-champ
    vector<int> erreurDate ;                                // Vecteur des erreurs liees a la saisie de la date

    // Initialisation
    erreur.clear() ;
    erreurDate.clear() ;

    switch (choix){
        // Chemin d'acces
        case 1 :
            // Completer le chemin
            nouveauTexte = "./DATA/Images/" + saisie ;
            // Si le chemin est invalide
            if(experimental::filesystem::exists(nouveauTexte) == false){
                // Erreur : Chemin invalide
                erreur.push_back(1) ;
            // Sinon : Chemin d'acces est valide
            }else{
                // Modifier le chemin de l'image
                setCheminAccesContenu(nouveauTexte) ;
                biblio["images"][getNumeroJson()]["cheminAcces"] = nouveauTexte ;
            }
            break ;

        // Source
        case 2 :
            nouveauTexte = saisie ;
            // Modifier la source de l'image
            setSource(nouveauTexte) ;
            biblio["images"][getNumeroJson()]["source"] = nouveauTexte ;
            break ;

        // Titre
        case 3 :
            nouveauTexte = saisie ;
            // Modifier le titre de l'image
            setTitre(nouveauTexte) ;
            biblio["images"][getNumeroJson()]["titre"] = nouveauTexte ;
            break ;

        // Numero
        case 4 :
            // Si la saisie est un numero
            if(VerifierNumero(saisie, nouveauEntier)){
                // Si le numero existe deja dans la bibliotheque
                if(VerifierNumero(nouveauEntier, biblio)){
                    // Erreur : Numero existant
                    erreur.push_back(4) ;
                    erreur.push_back(1) ;
                // Si le numero est negatif
                }else if(nouveauEntier < 0){
                    erreur.push_back(4) ;
                    erreur.push_back(2) ;
                // Sinon : numero valide
                }else{
                    // Modifier le numero de l'image
                    setNumero(nouveauEntier) ;
                    biblio["images"][getNumeroJson()]["numero"] = nouveauEntier ;
                }
            // Erreur de format
            }else{
                erreur.push_back(4) ;
                erreur.push_back(0) ;
            }
            break ;

        // Cout
        case 5 :
            // Verifier le format de la valeur saisie
            if(VerifierNumero(saisie, nouveauReel)){
                // Si le cout est negatif
                if(nouveauReel < 0){
                    // Erreur : Cout invalide
                    erreur.push_back(5) ;
                // Sinon : Cout est valide
                }else{
                    setCout(nouveauReel) ;
                    biblio["images"][getNumeroJson()]["cout"] = nouveauReel ;
                }
            // Erreur de format
            }else{
                erreur.push_back(5) ;
                erreur.push_back(0) ;
            }
            break ;

        // Acces (Permission)
        case 6 :
            // Si la saisie est incorrecte
            if((nouveauTexte != "P") && (nouveauTexte != "R")){
                // Erreur : Acces invalide
                erreur.push_back(6) ;
            // Sinon : Acces est valide
            }else{
                // Modifier l'acces de l'image
                setAcces(nouveauTexte) ;
                biblio["images"][getNumeroJson()]["acces"] = nouveauTexte ;
            }
            break ;

        // Date d'ajout
        case 7 :
            // Verifier les erreurs de la sasiie de la date
            erreurDate = VerifierDate(saisie, jourAjout, moisAjout, anneeAjout) ;
            // S'il n'y a aucune erreur
            if(erreurDate.empty()){
                // Extraction de la date de creation pour comparer avec la date d'ajout
                ExtraireDate(biblio["images"][getNumeroJson()]["dateAjout"].asString(), jourCreation, moisCreation, anneeCreation) ;
                // Si la date d'ajout est inferieure a la date de creation
                if((stoi(anneeAjout + moisAjout + anneeAjout))- (stoi(anneeCreation + moisCreation + jourCreation)) < 0){
                    // Erreur : Date d'ajout est inferieure a la date de creation
                    erreur.push_back(7) ;
                // Sinon : Date d'ajout est valide
                }else{
                    // Modifer la date d'ajout de l'image
                    setDateAjout(saisie) ;
                    biblio["images"][getNumeroJson()]["dateAjout"] = saisie ;
                }
            // S'il y a des erreurs
            }else{
                erreur.push_back(7) ;
                for(c = 0 ; c < (int)erreurDate.size() ; c++){
                    erreur.push_back(erreurDate[c]) ;
                }
            }
            break ;

        // Date de creation
        case 8 :
            // Verifier les erreurs de la sasiie de la date
            erreurDate = VerifierDate(saisie, jourCreation, moisCreation, anneeCreation) ;
            // S'il n'y a aucune erreur
            if(erreurDate.empty()){
                // Extraction de la date d'ajout pour comparer avec la date de creation
                ExtraireDate(biblio["images"][getNumeroJson()]["dateAjout"].asString(), jourAjout, moisAjout, anneeAjout) ;
                // Si la date de creation est superieure a la date de creation
                if((stoi(anneeAjout + moisAjout + anneeAjout))- (stoi(anneeCreation + moisCreation + jourCreation)) < 0){
                    // Erreur : Date de creation est superieure a la date de creation
                    erreur.push_back(8) ;
                // Sinon : Date de creation est valide
                }else{
                    // Modifer la date d'ajout de l'image
                    setDateCreation(saisie) ;
                    biblio["images"][getNumeroJson()]["dateCreation"] = saisie ;
                }
            // S'il y a des erreurs
            }else{
                erreur.push_back(8) ;
                for(c = 0 ; c < (int)erreurDate.size() ; c++){
                    erreur.push_back(erreurDate[c]) ;
                }
            }
            break ;

        default :
            break ;
    }

    // Retour
    return erreur ;
}

// Afficher les erreurs de la modification d'un descripteur de l'image
void Image::ModifierDescripteurImage(const vector<int> erreur){
    // Declaration de variable
    int c ;             // Indice

    // Affichage des erreurs
    // S'il y a au moins une erreur
    if((int)erreur.size() > 0){
        switch(erreur[0]){
            // Chemin d'acces
            case 1 :
                cout << "Ce chemin d'acces n'existe pas." << endl ;
            // Source
            case 2 :
                break ;
            // Titre
            case 3 :
                break ;
            // Numero
            case 4 :
                switch (erreur[1]){
                    case 0 :
                        cout << "Le numero doit etre un entier." << endl ;
                        break;
                    case 1 :
                        cout << "Cenumero est deja utilise dans la bibliotheque." << endl ;
                        break ;
                    case 2 :
                        cout << "Le numero doit etre positif ou nul." << endl ;
                        break ;
                    default:
                        break;
                }
                break ;
            // Cout
            case 5 :
                if(((int)erreur.size() > 1) && (erreur[1] == 0)){
                    cout << "Le cout doit eter un reel." << endl ;
                }else{
                    cout << "Le cout doit etre positif ou nul." << endl ;
                }
                break ;
            // Acces (Permission)
            case 6 :
                cout << "Acces doit etre 'P' ou 'R'." << endl ;
                break ;
            // Date d'ajout
            case 7 :
                if((int)erreur.size() == 1){
                    cout << "La date d'ajout doit etre superieure ou egale a la date de creation." << endl ;
                }else{
                    for(c = 1 ; c < (int)erreur.size() ; c++){
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
                }
                break ;
            // Date de creation
            case 8 :
                if((int)erreur.size() == 1){
                    cout << "La date de creation doit etre inferieure ou egale a la date d'ajout." << endl ;
                }else{
                    for(c = 1 ; c < (int)erreur.size() ; c++){
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
                }
                break ;

            default :
                break ;
        }
    }
}

/*
// Traitement de l'image
void Image::TraitementImage(int choixTraitement){
    Mat image = imread(getCheminAccesContenu(),IMREAD_COLOR) ;                                   // Charger l'image
    Mat imageResultat;
    string titreFigure;
    string stringSaisi;
    bool traitementFini;

    switch (choixTraitement){
        case 1 :
        imageResultat = ImageMonochrome(image) ;
        titreFigure = "Image en Niveau de Gris";
        break;
        case 2 :
        imageResultat = ImageInversement(image) ;
        titreFigure="Image en Négatif";
        break;
        case 3 :
        int choix;
        cout << endl << "Pour choisir une composante à afficher tapez : " << endl;
        cout << endl << "1 pour la composante Rouge." << endl;
        cout << endl << "2 pour la composante Verte." << endl;
        cout << endl << "3 pour la composante Bleue." << endl;
        do {
            traitementFini= true;
            cout << endl << "Votre choix :";
            cin >> stringSaisi;
            if (VerifierNumero(stringSaisi,choix)){
                if (choix==1){
                    imageResultat = ImageExtractionCouleur(image,1) ;
                    titreFigure = "Composante Rouge de l'Image en Couleur" ;
                }else if(choix==2){
                    imageResultat = ImageExtractionCouleur(image,2) ;
                    titreFigure = "Composante Verte de l'Image en Couleur" ;
                }else if(choix==3){
                    imageResultat = ImageExtractionCouleur(image,3) ;
                    titreFigure = "Composante Bleue de l'Image en Couleur" ;
                }else {
                    cout << endl <<"Choix non valide : il faut choisir 1,2 ou 3 !" << endl ;
                    traitementFini= false;
                }
            }else{
                cout << endl <<"Choix non valide : il faut un des entiers {1,2,3}" << endl ;
                traitementFini= false;
            }
        }while(traitementFini==false);
        break;
        case 4 :
        imageResultat = ImageRehaussementContraste(ImageMonochrome(image),1) ;
        titreFigure = "Image apres Normalisation" ;
        break;
        case 5 :
        imageResultat = ImageRehaussementContraste(ImageMonochrome(image),2) ;
        titreFigure = "Image apres Egalisation" ;
        break;
        case 6 :
        imageResultat = ImageFiltrage(ImageMonochrome(image),1) ;
        titreFigure = "Image Filtree avec Filtre Moyenneur 3x3" ;
        break;
        case 7 :
        imageResultat = ImageFiltrage(ImageMonochrome(image),2) ;
        titreFigure = "Image Filtree avec Filtre Gaussien 3x3" ;
        break;
        case 8 :
        imageResultat = ImageFiltrage(ImageMonochrome(image),3) ;
        titreFigure = "Image Filtree avec Filtre Median 3x3" ;
        break;
        case 9 :
        imageResultat = ImageContour(image,1) ;
        titreFigure = "Image de Contours avec Filtre Sobel 3x3" ;
        break;
        case 10 :
        imageResultat = ImageContour(image,2) ;
        titreFigure = "Image de Contours avec Filtre Laplacien 3x3" ;
        break;
        case 11 :
        imageResultat = ImageRehaussementContour(image,20,1) ;
        titreFigure = "Image apres Rehaussement de Contours (Gradient)" ;
        break;
        case 12 :
        imageResultat = ImageRehaussementContour(image,20,2) ;
        titreFigure = "Image apres Rehaussement de contours (Laplacien)" ;
        break;
        case 13 :
        imageResultat = ImageSeuillage(image) ;
        titreFigure = "Image apres Seuillage" ;
        break;
        case 14 :
        imageResultat = ImageSegmentation(image) ;
        titreFigure = "Image apres Segmentation" ;
        break;
        case 15 :
        //imageResultat = TransformHough(image) ;
        //titreFigure = "Image apres Rehaussement de contours (Laplacien)" ;
        break;
        case 16 :
        imageResultat = plot_histogram(image);
        titreFigure = "Histogramme de l'image en niveau de gris" ;
        break;
        default :
        cout << "Erreur choix Traitement d'images";
        break;
    }

    // Affichage
    //imageResultat=ConcatenerImage(image,imageResultat);
    namedWindow(titreFigure,WINDOW_NORMAL) ;
    imshow(titreFigure, imageResultat);
    waitKey(0) ;
    destroyWindow(titreFigure) ;

}*/


