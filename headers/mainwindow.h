#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Projet
#include "headers/image.h"
#include "headers/bibliotheque.h"
// QT
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QPixmap>          // Pour afficher les images
#include <QMessageBox>      // Pour afficher les messages d'erreur
#include <QString>          // Pour travailler avec les chaines de caracteres
#include <QListWidgetItem>  // Pour travailler avec les elements dans une liste
#include <QDebug>           // Pour afficher les messages de debug
#include <QtGui>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage imdisplay;
    QTimer* Timer;

private slots:

    void on_pushButtonIdentif_2_clicked();
    void on_pushButton_page_id_exit_clicked();

    // Page Image non modifiable
    // Liste des images
    void on_listWidget_listeImage_nonModifiable_itemClicked(QListWidgetItem* item) ;
    // Agrandissement de l'image (non modifiable)
    void on_horizontalSlider_agrandissementNonModifiable_valueChanged(int value) ;

    // Page Image modifiable
    // Liste des images
    void on_listWidget_listeImage_itemClicked(QListWidgetItem *item);
    // Champ d'affichage et de modification : Acces (Permisssion)
    void on_listWidget_descripteurImageAcces_itemDoubleClicked(QListWidgetItem* item) ;
    // Champ d'affichage et de modification : Cout
    void on_listWidget_descripteurImageCout_itemDoubleClicked(QListWidgetItem* item) ;
    // Champ d'affichage et de modification : Date d'ajout
    void on_listWidget_descripteurImageDateAjout_itemDoubleClicked(QListWidgetItem* item) ;
    // Champ d'affichage et de modification : Date de creation
    void on_listWidget_descripteurImageDateCreation_itemDoubleClicked(QListWidgetItem* item) ;
    // Champ d'affichage et de modification : Numero
    void on_listWidget_descripteurImageNumero_itemDoubleClicked(QListWidgetItem* item) ;
    // Champ d'affichage et de modification : Source
    void on_listWidget_descripteurImageSource_itemDoubleClicked(QListWidgetItem* item) ;
    // Champ d'affichage et de modification : Titre
    void on_listWidget_descripteurImageTitre_itemDoubleClicked(QListWidgetItem* item) ;
    // Bouton de sauvegarder les modifications
    void on_pushButton_modifier_clicked() ;
    // Agrandissement de l'image
    void on_horizontalSlider_agrandissement_valueChanged(int value) ;
    // Passer a la page des traitements de l'image choisie
    void on_pushButton_traitementImage_clicked() ;

    // Page Traitement
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

    // -------------Correction-------------

    // Initialiser les corrections
    void on_groupBox_correction_clicked() ;
    // Initialiser la modification de la nettete
    void on_radioButton_nettete_clicked() ;
    // Initialiser la modification de l'intensite de lumiere
    void on_radioButton_luminosite_clicked() ;
    // Initialiser la modification du constraste
    void on_radioButton_contraste_clicked() ;
    // Initialiser la modification du bruitage de l'image
    void on_radioButton_bruitage_clicked() ;
    // Modifier la luminosite de l'image
    void on_horizontalSlider_luminosite_valueChanged(int value) ;
    // Modifier le constraste de l'image
    void on_horizontalSlider_contraste_valueChanged(int value) ;
    // Modifier la nettete de l'image
    void on_horizontalSlider_nettete_valueChanged(int value) ;
    // Bruiter l'image
    void on_horizontalSlider_Bruitage_valueChanged(int value) ;

    // -------------Filtres de couleur-------------

    // Initialiser les filtres de couleur
    void on_groupBox_filtres_clicked() ;
    // Image originale
    void on_radioButton_originale_clicked() ;
    // Image monochrome
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

    // Extraction des canaux de couleur
    void on_groupBox_extractionRVB_clicked();
    // Extraction canal rouge
    void on_radioButton_extractionR_clicked() ;
    // Extraction canal vert
    void on_radioButton_extractionV_clicked() ;
    // Extraction canal bleu
    void on_radioButton_extractionB_clicked() ;

    // -------------Seuillage & Segmentation-------------

    // Initialiser le seuillage et la segmentation
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

    // Initialiser les fonctions liees aux contours
    void on_groupBox_contours_clicked() ;
    // Contours par filtres gradients
    void on_radioButton_contoursGradient_clicked() ;
    // Contours par filtre laplacien
    void on_radioButton_contoursLaplacien_clicked() ;

    //-------------Resolution-------------

    // Quantification
    void on_horizontalSlider_quantification_valueChanged(int value) ;

    //-------------Autres-------------

    // Generer les icones
    void GenererIcone() ;

    // Afficher l'image resultante apres un traitement avec inversement des canaux de couleur
    void AffichageResultat(const Mat image, const int choix) ;



    void on_groupBox_details_clicked() ;

    void on_groupBox_resolutionQuantification_clicked();

    void on_radioButton_resolution_clicked();

    void on_radioButton_quantification_clicked() ;

    void on_groupBox_debruitage_clicked() ;

    void on_groupBox_couleur_clicked() ;

    void on_horizontalSlider_temperature_valueChanged(int value) ;

    void on_radioButton_temperature_clicked() ;


    void on_radioButton_moyenneur_clicked() ;

    void on_radioButton_gaussien_clicked() ;

    void on_radioButton_median_clicked() ;

    void on_horizontalSlider_ombre_valueChanged(int value) ;

    void on_radioButton_ombre_clicked() ;

    void on_horizontalSlider_brillance_valueChanged(int value) ;

    void on_radioButton_brillance_clicked() ;

    void on_horizontalSlider_saturation_valueChanged(int value) ;

    void on_radioButton_saturation_clicked() ;

    void on_horizontalSlider_teinte_valueChanged(int value) ;

    void on_radioButton_teinte_clicked() ;

    void on_horizontalSlider_vividite_valueChanged(int value) ;

    void on_radioButton_vividite_clicked() ;

    void on_horizontalSlider_resolution_valueChanged(int value) ;

    void on_radioButton_bipolaire_clicked() ;

    void on_radioButton_PPP_clicked() ;

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

    void on_radioButton_kuwahara_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
