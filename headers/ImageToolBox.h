#pragma once
#define json_char TCHAR

// Systeme
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
// Maths
#include <cmath>
#include <complex>
// Json
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
// OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <experimental/filesystem>
#include "headers/bibliotheque.h"

namespace ImageToolBox {
using namespace std ;
using namespace rapidjson ;
using namespace cv ;
// Traitement de couleur
/**
 * @brief Modifier la temperature de l'image.
 * @param image Matrice de l'image à traiter
 * @param valeur
 * @return Matrice de l'image après traitement
 */
Mat ImageTemperature(const Mat image, const int valeur) ;               // Modifier la temperature de l'image
/**
 * @brief ImageSaturation
 * @param image
 * @param valeur
 * @return
 */
Mat ImageSaturation(const Mat image, const int valeur) ;                // Modifier la saturation
/**
 * @brief ImageSaturationElement
 * @param image
 * @param valeur
 * @return
 */
Mat ImageSaturationElement(const Mat image, const int valeur) ;         // Calcul elementaire pour la modification la saturation
/**
 * @brief ImageTeinte
 * @param image
 * @param valeur
 * @return
 */
Mat ImageTeinte(const Mat image, const int valeur) ;                    // Modifier la teinte
/**
 * @brief ImageVividite
 * @param image
 * @param valeur
 * @return
 */
Mat ImageVividite(const Mat image, const int valeur) ;                  // Modifier la vividite

// Filtre de couleur
/**
 * @brief ImageMonochrome
 * @param image
 * @return
 */
Mat ImageMonochrome(const Mat image) ;						            // Convertir une image en niveau de gris
/**
 * @brief ImageSepia
 * @param image
 * @return
 */
Mat ImageSepia(const Mat image) ;                                       // Monochrome - Sepia
/**
 * @brief ImageInversementMono
 * @param image
 * @return
 */
Mat ImageInversementMono(const Mat image) ;				                // Inverser une image en niveau de gris
/**
 * @brief ImageInversement
 * @param image
 * @return
 */
Mat ImageInversement(const Mat image) ;                                 // Inverser une image en couleurs
/**
 * @brief ImageExtractionCouleur
 * @param image
 * @param choix
 * @return
 */
Mat ImageExtractionCouleur(const Mat image, int choix) ;                // Extraction une composante de couleur de l'image
/**
 * @brief ImageRouge
 * @param image
 * @return
 */
Mat ImageRouge(const Mat image) ;                                       // Extraire la couleur rouge
/**
 * @brief ImageVert
 * @param image
 * @return
 */
Mat ImageVert(const Mat image) ;                                        // Extraire la couleur verte
/**
 * @brief ImageBleu
 * @param image
 * @return
 */
Mat ImageBleu(const Mat image) ;                                        // Extraire la couleur bleue
/**
 * @brief ImageJaune
 * @param image
 * @return
 */
Mat ImageJaune(const Mat image) ;                                       // Extraire la couleur jaune
/**
 * @brief ImageCyan
 * @param image
 * @return
 */
Mat ImageCyan(const Mat image) ;                                        // Extraire la couleur cyane
/**
 * @brief ImageMagenta
 * @param image
 * @return
 */
Mat ImageMagenta(const Mat image) ;                                     // Extraire la couleur magenta
/**
 * @brief ImageRGB
 * @param image
 * @return
 */
Mat ImageRGB(const Mat image) ;                                         // Filtre RGB

// Traitement a base d'histogramme
/**
 * @brief NormalisationMono
 * @param image
 * @return
 */
Mat NormalisationMono(const Mat image) ;                                // Normalisation de l'histogramme d'une image au niveau de gris
/**
 * @brief Normalisation
 * @param image
 * @param valeur
 * @return
 */
Mat Normalisation(const Mat image, const int valeur) ;                  // Normalisation de l'histogramme d'une image en couleurs avec valeur reglable
/**
 * @brief ImageEgalisationMono
 * @param image
 * @param valeur
 * @return
 */
Mat ImageEgalisationMono(const Mat image, const int valeur) ;           // Egalisation d'une image en niveau de gris avec valeur reglable
/**
 * @brief ImageEgalisation
 * @param image
 * @return
 */
Mat ImageEgalisation(const Mat image) ;                                 // Egalisation d'une image en couleurs
/**
 * @brief ImageRehaussementContraste
 * @param image
 * @param choix
 * @return
 */
Mat ImageRehaussementContraste(const Mat image, const int choix) ;      // Rehaussement de contraste
/**
 * @brief ImageLuminosite
 * @param image
 * @param valeur
 * @return
 */
Mat ImageLuminosite(const Mat image, const int valeur) ;                // Modifier la luminosite de l'image
/**
 * @brief ImageOmbre
 * @param image
 * @param valeur
 * @return
 */
Mat ImageOmbre(const Mat image, int valeur) ;                           // Modifier les basses intensites
/**
 * @brief ImageHauteLumiere
 * @param image
 * @param valeur
 * @return
 */
Mat ImageHauteLumiere(const Mat image, int valeur) ;                    // Modifier les hautes intensites



// Filtrage
/**
 * @brief ImageMedianMono
 * @param image
 * @return
 */
Mat ImageMedianMono(const Mat image) ;                                  // Filtrage par filtre median pour une image en niveau gris
/**
 * @brief ImageMedian
 * @param image
 * @return
 */
Mat ImageMedian(const Mat image) ;                                      // Filtrage par filtre median pour une image en couleurs
/**
 * @brief ImageFiltrage
 * @param image
 * @param choix
 * @return
 */
Mat ImageFiltrage(const Mat image, const int choix) ;                   // Filtrage
/**
 * @brief ImageLissage
 * @param image
 * @param valeur
 * @return
 */
Mat ImageLissage(const Mat image, const int valeur) ;                   // Lisser l'image
/**
 * @brief ImageKuwaharaMono
 * @param image
 * @return
 */
Mat ImageKuwaharaMono(const Mat image) ;                                // Filtre Kuwahara-Nagao sur une composante
/**
 * @brief ImageKuwahara
 * @param image
 * @return
 */
Mat ImageKuwahara(const Mat image) ;                                    // Filtre Kuwahara-Nagao

// Bruitage
/**
 * @brief ImageBruitGaussien
 * @param image
 * @param moyenne
 * @param sigma
 * @return
 */
Mat ImageBruitGaussien(const Mat image, const double moyenne, const double sigma) ;             // Ajouter du bruit gaussien sur l'image
/**
 * @brief ImageBruitPoivreSel
 * @param image
 * @return
 */
Mat ImageBruitPoivreSel(const Mat image) ;                              // Ajouter du bruit poivre et sel dans l'image

// Contours
/**
 * @brief ImageContourGradient
 * @param image
 * @return
 */
Mat ImageContourGradient(const Mat image) ;                             // Detection de contours par filtres gradients
/**
 * @brief ImageContourLaplace
 * @param image
 * @return
 */
Mat ImageContourLaplace(const Mat image) ;                              // Detection de contours par filtre laplacien
/**
 * @brief ImageContour
 * @param image
 * @param choix
 * @return
 */
Mat ImageContour(const Mat image, const int choix) ;                    // Detection de contours
/**
 * @brief ImageRehaussementContour
 * @param image
 * @param val
 * @param choix
 * @return
 */
Mat ImageRehaussementContour(const Mat image, const int val, const int choix) ;                 // Rehaussement de contours



// Seuillage
/**
 * @brief ImageSeuillage
 * @param image
 * @param seuil
 * @return
 */
Mat ImageSeuillage(const Mat image, const int seuil) ;                  // Seuillage d'une image en niveau de gris
/**
 * @brief ImageSeuillage
 * @param image
 * @param seuil
 * @return
 */
Mat ImageSeuillage(const Mat image, vector<int> seuil) ;                // Seuillage d'une image en couleurs
/**
 * @brief ImageSeuillage
 * @param image
 * @param seuilBas
 * @param seuilHaut
 * @return
 */
Mat ImageSeuillage(const Mat image, const int seuilBas, const int seuilHaut) ;                  // Seuillage par hysteresis d'une image en niveau de gris
/**
 * @brief ImageSeuillage
 * @param image
 * @param seuilBas
 * @param seuilHaut
 * @return
 */
Mat ImageSeuillage(const Mat image, vector<int> seuilBas, vector<int> seuilHaut) ;              // Seuillage par hysteresis d'une image en couleurs



// Segmentation
/**
 * @brief ImageSegmentation
 * @param image
 * @param seuil
 * @return
 */
Mat ImageSegmentation(const Mat image, const int seuil) ;                                       // Segmentation d'une image en niveau de gris par seuillage simple
/**
 * @brief ImageSegmentation
 * @param image
 * @param seuil
 * @return
 */
Mat ImageSegmentation(const Mat image, vector<int> seuil) ;                                     // Segmentation d'une image en couleurs par seuillage simple
/**
 * @brief ImageSegmentation
 * @param image
 * @param seuilBas
 * @param seuilHaut
 * @return
 */
Mat ImageSegmentation(const Mat image, const int seuilBas, const int seuilHaut) ;               // Segmentation d'une image en niveau de gris par seuillage hysteresis
/**
 * @brief ImageSegmentation
 * @param image
 * @param seuilBas
 * @param seuilHaut
 * @return
 */
Mat ImageSegmentation(const Mat image, vector<int> seuilBas, vector<int> seuilHaut) ;           // Segmentation d'une image en couleurs par seuillage hysteresis



// Resolution
/**
 * @brief ImageQuantification
 * @param image
 * @param valeur
 * @return
 */
Mat ImageQuantification(const Mat image, const int valeur) ;            // Quantification
/**
 * @brief ImageResolutionReduction
 * @param image
 * @param valeur
 * @return
 */
Mat ImageResolutionReduction(const Mat image, const int valeur) ;       // Reduire la dimension de l'image
/**
 * @brief InterpolationPPP
 * @param image
 * @param valeur
 * @return
 */
Mat InterpolationPPP(const Mat image, const int valeur) ;               // Interpolation par pixel le plus proche
/**
 * @brief InterpolationBilineaire
 * @param image
 * @param valeur
 * @return
 */
Mat InterpolationBilineaire(const Mat image, const int valeur) ;        // Interpolation bilineaire
/**
 * @brief InterpolationBilineaireMono
 * @param image
 * @param valeur
 * @return
 */
Mat InterpolationBilineaireMono(const Mat image, const int valeur) ;    // Interpolation bilineaire pour un canal



// Operations
/**
 * @brief MinImage
 * @param image
 * @return
 */
int MinImage(const Mat image) ;                                         // Determiner la valeur minimum dans une matrice entiere
/**
 * @brief MaxImage
 * @param image
 * @return
 */
int MaxImage(const Mat image) ;                                         // Determiner la valeur maximum dans une matrice entiere
/**
 * @brief MinVecteur
 * @param vecteur
 * @return
 */
double MinVecteur(const vector<double> vecteur) ;                       // Determiner la valeur minimum dans un vecteur reel
/**
 * @brief MaxVecteur
 * @param vecteur
 * @return
 */
double MaxVecteur(const vector<double> vecteur) ;                       // Determiner la valeur maximum dans un vecteur reel
/**
 * @brief MinVecteur
 * @param vecteur
 * @return
 */
int MinVecteur(const vector<int> vecteur) ;                             // Determiner la valeur minimum dans un vecteur entier
/**
 * @brief MaxVecteur
 * @param vecteur
 * @return
 */
int MaxVecteur(const vector<int> vecteur) ;                             // Determiner la valeur maximum dans un vecteur entier
/**
 * @brief MinVecteurIndice
 * @param vecteur
 * @return
 */
int MinVecteurIndice(const vector<int> vecteur) ;                       // Determiner l'indice de la valeur minimum dans un vecteur entier
/**
 * @brief MinVecteurIndice
 * @param vecteur
 * @return
 */
int MinVecteurIndice(const vector<double> vecteur) ;                    // Determiner l'indice de la valeur minimum dans un vecteur reel
/**
 * @brief Histogramme
 * @param image
 * @param nbIntervalle
 * @return
 */
vector<int> Histogramme(const Mat image, const int nbIntervalle) ;	    // Histogramme
/**
 * @brief Egalisation
 * @param image
 * @param nbIntervalle
 * @return
 */
vector<int> Egalisation(const Mat image, const int nbIntervalle) ;      // Egalisation de l'histogramme
/**
 * @brief ImageZero
 * @param nbLigne
 * @param nbColonne
 * @return
 */
Mat ImageZero(const int nbLigne, const int nbColonne) ; 	            // Generer une matrice zero
/**
 * @brief MatriceConvolution
 * @param image
 * @param filtre
 * @return
 */
Mat MatriceConvolution(const Mat image, const Mat filtre) ;             // Produit de convolution entre deux matrices
/**
 * @brief ImageConvolution
 * @param image
 * @param filtre
 * @return
 */
Mat ImageConvolution(const Mat image, const Mat filtre) ;	            // Produit de convolution entre deux images
/**
 * @brief MatriceNorme
 * @param imageX
 * @param imageY
 * @return
 */
Mat MatriceNorme(const Mat imageX, const Mat imageY) ;                  // Calculer la norme
/**
 * @brief GradientX
 * @param image
 * @param typeFiltre
 * @return
 */
Mat GradientX(const Mat image, const string typeFiltre) ;               // Gradient en X
/**
 * @brief GradientY
 * @param image
 * @param typeFiltre
 * @return
 */
Mat GradientY(const Mat image, const string typeFiltre) ;               // Gradient en Y
/**
 * @brief MaxNormeGradient
 * @param gradientNorme
 * @param gradientX
 * @param gradientY
 * @return
 */
Mat MaxNormeGradient(const Mat gradientNorme, const Mat gradientX, const Mat gradientY) ;       // Maximum de la norme du gradient
/**
 * @brief MatriceMedian
 * @param matrice
 * @return
 */
int MatriceMedian(const Mat matrice) ;                                  // Determiner la valeur mediane d'une matrice
/**
 * @brief VecteurMedian
 * @param vecteur
 * @return
 */
int VecteurMedian(vector<int> vecteur) ;                                // Determiner la valeur mediane d'un vecteur
/**
 * @brief MatriceEgale
 * @param matrice1
 * @param matrice2
 * @return
 */
bool MatriceEgale(const Mat matrice1, const Mat matrice2) ;             // Verifier l'egalite entre deux matrices de memes dimensions
/**
 * @brief MoyenneVecteur
 * @param vecteur
 * @return
 */
double MoyenneVecteur(const vector<double> vecteur) ;                   // Calculer la moyenne d'un vecteur
/**
 * @brief VarianceVecteur
 * @param vecteur
 * @return
 */
double VarianceVecteur(const vector<double> vecteur) ;                  // Calculer la variance d'un vecteur
/**
 * @brief ImageFourier
 * @param image
 * @return
 */
Mat ImageFourier(const Mat image) ;                                     // Transformee de Fourier 2D de l'image (module)
/**
 * @brief ImageFourierElement
 * @param image
 * @param ligne
 * @param colonne
 * @return
 */
double ImageFourierElement(const Mat image, const int ligne, const int colonne) ;               // Element de calcul de la transformee de Fourier 2D de l'image (module)



// Autres
/**
 * @brief ImageMiroir
 * @param image
 * @param filtre
 * @return
 */
Mat ImageMiroir(const Mat image, const Mat filtre) ;	                // Effet miroir - Filtre donne
/**
 * @brief ImageMiroir
 * @param image
 * @param taille
 * @return
 */
Mat ImageMiroir(const Mat image, const int taille) ;		            // Effet miroir - Taille donnee
/**
 * @brief GenererFiltre
 * @param typeFiltre
 * @return
 */
Mat GenererFiltre(const int typeFiltre) ;					            // Generer les filtres
/**
 * @brief ConcatenerImageMono
 * @param image1
 * @param image2
 * @return
 */
Mat ConcatenerImageMono(Mat image1, Mat image2) ;                       // Concatener 2 images de memes dimensions en 1 image (en niveau de gris)
/**
 * @brief ConcatenerImage
 * @param image1
 * @param image2
 * @return
 */
Mat ConcatenerImage(Mat image1, Mat image2) ;                           // Concatener 2 images de memes dimensions en 1 image (en couleurs)
/**
 * @brief MonoCouleur
 * @param image
 * @return
 */
Mat MonoCouleur(const Mat image) ;                                      // Convertir le format d'une image monochrome en format RVB
/**
 * @brief SaisirSeuil
 * @param seuil
 */
void SaisirSeuil(int& seuil) ;                                          // Saisie et verification de la valeur d'un seuil
/**
 * @brief SaisirSeuil
 * @param seuilBas
 * @param seuilHaut
 */
void SaisirSeuil(int& seuilBas, int& seuilHaut) ;                       // Saisie et verification des valeurs des seuils hysteresis
/**
 * @brief PlotHistogram1D
 * @param image
 * @param choixCouleur
 * @return
 */
Mat PlotHistogram1D(Mat image,int choixCouleur) ;                      // Image du Graphe Histogramme en niveau de gris
/**
 * @brief CalcHistogram
 * @param image
 * @return
 */
Mat CalcHistogram(Mat image) ;                                         // Calcul d'histogramme
/**
 * @brief PlotHistogram
 * @param image
 * @return
 */
Mat PlotHistogram(Mat image) ;                                         // Image du Graphe Histogramme
/**
 * @brief VerifierImage
 * @param image
 * @param imageVerifiee
 * @return
 */
bool VerifierImage(const Mat image, Mat& imageVerifiee) ;               // Verifier si l'image est en couleurs ou en niveau de gris
/**
 * @brief ImageBGRRGB
 * @param image
 * @return
 */
Mat ImageBGRRGB(const Mat image) ;                                      // Echanger les composantes R et B de l'image
/**
 * @brief ImageBruitage
 * @param image
 * @param valeur
 * @return
 */
Mat ImageBruitage(const Mat image, const int valeur) ;                  // Ajouter un bruit sur l'image
/**
 * @brief VerifierSaturation
 * @param valeur
 * @return
 */
int VerifierSaturation(const int valeur) ;                              // Verifier la saturation
/**
 * @brief ImageFourierArranger
 * @param image
 * @return
 */
Mat ImageFourierArranger(const Mat image) ;                             // Arranger les differentes parties de la transformee de Fourier

};
