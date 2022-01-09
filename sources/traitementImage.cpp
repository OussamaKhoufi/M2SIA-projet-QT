#include "../headers/traitementImage.h"
using namespace cv ;
using namespace std ;


//////////////////// Traitement de couleur ////////////////////

// Convertir une image en niveau de gris
Mat ImageMonochrome(const Mat image){
    // Declaration des variables
    int c ;                                     // Indice
    int nbComposante = image.channels() ;       // Nombre de composantes de couleur
    Mat imageComposante[nbComposante] ;         // Des composantes de l'image originale
    Mat imageGris ;                             // Image resultante
    Mat imageDouble ;                           // Image convertie en type double

    // Convertion en double
    image.convertTo(imageDouble, CV_32FC3) ;

    // Decomposition des composantes de couleur
    split(imageDouble, imageComposante) ;

    // Initialisation
    imageGris = imageComposante[0] ;

    // Calculs
    for(c = 1 ; c < nbComposante ; c++){
        imageGris += imageComposante[c] ;
    }
    imageGris = imageGris/3 ;

    // Convertion en unsigned char
    imageGris.convertTo(imageGris, CV_8U) ;

    // Retour
    return imageGris ;
}

// Inverser une image en niveau de gris
Mat ImageInversementMono(const Mat image){
    // Declaration des variables
    int ligne, colonne ;
    Mat imageInversee(image.size(), CV_8U) ;

    // Inversement
    for(ligne = 0 ; ligne < image.size().height ; ligne++){
        for(colonne = 0 ; colonne < image.size().width ; colonne++){
            imageInversee.at<unsigned char>(ligne, colonne) = 255 - image.at<unsigned char>(ligne, colonne) ;
        }
    }

    // Retour
    return imageInversee ;
}

// Inverser une image en couleurs
Mat ImageInversement(const Mat image){
    // Declaration des variables
    int c ;                                     // Indice
    int nbComposante = image.channels() ;       // Nombre de composantes de couleur
    Mat imageComposante[nbComposante] ;         // Des composantes de l'image originale
    Mat imageInversee ;                         // Image resultante
    vector<Mat> imageInverseeComposante ;       // Des composantes de l'image resultante

    // Decomposition des composantes de couleur
    split(image, imageComposante) ;

    // Inverser sur chaque canal de couleur
    for(c = 0 ; c < nbComposante ; c++){
        imageInverseeComposante.push_back(ImageInversementMono(imageComposante[c]))  ;
    }
    
    // Fusion des composantes de couleur
    merge(imageInverseeComposante, imageInversee) ;   

    // Retour
    return imageInversee ;
}                                

// Extraction une composante de couleur de l'image
Mat ImageExtractionCouleur(const Mat image, int choix){
    // Declaration de variable
    Mat imageComposante[3] ;         // Des composantes de l'image originale

    // Decomposition des composantes de couleur
    split(image, imageComposante) ;

    // Retour
    return imageComposante[choix-1] ;
}


//////////////////// Traitement a base d'histogramme ////////////////////

// Normalisation de l'histogramme
Mat NormalisationMono(const Mat image){    
    // Declaration des variables
    int ligne, colonne ;                                // Indices
    int min = MinImage(image) ;                         // Valeur minimum l'image de depart
    int max = MaxImage(image) ;                         // Valeur maximum l'image de depart
    double val ;                                        // Valeur intermediaire
    Mat imageNormalisation(image.size(), CV_8U) ;       // Image resultante

    // Normalisation
    val = (double)255/(max - min) ;
    for(ligne = 0 ; ligne < image.size().height ; ligne++){
        for(colonne = 0 ; colonne < image.size().width ; colonne++){
            imageNormalisation.at<unsigned char>(ligne, colonne) = (double)(image.at<unsigned char>(ligne, colonne) - min)*val ;
        }
    }

    // Retour
    return imageNormalisation ;
}

// Normalisation de l'histogramme d'une image en couleurs
Mat Normalisation(const Mat image){
    // Declaration des variables
    int c ;                                     // Indice
    int nbComposante = image.channels() ;       // Nombre de composantes de couleur
    Mat imageComposante[nbComposante] ;         // Des composantes de l'image originale
    Mat imageNormalisation ;                    // Image resultante
    vector<Mat> imageNormalisationComposante ;  // Des composantes de l'image resultante

    // Decomposition des composantes de couleur
    split(image, imageComposante) ;

    // Normalisation sur chaque canal de couleur
    for(c = 0 ; c < nbComposante ; c++){
        imageNormalisationComposante.push_back(NormalisationMono(imageComposante[c]))  ;
    }
    
    // Fusion des composantes de couleur
    merge(imageNormalisationComposante, imageNormalisation) ;    

    // Retour
    return imageNormalisation ;
}

// Egalisation d'une image en niveau de gris
Mat ImageEgalisationMono(const Mat image){
    // Declaration des variables
    int ligne, colonne ;                                    // Indices
    vector<int> valeurEgal = Egalisation(image, 255) ;      // Histogramme egalise
    Mat imageEgalisation(image.size(), CV_8U) ;             // Image resultante

    // Remplacer les valeur d'intensite de chaque pixel par sa valeur egalisee
    for(ligne = 0 ; ligne < image.size().height ; ligne++){
        for(colonne = 0 ; colonne < image.size().width ; colonne++){
            imageEgalisation.at<unsigned char>(ligne, colonne) = valeurEgal[(int)image.at<unsigned char>(ligne, colonne)] ;
        }
    }

    // Retour
    return imageEgalisation ;
}

// Egalisation d'une image en couleurs
Mat ImageEgalisation(const Mat image){
    // Declaration des variables
    int c ;                                     // Indice
    int nbComposante = image.channels() ;       // Nombre de composantes de couleur
    Mat imageComposante[nbComposante] ;         // Des composantes de l'image originale
    Mat imageEgalisation ;                      // Image resultante
    vector<Mat> imageEgalisationComposante ;    // Des composantes de l'image resultante

    // Decomposition des composantes de couleur
    split(image, imageComposante) ;

    // Egalisation sur chaque canal de couleur
    for(c = 0 ; c < nbComposante ; c++){
        imageEgalisationComposante.push_back(ImageEgalisationMono(imageComposante[c]))  ;
    }
    
    // Fusion des composantes de couleur
    merge(imageEgalisationComposante, imageEgalisation) ;   

    // Retour
    return imageEgalisation ;
}

// Rehaussement de contraste
Mat ImageRehaussementContraste(const Mat image, const int choix){
    switch (choix){
        // Normalisation
        case 1 :
            return Normalisation(image) ;
            break ;
        // Egalisation
        case 2 :
            return ImageEgalisation(image) ;
            break ;
        default :
            return ImageEgalisation(image) ;
            break ;
    }
}

//////////////////// Debruitage ////////////////////

