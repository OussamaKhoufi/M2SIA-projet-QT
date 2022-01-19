#ifndef IMAGE_H
#define IMAGE_H
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
// Autres librairies
#include "traitementImage.h"
#include "bibliotheque.h"
#include "complement.h"

using namespace std ;
using namespace rapidjson ;
using namespace cv ;


class Image{
    private :
        string _cheminAccesContenu ;			// Chemin acces a l'image
        string _source ;						// Source de l'image
        string _titre ;							// Titre de l'image
        int _numero ;							// Numero de l'image
        double _cout ;							// Cout de l'image
        string _acces ;							// Permission d'acces de l'image
        string _dateAjout ;						// Date d'ajout de l'image
        string _dateCreation ;					// Date de creation de l'image
        string _cheminJson ;					// Chemin vers la bibliotheque contenant l'image
        int _numeroJson ;						// Indice de l'image dans la bibiotheque

    public :
        /*Constructeurs*/
        Image();																			// Constructeur vide
        Image(string chemin) ;																// Constructeur avec un chemin d'acces a la bibliotheque donne
        Image(string chemin, int num) ;														// Constructeur avec un chemin d'acces a la bibliotheque et un numero de l'image donnes
        Image(Bibliotheque objBiblio,int numImage) ;										// Constructeur avec un objet bibliotheque et le numero de l'image connu

        /*Getter*/
        string getCheminAccesContenu() const ;      										// Chemin d'acces
        string getSource() const ;                  										// Source
        string getTitre() const ;                   										// Titre
        int getNumero() const ;                     										// Numero
        double getCout() const ;                    										// Cout
        string getAcces() const ;                   										// Permission
        string getDateAjout() const ;               										// Date d'ajout
        string getDateCreation() const ;            										// Date de creation
        string getCheminJson() const ;														// Chemin vers la bibliotheque
        int getNumeroJson() const ;															// Numero de l'image dans la bibiotheque

        /*Setters*/
        void setCheminAccesContenu(const string cheminAccesContenu) ;   					// Chemin d'acces
        void setSource(const string source) ;                           					// Source
        void setTitre(const string titre) ;                             					// Titre
        void setNumero(const int numero) ;                              					// Numero
        void setCout(const double cout) ;                               					// Cout
        void setAcces(const string acces) ;                             					// Permission
        void setDateAjout(const string dateAjout) ;                     					// Date d'ajout
        void setDateCreation(const string dateCreation) ;               					// Date de creation
        void setCheminJson(const string cheminJson) ;										// Chemin Json
        void setNumeroJson(const int numeroJson) ;											// Numero Json

        /*Methodes*/
        void AfficherContenuImage() ;														// Afficher le contenu de l'image
        void AfficherDescripteurImage() ;													// Afficher les descripteurs de l'image
        void ModifierDescripteurImage() ;													// Modifier un descripteur de l'image (saisie & affichage)
        vector<int> ModifierDescripteurImage(const int choix, const string saisie, Json::Value& biblio) ;		// Modifier un descripteur de l'image (verification et affectation)
        void ModifierDescripteurImage(const vector<int> erreur) ;							// Afficher les erreurs de la modification d'un descripteur de l'image
        void TraitementImage(int choixTraitement) ;											// Traitement de l'image
} ;

#endif // IMAGE_H








