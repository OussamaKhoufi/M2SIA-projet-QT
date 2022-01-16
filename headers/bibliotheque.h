#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

// Systeme
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 
#include <experimental/filesystem>
// Json
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
// Fonctions complementaires
#include "complement.h"

using namespace rapidjson ;
using namespace std ;


class Bibliotheque{
    private :      
        Json::Value _bibliotheque ;                                             // Objet de type Json
        string _cheminJson;
    public :
        /*Constructeurs*/
        Bibliotheque() ;                                                        // Constructeur vide 
        Bibliotheque(string nom) ;                                              // Constructeur avec le nom de la bibliotheque donnee par l'utilisateur
        Bibliotheque(const Json::Value bibliotheque) ;                          // Constructeur avec un objet Json
        /*Getters*/
        Json::Value getBilbiotheque() const ;
        string getCheminJson() const;
        /*Setters*/
        void setBilbiotheque(const Json::Value bibliotheque) ;
        void setCheminJson(const string cheminJson) ;

        /*Methodes principales*/
        void AfficherDescripteurs() ;                                                   // Afficher la liste des descripteurs
        void AfficherDescripteurs(const Json::Value bibliotheque, const int indice) ;   // Afficher la liste des descripteurs d'une partie indiquee de la bibliotheque
        void AfficherCout() ;                                                           // Affichage le cout d'une image
        void ConstruireAfficherSousListe() ;                                            // Construire et afficher une sous-liste
        void Trier() ;                                                                  // Trier la bibliotheque suivant une critere
        void AjouterImage() ;                                                           // Ajouter une image dans la bibliotheque
        void SupprimerImage() ;                                                         // Supprimer une image de la bibliotheque
        void Sauvegarder() ;                                                            // Sauvegarder une bibliotheque
        void majBiblioSuivantDroitAcces(const bool droitAcces) ;                 // Creer une sous-bibliotheque avec les images correspondantes au droit d'utilisateur

        /*Methodes supplementaires*/
        int ConstruireAfficherSousListeCout(const int choix) ;                          // Construire et afficher une sous-liste en fonction du cout (4 premieres options)
        int ConstruireAfficherSousListeCout(double coutMin, double coutMax) ;           // Construire et afficher une sous-liste en fonction du cout (derniere option)
        int ConstruireAfficherSousListeSource(const string source) ;                    // Construire et afficher une sous-liste en fonction de la source
        Json::Value Trier(const int choix) ;
        vector<int> Trier(vector<double>valeurNonTri) ;                                 // Determiner les indices des elements avant le tri (reel)
        vector<int> Trier(vector<string>valeurNonTri) ;                                 // Determiner les indices des elements avant le tri (chaine de caracteres)
        vector<int> Trier(vector<int>valeurNonTri) ;                                    // Determiner les indices des elements avant le tri (entier)
        bool VerifierBibliotheque() ;                                                   // Veriffier bibliotheque vide ou invalide
        
};

#endif // BIBLIOTHEQUE_H