// Debruitage par filtre median pour une image en niveau de gris
Mat ImageMedianMono(const Mat image){
    // Declaraton des variables
    int ligne, colonne, lig, col ;                      // Indices
    int taille = 3 ;                                    // Taille du filtre median
    Mat matrice = ImageZero(taille, taille) ;           // Matrice intermediaire
    Mat imageMiroir = ImageMiroir(image, taille) ;      // Image miroir
    Mat imageMedian(image.size(), CV_8U) ;              // Image resultante

    // Appliquer le filtre median
    for(ligne = 0 ; ligne < (int)image.size().height ; ligne++){
        for(colonne = 0 ; colonne < (int)image.size().width ; colonne++){
            // Matrice intermediaire
            for(lig = 0 ; lig < taille ; lig++){
                for(col = 0 ; col < 3 ; col++){
                    matrice.at<unsigned char>(lig, col) = imageMiroir.at<unsigned char>(ligne + lig, colonne + col) ;
                }
            }
            imageMedian.at<unsigned char>(ligne, colonne) = MatriceMedian(matrice) ;
        }
    }

    // Retour
    return imageMedian ;
}

// Debruitage par filtre median pour une image en couleurs
Mat ImageMedian(const Mat image){
    // Declaration des variables
    int c ;                                     // Indice
    int nbComposante = image.channels() ;       // Nombre de composantes de couleur
    Mat imageComposante[nbComposante] ;         // Des composantes de l'image originale
    Mat imageMedian ;                           // Image resultante
    vector<Mat> imageMedianComposante ;         // Des composantes de l'image resultante

    // Decomposition des composantes de couleur
    split(image, imageComposante) ;

    // Appliquer le filtre median sur chaque canal de couleur
    for(c = 0 ; c < nbComposante ; c++){
        imageMedianComposante.push_back(ImageMedianMono(imageComposante[c]))  ;
    }
    
    // Fusion des composantes de couleur
    merge(imageMedianComposante, imageMedian) ;   

    // Retour
    return imageMedian ;    
}

// Debruitage
Mat ImageFiltrage(const Mat image, const int choix){
    switch(choix){
        // Filtre moyenneur
        case 1 :
            return ImageConvolution(image, GenererFiltre(1)) ;
            break ;
        // Filtre gaussien
        case 2 :
            return ImageConvolution(image, GenererFiltre(3)) ;
            break ;
        // Filtre median
        case 3 : 
            return ImageMedian(image) ;
            break ;
        default :
            return ImageConvolution(image, GenererFiltre(3)) ;
            break ;
    }
}

//////////////////// Contours ////////////////////

// Detection de contours par filtres gradients
Mat ImageContourGradient(const Mat image){
    // Declaration des variables
    int nbComposante = image.channels() ;                   // Nombre de composantes de couleur de l'image originale
    Mat gradientX, gradientY ;                              // Gradients en x et en y
    Mat imageContour(image.size(), CV_8U) ;                 // Image resultante

    // Verifier si l'image de depart est en niveau de gris
    if(nbComposante > 1){
        imageContour = ImageMonochrome(image) ;
    }

    // Calculer des gradients
	gradientX = GradientX(imageContour, "Simple") ;          // En x
    gradientY = GradientY(imageContour, "Simple") ;          // En y

    // Norme du gradient
    imageContour = MatriceNorme(gradientX, gradientY) ;
    // imageContour = ImageSeuillage(MatriceNorme(gradientX, gradientY), 250) ;

    // Maximum de la norme du gradient dans la direction du gradient
    //imageContour = MaxNormeGradient(ImageSeuillage(MatriceNorme(gradientX, gradientY), 250), gradientX, gradientY) ;
    // Retour
    return imageContour ;
}

// Detection de contours par filtre laplacien
Mat ImageContourLaplace(const Mat image){
   	return ImageConvolution(ImageMonochrome(image), GenererFiltre(2)) ;
}

// Detection de contours
Mat ImageContour(const Mat image, const int choix){
    switch (choix){
    // Filtres gradients
    case 1 :
        return ImageContourGradient(image) ;
        break ;
    // Filtre laplacien
    case 2 :
        return ImageContourLaplace(image) ;
        break ;
    default:
        return ImageContourGradient(image) ;
        break;
    }
}

// Rehaussement de contours
Mat ImageRehaussementContour(const Mat image, const int val, const int choix){
    // Declaration de variables
    int c ;                                             // Indice
    int nbComposante = image.channels() ;               // Nombre de composantes de couleurs de l'image originale
    Mat imageComposante[nbComposante] ;                 // Composantes de couleurs de l'image originale
    Mat imageContour = ImageContour(image, choix) ;     // Image de contours
    Mat imageRehaussement ;                             // Image resultante
    vector<Mat> imageRehaussementComposante ;           // Composantes de couleurs de l'image resultante

    imageContour = imageContour/255 ;

    if(nbComposante == 1){
        imageRehaussement = image + imageContour*val ;
    }else{
        split(image, imageComposante) ;
        for(c = 0 ; c < nbComposante ; c++){
            imageRehaussementComposante.push_back(imageComposante[c] + imageContour*val) ;
        }
        merge(imageRehaussementComposante, imageRehaussement) ;
    }

    // Retour
    return imageRehaussement ;
}

//////////////////// Seuillage ////////////////////

// Seuillage d'une image en niveau de gris
Mat ImageSeuillage(const Mat image, const int seuil){
    // Declaration des ariables
    int ligne, colonne ;                        // Indice
    Mat imageSeuil(image.size(), CV_8U) ;       // Image resultante

    // Seuillage
    for(ligne = 0 ; ligne < image.size().height ; ligne++){
        for(colonne = 0 ; colonne < image.size().width ; colonne++){
            if((int)image.at<unsigned char>(ligne, colonne) <= seuil){
                imageSeuil.at<unsigned char>(ligne, colonne) = 0 ;
            }else{
                imageSeuil.at<unsigned char>(ligne, colonne) = 255 ;
            }
        }
    }

    // Retour
    return imageSeuil ;
}

// Seuillage d'une image en couleurs
Mat ImageSeuillage(const Mat image, vector<int> seuil){
    // Declaration des variables
    int c ;                                     // Indice
    int nbComposante = image.channels() ;       // Nombre de composantes de couleur
    Mat imageComposante[nbComposante] ;         // Des composantes de l'image originale
    Mat imageSeuillage ;                      // Image resultante
    vector<Mat> imageSeuillageComposante ;    // Des composantes de l'image resultante

    // Decomposition des composantes de couleur
    split(image, imageComposante) ;

    // Seuillage sur chaque canal de couleur
    for(c = 0 ; c < nbComposante ; c++){
        imageSeuillageComposante.push_back(ImageSeuillage(imageComposante[c], seuil[c]))  ;
    }
    
    // Fusion des composantes de couleur
    merge(imageSeuillageComposante, imageSeuillage) ;   

    // Retour
    return imageSeuillage ;
}             

// Seuillage par hysteresis d'une image en niveau de gris
Mat ImageSeuillage(const Mat image, const int seuilBas, const int seuilHaut){
    return (ImageSeuillage(image, seuilBas) - ImageSeuillage(image, seuilHaut)) ;
}       

// Seuillage par hysteresis d'une image en couleurs (Attention : B, V, R)
Mat ImageSeuillage(const Mat image, vector<int> seuilBas, vector<int> seuilHaut){
    return(ImageSeuillage(image, seuilBas) - ImageSeuillage(image, seuilHaut)) ;
}   

