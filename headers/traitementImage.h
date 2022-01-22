#include "image.h"

using namespace cv ;
using namespace std ;

// Traitement de couleur
Mat ImageTemperature(const Mat image, const int valeur) ;               // Modifier la temperature de l'image
Mat ImageSaturation(const Mat image, const int valeur) ;                // Modifier la saturation
Mat ImageSaturationElement(const Mat image, const int valeur) ;         // Calcul elementaire pour la modification la saturation
Mat ImageTeinte(const Mat image, const int valeur) ;                    // Modifier la teinte
Mat ImageVividite(const Mat image, const int valeur) ;                  // Modifier la vividite

// Filtre de couleur
Mat ImageMonochrome(const Mat image) ;						            // Convertir une image en niveau de gris
Mat ImageSepia(const Mat image) ;                                       // Monochrome - Sepia
Mat ImageInversementMono(const Mat image) ;				                // Inverser une image en niveau de gris
Mat ImageInversement(const Mat image) ;                                 // Inverser une image en couleurs
Mat ImageExtractionCouleur(const Mat image, int choix) ;                // Extraction une composante de couleur de l'image
Mat ImageRouge(const Mat image) ;                                       // Extraire la couleur rouge
Mat ImageVert(const Mat image) ;                                        // Extraire la couleur verte
Mat ImageBleu(const Mat image) ;                                        // Extraire la couleur bleue
Mat ImageJaune(const Mat image) ;                                       // Extraire la couleur jaune
Mat ImageCyan(const Mat image) ;                                        // Extraire la couleur cyane
Mat ImageMagenta(const Mat image) ;                                     // Extraire la couleur magenta
Mat ImageRGB(const Mat image) ;                                         // Filtre RGB

// Traitement a base d'histogramme
Mat NormalisationMono(const Mat image) ;                                // Normalisation de l'histogramme d'une image au niveau de gris
Mat Normalisation(const Mat image, const int valeur) ;                  // Normalisation de l'histogramme d'une image en couleurs avec valeur reglable
Mat ImageEgalisationMono(const Mat image, const int valeur) ;           // Egalisation d'une image en niveau de gris avec valeur reglable
Mat ImageEgalisation(const Mat image) ;                                 // Egalisation d'une image en couleurs
Mat ImageRehaussementContraste(const Mat image, const int choix) ;      // Rehaussement de contraste
Mat ImageLuminosite(const Mat image, const int valeur) ;                // Modifier la luminosite de l'image
Mat ImageOmbre(const Mat image, int valeur) ;                           // Modifier les basses intensites
Mat ImageHauteLumiere(const Mat image, int valeur) ;                    // Modifier les hautes intensites

// Filtrage
Mat ImageMedianMono(const Mat image) ;                                  // Filtrage par filtre median pour une image en niveau gris
Mat ImageMedian(const Mat image) ;                                      // Filtrage par filtre median pour une image en couleurs
Mat ImageFiltrage(const Mat image, const int choix) ;                   // Filtrage
Mat ImageLissage(const Mat image, const int valeur) ;                   // Lisser l'image
Mat ImageKuwaharaMono(const Mat image) ;                                // Filtre Kuwahara-Nagao sur une composante
Mat ImageKuwahara(const Mat image) ;                                    // Filtre Kuwahara-Nagao

// Bruitage
Mat ImageBruitGaussien(const Mat image, const double moyenne, const double sigma) ;             // Ajouter du bruit gaussien sur l'image
Mat ImageBruitPoivreSel(const Mat image) ;                              // Ajouter du bruit poivre et sel dans l'image

// Contours
Mat ImageContourGradient(const Mat image) ;                             // Detection de contours par filtres gradients
Mat ImageContourLaplace(const Mat image) ;                              // Detection de contours par filtre laplacien
Mat ImageContour(const Mat image, const int choix) ;                    // Detection de contours
Mat ImageRehaussementContour(const Mat image, const int val, const int choix) ;                 // Rehaussement de contours

// Seuillage
Mat ImageSeuillage(const Mat image, const int seuil) ;                  // Seuillage d'une image en niveau de gris
Mat ImageSeuillage(const Mat image, vector<int> seuil) ;                // Seuillage d'une image en couleurs
Mat ImageSeuillage(const Mat image, const int seuilBas, const int seuilHaut) ;                  // Seuillage par hysteresis d'une image en niveau de gris
Mat ImageSeuillage(const Mat image, vector<int> seuilBas, vector<int> seuilHaut) ;              // Seuillage par hysteresis d'une image en couleurs

// Segmentation
Mat ImageSegmentation(const Mat image, const int seuil) ;                                       // Segmentation d'une image en niveau de gris par seuillage simple
Mat ImageSegmentation(const Mat image, vector<int> seuil) ;                                     // Segmentation d'une image en couleurs par seuillage simple
Mat ImageSegmentation(const Mat image, const int seuilBas, const int seuilHaut) ;               // Segmentation d'une image en niveau de gris par seuillage hysteresis
Mat ImageSegmentation(const Mat image, vector<int> seuilBas, vector<int> seuilHaut) ;           // Segmentation d'une image en couleurs par seuillage hysteresis

