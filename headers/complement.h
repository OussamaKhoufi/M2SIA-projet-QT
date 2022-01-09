// Systeme
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 
#include <experimental/filesystem>
#include <dirent.h>

// Json
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

using namespace std ;
using namespace rapidjson ;

/*Date*/
string SaisirDate(string& jour, string& mois, string& annee) ;                              // Saisir et valider la date
bool VerifierDate(const string date) ;                                                      // Verifier le format de la date
vector<int> VerifierDate(const string date, string& jour, string& mois, string& annee) ;    // Valider la date et remplir les champs requis
void ExtraireDate(const string date, string& jour, string& mois, string& annee) ;	        // Extraire jour, mois, annee a partir d'une date

/*Verification*/
bool VerifierCout(const string saisie, double& chiffre) ;                         	        // Verifier le format du cout saisie
void VerifierExtension(string& nom) ;												        // Verifier l'extension ".json"
bool VerifierNumero(const string saisie, int& numero) ;                         	        // Verifier le format du numero (entier)
bool VerifierNumero(const string saisie, double& numero) ;                         	        // Verifier le format du numero (reel)
bool VerifierNumero(const int numero, const Json::Value biblio) ;               	        // Verifier l'existance d'un numero de l'image
bool VerifierExistance(vector<string> vecteur, string valeur) ;                             // Verifier l'existance d'un element dans un vecteur

/*Continuement*/
bool Continuer() ;                                                              	        // Continuer [Y/N]
bool Continuer(const string message) ;                                          	        // Continuer [Y/N] avec message personnalisee

/*Lister*/
vector<string> ListerSource(Json::Value biliotheque) ;                                      // Creer une liste des sources des images contenues dans une bibliotheque
vector<string> ListerImage() ;                                                              // Creer une liste des noms des fichiers des images dans la base de donnees
vector<int> ListerNumero(Json::Value biliotheque) ;                                         // Creer une liste des numeros des images contenues dans une bibliotheque