// Seuillage - Menu
Mat ImageSeuillage(const Mat image){
    // Declaration des variabes
    bool validation ;                   // Verification des conditions pour la saisie
    int choix ;                         // Choix du type de seuillage
    int valTemp1, valTemp2 ;            // Valeur temporelle
    string saisie ;                     // Valeur saisie par l'utilisateur
    vector<int> seuilBas, seuilHaut ;   // Seuil bas, seuil haut
    Mat imageSeuillage ;                // Image resultante

    // Initialisation
    saisie.clear() ;
    seuilBas.clear() ;
    seuilHaut.clear() ;

    // Choisir le type de seuillage souhaite
    cout << "Quel type de seuillage voulez-vous effectuer ?" << endl ;
    cout << "1. Seuillage simple" << endl ;
    cout << "2. Seuillage par hysteresis" << endl ;
    cout << "Votre choix : " ;
    // Saisie et verification
    do{
        validation = true ;
        // Saisie du choix
        cin >> saisie ;
        // Si le format du choix est invalide
        if(VerifierNumero(saisie, choix) == false){
            cout << "Le choix doit etre un entier. Veuillez reessayer : " ;
            validation = false ;
        // Si le choix est invalide
        }else if((choix != 1) && (choix != 2)){
            cout << "Le choix doit etre '1' ou '2'. Veuillez reessayer : " ;
            validation = false ;
        }
    }while(validation == false) ;

    // Saisie des seuils
    switch(choix){
    // Seuillage simple
        case 1 :
            // Si l'image est en niveau de gris
            if(VerifierImage(image, imageSeuillage)){
                cout << "Veuillez saisir la valeur du seuil : " ;
                SaisirSeuil(valTemp1) ;
                imageSeuillage = ImageSeuillage(imageSeuillage, valTemp1) ;     
            // Si m'image est en couleurs
            }else{
                // Saisie du seuil de la composante bleue
                cout << "Veuillez saisir la valeur du seuil de la composante bleue : " ;
                SaisirSeuil(valTemp1) ;
                seuilBas.push_back(valTemp1) ;
                // Saisie du seuil de la composante verte
                cout << "Veuillez saisir la valeur du seuil de la composante verte : " ;
                SaisirSeuil(valTemp1) ;
                seuilBas.push_back(valTemp1) ;
                // Saisie du seuil de la composante rouge
                cout << "Veuillez saisir la valeur du seuil de la composante rouge : " ;
                SaisirSeuil(valTemp1) ;
                seuilBas.push_back(valTemp1) ;    
                imageSeuillage = ImageSeuillage(image, seuilBas) ;     
            }    
                           
            break ;
        // Seuillage par hysteresis
        case 2 :
            // Si l'image est en niveau de gris
            if(VerifierImage(image, imageSeuillage)){
                // Saisie et verification des seuils
                SaisirSeuil(valTemp1, valTemp2) ;
                // Seuillage
                imageSeuillage = ImageSeuillage(imageSeuillage, valTemp1, valTemp2) ;     
            // Si m'image est en couleurs
            }else{
                // Seuils pour la composante bleue
                cout << "Seuils pour la composante bleue" << endl ;
                SaisirSeuil(valTemp1, valTemp2) ;
                seuilBas.push_back(valTemp1) ;
                seuilHaut.push_back(valTemp2) ;                
                // Seuils pour la composante verte
                cout << "Seuils pour la composante verte" << endl ;
                SaisirSeuil(valTemp1, valTemp2) ;
                seuilBas.push_back(valTemp1) ;
                seuilHaut.push_back(valTemp2) ;    
                // Seuils pour la composante rouge
                cout << "Seuils pour la composante rouge" << endl ;
                SaisirSeuil(valTemp1, valTemp2) ;
                seuilBas.push_back(valTemp1) ;
                seuilHaut.push_back(valTemp2) ;  
                // Seuillage        
                imageSeuillage = ImageSeuillage(image, seuilBas, seuilHaut) ;               
            }                   
            break ;
        default :
            break ;
    }

    // Retour
    return imageSeuillage ;
}                                             

//////////////////// Segmentation ////////////////////

// Segmentation d'une image en niveau de gris par seuillage simple
Mat ImageSegmentation(const Mat image, const int seuil){
    // Declaration des variables
    int ligne, colonne ;
    Mat imageSeuillee = ImageSeuillage(image, seuil) ;
    Mat imageSegmentee(image.size(), CV_8U) ;

    // Segmentation
    for(ligne = 0 ; ligne < image.size().height ; ligne++){
        for(colonne = 0 ; colonne < image.size().width ; colonne++){
            imageSegmentee.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(ligne, colonne)*(imageSeuillee.at<unsigned char>(ligne, colonne)/255) ;
        }
    }

    // Retour
    return imageSegmentee ;
}

// Segmentation d'une image en couleurs par seuillage simple (Attention : B, V, R)
Mat ImageSegmentation(const Mat image, vector<int> seuil){
    // Declaration des variables
    int c ;                                     // Indice
    int nbComposante = image.channels() ;       // Nombre de composantes de couleur
    Mat imageComposante[nbComposante] ;         // Des composantes de l'image originale
    Mat imageSegmentee ;                        // Image resultante
    vector<Mat> imageSegmenteeComposante ;      // Des composantes de l'image resultante

    // Decomposition des composantes de couleur
    split(image, imageComposante) ;

    // Segmentation sur chaque canal de couleur
    for(c = 0 ; c < nbComposante ; c++){
        imageSegmenteeComposante.push_back(ImageSegmentation(imageComposante[c], seuil[c]))  ;
    }
    
    // Fusion des composantes de couleur
    merge(imageSegmenteeComposante, imageSegmentee) ;   

    // Retour
    return imageSegmentee ;    
}

// Segmentation d'une image en niveau de gris par seuillage hysteresis
Mat ImageSegmentation(const Mat image, const int seuilBas, const int seuilHaut){
    return (ImageSegmentation(image, seuilBas) - ImageSegmentation(image, seuilHaut)) ;    
}           

// Segmentation d'une image en couleurs par seuillage hysteresis (Attention : B, V, R)
Mat ImageSegmentation(const Mat image, vector<int> seuilBas, vector<int> seuilHaut){
    return (ImageSegmentation(image, seuilBas) - ImageSegmentation(image, seuilHaut)) ; 
}          

