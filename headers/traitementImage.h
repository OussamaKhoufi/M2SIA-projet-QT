#include "image.h"

using namespace cv ;
using namespace std ;

// Traitement de couleur
Mat ImageMonochrome(const Mat image) ;						            // Convertir une image en niveau de gris
Mat ImageInversementMono(const Mat image) ;				                // Inverser une image en niveau de gris
Mat ImageInversement(const Mat image) ;                                 // Inverser une image en couleurs
Mat ImageExtractionCouleur(const Mat image, int choix) ;                // Extraction une composante de couleur de l'image

// Traitement a base d'histogramme
Mat NormalisationMono(const Mat image) ;                                // Normalisation de l'histogramme d'une image au niveau de gris
Mat Normalisation(const Mat image) ;                                    // Normalisation de l'histogramme d'une image en couleurs
Mat ImageEgalisationMono(const Mat image) ;                             // Egalisation d'une image en niveau de gris
Mat ImageEgalisation(const Mat image) ;                                 // Egalisation d'une image en couleurs
Mat ImageRehaussementContraste(const Mat image, const int choix) ;      // Rehaussement de contraste

// Filtrage
Mat ImageMedianMono(const Mat image) ;                                  // Filtrage par filtre median pour une image en niveau gris
Mat ImageMedian(const Mat image) ;                                      // Filtrage par filtre median pour une image en couleurs
Mat ImageFiltrage(const Mat image, const int choix) ;                   // Filtrage

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
Mat ImageSeuillage(const Mat image) ;                                   // Seuillage - Menu

// Segmentation
Mat ImageSegmentation(const Mat image, const int seuil) ;                                       // Segmentation d'une image en niveau de gris par seuillage simple
Mat ImageSegmentation(const Mat image, vector<int> seuil) ;                                     // Segmentation d'une image en couleurs par seuillage simple
Mat ImageSegmentation(const Mat image, const int seuilBas, const int seuilHaut) ;               // Segmentation d'une image en niveau de gris par seuillage hysteresis
Mat ImageSegmentation(const Mat image, vector<int> seuilBas, vector<int> seuilHaut) ;           // Segmentation d'une image en couleurs par seuillage hysteresis
Mat ImageSegmentation(const Mat image) ;                                // Segmentation - Menu

// Operations
int MinImage(const Mat image) ;                                         // Determiner la valeur minimum dans une matrice entiere
int MaxImage(const Mat image) ;                                         // Determiner la valeur maximum dans une matrice entiere
double MaxVecteur(const vector<double> vecteur) ;                       // Determiner la valeur maximum dans un vecteur reel
int MaxVecteur(const vector<int> vecteur) ;                             // Determiner la valeur maximum dans un vecteur entier
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

// Autres
Mat ImageMiroir(const Mat image, const Mat filtre) ;	                // Effet miroir - Filtre donne
Mat ImageMiroir(const Mat image, const int taille) ;		            // Effet miroir - Taille donnee
Mat GenererFiltre(const int typeFiltre) ;					            // Generer les filtres
Mat ConcatenerImageMono(Mat image1, Mat image2) ;                       // Concatener 2 images de memes dimensions en 1 image (en niveau de gris)
Mat ConcatenerImage(Mat image1, Mat image2) ;                           // Concatener 2 images de memes dimensions en 1 image (en couleurs)
Mat MonoCouleur(const Mat image) ;                                      // Convertir le format d'une image monochrome en format RVB
void SaisirSeuil(int& seuil) ;                                          // Saisie et verification de la valeur d'un seuil
void SaisirSeuil(int& seuilBas, int& seuilHaut) ;                       // Saisie et verification des valeurs des seuils hysteresis
Mat plot_histogram1D(Mat image,int choixCouleur) ;                                    // Image du Graphe Histogramme
Mat calc_histogram(Mat image) ;                                           // Calcul d'histogramme
Mat plot_histogram(Mat image) ;  
bool VerifierImage(const Mat image, Mat& imageVerifiee) ;               // Verifier si l'image est en couleurs ou en niveau de gris
