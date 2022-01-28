/**
 * @file mainwindow.h
 * @brief Header de la classe MainWindow de QT
 * @version 0.1
 * @date 2022-01-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include "headers/ImageToolBox.h"
#include "headers/bibliotheque.h"

using namespace std;
using namespace ImageToolBox;

namespace Ui {
class MainWindow;
}
/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    /**
     * @brief on_pushButtonIdentifier_clicked
     */
    void on_pushButtonIdentifier_clicked();             // button identification
    /**
     * @brief on_pushButtonQuitter_clicked
     */
    void on_pushButtonQuitter_clicked();                // Button Quitter l'application
    /**
     * @brief on_pushButtonChargerBiblio_clicked
     */
    void on_pushButtonChargerBiblio_clicked();          // Button charger une bibliothèque
    /**
     * @brief on_pushButtonRetourIdentification_clicked
     */
    void on_pushButtonRetourIdentification_clicked();   // button retour au menu identification
    /**
     * @brief on_tableBiblioRowClicked
     */
    void on_tableBiblioRowClicked(int , int);
    /**
     * @brief on_pushButtonSauvegarder_clicked
     */
    void on_pushButtonSauvegarder_clicked();
    /**
     * @brief on_pushButtonSupprimerImage_clicked
     */
    void on_pushButtonSupprimerImage_clicked();
    /**
     * @brief on_pushButtonRetourMenuPrincipal_clicked
     */
    void on_pushButtonRetourMenuPrincipal_clicked();
    /**
     * @brief on_lineEditMdp_returnPressed
     */
    void on_lineEditMdp_returnPressed();
    /**
     * @brief on_comboBoxTrierIndexChanged
     */
    void on_comboBoxTrierIndexChanged(int);
    /**
     * @brief on_comboBoxCritereCoutIndexChanged
     */
    void on_comboBoxCritereCoutIndexChanged(int);
    /**
     * @brief on_comboBoxCritereDateAjoutIndexChanged
     */
    void on_comboBoxCritereDateAjoutIndexChanged(int);
    /**
     * @brief on_pushButtonAjouterImage_clicked
     */
    void on_pushButtonAjouterImage_clicked();
    /**
     * @brief on_pushButtonAjoutImageAnnuler_clicked
     */
    void on_pushButtonAjoutImageAnnuler_clicked();
    /**
     * @brief on_pushButtonAjoutImageAjouter_clicked
     */
    void on_pushButtonAjoutImageAjouter_clicked();
    /**
     * @brief on_pushButtonCreerBiblio_clicked
     */
    void on_pushButtonCreerBiblio_clicked();
    /**
     * @brief on_pushButtonSauvegarderSousListe_clicked
     */
    void on_pushButtonSauvegarderSousListe_clicked();
    /**
     * @brief on_pushButtonOuvrirImage_clicked
     */
    void on_pushButtonOuvrirImage_clicked();
    /**
     * @brief on_pushButtonRetourMenuModificationImage_clicked
     */
    void on_pushButtonRetourMenuModificationImage_clicked();
    /**
     * @brief on_doubleSpinBoxMin_valueChanged
     */
    void on_doubleSpinBoxMin_valueChanged(double);
    /**
     * @brief on_doubleSpinBoxMax_valueChanged
     */
    void on_doubleSpinBoxMax_valueChanged(double);

    // Page Consultation Image --------------------------------
    // Agrandissement de l'image
    /**
     * @brief on_horizontalSlider_agrandissementNonModifiable_valueChanged
     */
    void on_horizontalSlider_agrandissementNonModifiable_valueChanged(int) ;
    // Page Image modifiable--------------------------------
    // Bouton de sauvegarder les modifications
    /**
     * @brief on_pushButton_modifier_clicked
     */
    void on_pushButton_modifier_clicked() ;
    // Agrandissement de l'image
    /**
     * @brief on_horizontalSlider_agrandissement_valueChanged
     */
    void on_horizontalSlider_agrandissement_valueChanged(int) ;
    // Passer a la page des traitements de l'image choisie
    /**
     * @brief on_pushButton_traitementImage_clicked
     */
    void on_pushButton_traitementImage_clicked() ;

    // Page Traitement--------------------------------
    // -------------Standars-------------

    // Retour a la page pour choisir l'image a traiter
    /**
     * @brief on_pushButton_retour_clicked
     */
    void on_pushButton_retour_clicked() ;
    // Agrandissement de l'image originale
    /**
     * @brief on_horizontalSlider_imageOriginale_valueChanged
     */
    void on_horizontalSlider_imageOriginale_valueChanged(int) ;
    // Agrandissement de l'image traitee
    /**
     * @brief on_horizontalSlider_imageTraitee_valueChanged
     */
    void on_horizontalSlider_imageTraitee_valueChanged(int) ;
    // Reinitialiser l'image originale
    /**
     * @brief on_pushButton_traitementReinitialiser_clicked
     */
    void on_pushButton_traitementReinitialiser_clicked() ;
    // Sauvegarder temporellement l'image de resultat
    /**
     * @brief on_pushButton_traitementAppliquer_clicked
     */
    void on_pushButton_traitementAppliquer_clicked() ;

    // -------------Luminosite-------------

    // Initialiser
    /**
     * @brief on_groupBox_correction_clicked
     */
    void on_groupBox_correction_clicked() ;
    // Bouton : Intensite lumineuse
    /**
     * @brief on_radioButton_luminosite_clicked
     */
    void on_radioButton_luminosite_clicked() ;
    // Intensite lumineuse
    /**
     * @brief on_horizontalSlider_luminosite_valueChanged
     */
    void on_horizontalSlider_luminosite_valueChanged(int) ;
    // Bouton : Contraste
    /**
     * @brief on_radioButton_contraste_clicked
     */
    void on_radioButton_contraste_clicked() ;
    // Contraste
    /**
     * @brief on_horizontalSlider_contraste_valueChanged
     */
    void on_horizontalSlider_contraste_valueChanged(int) ;
    // Bouton : Ombre
    /**
     * @brief on_radioButton_ombre_clicked
     */
    void on_radioButton_ombre_clicked() ;
    // Ombre
    /**
     * @brief on_horizontalSlider_ombre_valueChanged
     */
    void on_horizontalSlider_ombre_valueChanged(int) ;
    // Bouton : Haute lumiere
    /**
     * @brief on_radioButton_brillance_clicked
     */
    void on_radioButton_brillance_clicked() ;
    // Haute lumiere
    /**
     * @brief on_horizontalSlider_brillance_valueChanged
     */
    void on_horizontalSlider_brillance_valueChanged(int) ;

    // -------------Details-------------

    // Initialiser
    /**
     * @brief on_groupBox_details_clicked
     */
    void on_groupBox_details_clicked() ;
    // Bouton : Nettete
    /**
     * @brief on_radioButton_nettete_clicked
     */
    void on_radioButton_nettete_clicked() ;
    // Nettete
    /**
     * @brief on_horizontalSlider_nettete_valueChanged
     */
    void on_horizontalSlider_nettete_valueChanged(int) ;
    // Bouton : Bruitage
    /**
     * @brief on_radioButton_bruitage_clicked
     */
    void on_radioButton_bruitage_clicked() ;
    // Bruitage
    /**
     * @brief on_horizontalSlider_Bruitage_valueChanged
     */
    void on_horizontalSlider_Bruitage_valueChanged(int) ;

    // -------------Filtres de couleur-------------

    // Initialiser
    /**
     * @brief on_groupBox_filtres_clicked
     */
    void on_groupBox_filtres_clicked() ;
    // Image originale
    /**
     * @brief on_radioButton_originale_clicked
     */
    void on_radioButton_originale_clicked() ;
    // Image en niveau de gris
    /**
     * @brief on_radioButton_niveauGris_clicked
     */
    void on_radioButton_niveauGris_clicked() ;
    // Image inversee
    /**
     * @brief on_radioButton_inversement_clicked
     */
    void on_radioButton_inversement_clicked() ;
    // Image rouge
    /**
     * @brief on_radioButton_rouge_clicked
     */
    void on_radioButton_rouge_clicked() ;
    // Image verte
    /**
     * @brief on_radioButton_vert_clicked
     */
    void on_radioButton_vert_clicked() ;
    // Image bleue
    /**
     * @brief on_radioButton_bleu_clicked
     */
    void on_radioButton_bleu_clicked() ;
    // Image jaune
    /**
     * @brief on_radioButton_jaune_clicked
     */
    void on_radioButton_jaune_clicked() ;
    // Image cyane
    /**
     * @brief on_radioButton_cyan_clicked
     */
    void on_radioButton_cyan_clicked() ;
    // Image sepia
    /**
     * @brief on_radioButton_sepia_clicked
     */
    void on_radioButton_sepia_clicked() ;
    // Image magenta
    /**

     * @brief on_radioButton_magenta_clicked
     */
    void on_radioButton_magenta_clicked() ;
    // Image RGB
    /**
     * @brief on_radioButton_rgb_clicked
     */
    void on_radioButton_rgb_clicked() ;

    // -------------Extraction du canal de couleur-------------

    // Initialiser
    /**
    * @brief on_groupBox_extractionRVB_clicked
    */
   void on_groupBox_extractionRVB_clicked();
    // Extraction canal rouge
   /**
     * @brief on_radioButton_extractionR_clicked
     */
    void on_radioButton_extractionR_clicked() ;
    // Extraction canal vert
    /**
     * @brief on_radioButton_extractionV_clicked
     */
    void on_radioButton_extractionV_clicked() ;
    // Extraction canal bleu
    /**
     * @brief on_radioButton_extractionB_clicked
     */
    void on_radioButton_extractionB_clicked() ;

    // -------------Seuillage & Segmentation-------------

    // Initialiser
    /**
     * @brief on_groupBox_seuillageSegmentation_clicked
     */
    void on_groupBox_seuillageSegmentation_clicked();
    // Seuillage
    /**
     * @brief on_radioButton_seuillage_clicked
     */
    void on_radioButton_seuillage_clicked() ;
    // Segmentation
    /**
     * @brief on_radioButton_segmentation_clicked
     */
    void on_radioButton_segmentation_clicked() ;
    // Seuils simples
    /**
     * @brief on_radioButton_seuillageSimple_clicked
     */
    void on_radioButton_seuillageSimple_clicked() ;
    // Seuils par hysteresis
    /**
     * @brief on_radioButton_seuillageHysteresis_clicked
     */
    void on_radioButton_seuillageHysteresis_clicked() ;
    // Seuil bas rouge
    /**
     * @brief on_verticalSlider_seuilBasR_2_valueChanged
     */
    void on_verticalSlider_seuilBasR_2_valueChanged(int) ;
    // Seuil bas vert
    /**
     * @brief on_verticalSlider_seuilBasV_2_valueChanged
     */
    void on_verticalSlider_seuilBasV_2_valueChanged(int) ;
    // Seuil bas bleu
    /**
     * @brief on_verticalSlider_seuilBasB_2_valueChanged
     */
    void on_verticalSlider_seuilBasB_2_valueChanged(int) ;
    // Seuil haut rouge
    /**
     * @brief on_verticalSlider_seuilHautR_2_valueChanged
     */
    void on_verticalSlider_seuilHautR_2_valueChanged(int) ;
    // Seuil haut vert
    /**
     * @brief on_verticalSlider_seuilHautV_2_valueChanged
     */
    void on_verticalSlider_seuilHautV_2_valueChanged(int) ;
    // Seuil haut bleu
    /**
     * @brief on_verticalSlider_seuilHautB_2_valueChanged
     */
    void on_verticalSlider_seuilHautB_2_valueChanged(int) ;

    // Reinitialiser seuil bas rouge
    /**
     * @brief on_pushButton_seuilBasR_clicked
     */
    void on_pushButton_seuilBasR_clicked() ;
    // Reinitialiser seuil bas vert
    /**
     * @brief on_pushButton_seuilBasV_clicked
     */
    void on_pushButton_seuilBasV_clicked() ;
    // Reinitialiser seuil bas bleu
    /**
     * @brief on_pushButton_seuilBasB_clicked
     */
    void on_pushButton_seuilBasB_clicked() ;
    // Reinitialiser seuil haut rouge
    /**
     * @brief on_pushButton_seuilHautR_clicked
     */
    void on_pushButton_seuilHautR_clicked() ;
    // Reinitialiser seuil haut vert
    /**
     * @brief on_pushButton_seuilHautV_clicked
     */
    void on_pushButton_seuilHautV_clicked() ;
    // Reinitialiser seuil haut bleu
    /**
     * @brief on_pushButton_seuilHautB_clicked
     */
    void on_pushButton_seuilHautB_clicked() ;

    // -------------Contours-------------

    // Initialiser
    /**
     * @brief on_groupBox_contours_clicked
     */
    void on_groupBox_contours_clicked() ;
    // Contours par filtres gradients
    /**
     * @brief on_radioButton_contoursGradient_clicked
     */
    void on_radioButton_contoursGradient_clicked() ;
    // Contours par filtre laplacien
    /**
     * @brief on_radioButton_contoursLaplacien_clicked
     */
    void on_radioButton_contoursLaplacien_clicked() ;

    //-------------Resolution-------------

    // Initialiser
    /**
     * @brief on_groupBox_resolutionQuantification_clicked
     */
    void on_groupBox_resolutionQuantification_clicked();
    // Bouton : Resolution
    /**
     * @brief on_radioButton_resolution_clicked
     */
    void on_radioButton_resolution_clicked();
    // Bouton : Interpolation par pixel le plus proche
    /**
     * @brief on_radioButton_PPP_clicked
     */
    void on_radioButton_PPP_clicked() ;
    // Bouton : Interpolation bilineaire
    /**
     * @brief on_radioButton_bipolaire_clicked
     */
    void on_radioButton_bipolaire_clicked() ;
    // Resolution
    /**
     * @brief on_horizontalSlider_resolution_valueChanged
     * @param value
     */
    void on_horizontalSlider_resolution_valueChanged(int value) ;
    // Bouton : Quantification
    /**
     * @brief on_radioButton_quantification_clicked
     */
    void on_radioButton_quantification_clicked() ;
    // Quantification
    /**
     * @brief on_horizontalSlider_quantification_valueChanged
     * @param value
     */
    void on_horizontalSlider_quantification_valueChanged(int value) ;

    // -------------Debruitage-------------

    // Initialiser
    /**
     * @brief on_groupBox_debruitage_clicked
     */
    void on_groupBox_debruitage_clicked() ;
    // Filtre moyeneur
    /**
     * @brief on_radioButton_moyenneur_clicked
     */
    void on_radioButton_moyenneur_clicked() ;
    // Filtre gaussien
    /**
     * @brief on_radioButton_gaussien_clicked
     */
    void on_radioButton_gaussien_clicked() ;
    // Filtre median
    /**
     * @brief on_radioButton_median_clicked
     */
    void on_radioButton_median_clicked() ;
    // Filtre de Kuwahara-Nagao
    /**
     * @brief on_radioButton_kuwahara_clicked
     */
    void on_radioButton_kuwahara_clicked();

    // -------------Couleur-------------

    // Initialiser
    /**
     * @brief on_groupBox_couleur_clicked
     */
    void on_groupBox_couleur_clicked() ;
    // Bouton : Temperature
    /**
     * @brief on_radioButton_temperature_clicked
     */
    void on_radioButton_temperature_clicked() ;
    // Temperature
    /**
     * @brief on_horizontalSlider_temperature_valueChanged
     * @param value
     */
    void on_horizontalSlider_temperature_valueChanged(int value) ;
    // Bouton : Vividite
    /**
     * @brief on_radioButton_vividite_clicked
     */
    void on_radioButton_vividite_clicked() ;
    // Vividite
    /**
     * @brief on_horizontalSlider_vividite_valueChanged
     * @param value
     */
    void on_horizontalSlider_vividite_valueChanged(int value) ;
    // Bouton : Teinte
    /**
     * @brief on_radioButton_teinte_clicked
     */
    void on_radioButton_teinte_clicked() ;
    // Teinte
    /**
     * @brief on_horizontalSlider_teinte_valueChanged
     * @param value
     */
    void on_horizontalSlider_teinte_valueChanged(int value) ;
    // Bouton : Saturation
    /**
     * @brief on_radioButton_saturation_clicked
     */
    void on_radioButton_saturation_clicked() ;
    // Saturation
    /**
     * @brief on_horizontalSlider_saturation_valueChanged
     * @param value
     */
    void on_horizontalSlider_saturation_valueChanged(int value) ;


    //-------------Autres-------------
    // Generer les icones
    /**
     * @brief GenererIcone
     */
    void GenererIcone() ;
    // Afficher l'image resultante apres un traitement avec inversement des canaux de couleur
    /**
     * @brief AffichageResultat
     * @param image
     * @param choix
     */
    void AffichageResultat(const Mat image, const int choix) ;
    // Messages d'aide
    /**
     * @brief AfficherMessageAide
     */
    void AfficherMessageAide() ;
    // Messages d'aide : Luminosite
    /**
     * @brief AfficherMessageAideLuminosite
     */
    void AfficherMessageAideLuminosite() ;
    // Messages d'aide : Couleur
    /**
     * @brief AfficherMessageAideCouleur
     */
    void AfficherMessageAideCouleur() ;
    // Messages d'aide : Details
    /**
     * @brief AfficherMessageAideDetail
     */
    void AfficherMessageAideDetail() ;

    // Messages d'aide : Resolution
    /**
     * @brief AfficherMessageAideResolution
     */
    void AfficherMessageAideResolution() ;
    // Messages d'aide : Extraction
    /**
     * @brief AfficherMessageAideExtraction
     */
    void AfficherMessageAideExtraction() ;

    // Messages d'aide : Contours
    /**
     * @brief AfficherMessageAideContour
     */
    void AfficherMessageAideContour() ;


    // Messages d'aide : Debruitage
    /**
     * @brief AfficherMessageAideDebruitage
     */
    void AfficherMessageAideDebruitage() ;

    // Messages d'aide : Seuillage et segmentation
    /**
     * @brief AfficherMessageAideSeuillageSegmentation
     */
    void AfficherMessageAideSeuillageSegmentation() ;

    // Messages d'aide : Filtres
    /**
     * @brief AfficherMessageAideFiltre
     */
    void AfficherMessageAideFiltre() ;





    // Reinitialisation generale
    /**
     * @brief Reinitialiser
     */
    void Reinitialiser() ;

    // Reinitialiser : Box Luminosite
    /**
     * @brief ReinitialiserLuminosite
     */
    void ReinitialiserLuminosite() ;
    // Reinitialiser : Box Couleur
    /**
     * @brief ReinitialiserCouleur
     */
    void ReinitialiserCouleur() ;

    // Reinitialiser : Box Resolution
    /**
     * @brief ReinitialiserResolution
     */
    void ReinitialiserResolution() ;

    // Reinitialiser : Box Details
    /**
     * @brief ReinitialiserDetail
     */
    void ReinitialiserDetail() ;

    // Reinitialiser : Box Extraction

    /**
     * @brief ReinitialiserExtraction
     */
    void ReinitialiserExtraction() ;

    // Reinitialiser : Box Contours
    /**
     * @brief ReinitialiserContour
     */
    void ReinitialiserContour() ;

    // Reinitialiser : Box Debruitage
    /**
     * @brief ReinitialiserDebruitage
     */
    void ReinitialiserDebruitage() ;

    // Reinitialiser : Box Seuillage et segmentation
    /**
     * @brief ReinitialiserSeuillageSegmentation
     */
    void ReinitialiserSeuillageSegmentation() ;

    // Reinitialiser : Box Filtres
    /**
     * @brief ReinitialiserFiltre
     */
    void ReinitialiserFiltre() ;

    /**
     * @brief on_radioButton_fourier_clicked
     */
    void on_radioButton_fourier_clicked() ;


    /**
     * @brief on_radioButtonEgalisation_clicked
     */
    void on_radioButtonEgalisation_clicked() ;
    /**
     * @brief on_radioButtonBruitPoivreSel_clicked
     */
    void on_radioButtonBruitPoivreSel_clicked() ;




    /**
     * @brief on_groupBox_autre_clicked
     */
    void on_groupBox_autre_clicked();
    // Reinitialiser : Box Autres
    /**
     * @brief ReinitialiserAutre
     */
    void ReinitialiserAutre() ;

    /**
     * @brief on_radioButtonKmeans_clicked
     */
    void on_radioButtonKmeans_clicked();


    /**
     * @brief on_radioButtonTransformeeHough_clicked
     */
    void on_radioButtonTransformeeHough_clicked();






    /**
     * @brief on_pushButtonRetourMenuConsultationImage_clicked
     */
    void on_pushButtonRetourMenuConsultationImage_clicked();


    /**
     * @brief on_pushButton_traitementSauvegarder_clicked
     */
    void on_pushButton_traitementSauvegarder_clicked();

    /**
     * @brief on_pushButtonAfficherImageTraitee_clicked
     */
    void on_pushButtonAfficherImageTraitee_clicked();

    void on_pushButton_clicked();