// Segmentation - Menu
Mat ImageSegmentation(const Mat image){
    // Declaration des variabes
    bool validation ;                   // Verification des conditions pour la saisie
    int choix ;                         // Choix du type de seuillage
    int valTemp1, valTemp2 ;            // Valeur temporelle
    string saisie ;                     // Valeur saisie par l'utilisateur
    vector<int> seuilBas, seuilHaut ;   // Seuil bas, seuil haut
    Mat imageSegmentation ;             // Image resultante

    // Initialisation
    seuilBas.clear() ;
    seuilHaut.clear() ;

    // Choisir le type de seuillage souhaite
    cout << "Quel type de seuillage voulez-vous effectuer ?" << endl ;
    cout << "1. Seuillage simple" << endl ;
    cout << "2. Seuillage par hysteresis" << endl ;
    cout << "Votre choix : " ;
    // Saisie et verification
    do{
        validation = true ;
        // Saisie du choix
        saisie.clear() ;
        cin >> saisie ;
        // Si le format du choix est invalide
        if(VerifierNumero(saisie, choix) == false){
            cout << "Le choix doit etre un entier. Veuillez reessayer : " ;
            validation = false ;
        // Si le choix est invalide
        }else if((choix != 1) && (choix != 2)){
            cout << "Le choix doit etre '1' ou '2'. Veuillez reessayer : " ;
            validation = false ;
        }
    }while(validation == false) ;

    // Saisie des seuils
    switch(choix){
    // Seuillage simple
        case 1 :
            // Si l'image est en niveau de gris
            if(VerifierImage(image, imageSegmentation)){
                cout << "Veuillez saisir la valeur du seuil : " ;
                SaisirSeuil(valTemp1) ;
                // Segmentation 
                imageSegmentation = ImageSegmentation(imageSegmentation, valTemp1) ;              
            // Si m'image est en couleurs
            }else{
                // Saisie du seuil de la composante bleue
                cout << "Veuillez saisir la valeur du seuil de la composante bleue : " ;
                SaisirSeuil(valTemp1) ;
                seuilBas.push_back(valTemp1) ;
                // Saisie du seuil de la composante verte
                cout << "Veuillez saisir la valeur du seuil de la composante verte : " ;
                SaisirSeuil(valTemp1) ;
                seuilBas.push_back(valTemp1) ;
                // Saisie du seuil de la composante rouge
                cout << "Veuillez saisir la valeur du seuil de la composante rouge : " ;
                SaisirSeuil(valTemp1) ;
                seuilBas.push_back(valTemp1) ; 
                // Segmentation   
                imageSegmentation = ImageSegmentation(image, seuilBas) ;              
            }    
            break ;
        // Seuillage par hysteresis
        case 2 :
            // Si l'image est en niveau de gris
            if(VerifierImage(image, imageSegmentation)){
                // Saisie et verification des seuils
                SaisirSeuil(valTemp1, valTemp2) ;
                // Segmentation
                imageSegmentation = ImageSegmentation(imageSegmentation, valTemp1, valTemp2) ;                 
            // Si m'image est en couleurs
            }else{
                // Seuils pour la composante bleue
                cout << "Seuils pour la composante bleue" << endl ;
                SaisirSeuil(valTemp1, valTemp2) ;
                seuilBas.push_back(valTemp1) ;
                seuilHaut.push_back(valTemp2) ;                
                // Seuils pour la composante verte
                cout << "Seuils pour la composante verte" << endl ;
                SaisirSeuil(valTemp1, valTemp2) ;
                seuilBas.push_back(valTemp1) ;
                seuilHaut.push_back(valTemp2) ;    
                // Seuils pour la composante rouge
                cout << "Seuils pour la composante rouge" << endl ;
                SaisirSeuil(valTemp1, valTemp2) ;
                seuilBas.push_back(valTemp1) ;
                seuilHaut.push_back(valTemp2) ;     
                // Segmentation               
                imageSegmentation = ImageSegmentation(image, seuilBas, seuilHaut) ;                 
            }      
                        
            break ;
        default :
            break ;
    }   

    // Retour
    return imageSegmentation ; 
}                               

//////////////////// Operations ////////////////////

// Determiner la valeur minimum dans une matrice entiere
int MinImage(const Mat image){
    // Declaration des variables
    int ligne, colonne ;    // Indices
    int min ;               // Valeur min

    // Initialisation
    min = image.at<unsigned char>(0, 0) ;

    // Chercher le minimum
    for(ligne = 1 ; ligne < image.size().height ; ligne++){
        for(colonne = 1 ; colonne < image.size().width ; colonne++){
            if(min > image.at<unsigned char>(ligne, colonne)){
                min = image.at<unsigned char>(ligne, colonne) ;
            }
        }
    }

    // Retour
    return min ;
}

// Determiner la valeur maximum dans une matrice entiere
int MaxImage(const Mat image){
    // Declaration des variables
    int ligne, colonne ;    // Indices
    int max ;               // Valeur max

    // Initialisation
    max = image.at<unsigned char>(0, 0) ;

    // Chercher le maximum
    for(ligne = 1 ; ligne < image.size().height ; ligne++){
        for(colonne = 1 ; colonne < image.size().width ; colonne++){
            if(max < image.at<unsigned char>(ligne, colonne)){
                max = image.at<unsigned char>(ligne, colonne) ;
            }
        }
    }

    // Retour
    return max ;    
}

// Determiner la valeur maximum dans un vecteur reel
double MaxVecteur(const vector<double> vecteur){
    // Declaration des variables
    int c ;                 // Indice
    double valeurMax ;      // Valeur maximum

    // Initialisation
    valeurMax = vecteur[0] ;

    // Chercher le maximum
    for(c = 1 ; c < (int)vecteur.size() ; c++){
        if(valeurMax < vecteur[c]){
            valeurMax = vecteur[c] ;
        }
    }

    // Retour
    return valeurMax ;
}
int MaxVecteur(const vector<int> vecteur){
    // Declaration des variables
    int c ;                 // Indice
    int valeurMax ;      // Valeur maximum

    // Initialisation
    valeurMax = vecteur[0] ;

    // Chercher le maximum
    for(c = 1 ; c < (int)vecteur.size() ; c++){
        if(valeurMax < vecteur[c]){
            valeurMax = vecteur[c] ;
        }
    }

    // Retour
    return valeurMax ;
}

// Histogramme
vector<int> Histogramme(const Mat image, const int nbIntervalle){
    // Declaration des variables
    int c, ligne, colonne ;                     // Indices
    vector<int> occurence(nbIntervalle) ;       // Vecteur des occurences

    // Initialisation
    for(c = 0 ; c < nbIntervalle ; c++){
        occurence[c] = 0 ;
    }

    // Determiner le nombre d'occurences de chaque intervalle
    for(c = 0 ; c < nbIntervalle - 1 ; c++){
        for(ligne = 0 ; ligne < image.size().height ; ligne++){
            for(colonne = 0 ; colonne < image.size().width ; colonne++){
                if((image.at<unsigned char>(ligne, colonne) >= ((float)255/nbIntervalle*c)) && (image.at<unsigned char>(ligne, colonne) < ((float)255/nbIntervalle*(c+1)))){
                    occurence[c]++ ;
                }
            }
        }
    }

    // Derniere intervalle
    for(ligne = 0 ; ligne < image.size().height ; ligne++){
        for(colonne = 0 ; colonne < image.size().width ; colonne++){
            if((image.at<unsigned char>(ligne, colonne) == ((float)255/nbIntervalle*c)) ){
                occurence[nbIntervalle - 1]++ ;
            }
        }
    }

    // Retour
    return occurence ;
}

// Egalisation de l'histogramme d'une image au niveau de gris
vector<int> Egalisation(const Mat image, const int nbIntervalle){
    // Declaration des variables
    int c ;                                                         // Indice   
    int nbPixel = image.size().height*image.size().width ;          // Nombre de pixels de l'image 
    double somme = 0 ;                                              // Histogramme cumule
    double coefficient = (double)255/nbPixel ;                              // Niveau de gris divise par pixel
    vector<int> occurence = Histogramme(image, nbIntervalle) ;      // Histogramme de l'image
    vector<int> occurenceEgal(nbIntervalle) ;                       // Histogramme egalise

    // Egalisation
    for(c = 0 ; c < nbIntervalle ; c++){
        somme += occurence[c] ;
        occurenceEgal[c] = coefficient*somme ;
    }

    // Retour
    return occurenceEgal ;
}