// Resolution
Mat ImageQuantification(const Mat image, const int valeur) ;            // Quantification
Mat ImageResolutionReduction(const Mat image, const int valeur) ;       // Reduire la dimension de l'image
Mat InterpolationPPP(const Mat image, const int valeur) ;               // Interpolation par pixel le plus proche
Mat InterpolationBilineaire(const Mat image, const int valeur) ;        // Interpolation bilineaire
Mat InterpolationBilineaireMono(const Mat image, const int valeur) ;    // Interpolation bilineaire pour un canal

// Operations
int MinImage(const Mat image) ;                                         // Determiner la valeur minimum dans une matrice entiere
int MaxImage(const Mat image) ;                                         // Determiner la valeur maximum dans une matrice entiere
double MinVecteur(const vector<double> vecteur) ;                       // Determiner la valeur minimum dans un vecteur reel
double MaxVecteur(const vector<double> vecteur) ;                       // Determiner la valeur maximum dans un vecteur reel
int MinVecteur(const vector<int> vecteur) ;                             // Determiner la valeur minimum dans un vecteur entier
int MaxVecteur(const vector<int> vecteur) ;                             // Determiner la valeur maximum dans un vecteur entier
int MinVecteurIndice(const vector<int> vecteur) ;                       // Determiner l'indice de la valeur minimum dans un vecteur entier
int MinVecteurIndice(const vector<double> vecteur) ;                    // Determiner l'indice de la valeur minimum dans un vecteur reel
vector<int> Histogramme(const Mat image, const int nbIntervalle) ;	    // Histogramme
vector<int> Egalisation(const Mat image, const int nbIntervalle) ;      // Egalisation de l'histogramme
Mat ImageZero(const int nbLigne, const int nbColonne) ; 	            // Generer une matrice zero
Mat MatriceConvolution(const Mat image, const Mat filtre) ;             // Produit de convolution entre deux matrices
Mat ImageConvolution(const Mat image, const Mat filtre) ;	            // Produit de convolution entre deux images
Mat MatriceNorme(const Mat imageX, const Mat imageY) ;                  // Calculer la norme
Mat GradientX(const Mat image, const string typeFiltre) ;               // Gradient en X
Mat GradientY(const Mat image, const string typeFiltre) ;               // Gradient en Y
Mat MaxNormeGradient(const Mat gradientNorme, const Mat gradientX, const Mat gradientY) ;       // Maximum de la norme du gradient
int MatriceMedian(const Mat matrice) ;                                  // Determiner la valeur mediane d'une matrice
int VecteurMedian(vector<int> vecteur) ;                                // Determiner la valeur mediane d'un vecteur
bool MatriceEgale(const Mat matrice1, const Mat matrice2) ;             // Verifier l'egalite entre deux matrices de memes dimensions
double MoyenneVecteur(const vector<double> vecteur) ;                   // Calculer la moyenne d'un vecteur
double VarianceVecteur(const vector<double> vecteur) ;                  // Calculer la variance d'un vecteur
Mat ImageFourier(const Mat image) ;                                     // Transformee de Fourier 2D de l'image (module)
double ImageFourierElement(const Mat image, const int ligne, const int colonne) ;               // Element de calcul de la transformee de Fourier 2D de l'image (module)

// Autres
Mat ImageMiroir(const Mat image, const Mat filtre) ;	                // Effet miroir - Filtre donne
Mat ImageMiroir(const Mat image, const int taille) ;		            // Effet miroir - Taille donnee
Mat GenererFiltre(const int typeFiltre) ;					            // Generer les filtres
Mat ConcatenerImageMono(Mat image1, Mat image2) ;                       // Concatener 2 images de memes dimensions en 1 image (en niveau de gris)
Mat ConcatenerImage(Mat image1, Mat image2) ;                           // Concatener 2 images de memes dimensions en 1 image (en couleurs)
Mat MonoCouleur(const Mat image) ;                                      // Convertir le format d'une image monochrome en format RVB
void SaisirSeuil(int& seuil) ;                                          // Saisie et verification de la valeur d'un seuil
void SaisirSeuil(int& seuilBas, int& seuilHaut) ;                       // Saisie et verification des valeurs des seuils hysteresis
Mat PlotHistogram1D(Mat image,int choixCouleur) ;                      // Image du Graphe Histogramme en niveau de gris
Mat CalcHistogram(Mat image) ;                                         // Calcul d'histogramme
Mat PlotHistogram(Mat image) ;                                         // Image du Graphe Histogramme
bool VerifierImage(const Mat image, Mat& imageVerifiee) ;               // Verifier si l'image est en couleurs ou en niveau de gris
Mat ImageBGRRGB(const Mat image) ;                                      // Echanger les composantes R et B de l'image
Mat ImageBruitage(const Mat image, const int valeur) ;                  // Ajouter un bruit sur l'image
int VerifierSaturation(const int valeur) ;                              // Verifier la saturation
Mat ImageFourierArranger(const Mat image) ;                             // Arranger les differentes parties de la transformee de Fourier