private:

    Ui::MainWindow *ui;
    /**
     * @brief _objBiblio
     */
    Bibliotheque _objBiblio;          // Objet de classe Bibliothèque
    /**
     * @brief _droitAcces
     */
    bool _droitAcces;                 // droit d'acces de l'utilisateur, true : utilisateur niveau 2 , false : utilisateur niveau 1
    /**
     * @brief _numImageSelected
     */
    int _numImageSelected;            // numéro de l'image selectionnee par l'utilisateur
    /**
     * @brief _ImageAjouteeFileName
     */
    string _ImageAjouteeFileName;     //
    /**
     * @brief _objSousListeBiblio
     */
    Bibliotheque _objSousListeBiblio ;
    /**
     * @brief _indiceImageSelectionnee
     */
    int _indiceImageSelectionnee ;   // Indice de l'image choisi dans la bibliotheque
    /**
     * @brief _imageOriginale
     */
    Mat _imageOriginale ;            // Image originale
    /**
    * @brief _histoImageOriginale
    */
   Mat _histoImageOriginale ;       // Histogramme de l'image originale

   /**
     * @brief _imageResultat
     */
    Mat _imageResultat ;             // Image resultante
    /**
     * @brief _histoImageResultat
     */
    Mat _histoImageResultat ;        // Histogramme de l'image resultante
    /**
     * @brief _seuilBas
     */
    vector<int> _seuilBas ;          // Seuils bas
    /**
     * @brief _seuilHaut
     */
    vector<int> _seuilHaut;          // Seuils hauts


    /**
     * @brief updateTableWidgetBiblio
     */
    void updateTableWidgetBiblio();                     // mise à jour du tableau des descripteurs après chargement de la bibliothèque
    /**
     * @brief updateTableWidgetSousListeBiblio
     */
    void updateTableWidgetSousListeBiblio(Json::Value);            // mise à jour du tableau de la sous liste de la bibliothèque


};