// Generer une matrice zero
Mat ImageZero(const int nbLigne, const int nbColonne){
    // Declaration des variables
    int ligne, colonne ;        // Indices
    Size dimensionZero ;
    dimensionZero.height = nbLigne ;
    dimensionZero.width = nbColonne ;
    Mat ImageZero = Mat(dimensionZero, CV_8U) ;

    // Remplir la matrice
    for(ligne = 0 ; ligne < nbLigne ; ligne++){
        for (colonne = 0 ; colonne < nbColonne ; colonne++){
            ImageZero.at<unsigned char>(ligne, colonne) = 0 ;
        }
    }

    // Retour
    return ImageZero ;
}

// Produit de convolution entre deux matrices
Mat MatriceConvolution(const Mat image, const Mat filtre){
    // Declaration des variables
    int ligne, colonne, lig, col ;                                  // Indices
    int L_image, C_image ;                                          // Dimensions de l'image
    int L_filtre, C_filtre ;                                        // Dimensions du filtre
    int val ;                                                       // Variable intermediaire
    Mat imageConv(image.size(), CV_8U) ;                            // Image resultante
    Mat imageMiroir = ImageMiroir(image, filtre) ;                  // Image avec effet miroir
    
    // Dimensions de l'image
    L_image = image.size().height ;                                 // Nombre de lignes
    C_image = image.size().width ;                                  // Nombre de colonnes

    // Dimensions du filtre
    L_filtre = filtre.size().height ;                               // Nombre de lignes
    C_filtre = filtre.size().width ;                                // Nombre de colonnes

    // Produit de convolution
    for(ligne = 0 ; ligne <= L_image - 1 ; ligne++){                // Pour chaque ligne de l'image
        for(colonne = 0 ; colonne <= C_image - 1 ; colonne++){      // Pour chaque colonne de l'image
            val = 0 ;                                               // Remise a zero la variable intermediaire
            for(lig = 0 ; lig <= L_filtre/2 + 1  ; lig++){          // Pour chaque ligne du filtre
                for(col = 0 ; col <= C_filtre/2 + 1 ; col++){       // Pour chaque colonne du filtre
                    val += imageMiroir.at<unsigned char>(ligne + lig, colonne + col)*filtre.at<double>(lig, col) ;
                }
            }
            imageConv.at<unsigned char>(ligne, colonne) = val ;
        }
    }

    // Retour
    return imageConv ;
}

// Produit de convolution entre deux images
Mat ImageConvolution(const Mat image, const Mat filtre){
    // Declaration des variables
    int c ;                                     // Indice
    int nbComposante = image.channels() ;       // Nombre de composantes de couleur
    Mat imageConv ;                             // Image resultante
    Mat imageComposante[nbComposante] ;         // Des composantes de l'image originale
    vector<Mat> imageConvComposante ;           // Des composantes de l'image resultante

    // Decomposition des composantes de couleur
    split(image, imageComposante) ;
    
    // Convolution sur chaque canal de couleur
    for(c = 0 ; c < nbComposante ; c++){
        imageConvComposante.push_back(MatriceConvolution(imageComposante[c], filtre))  ;
    }
    
    // Fusion des composantes de couleur
    merge(imageConvComposante, imageConv) ;

    // Retour
    return imageConv ;
}

// Calculer la norme
Mat MatriceNorme(const Mat imageX, const Mat imageY){
    // Declaration des variables
    int ligne, colonne ;                            // Indices
    double x2, y2 ;                                 // x au carre et y au carre
    Mat imageNorme(imageX.size(), CV_8U) ;          // Image resultante

    // Calculer la norme de chaque pixel
    for(ligne = 0 ; ligne < imageX.size().height ; ligne++){
        for(colonne = 0 ; colonne < imageX.size().width ; colonne++){
            x2 = (double)imageX.at<unsigned char>(ligne, colonne)*imageX.at<unsigned char>(ligne, colonne) ;
            y2 = (double)imageY.at<unsigned char>(ligne, colonne)*imageY.at<unsigned char>(ligne, colonne) ;
            imageNorme.at<unsigned char>(ligne, colonne) = (int)sqrt(x2 + y2) ;
        }
    }

    // Retour
    return imageNorme ;
}

// Gradient en X
Mat GradientX(const Mat image, const string typeFiltre){
    if(typeFiltre == "Sobel"){
        return ImageConvolution(image, GenererFiltre(4)) ;
    }else if(typeFiltre == "Simple"){
        return ImageConvolution(image, GenererFiltre(6)) ;
    }else{
        cout << "Type de filtre invalide." << endl ;
        return image ;
    }
}

// Gradient en Y
Mat GradientY(const Mat image, const string typeFiltre){
    if(typeFiltre == "Sobel"){
        return ImageConvolution(image, GenererFiltre(5)) ;
    }else if(typeFiltre == "Simple"){
        return ImageConvolution(image, GenererFiltre(7)) ;
    }else{
        cout << "Type de filtre invalide." << endl ;
        return image ;
    }
}                             

// Maximum de la norme du gradient// Ne pas marcher  pour le moment
Mat MaxNormeGradient(const Mat gradientNorme, const Mat gradientX, const Mat gradientY){
    // Declaration des variables
    const double pi = 3.141592 ;                                                                // Nombre pi
    int ligne, colonne ;                                                                        // Indices
    double theta ;                                                                              // Direction de la norme du gradient
    vector<double> val ;                                                                        // Vecteur des valeurs a determiner le maximum
    Mat imageMaxNormeGradient(gradientNorme.size(), CV_8U) ;                                    // Image resultante

    // Initialisation
    imageMaxNormeGradient = gradientNorme ;

    // Ne pas traiter les bords horizontaux de l'image
    for(ligne = 1 ; ligne < gradientNorme.size().height - 1 ; ligne++){
        // Ne pas traiter les bords verticaux de l'image
        for(colonne = 1 ; colonne < gradientNorme.size().width - 1 ; colonne++){     
            // Initialisation   
            val.clear() ;       

            // Corriger les division par zero
            if(gradientX.at<unsigned char>(ligne, colonne) == 0){
                theta = pi/2 ;
            }else{
                theta = (double)gradientY.at<unsigned char>(ligne, colonne)/gradientX.at<unsigned char>(ligne, colonne) ;
                // Mettre l'angle theta a la partie superieure du cercle trigonometrique
                if((theta < 0) || (theta > pi)){
                    theta += pi ;
                }
            }

            // Remplir le vecteur des valeurs a comparer
            // Si theta se situe entre [0, pi/4[ ou ]3pi/4, pi]
            if((theta > 3*pi/4) || (theta < pi/4)){
                val.push_back((double)gradientNorme.at<unsigned char>(ligne, colonne - 1)) ;    // Valeur du pixel a gauche
                val.push_back((double)gradientNorme.at<unsigned char>(ligne, colonne + 1)) ;    // Valeur du pixel a droite
            // Si theta se situe entre [pi/4, 3pi/4]
            }else{
                val.push_back((double)gradientNorme.at<unsigned char>(ligne - 1, colonne)) ;    // Valeur du pixel en bas
                val.push_back((double)gradientNorme.at<unsigned char>(ligne + 1, colonne)) ;    // Valeur du pixel en haut
            }
            
            // Valeur du pixel courant
            val.push_back((double)gradientNorme.at<unsigned char>(ligne, colonne)) ;

            // Determiner la valeur maximum
            imageMaxNormeGradient.at<unsigned char>(ligne, colonne) = (unsigned char)MaxVecteur(val) ;
        }
    }

    // Retour
    return imageMaxNormeGradient ;
}

