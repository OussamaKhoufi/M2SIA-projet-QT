#ifndef APPMAINWINDOW_H
#define APPMAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <QPixmap>          // Pour afficher les images
#include <QMessageBox>      // Pour afficher les messages d'erreur
#include <QString>          // Pour travailler avec les chaines de caracteres
#include <QListWidgetItem>  // Pour travailler avec les elements dans une liste
#include <QDebug>           // Pour afficher les messages de debug
#include <QtGui>
#include <QtWidgets>
#include "headers/image.h"
#include "headers/bibliotheque.h"
using namespace std;

namespace Ui {
class AppMainWindow;
}

class AppMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppMainWindow(QWidget *parent = 0);
    ~AppMainWindow();

private slots:
    void on_pushButtonIdentifier_clicked();             // button identification

    void on_pushButtonQuitter_clicked();                // Button Quitter l'application

    void on_pushButtonChargerBiblio_clicked();          // Button charger une bibliothèque

    void on_pushButtonRetourIdentification_clicked();   // button retour au menu identification

    void on_tableBiblioRowClicked(int , int );

    void on_pushButtonSauvegarder_clicked();

    void on_pushButtonSupprimerImage_clicked();

    void on_pushButtonRetourMenuPrincipal_clicked();

    void on_lineEditMdp_returnPressed();

    void on_comboBoxTrierIndexChanged(int);

    void on_comboBoxCritereCoutIndexChanged(int);

    void on_comboBoxCritereDateAjoutIndexChanged(int);


    void on_pushButtonAjouterImage_clicked();

    void on_pushButtonAjoutImageAnnuler_clicked();


    void on_pushButtonAjoutImageAjouter_clicked();

    void on_pushButtonCreerBiblio_clicked();

    void on_pushButtonSauvegarderSousListe_clicked();

    void on_pushButtonOuvrirImage_clicked();

    void on_pushButtonRetourMenuModificationImage_clicked();

    void on_doubleSpinBoxMin_valueChanged(double );

    void on_doubleSpinBoxMax_valueChanged(double );

    // Page Image non modifiable--------------------------------

    // Agrandissement de l'image (non modifiable)
    void on_horizontalSlider_agrandissementNonModifiable_valueChanged(int value) ;

    // Page Image modifiable--------------------------------

    // Bouton de sauvegarder les modifications
    void on_pushButton_modifier_clicked() ;
    // Agrandissement de l'image
    void on_horizontalSlider_agrandissement_valueChanged(int value) ;
    // Passer a la page des traitements de l'image choisie
    void on_pushButton_traitementImage_clicked() ;

    // Page Traitement--------------------------------
    // -------------Standars-------------

    // Retour a la page pour choisir l'image a traiter
    void on_pushButton_retour_clicked() ;
    // Agrandissement de l'image originale
    void on_horizontalSlider_imageOriginale_valueChanged(int value) ;
    // Agrandissement de l'image traitee
    void on_horizontalSlider_imageTraitee_valueChanged(int value) ;
    // Reinitialiser l'image originale
    void on_pushButton_traitementReinitialiser_clicked() ;
    // Sauvegarder temporellement l'image de resultat
    void on_pushButton_traitementAppliquer_clicked() ;

    // -------------Luminosite-------------

    // Initialiser
    void on_groupBox_correction_clicked() ;
    // Bouton : Intensite lumineuse
    void on_radioButton_luminosite_clicked() ;
    // Intensite lumineuse
    void on_horizontalSlider_luminosite_valueChanged(int value) ;
    // Bouton : Contraste
    void on_radioButton_contraste_clicked() ;
    // Contraste
    void on_horizontalSlider_contraste_valueChanged(int value) ;
    // Bouton : Ombre
    void on_radioButton_ombre_clicked() ;
    // Ombre
    void on_horizontalSlider_ombre_valueChanged(int value) ;
    // Bouton : Haute lumiere
    void on_radioButton_brillance_clicked() ;
    // Haute lumiere
    void on_horizontalSlider_brillance_valueChanged(int value) ;

    // -------------Details-------------

    // Initialiser
    void on_groupBox_details_clicked() ;
    // Bouton : Nettete
    void on_radioButton_nettete_clicked() ;
    // Nettete
    void on_horizontalSlider_nettete_valueChanged(int value) ;
    // Bouton : Bruitage
    void on_radioButton_bruitage_clicked() ;
    // Bruitage
    void on_horizontalSlider_Bruitage_valueChanged(int value) ;

    // -------------Filtres de couleur-------------

    // Initialiser
    void on_groupBox_filtres_clicked() ;
    // Image originale
    void on_radioButton_originale_clicked() ;
    // Image en niveau de gris
    void on_radioButton_niveauGris_clicked() ;
    // Image inversee
    void on_radioButton_inversement_clicked() ;
    // Image rouge
    void on_radioButton_rouge_clicked() ;
    // Image verte
    void on_radioButton_vert_clicked() ;
    // Image bleue
    void on_radioButton_bleu_clicked() ;
    // Image jaune
    void on_radioButton_jaune_clicked() ;
    // Image cyane
    void on_radioButton_cyan_clicked() ;
    // Image sepia
    void on_radioButton_sepia_clicked() ;
    // Image magenta
    void on_radioButton_magenta_clicked() ;
    // Image RGB
    void on_radioButton_rgb_clicked() ;

    // -------------Extraction du canal de couleur-------------

    // Initialiser
    void on_groupBox_extractionRVB_clicked();
    // Extraction canal rouge
    void on_radioButton_extractionR_clicked() ;
    // Extraction canal vert
    void on_radioButton_extractionV_clicked() ;
    // Extraction canal bleu
    void on_radioButton_extractionB_clicked() ;

    // -------------Seuillage & Segmentation-------------

    // Initialiser
    void on_groupBox_seuillageSegmentation_clicked();
    // Seuillage
    void on_radioButton_seuillage_clicked() ;
    // Segmentation
    void on_radioButton_segmentation_clicked() ;
    // Seuils simples
    void on_radioButton_seuillageSimple_clicked() ;
    // Seuils par hysteresis
    void on_radioButton_seuillageHysteresis_clicked() ;
    // Seuil bas rouge
    void on_verticalSlider_seuilBasR_2_valueChanged(int value) ;
    // Seuil bas vert
    void on_verticalSlider_seuilBasV_2_valueChanged(int value) ;
    // Seuil bas bleu
    void on_verticalSlider_seuilBasB_2_valueChanged(int value) ;
    // Seuil haut rouge
    void on_verticalSlider_seuilHautR_2_valueChanged(int value) ;
    // Seuil haut vert
    void on_verticalSlider_seuilHautV_2_valueChanged(int value) ;
    // Seuil haut bleu
    void on_verticalSlider_seuilHautB_2_valueChanged(int value) ;

    // Reinitialiser seuil bas rouge
    void on_pushButton_seuilBasR_clicked() ;
    // Reinitialiser seuil bas vert
    void on_pushButton_seuilBasV_clicked() ;
    // Reinitialiser seuil bas bleu
    void on_pushButton_seuilBasB_clicked() ;
    // Reinitialiser seuil haut rouge
    void on_pushButton_seuilHautR_clicked() ;
    // Reinitialiser seuil haut vert
    void on_pushButton_seuilHautV_clicked() ;
    // Reinitialiser seuil haut bleu
    void on_pushButton_seuilHautB_clicked() ;

    // -------------Contours-------------

    // Initialiser
    void on_groupBox_contours_clicked() ;
    // Contours par filtres gradients
    void on_radioButton_contoursGradient_clicked() ;
    // Contours par filtre laplacien
    void on_radioButton_contoursLaplacien_clicked() ;

    //-------------Resolution-------------

    // Initialiser
    void on_groupBox_resolutionQuantification_clicked();
    // Bouton : Resolution
    void on_radioButton_resolution_clicked();
    // Bouton : Interpolation par pixel le plus proche
    void on_radioButton_PPP_clicked() ;
    // Bouton : Interpolation bilineaire
    void on_radioButton_bipolaire_clicked() ;
    // Resolution
    void on_horizontalSlider_resolution_valueChanged(int value) ;
    // Bouton : Quantification
    void on_radioButton_quantification_clicked() ;
    // Quantification
    void on_horizontalSlider_quantification_valueChanged(int value) ;

    // -------------Debruitage-------------

    // Initialiser
    void on_groupBox_debruitage_clicked() ;
    // Filtre moyeneur
    void on_radioButton_moyenneur_clicked() ;
    // Filtre gaussien
    void on_radioButton_gaussien_clicked() ;
    // Filtre median
    void on_radioButton_median_clicked() ;
    // Filtre de Kuwahara-Nagao
    void on_radioButton_kuwahara_clicked();

    // -------------Couleur-------------

    // Initialiser
    void on_groupBox_couleur_clicked() ;
    // Bouton : Temperature
    void on_radioButton_temperature_clicked() ;
    // Temperature
    void on_horizontalSlider_temperature_valueChanged(int value) ;
    // Bouton : Vividite
    void on_radioButton_vividite_clicked() ;
    // Vividite
    void on_horizontalSlider_vividite_valueChanged(int value) ;
    // Bouton : Teinte
    void on_radioButton_teinte_clicked() ;
    // Teinte
    void on_horizontalSlider_teinte_valueChanged(int value) ;
    // Bouton : Saturation
    void on_radioButton_saturation_clicked() ;
    // Saturation
    void on_horizontalSlider_saturation_valueChanged(int value) ;

    //-------------Autres-------------

    // Generer les icones
    void GenererIcone() ;
    // Afficher l'image resultante apres un traitement avec inversement des canaux de couleur
    void AffichageResultat(const Mat image, const int choix) ;
    // Messages d'aide
    void AfficherMessageAide() ;
    // Messages d'aide : Luminosite
    void AfficherMessageAideLuminosite() ;
    // Messages d'aide : Couleur
    void AfficherMessageAideCouleur() ;
    // Messages d'aide : Details
    void AfficherMessageAideDetail() ;
    // Messages d'aide : Resolution
    void AfficherMessageAideResolution() ;
    // Messages d'aide : Extraction
    void AfficherMessageAideExtraction() ;
    // Messages d'aide : Contours
    void AfficherMessageAideContour() ;
    // Messages d'aide : Debruitage
    void AfficherMessageAideDebruitage() ;
    // Messages d'aide : Seuillage et segmentation
    void AfficherMessageAideSeuillageSegmentation() ;
    // Messages d'aide : Filtres
    void AfficherMessageAideFiltre() ;


    // Reinitialisation generale
    void Reinitialiser() ;
    // Reinitialiser : Box Luminosite
    void ReinitialiserLuminosite() ;
    // Reinitialiser : Box Couleur
    void ReinitialiserCouleur() ;
    // Reinitialiser : Box Resolution
    void ReinitialiserResolution() ;
    // Reinitialiser : Box Details
    void ReinitialiserDetail() ;
    // Reinitialiser : Box Extraction
    void ReinitialiserExtraction() ;
    // Reinitialiser : Box Contours
    void ReinitialiserContour() ;
    // Reinitialiser : Box Debruitage
    void ReinitialiserDebruitage() ;
    // Reinitialiser : Box Seuillage et segmentation
    void ReinitialiserSeuillageSegmentation() ;
    // Reinitialiser : Box Filtres
    void ReinitialiserFiltre() ;



    void on_pushButtonRetourMenuConsultationImage_clicked();

private:
    Ui::AppMainWindow *ui;
    Bibliotheque _objBiblio;                            // Objet de classe Bibliothèque
    bool _droitAcces;
    int _numImageSelected;
    string _newImageFileName;
    Bibliotheque _objSousListeBiblio ;
    int _indiceImageSelectionnee ;   // Indice de l'image choisi dans la bibliotheque
    Mat _imageOriginale ;            // Image originale
    Mat _histoImageOriginale ;       // Histogramme de l'image originale
    Mat _imageResultat ;             // Image resultante
    Mat _histoImageResultat ;        // Histogramme de l'image resultante
    vector<int> _seuilBas ;          // Seuils bas
    vector<int> _seuilHaut;          // Seuils hauts

    void updateTableWidgetBiblio();                     // mise à jour du tableau des descripteurs après chargement de la bibliothèque
    void updateTableWidgetSousListeBiblio(Json::Value);            // mise à jour du tableau de la sous liste de la bibliothèque

};

#endif // APPMAINWINDOW_H