// Determiner la valeur mediane d'une matrice
int MatriceMedian(const Mat matrice){
    // Declaration des variables
    int ligne, colonne ;
    vector<int> vecteurValeur ;

    // Initialisation
    vecteurValeur.clear() ;

    // Redimensionner la matrice en un veteur
    for(ligne = 0 ; ligne < matrice.size().height ; ligne++){
        for(colonne = 0 ; colonne < matrice.size().width ; colonne++){
            vecteurValeur.push_back((int)matrice.at<unsigned char>(ligne, colonne)) ;
        }
    }     

    // Retour
    return VecteurMedian(vecteurValeur) ;
} 

// Determiner la valeur mediane d'un vecteur
int VecteurMedian(vector<int> vecteur){
    // Declaration des variables
    int c ;                                 // Indice
    vector<int> vecteurDecroissant ;        // Vecteur des valeurs rangees dans l'ordre decroissant

    // Initialisation
    vecteurDecroissant.clear() ;

    // Ranger les valeurs du vecteur de depart dans l'ordre decroissant
    while(vecteur.size()){
        // Ecrire la valeur maximum du vecteur de depart
        vecteurDecroissant.push_back(MaxVecteur(vecteur)) ;
        for(c = 0 ; c < (int)vecteur.size() ; c++){
            // Supprimer la valeur ecrite
            if(MaxVecteur(vecteur) == vecteur[c]){
                vecteur.erase(vecteur.begin() + c) ;
            }
        }
    }

    // Retour
    return vecteurDecroissant[ceil((double)vecteurDecroissant.size()/2)] ;
}

// Verifier l'egalite entre deux matrices de memes dimensions
bool MatriceEgale(const Mat matrice1, const Mat matrice2){
    // Declaration des variables
    int ligne, colonne ;        // Indices
    bool egal ;                 // Egalite entre deux matrices

    // Verification de l'egalite de toutes les valeurs dans les deux matrices
    for(ligne = 0 ; ligne < (int)matrice1.size().height ; ligne++){
        for(colonne = 0 ; colonne < (int)matrice1.size().width ; colonne++){
            if(matrice1.at<unsigned char>(ligne, colonne) == matrice2.at<unsigned char>(ligne, colonne)){
                egal = true ;
            }else{
                egal = false ;
                return egal ;
                break ;
            }
        }
    }

    // Retour
    return egal ;
}     


//////////////////// Autres ////////////////////

// Effet miroir
Mat ImageMiroir(const Mat image, const Mat filtre){
    // Declaration des variables
    int ligne, colonne, lig, col ;                                          // Indices
    int L_image, C_image, L_filtre, C_filtre, L_miroir, C_miroir  ;         // Dimensions

    // Dimensions de l'image
    L_image = image.size().height ;                                         // Nombre de lignes
    C_image = image.size().width ;                                          // Nombre de colonnes

    // Dimensions du filtre
    L_filtre = filtre.size().height ;                                       // Nombre de lignes
    C_filtre = filtre.size().width ;                                        // Nombre de colonnes

    // Initialisation de l'image resultante - Effet miroir
    L_miroir = L_image + L_filtre - 1 ;                                     // Nombre de lignes
    C_miroir = C_image + C_filtre - 1 ;                                     // Nombre de colonnes

    // Initialisation de l'image resultante
    Mat ImageMiroir = ImageZero(L_miroir, C_miroir) ;                 

    // Les bords horizontaux de l'image avec effet miroir
    // Premieres lignes 
    // Initialisation des indices
    lig = 0 ;      
    for(ligne = floor(L_filtre/2) - 1 ; ligne >= 0 ; ligne--){
        col = 0 ;
        for (colonne = ceil(C_filtre/2) ; colonne <= (C_miroir - ceil(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }
  
    // Dernieres lignes 
    // Initialisation des indices
    lig = L_image - floor(L_filtre/2) ; 
    for(ligne = L_miroir - 1 ; ligne >= L_miroir - floor(L_filtre/2) ; ligne--){
        col = 0 ;     
        for (colonne = ceil(C_filtre/2) ; colonne <= (C_miroir - ceil(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }

    // Les bords verticaux de l'image avec effet miroir
    // Premieres colonnes 
    // Initialisation des indices
    lig = 0 ; 
    for(ligne = ceil(L_filtre/2) ; ligne <= (L_miroir - floor(L_filtre/2) - 1) ; ligne++){
        col = 0 ; 
        for (colonne = floor(C_filtre/2) - 1 ; colonne >= 0 ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }
 
    // Dernieres colonnes
    // Initialisation des indices
    lig = 0 ; 
    for(ligne = ceil(L_filtre/2) ; ligne <= (L_miroir - floor(L_filtre/2) - 1) ; ligne++){
        col = C_image - 1 ; 
        for (colonne = C_miroir - floor(C_filtre/2) ; colonne <= (C_miroir - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col-- ; 
        }
        lig++ ; 
    }

    // Les coins
    // En haut, a gauche
    // Initialisation des indices
    lig = floor(L_filtre/2) ; 
    for(ligne = 0 ; ligne <= (floor(L_filtre/2) - 1) ; ligne++){
        col = floor(C_filtre/2) ;    
        for (colonne = 0 ; colonne <= (floor(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col-- ; 
        }
        lig-- ; 
    }    

    // En haut, a droite
    // Initialisation des indices
    lig = floor(L_filtre/2) ; 
    for(ligne = 0 ; ligne <= (floor(L_filtre/2) - 1) ; ligne++){
        col = C_image - floor(C_filtre/2) ;    
        for (colonne = C_miroir - 1 ; colonne >= (C_miroir - floor(C_filtre/2)) ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig-- ; 
    }    

    // En bas, a gauche
    // Initialisation des indices
    lig = L_image - 1 ; 
    for(ligne = L_miroir - floor(L_filtre/2) ; ligne <= (L_miroir - 1) ; ligne++){
        col = 0 ;    
        for (colonne = floor(C_filtre/2) - 1 ; colonne >= 0 ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig-- ; 
    }       

    // En bas, a droite
    // Initialisation des indices
    lig = L_image - 1 ; 
    for(ligne = L_miroir - floor(L_filtre/2) ; ligne <= (L_miroir - 1) ; ligne++){
        col = C_image - floor(C_filtre/2) ;    
        for (colonne = C_miroir - 1 ; colonne >= C_miroir - floor(C_filtre/2) ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig-- ; 
    }    

    // Contenu
    // Initialisation des indices
    lig = 0 ; 
    for(ligne = ceil(L_filtre/2) ; ligne <= (L_miroir - floor(L_filtre/2) - 1) ; ligne++){
        col = 0 ;    
        for (colonne = ceil(C_filtre/2) ; colonne <= (C_miroir - floor(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }    

    return ImageMiroir ;
}

Mat ImageMiroir(const Mat image, const int taille){
    // Declaration des variables
    int ligne, colonne, lig, col ;                                          // Indices
    int L_image, C_image, L_filtre, C_filtre, L_miroir, C_miroir  ;         // Dimensions

    // Dimensions de l'image
    L_image = image.size().height ;                                         // Nombre de lignes
    C_image = image.size().width ;                                          // Nombre de colonnes

    // Dimensions du filtre
    L_filtre = taille ;                                                     // Nombre de lignes
    C_filtre = taille ;                                                     // Nombre de colonnes

    // Initialisation de l'image resultante - Effet miroir
    L_miroir = L_image + L_filtre - 1 ;                                     // Nombre de lignes
    C_miroir = C_image + C_filtre - 1 ;                                     // Nombre de colonnes

    // Initialisation de l'image resultante
    Mat ImageMiroir = ImageZero(L_miroir, C_miroir) ;                 

    // Les bords horizontaux de l'image avec effet miroir
    // Premieres lignes 
    // Initialisation des indices
    lig = 0 ;      
    for(ligne = floor(L_filtre/2) - 1 ; ligne >= 0 ; ligne--){
        col = 0 ;
        for (colonne = ceil(C_filtre/2) ; colonne <= (C_miroir - ceil(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }
  
    // Dernieres lignes 
    // Initialisation des indices
    lig = L_image - floor(L_filtre/2) ; 
    for(ligne = L_miroir - 1 ; ligne >= L_miroir - floor(L_filtre/2) ; ligne--){
        col = 0 ;     
        for (colonne = ceil(C_filtre/2) ; colonne <= (C_miroir - ceil(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }

    // Les bords verticaux de l'image avec effet miroir
    // Premieres colonnes 
    // Initialisation des indices
    lig = 0 ; 
    for(ligne = ceil(L_filtre/2) ; ligne <= (L_miroir - floor(L_filtre/2) - 1) ; ligne++){
        col = 0 ; 
        for (colonne = floor(C_filtre/2) - 1 ; colonne >= 0 ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }
 
    // Dernieres colonnes
    // Initialisation des indices
    lig = 0 ; 
    for(ligne = ceil(L_filtre/2) ; ligne <= (L_miroir - floor(L_filtre/2) - 1) ; ligne++){
        col = C_image - 1 ; 
        for (colonne = C_miroir - floor(C_filtre/2) ; colonne <= (C_miroir - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col-- ; 
        }
        lig++ ; 
    }

    // Les coins
    // En haut, a gauche
    // Initialisation des indices
    lig = floor(L_filtre/2) ; 
    for(ligne = 0 ; ligne <= (floor(L_filtre/2) - 1) ; ligne++){
        col = floor(C_filtre/2) ;    
        for (colonne = 0 ; colonne <= (floor(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col-- ; 
        }
        lig-- ; 
    }    

    // En haut, a droite
    // Initialisation des indices
    lig = floor(L_filtre/2) ; 
    for(ligne = 0 ; ligne <= (floor(L_filtre/2) - 1) ; ligne++){
        col = C_image - floor(C_filtre/2) ;    
        for (colonne = C_miroir - 1 ; colonne >= (C_miroir - floor(C_filtre/2)) ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig-- ; 
    }    

    // En bas, a gauche
    // Initialisation des indices
    lig = L_image - 1 ; 
    for(ligne = L_miroir - floor(L_filtre/2) ; ligne <= (L_miroir - 1) ; ligne++){
        col = 0 ;    
        for (colonne = floor(C_filtre/2) - 1 ; colonne >= 0 ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig-- ; 
    }       

    // En bas, a droite
    // Initialisation des indices
    lig = L_image - 1 ; 
    for(ligne = L_miroir - floor(L_filtre/2) ; ligne <= (L_miroir - 1) ; ligne++){
        col = C_image - floor(C_filtre/2) ;    
        for (colonne = C_miroir - 1 ; colonne >= C_miroir - floor(C_filtre/2) ; colonne--){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig-- ; 
    }    

    // Contenu
    // Initialisation des indices
    lig = 0 ; 
    for(ligne = ceil(L_filtre/2) ; ligne <= (L_miroir - floor(L_filtre/2) - 1) ; ligne++){
        col = 0 ;    
        for (colonne = ceil(C_filtre/2) ; colonne <= (C_miroir - floor(C_filtre/2) - 1) ; colonne++){
            ImageMiroir.at<unsigned char>(ligne, colonne) = image.at<unsigned char>(lig, col) ;
            // Incrementation des indices
            col++ ; 
        }
        lig++ ; 
    }    

    return ImageMiroir ;
}

// Generer les filtres
Mat GenererFiltre(const int typeFiltre){
    switch (typeFiltre){
    // Filtre moyenneur
    case 1 :
        return ((Mat_<double>(3,3) << 1, 1, 1, 1, 1, 1, 1, 1, 1)/9) ;
        break ;
    // Filtre laplacien
    case 2 :
        return (Mat_<double>(3,3) << -1, -1, -1, -1, 8, -1, -1, -1, -1) ;
        break ;
    // Filtre gaussien
    case 3 :
        return ((Mat_<double>(3,3) << 1, 2, 1, 2, 4, 2, 1, 2, 1)/16) ;
        break ;
    // Filtre gradient en x (Sobel)
    case 4 :
        return (Mat_<double>(3,3) << -1, -2, -1, 0, 0, 0, 1, 2, 1) ;
        break ;
    // Filtre gradient en y (Sobel)
    case 5 :
        return (Mat_<double>(3,3) << -1, 0, 1, -2, 0, 2, -1, 0, 1) ;
        break ;
    // Filtre gradient en x (simple)
    case 6 : 
        return (Mat_<double>(3,3) << 0, 1, 0, 0, 0, 0, 0, -1, 0) ;
        break ;
    // Filtre gradient en y (simple)
    case 7 :
        return (Mat_<double>(3,3) << 0, 0, 0, 1, 0, -1, 0, 0, 0) ;
        break ;
    default:
        return (Mat_<double>(3,3) << 0, 0, 0, 0, 1, 0, 0, 0, 0) ;
        break;
    }
}

// Concatener 2 images de memes dimensions en 1 image (en niveau de gris)
Mat ConcatenerImageMono(Mat image1, Mat image2){
    // Declaration des variables
    int ligne, colonne ;                                // Indices
    Size dimensionImage ;                               // Dimensions de l'image resultante

    // Calculer les dimensions de l'image resultante
    dimensionImage.height = image1.size().height ;      // Nombre de lignes
    dimensionImage.width = image1.size().width*2 ;      // Nombre de colonne

    // Initialisation de l'image resultante
    Mat imageConcatener(dimensionImage, CV_8U) ;  

    // Concatenation
    // Image 1
    for(ligne = 0 ; ligne < image1.size().height ; ligne++){
        for(colonne = 0 ; colonne < image1.size().width ; colonne++){
            imageConcatener.at<unsigned char>(ligne, colonne) = image1.at<unsigned char>(ligne, colonne) ;
        }
    }
    // Image 2
    for(ligne = 0 ; ligne < image2.size().height ; ligne++){
        for(colonne = image2.size().width ; colonne < image2.size().width*2 ; colonne++){
            imageConcatener.at<unsigned char>(ligne, colonne) = image2.at<unsigned char>(ligne, colonne - image2.size().width) ;
        }
    }    

    // Retour
    return imageConcatener ;
}

// Concatener 2 images de memes dimensions en 1 image (en couleurs)
Mat ConcatenerImage(Mat image1, Mat image2){
    // Declaration des variables
    int c ;                                             // Indice
    int nbComposante = 3 ;                              // Nombre de composantes de couleur
    Mat image1Composante[nbComposante] ;                // Des composantes de l'image originale 1 
    Mat image2Composante[nbComposante] ;                // Des composantes de l'image originale 2
    Size dimensionImage ;                               // Dimensions de l'image resultante
    vector<Mat> imageConcatComposante ;                 // Des composantes de l'image resultante

    // Calculer les dimensions de l'image resultante
    dimensionImage.height = image1.size().height ;      // Nombre de lignes
    dimensionImage.width = image1.size().width*2 ;      // Nombre de colonne

    // Initialisation de l'image resultante
    Mat imageConcatener(dimensionImage, CV_8UC3) ;  

    // Verifier si les images sont en couleurs et corriger si necesaire
    if(image1.channels() == 1){
        image1 = MonoCouleur(image1) ;
    }
    if(image2.channels() == 1){
        image2 = MonoCouleur(image2) ;
    }

    // Decomposition des composantes de couleur
    split(image1, image1Composante) ;                   // Image 1
    split(image2, image2Composante) ;                   // Image 2

    // Normalisation sur chaque canal de couleur
    for(c = 0 ; c < nbComposante ; c++){
        imageConcatComposante.push_back(ConcatenerImageMono(image1Composante[c], image2Composante[c]))  ;
    }
    
    // Fusion des composantes de couleur
    merge(imageConcatComposante, imageConcatener) ;   

    // Retour
    return imageConcatener ;
}

// Convertir le format d'une image monochrome en format RVB
Mat MonoCouleur(const Mat image){
    // Declaration des variables
    int c ;                                             // Indice
    Mat imageCouleur(image.size(), CV_8UC3) ;           // Image resultante
    vector<Mat> imageCouleurComposante ;                // Des composantes de l'image resultante

    // Copier le contenu de l'image de depart dans les trois canaux de couleurs
    for(c = 0 ; c < 3 ; c++){
        imageCouleurComposante.push_back(image) ;
    }
    
    // Fusion
    merge(imageCouleurComposante, imageCouleur) ;
    // Retour
    return imageCouleur ;
}

 // Saisie et verification de la valeur d'un seuil
void SaisirSeuil(int& seuil){
    // Declaration des variables
    bool validation ;           // Validation les conditions de la saisie du seuil
    string saisie ;             // Valeur saisie par l'utilisateur

    // Saisie et verification du seuil
    do{
        validation = true ;
        // Saisie de la valeur du seuil
        saisie.clear() ;
        cin >> saisie ;
        // Verifier le format de la valeur saisie
        // Si le seuil saisi n'est pas un entier
        if(VerifierNumero(saisie, seuil) == false){
            cout << "Le seuil doit etre un entier. Veuillez reessayer : " ;
            validation = false ;
        // Si le seuil n'est pas dans [0,255]
        }else if((seuil < 0) || (seuil > 255)){
            cout << "Le seuil doit etre entre entre 0 et 255. Veuillez reessayer : " ;
            validation = false ;
        // Sinon : seuil valide
        }
    }while(validation == false) ;    
}                                               

// Saisie et verification des valeurs des seuils hysteresis
void SaisirSeuil(int& seuilBas, int& seuilHaut){
    // Saisie du seuil bas
    cout << "Veuillez saisir le seuil bas : " ;
    SaisirSeuil(seuilBas) ;
    // Saisie du seuil haut
    cout << "Veuillez saisir le seuil haut : " ;
    do{
        SaisirSeuil(seuilHaut) ;
        if(seuilHaut < seuilBas){
            cout << "La valeur du seuil haut doit etre superieure ou egale a la valeur du seuil bas. Veuillez reessayer : " ;
        }
    }while(seuilHaut < seuilBas) ;    
}                     

// Calcul d'histogramme sur un cannal
Mat calc_histogram(Mat image) {
	Mat hist;
	hist = Mat::zeros(256, 1, CV_32F);
	image.convertTo(image, CV_32F);
	double value = 0;
	for (int i = 0; i < image.rows; i++)
	{
	for (int j = 0; j < image.cols; j++)
		{
			value = image.at<float>(i, j);
			hist.at<float>(value) = hist.at<float>(value) + 1;
		}
	}
	return hist;
}

// Image du Graphe Histogramme d'un seul canal
Mat plot_histogram1D(Mat image,int choixCouleur) {
	Mat histogram_image(400, 512, CV_8UC3, Scalar(0, 0, 0));
	Mat normalized_histogram;
    Mat histogram = calc_histogram(image);
    Scalar couleur;
	normalize(histogram, normalized_histogram, 0, 400, NORM_MINMAX, -1, Mat());
    if (choixCouleur==1) {
        couleur=Scalar(255,0,0);
    }else if (choixCouleur==2) {
        couleur=Scalar(0,255,0);
    }else if(choixCouleur==3){
        couleur=Scalar(0,0,255);
    }else{
        couleur=Scalar(255,255,255);
    }
	for (int i = 0; i < 256; i++)
	{
		rectangle(histogram_image, Point(2 * i, histogram_image.rows - normalized_histogram.at<float>(i)),
			Point(2 * (i + 1), histogram_image.rows), couleur);
	}
    return histogram_image;
}
// Image du graphe histogramme d'image 1 canals ou 3 canals
Mat plot_histogram(Mat image) {
     Mat histogram_image_R(400, 512, CV_8UC3, Scalar(0, 0, 0));
     Mat histogram_image_G(400, 512, CV_8UC3, Scalar(0, 0, 0));
     Mat histogram_image_B(400, 512, CV_8UC3, Scalar(0, 0, 0));
     Mat histogram_image(400, 512, CV_8UC3, Scalar(0, 0, 0));
     Mat imageTemp;
    if (VerifierImage(image,imageTemp)){
    return plot_histogram1D(imageTemp,0);
    }else {
        histogram_image_R = plot_histogram1D(ImageExtractionCouleur(imageTemp,1),1) ;
        histogram_image_G = plot_histogram1D(ImageExtractionCouleur(imageTemp,2),2) ;
        histogram_image_B = plot_histogram1D(ImageExtractionCouleur(imageTemp,3),3) ; 
        addWeighted(histogram_image_R,0.5,
        histogram_image_G,0.5,0.0,histogram_image);
        addWeighted(histogram_image,0.5,
        histogram_image_B,0.5,0.0,histogram_image);
    }
    return histogram_image;
}
// Verifier si l'image est en couleurs ou en niveau de gris
bool VerifierImage(const Mat image, Mat& imageVerifiee){
    // Declaration des variables
    bool imageNiveauGris ;          // Verification si l'image est en niveau de gris
    vector<Mat> composante ;        // Composantes de couleur de l'image

    // Si l'image contient une seule composante
    if(image.channels() == 1){
        // L'image est en niveau de gris
        imageVerifiee = image ;
        imageNiveauGris = true ;
    // Si l'image contient plusieurs composantes
    }else{
        // Decomposer l'image en composantes
        split(image, composante) ;
        // Si les trois composantes sont egales
        if(MatriceEgale(composante[0], composante[1]) && MatriceEgale(composante[1], composante[2])){
            imageVerifiee = composante[0] ;
            imageNiveauGris = true ;
        // Sinon : image en couleurs
        }else{
            imageVerifiee = image ;
            imageNiveauGris = false ;
        }
    }

    // Retour
    return imageNiveauGris ;
}


