#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

using namespace cv;

// Variables globales
string nomBiblio = "test.json" ;                                                    // Nom de la bibliotheque
Bibliotheque bibliotheque(nomBiblio) ;                                              // Charger de la bibliotheque
Json::Value biblio = bibliotheque.getBilbiotheque() ;                               // Objet Json bibliotheque
int indice ;                                                                        // Indice de l'image choisi dans la bibliotheque
Image A(bibliotheque.getCheminJson(), biblio["images"][indice]["numero"].asInt()) ; // Objet Image


Mat imageOriginale ;            // Image originale
Mat histoImageOriginale ;       // Histogramme de l'image originale
Mat imageResultat ;             // Image resultante
Mat histoImageResultat ;        // Histogramme de l'image resultante

vector<int> seuilBas(3) ;       // Seuils bas
vector<int> seuilHaut(3) ;      // Seuils hauts
Mat imageTemp[10] ;             // Image temporelle

// Fenetre principale
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int c ;                                             // Indice

    // Page non modifiable-----------------------------
    // Creer la liste des images
    for(c = 0 ; c < biblio["nbImages"].asInt() ; c++){
        ui->listWidget_listeImage_nonModifiable->addItem(QString::fromStdString(biblio["images"][c]["titre"].asString()));
    }
    // Messages d'aide
    // Liste d'images
    ui->listWidget_listeImage_nonModifiable->setToolTip("Liste des images accessibles") ;
    // Fenetre d'affichage
    ui->graphicsView_contenuImageNonModifiable->setToolTip("Contenu de l'image choisie") ;
    // Agrandissement
    ui->label_ZoomNonModifiable->setToolTip("Agrandissement") ;
    ui->horizontalSlider_agrandissementNonModifiable->setToolTip("Tirer vers la droite pour agrandir l'image") ;
    // Descripteur de l'image
    ui->groupBox_descripteurImageNiv1->setToolTip("Informations de l'image choisie :\nAccès (Permission), coût, date d'ajout, date de création, numéro, source, titre") ;

    // Page modifiable-----------------------------
    // Creer la liste des images
    for(c = 0 ; c < biblio["nbImages"].asInt() ; c++){
        ui->listWidget_listeImage->addItem(QString::fromStdString(biblio["images"][c]["titre"].asString()));
    }
    // Messages d'aide
    ui->listWidget_listeImage->setToolTip("Liste des images accessibles") ;
    // Fenetre d'affichage
    ui->graphicsView_contenuImage->setToolTip("Contenu de l'image choisie") ;
    // Agrandissement
    ui->label_Zoom->setToolTip("Agrandissement") ;
    ui->horizontalSlider_agrandissement->setToolTip("Tirer vers la droite pour agrandir l'image") ;
    // Descripteur de l'image
    ui->groupBox_descripteurImage->setToolTip("Informations de l'image choisie :\nAccès (Permission), coût, date d'ajout, date de création, numéro, source, titre") ;
    ui->listWidget_descripteurImageAcces->setToolTip("Accès (Permission) :\nP : Publique, R : Restreint") ;
    ui->listWidget_descripteurImageCout->setToolTip("Coût (€)") ;
    ui->listWidget_descripteurImageDateAjout->setToolTip("Date d'ajout (dd/mm/yyyy)") ;
    ui->listWidget_descripteurImageDateCreation->setToolTip("Date de création (dd/mm/yyyy)") ;
    ui->listWidget_descripteurImageNumero->setToolTip("Numéro") ;
    ui->listWidget_descripteurImageSource->setToolTip("Source") ;
    ui->listWidget_descripteurImageTitre->setToolTip("Titre") ;
    // Passer au traitement
    ui->pushButton_traitementImage->setToolTip("Commencer le traitement de l'image choisie") ;
    // Sauvegarder les modifications
    ui->pushButton_modifier->setToolTip("Sauvegarder les modifications") ;

    // Page du traitement-----------------------------
    // Initialiser
    GenererIcone() ;
    // Messages d'aide
    AfficherMessageAide() ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --------------------------Page Choisir Image (utilisateur niveau 1)--------------------------

// Afficher le contenu et le descripteur de l'image choisie (non modifiable)
void MainWindow::on_listWidget_listeImage_nonModifiable_itemClicked(QListWidgetItem* item){
    // Declaration des variables
    QString chemin ;                                        // Chemin d'acces a l'image choisie
    QString descripteur ;                                   // Descripteur
    int indice ;                                            // Indice

    // Determiner l'indice de l'image
    indice = ui->listWidget_listeImage_nonModifiable->row(item) ;
    // Determiner le chemin d'acces a l'image
    chemin = QString::fromStdString(bibliotheque.getBilbiotheque()["images"][indice]["cheminAcces"].asString()) ;

    // Affichage de l'image choisie
    // Charger l'image avec son chemin d'acces
    QPixmap image(chemin) ;
    QGraphicsScene* scene = new QGraphicsScene() ;
    scene->addPixmap(image) ;
    ui->graphicsView_contenuImageNonModifiable->setScene(scene) ;
    ui->graphicsView_contenuImageNonModifiable->show() ;
    ui->graphicsView_contenuImageNonModifiable->fitInView(scene->sceneRect(), Qt::KeepAspectRatio) ;

    // Descripteur de l'image
    descripteur = QString::fromStdString("Acces : \t\t\t" + biblio["images"][indice]["acces"].asString() + "\n"
            + "Coût (€) : \t\t\t" + biblio["images"][indice]["cout"].asString() + "\n"
            + "Date d'ajout : \t\t" + biblio["images"][indice]["dateAjout"].asString() + "\n"
            + "Date de creation : \t" + biblio["images"][indice]["dateCreation"].asString() + "\n"
            + "Numéro : \t\t" + biblio["images"][indice]["numero"].asString() + "\n"
            + "Source : \t\t\t" + biblio["images"][indice]["source"].asString() + "\n"
            + "Titre : \t\t\t" + biblio["images"][indice]["titre"].asString() + "\n") ;
    // Affichage du descripteur de l'image
    ui->label_descripteurImage_nonModifiable->setText(descripteur);
}

// Agrandissement de l'image (non modifiable)
void MainWindow::on_horizontalSlider_agrandissementNonModifiable_valueChanged(int value){
    // Sevlaration des variables
    int hauteurImage = ui->graphicsView_contenuImageNonModifiable->scene()->height() ;      // Hauteur de l'image
    int largeurImage = ui->graphicsView_contenuImageNonModifiable->scene()->width() ;       // Largeur de l'image
    int hauteurFenetre = ui->graphicsView_contenuImageNonModifiable->height() ;             // Hauteur de la fenetre
    int largeurFenetre = ui->graphicsView_contenuImageNonModifiable->width() ;              // Largeur de la fenetre
    double facteur ;                                                                        // Facteur d'agrandissement

    // Calculer le facteur d'agrandissement
    if(hauteurImage > largeurImage){
        facteur = (double)hauteurFenetre/hauteurImage*value/2 ;
    }else{
        facteur = (double)largeurFenetre/largeurImage*value/2 ;
    }

    // Agrandissement
    if(value == 1){
        QGraphicsScene* scene = ui->graphicsView_contenuImageNonModifiable->scene() ;
        ui->graphicsView_contenuImageNonModifiable->fitInView(scene->sceneRect(), Qt::KeepAspectRatio) ;
    }else{
        ui->graphicsView_contenuImageNonModifiable->setTransform(QTransform::fromScale(facteur, facteur)) ;
    }
}

// --------------------------Page Choisir Image (utilisateur niveau 2)--------------------------

// Afficher le contenu et le descripteur de l'image choisie
void MainWindow::on_listWidget_listeImage_itemClicked(QListWidgetItem* item){
    // Declaration de variable
    string chemin ;             // Chemin d'acces a l'image choisie
    QString cheminQT ;          // Chemin d'acces a l'image choisie

    // Determiner l'indice de l'image
    indice = ui->listWidget_listeImage->row(item) ;

    // Extraction des informations du descripteur de l'image choisie
    // Acces (Permission)
    ui->listWidget_descripteurImageAcces->clear() ;
    ui->listWidget_descripteurImageAcces->addItem(QString::fromStdString(biblio["images"][indice]["acces"].asString())) ;
    // Cout
    ui->listWidget_descripteurImageCout->clear() ;
    ui->listWidget_descripteurImageCout->addItem(QString::fromStdString(biblio["images"][indice]["cout"].asString())) ;
    // Date d'ajout
    ui->listWidget_descripteurImageDateAjout->clear() ;
    ui->listWidget_descripteurImageDateAjout->addItem(QString::fromStdString(biblio["images"][indice]["dateAjout"].asString())) ;
    // Date de creation
    ui->listWidget_descripteurImageDateCreation->clear() ;
    ui->listWidget_descripteurImageDateCreation->addItem(QString::fromStdString(biblio["images"][indice]["dateCreation"].asString()));
    // Numero
    ui->listWidget_descripteurImageNumero->clear() ;
    ui->listWidget_descripteurImageNumero->addItem(QString::fromStdString(biblio["images"][indice]["numero"].asString()));
    // Source
    ui->listWidget_descripteurImageSource->clear() ;
    ui->listWidget_descripteurImageSource->addItem(QString::fromStdString(biblio["images"][indice]["source"].asString()));
    // Titre
    ui->listWidget_descripteurImageTitre->clear() ;
    ui->listWidget_descripteurImageTitre->addItem(QString::fromStdString(biblio["images"][indice]["titre"].asString()));

    // Affichage de l'image choisie
    // Determiner le chemin d'acces a l'image
    cheminQT = QString::fromStdString(biblio["images"][indice]["cheminAcces"].asString()) ;
    chemin = cheminQT.toStdString() ;

    // Charger l'image avec son chemin d'acces
    imageOriginale = imread(chemin) ;
    QPixmap imageQT(cheminQT) ;
    QGraphicsScene* sceneImageDescripteur = new QGraphicsScene() ;
    sceneImageDescripteur->addPixmap(imageQT) ;
    ui->graphicsView_contenuImage->setScene(sceneImageDescripteur) ;
    ui->graphicsView_contenuImage->show() ;
    ui->graphicsView_contenuImage->fitInView(sceneImageDescripteur->sceneRect(), Qt::KeepAspectRatio) ;
}

// Champ d'affichage et de modification : Acces (Permission)
void MainWindow::on_listWidget_descripteurImageAcces_itemDoubleClicked(QListWidgetItem* item){
    // Rendre l'element choisi devenir modififable
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable) ;
    // Modifier l'element
    ui->listWidget_descripteurImageAcces->editItem(item);
}

// Champ d'affichage et de modification : Date d'ajout
void MainWindow::on_listWidget_descripteurImageDateAjout_itemDoubleClicked(QListWidgetItem* item){
    // Rendre l'element choisi devenir modififable
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable) ;
    // Modifier l'element
    ui->listWidget_descripteurImageDateAjout->editItem(item);
}

// Champ d'affichage et de modification : Date de creation
void MainWindow::on_listWidget_descripteurImageDateCreation_itemDoubleClicked(QListWidgetItem* item){
    // Rendre l'element choisi devenir modififable
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable) ;
    // Modifier l'element
    ui->listWidget_descripteurImageDateCreation->editItem(item);
}

// Champ d'affichage et de modification : Cout
void MainWindow::on_listWidget_descripteurImageCout_itemDoubleClicked(QListWidgetItem* item){
    // Rendre l'element choisi devenir modififable
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable) ;
    // Modifier l'element
    ui->listWidget_descripteurImageCout->editItem(item);
}

// Champ d'affichage et de modification : Numero
void MainWindow::on_listWidget_descripteurImageNumero_itemDoubleClicked(QListWidgetItem* item){
    // Rendre l'element choisi devenir modififable
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable) ;
    // Modifier l'element
    ui->listWidget_descripteurImageNumero->editItem(item);
}

// Champ d'affichage et de modification : Source
void MainWindow::on_listWidget_descripteurImageSource_itemDoubleClicked(QListWidgetItem* item){
    // Rendre l'element choisi devenir modififable
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable) ;
    // Modifier l'element
    ui->listWidget_descripteurImageSource->editItem(item);
}

// Champ d'affichage et de modification : Titre
void MainWindow::on_listWidget_descripteurImageTitre_itemDoubleClicked(QListWidgetItem* item){
    // Rendre l'element choisi devenir modififable
    item->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable) ;
    // Modifier l'element
    ui->listWidget_descripteurImageTitre->editItem(item);
}

// Bouton de sauvegarder les modifications
void MainWindow::on_pushButton_modifier_clicked(){
    // Declaration des variables
    QString acces = ui->listWidget_descripteurImageAcces->item(0)->text() ;                 // Acces (Permission)
    QString coutSaisi = ui->listWidget_descripteurImageCout->item(0)->text() ;              // Cout saisi par l'utilisateur
    double coutVerifie ;                                                                    // Cout verifie
    QString dateAjout = ui->listWidget_descripteurImageDateAjout->item(0)->text() ;         // Date d'ajout (entiere)
    string jourAjout, moisAjout, anneeAjout ;                                               // Date d'ajout (jour, mois, annee)
    vector<int> erreurDateAjout ;                                                           // Vecteur des codes d'erreur (date d'ajout)
    QString dateCreation = ui->listWidget_descripteurImageDateCreation->item(0)->text() ;   // Date de creation (texte)
    string jourCreation, moisCreation, anneeCreation ;                                      // Date de creation (jour, mois, annee)
    vector<int> erreurDateCreation ;                                                        // Vecteur des codes d'erreur (date de creation)
    QString numeroSaisi = ui->listWidget_descripteurImageNumero->item(0)->text() ;          // Numero (texte)
    int numero ;                                                                            // Numero (numerique)
    QString source = ui->listWidget_descripteurImageSource->item(0)->text() ;               // Source
    QString titre = ui->listWidget_descripteurImageTitre->item(0)->text() ;                 // Titre

    int c ;                                                                                 // Indice
    QString messageErreur ;                                                                 // Message d'erreur

    // Initialisation
    messageErreur.clear() ;
    erreurDateAjout.clear() ;
    ExtraireDate(dateAjout.toStdString(), jourAjout, moisAjout, anneeAjout) ;
    ExtraireDate(dateCreation.toStdString(), jourCreation, moisCreation, anneeCreation) ;

    // Verification
    // Acces
    // Si l'acces est valide (P ou R)
    if((acces == "P") || (acces == "R")){
        biblio["images"][indice]["acces"] = acces.toStdString() ;
    }else{
        messageErreur += "L'acces doit etre 'P' (Publique) ou 'R' (Restreint)\n" ;
    }

    // Cout
    // Si le cout est valide (valeur reelle et non negative)
    if(VerifierNumero(coutSaisi.toStdString(), coutVerifie)){
         biblio["images"][indice]["cout"] = coutVerifie ;
    }else{
        messageErreur += "Le cout est invalide\n" ;
    }

    // Date d'ajout
    // Si la date est valide (format)
    erreurDateAjout = VerifierDate(dateAjout.toStdString(), jourAjout, moisAjout, anneeAjout) ;
    if((int)erreurDateAjout.size() == 0){
        // Si la valeur de la date est correcte
        if((stoi(anneeAjout + moisAjout + anneeAjout))- (stoi(anneeCreation + moisCreation + jourCreation)) > 0){
            biblio["images"][indice]["dateAjout"] = dateAjout.toStdString() ;
        }else{
            messageErreur += "La date d'ajout doit etre superieure ou egale a la date de creation\n" ;
        }
    }else{
        for(c = 0 ; c < (int)erreurDateAjout.size() ; c++){
            switch(erreurDateAjout[c]){
                case 0 :
                   messageErreur += "Le format de la date d'ajout est invalide\n" ;
                    break ;
                case 1 :
                    messageErreur += "L'annee de la date d'ajout dois etre entre 1800 et 2022\n" ;
                    break ;
                case 2 :
                    messageErreur += "Le mois de la date d'ajout doit etre entre 1 et 12\n" ;
                    break ;
                case 3 :
                    messageErreur += "Le jour de la date d'ajout doit etre entre 1 et 31\n" ;
                    break ;
                case 4 :
                    messageErreur += "Le jour de la date d'ajout doit etre < 29\n" ;
                    break ;
                case 5 :
                    messageErreur += "Le jour de la date d'ajout doit etre < 31" ;
                    break ;
                default :
                    break ;
            }
        }
    }

    // Date de creation
    // Si la date est valide (format)
    erreurDateCreation = VerifierDate(dateCreation.toStdString(), jourCreation, moisCreation, anneeCreation) ;
    if((int)erreurDateCreation.size() == 0){
        // Si la valeur de la date est correcte
        if((stoi(anneeAjout + moisAjout + anneeAjout))- (stoi(anneeCreation + moisCreation + jourCreation)) > 0){
            biblio["images"][indice]["dateCreation"] = dateCreation.toStdString() ;
        }else{
            messageErreur += "La date de creation doit etre inferieure ou egale a la date d'ajout\n" ;
        }
    }else{
        for(c = 0 ; c < (int)erreurDateCreation.size() ; c++){
            switch(erreurDateCreation[c]){
                case 0 :
                   messageErreur += "Le format de la date de creation est invalide\n" ;
                    break ;
                case 1 :
                    messageErreur += "L'annee de la date de creation dois etre entre 1800 et 2022\n" ;
                    break ;
                case 2 :
                    messageErreur += "Le mois de la date de creation doit etre entre 1 et 12\n" ;
                    break ;
                case 3 :
                    messageErreur += "Le jour de la date de creation doit etre entre 1 et 31\n" ;
                    break ;
                case 4 :
                    messageErreur += "Le jour de la date de creation doit etre < 29\n" ;
                    break ;
                case 5 :
                    messageErreur += "Le jour de la date de creation doit etre < 31\n" ;
                    break ;
                default :
                    break ;
            }
        }
    }

    // Numero
    // Si le numero est valide (format)
    if(VerifierNumero(numeroSaisi.toStdString(), numero)){
        // Si le numero est valide (valeur non negative)
        if(numero >= 0){
            biblio["images"][indice]["numero"] = numero ;
        }else{
            messageErreur += "Le numero de l'image doit etre non nul\n" ;
        }
    }else{
        messageErreur += "Le numero doit etre un chiffre\n" ;
    }

    // Source
    biblio["images"][indice]["source"] = source.toStdString() ;

    // Titre
    biblio["images"][indice]["titre"] = titre.toStdString() ;

    // Message d'erreur
    if((int)messageErreur.size() !=0){
        QMessageBox::information(0, "Erreur", messageErreur) ;
    }
}

// Agrandissement de l'image
void MainWindow::on_horizontalSlider_agrandissement_valueChanged(int value){
    // Sevlaration des variables
    int hauteurImage = ui->graphicsView_contenuImage->scene()->height() ;   // Hauteur de l'image
    int largeurImage = ui->graphicsView_contenuImage->scene()->width() ;    // Largeur de l'image
    int hauteurFenetre = ui->graphicsView_contenuImage->height() ;          // Hauteur de la fenetre
    int largeurFenetre = ui->graphicsView_contenuImage->width() ;           // Largeur de la fenetre
    double facteur ;                                                        // Facteur d'agrandissement

    // Calculer le facteur d'agrandissement
    if(hauteurImage > largeurImage){
        facteur = (double)hauteurFenetre/hauteurImage*value/2 ;
    }else{
        facteur = (double)largeurFenetre/largeurImage*value/2 ;
    }

    // Agrandissement
    if(value == 1){
        QGraphicsScene* scene = ui->graphicsView_contenuImage->scene() ;
        ui->graphicsView_contenuImage->fitInView(scene->sceneRect(), Qt::KeepAspectRatio) ;
    }else{
        ui->graphicsView_contenuImage->setTransform(QTransform::fromScale(facteur, facteur)) ;
    }
}

// Passer a la page des traitements de l'image choisie
void MainWindow::on_pushButton_traitementImage_clicked(){
    // Declaration de variable
    string nbLigne, nbColonne ;     // Nombre de lignes et de colonnes
    string resolution ;             // Resolution
    QString cheminQT = QString::fromStdString(biblio["images"][indice]["cheminAcces"].asString()) ;

    // Preparation de l'espace de travail
    Reinitialiser() ;
    // Affichage de l'image choisie dans la page du traitement
    QPixmap imageOriginaleQT(cheminQT) ;
    QGraphicsScene* sceneImageOriginale = new QGraphicsScene() ;
    sceneImageOriginale->addPixmap(imageOriginaleQT) ;
    ui->graphicsView_imageOriginale->setScene(sceneImageOriginale) ;
    ui->graphicsView_imageOriginale->show() ;
    ui->graphicsView_imageOriginale->fitInView(sceneImageOriginale->sceneRect(), Qt::KeepAspectRatio);

    // Histogramme de l'image choisie
    histoImageOriginale = Normalisation(plot_histogram(imageOriginale), 255) ;
    QImage histoImageOriginaleQT = QImage((uchar*) histoImageOriginale.data, histoImageOriginale.cols, histoImageOriginale.rows, histoImageOriginale.step, QImage::Format_RGB888) ;
    QPixmap histoImageOrginalePixmap = QPixmap::fromImage(histoImageOriginaleQT) ;
    int hauteur = ui->label_histogrammeImageOriginale->height() ;       // Hauteur de la fenetre d'affichage
    int largeur = ui->label_histogrammeImageOriginale->width() ;        // Largeur de la fenetre d'affichage
    ui->label_histogrammeImageOriginale->setPixmap(histoImageOrginalePixmap.scaled(largeur, hauteur, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->label_histogrammeImageOriginale->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;

    // Initialiser l'image resultante et son histogramme
    ui->graphicsView_imageTraitee->setScene(sceneImageOriginale) ;
    ui->graphicsView_imageTraitee->show() ;
    ui->graphicsView_imageTraitee->fitInView(sceneImageOriginale->sceneRect(), Qt::KeepAspectRatio) ;

    // Histogramme - Initialisation
    ui->label_histogrammeImageTraitee->setPixmap(histoImageOrginalePixmap.scaled(largeur, hauteur, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->label_histogrammeImageTraitee->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;

    // Passer a la page du traitement
    ui->stackedWidget->setCurrentIndex(3) ;

    // Afficher la resolution
    nbLigne = to_string((int)imageOriginale.size().height) ;
    nbColonne = to_string((int)imageOriginale.size().width) ;
    resolution = "Resolution : [" + nbLigne + " x " + nbColonne + "]" ;
    // Image originale
    ui->label_resolutionOriginale->setText(QString::fromStdString(resolution)) ;
    // Image traitee
    ui->label_resolutionTraitee->setText(QString::fromStdString(resolution)) ;
}

// --------------------------Page Traitement--------------------------

// -------------Standars-------------

// Retour a la page pour choisir l'image a traiter
void MainWindow::on_pushButton_retour_clicked(){
    // Desactiver les foncitonnalites
    // Luminosite
    ui->groupBox_correction->setChecked(false) ;
    ui->horizontalSlider_luminosite->setValue(0) ;      // Luminosite
    ui->horizontalSlider_contraste->setValue(0) ;       // Contraste
    ui->horizontalSlider_brillance->setValue(0) ;       // Haute lumiere
    ui->horizontalSlider_ombre->setValue(0) ;           // Ombre

    // Couleur
    ui->groupBox_couleur->setChecked(false) ;
    ui->horizontalSlider_temperature->setValue(0) ;     // Temperature
    ui->horizontalSlider_teinte->setValue(0) ;          // Teinte
    ui->horizontalSlider_saturation->setValue(0) ;      // Saturation
    ui->horizontalSlider_vividite->setValue(0) ;        // Vividite

    // Details
    ui->groupBox_details->setChecked(false) ;
    ui->horizontalSlider_nettete->setValue(0) ;         // Nettete
    ui->horizontalSlider_Bruitage->setValue(0) ;        // Bruitage

    // Resolution
    ui->groupBox_resolutionQuantification->setChecked(false) ;
    ui->horizontalSlider_resolution->setValue(0) ;      // Resolution
    ui->horizontalSlider_quantification->setValue(8) ;  // Quantification

    // Extraction
    ui->groupBox_extractionRVB->setChecked(false) ;

    // Contours
    ui->groupBox_contours->setChecked(false) ;

    // Debruitage
    ui->groupBox_debruitage->setChecked(false) ;

    // Seuillage et segmentation
    ui->groupBox_seuillageSegmentation->setChecked(false) ;
    // Seuils bas
    ui->verticalSlider_seuilBasB_2->setValue(0) ;       // Bleu
    ui->verticalSlider_seuilBasR_2->setValue(0) ;       // Rouge
    ui->verticalSlider_seuilBasV_2->setValue(0) ;       // Vert
    // Seuils hauts
    ui->verticalSlider_seuilHautB_2->setValue(256) ;    // Bleu
    ui->verticalSlider_seuilHautR_2->setValue(256) ;    // Rouge
    ui->verticalSlider_seuilHautV_2->setValue(256) ;    // Vert

    // Filtres
    ui->groupBox_filtres->setChecked(false) ;

    // Passer a la page precedente
    ui->stackedWidget->setCurrentIndex(2) ;
}

// Agrandissement de l'image originale
void MainWindow::on_horizontalSlider_imageOriginale_valueChanged(int value){
    // Sevlaration des variables
    int hauteurImage = ui->graphicsView_imageOriginale->scene()->height() ;     // Hauteur de l'image
    int largeurImage = ui->graphicsView_imageOriginale->scene()->width() ;      // Largeur de l'image
    int hauteurFenetre = ui->graphicsView_imageOriginale->height() ;            // Hauteur de la fenetre
    int largeurFenetre = ui->graphicsView_imageOriginale->width() ;             // Largeur de la fenetre
    double facteur ;                                                            // Facteur d'agrandissement

    // Calculer le facteur d'agrandissement
    if(hauteurImage > largeurImage){
        facteur = (double)hauteurFenetre/hauteurImage*value/2 ;
    }else{
        facteur = (double)largeurFenetre/largeurImage*value/2 ;
    }

    // Agrandissement
    if(value == 1){
        QGraphicsScene* scene = ui->graphicsView_imageOriginale->scene() ;
        ui->graphicsView_imageOriginale->fitInView(scene->sceneRect(), Qt::KeepAspectRatio) ;
    }else{
        ui->graphicsView_imageOriginale->setTransform(QTransform::fromScale(facteur, facteur)) ;
    }
}

// Agrandissement de l'image traitee
void MainWindow::on_horizontalSlider_imageTraitee_valueChanged(int value){
    // Sevlaration des variables
    int hauteurImage = ui->graphicsView_imageTraitee->scene()->height() ;   // Hauteur de l'image
    int largeurImage = ui->graphicsView_imageTraitee->scene()->width() ;    // Largeur de l'image
    int hauteurFenetre = ui->graphicsView_imageTraitee->height() ;          // Hauteur de la fenetre
    int largeurFenetre = ui->graphicsView_imageTraitee->width() ;           // Largeur de la fenetre
    double facteur ;                                                        // Facteur d'agrandissement

    // Calculer le facteur d'agrandissement
    if(hauteurImage > largeurImage){
        facteur = (double)hauteurFenetre/hauteurImage*value/2 ;
    }else{
        facteur = (double)largeurFenetre/largeurImage*value/2 ;
    }

    // Agrandissement
    if(value == 1){
        QGraphicsScene* scene = ui->graphicsView_imageTraitee->scene() ;
        ui->graphicsView_imageTraitee->fitInView(scene->sceneRect(), Qt::KeepAspectRatio) ;
    }else{
        ui->graphicsView_imageTraitee->setTransform(QTransform::fromScale(facteur, facteur)) ;
    }
}

// Reinitialiser
void MainWindow::on_pushButton_traitementReinitialiser_clicked(){
    // Declaration de variable
    QString cheminQT = QString::fromStdString(biblio["images"][indice]["cheminAcces"].asString()) ;

    Reinitialiser() ;
    // Affichage de l'image originale
    QPixmap imageOriginaleQT(cheminQT) ;
    QGraphicsScene* sceneImageOriginale = new QGraphicsScene() ;
    sceneImageOriginale->addPixmap(imageOriginaleQT) ;
    ui->graphicsView_imageOriginale->setScene(sceneImageOriginale) ;
    ui->graphicsView_imageOriginale->show() ;
    ui->graphicsView_imageOriginale->fitInView(sceneImageOriginale->sceneRect(), Qt::KeepAspectRatio);

    // Histogramme de l'image originale
    imageOriginale = imread(biblio["images"][indice]["cheminAcces"].asString()) ;
    histoImageOriginale = Normalisation(plot_histogram(imageOriginale), 255) ;
    QImage histoImageOriginaleQT = QImage((uchar*) histoImageOriginale.data, histoImageOriginale.cols, histoImageOriginale.rows, histoImageOriginale.step, QImage::Format_RGB888) ;
    QPixmap histoImageOrginalePixmap = QPixmap::fromImage(histoImageOriginaleQT) ;
    int hauteur = ui->label_histogrammeImageOriginale->height() ;       // Hauteur de la fenetre d'affichage
    int largeur = ui->label_histogrammeImageOriginale->width() ;        // Largeur de la fenetre d'affichage
    ui->label_histogrammeImageOriginale->setPixmap(histoImageOrginalePixmap.scaled(largeur, hauteur, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->label_histogrammeImageOriginale->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;

    // Initialiser l'image resultante et son histogramme
    ui->graphicsView_imageTraitee->setScene(sceneImageOriginale) ;
    ui->graphicsView_imageTraitee->show() ;
    ui->graphicsView_imageTraitee->fitInView(sceneImageOriginale->sceneRect(), Qt::KeepAspectRatio) ;

    // Histogramme - Initialisation
    ui->label_histogrammeImageTraitee->setPixmap(histoImageOrginalePixmap.scaled(largeur, hauteur, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->label_histogrammeImageTraitee->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
}

// Appliquer le traitement
void MainWindow::on_pushButton_traitementAppliquer_clicked(){
    // Declaration des variables
    string nbLigne, nbColonne ;     // Nombre de lignes et de colonnes
    string resolution ;             // Resolution

    // Mise a jour l'image originale temporelle
    imwrite("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png", imageResultat) ;
    imageOriginale = imread("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png") ;
    // Convertir en format QT
    QImage imageOriginaleQT("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png") ;
    // Histogramme
    histoImageOriginale = Normalisation(plot_histogram(imageOriginale), 255) ;
    QImage histoImageOriginaleQT = QImage((uchar*) histoImageOriginale.data, histoImageOriginale.cols, histoImageOriginale.rows, histoImageOriginale.step, QImage::Format_RGB888) ;

    // Affichage : Nouvelle image originale
    QGraphicsScene* scene = new QGraphicsScene() ;
    scene->addPixmap(QPixmap::fromImage(imageOriginaleQT)) ;
    ui->graphicsView_imageOriginale->setScene(scene) ;
    ui->graphicsView_imageOriginale->show() ;
    ui->graphicsView_imageOriginale->fitInView(scene->sceneRect(), Qt::KeepAspectRatio) ;
    // Affichage : Histogramme
    QPixmap histogrammeOriginalePixmap(QPixmap::fromImage(histoImageOriginaleQT)) ;
    int hauteur = ui->label_histogrammeImageOriginale->height() ;       // Hauteur de la fenetre d'affichage
    int largeur = ui->label_histogrammeImageOriginale->width() ;        // Largeur de la fenetre d'affichage
    ui->label_histogrammeImageOriginale->setPixmap(histogrammeOriginalePixmap.scaled(largeur, hauteur, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->label_histogrammeImageOriginale->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;

    // Afficher la resolution
    // Image originale
    nbLigne = to_string((int)imageOriginale.size().height) ;
    nbColonne = to_string((int)imageOriginale.size().width) ;
    resolution = "Resolution : [" + nbLigne + " x " + nbColonne + "]" ;
    ui->label_resolutionOriginale->setText(QString::fromStdString(resolution)) ;
    // Image traitee
    ui->label_resolutionTraitee->setText(QString::fromStdString(resolution)) ;
}

// -------------Luminosite-------------

// Initialiser
void MainWindow::on_groupBox_correction_clicked(){
    AffichageResultat(imageOriginale, 1) ;                      // Image originale
    // Si le box est choisi
    if(ui->groupBox_correction->isChecked()){
        // Desactiver les autres fonctionnalites
        ReinitialiserCouleur() ;                // Couleur
        ReinitialiserDetail() ;                 // Details
        ReinitialiserResolution() ;             // Resolution
        ReinitialiserExtraction() ;             // Extraction
        ReinitialiserContour() ;                // Contours
        ReinitialiserDebruitage() ;             // Debruitage
        ReinitialiserSeuillageSegmentation() ;  // Seuillage et segmentation
        ReinitialiserFiltre() ;                 // Filtres
    // Sinon : Reinitialiser
    }else{
        ReinitialiserLuminosite() ;
    }
}

// Bouton : Luminosite
void MainWindow::on_radioButton_luminosite_clicked(){
    // Si le bouton est coche
    if(ui->radioButton_luminosite->isChecked()){
        // Desactiver les autres fonctionnalites
        // Contraste
        ui->radioButton_contraste->setChecked(false) ;
        ui->horizontalSlider_contraste->setValue(0) ;
        ui->horizontalSlider_contraste->setEnabled(false) ;
        // Ombre
        ui->radioButton_ombre->setChecked(false) ;
        ui->horizontalSlider_ombre->setValue(0) ;
        ui->horizontalSlider_ombre->setEnabled(false) ;
        // Haute lumiere
        ui->radioButton_brillance->setChecked(false) ;
        ui->horizontalSlider_brillance->setValue(0) ;
        ui->horizontalSlider_brillance->setEnabled(false) ;

        // Activer et initialiser le slider
        ui->horizontalSlider_luminosite->setEnabled(true) ;
    }
}

// Modifier la luminosite de l'image
void MainWindow::on_horizontalSlider_luminosite_valueChanged(int value){
    // Application du reglage de luminosite
    imageResultat = ImageLuminosite(imageOriginale, value) ;

    // Affichage du resultat
    AffichageResultat(imageResultat, 1) ;
}

// Bouton : Contraste
void MainWindow::on_radioButton_contraste_clicked(){
    // Si le bouton est coche
    if(ui->radioButton_contraste->isChecked()){
        // Desactiver les autres fonctionnalites
        // Luminosite
        ui->radioButton_luminosite->setChecked(false) ;
        ui->horizontalSlider_luminosite->setValue(0) ;
        ui->horizontalSlider_luminosite->setEnabled(false) ;
        // Ombre
        ui->radioButton_ombre->setChecked(false) ;
        ui->horizontalSlider_ombre->setValue(0) ;
        ui->horizontalSlider_ombre->setEnabled(false) ;
        // Haute lumiere
        ui->radioButton_brillance->setChecked(false) ;
        ui->horizontalSlider_brillance->setValue(0) ;
        ui->horizontalSlider_brillance->setEnabled(false) ;

        // Activer et initialiser le slider
        ui->horizontalSlider_contraste->setEnabled(true) ;
    }
}

// Modifier le constraste de l'image
void MainWindow::on_horizontalSlider_contraste_valueChanged(int value){
    // Application de la normalisation
    imageResultat = Normalisation(imageOriginale, value) ;

    // Affichage du resultat
    AffichageResultat(imageResultat, 1) ;
}

// Bouton : Ombre
void MainWindow::on_radioButton_ombre_clicked(){
    // Si le bouton est coche
    if(ui->radioButton_ombre->isChecked()){
        // Desactiver les autres fonctionnalites
        // Luminosite
        ui->radioButton_luminosite->setChecked(false) ;
        ui->horizontalSlider_luminosite->setValue(0) ;
        ui->horizontalSlider_luminosite->setEnabled(false) ;
        // Contraste
        ui->radioButton_contraste->setChecked(false) ;
        ui->horizontalSlider_contraste->setValue(0) ;
        ui->horizontalSlider_contraste->setEnabled(false) ;
        // Haute lumiere
        ui->radioButton_brillance->setChecked(false) ;
        ui->horizontalSlider_brillance->setValue(0) ;
        ui->horizontalSlider_brillance->setEnabled(false) ;

        // Activer et initialiser le slider
        ui->horizontalSlider_ombre->setEnabled(true) ;
    }
}

// Ombre
void MainWindow::on_horizontalSlider_ombre_valueChanged(int value){
    imageResultat = ImageOmbre(imageOriginale, value) ;
    AffichageResultat(imageResultat, 1) ;
}

// Bouton : Haute lumiere
void MainWindow::on_radioButton_brillance_clicked(){
    // Si le bouton est coche
    if(ui->radioButton_brillance->isChecked()){
        // Desactiver les autres fonctionnalites
        // Luminosite
        ui->radioButton_luminosite->setChecked(false) ;
        ui->horizontalSlider_luminosite->setValue(0) ;
        ui->horizontalSlider_luminosite->setEnabled(false) ;
        // Contraste
        ui->radioButton_contraste->setChecked(false) ;
        ui->horizontalSlider_contraste->setValue(0) ;
        ui->horizontalSlider_contraste->setEnabled(false) ;
        // Ombre
        ui->radioButton_ombre->setChecked(false) ;
        ui->horizontalSlider_ombre->setValue(0) ;
        ui->horizontalSlider_ombre->setEnabled(false) ;

        // Activer et initialiser le slider
        ui->horizontalSlider_brillance->setEnabled(true) ;
    }
}

// Haute lumiere
void MainWindow::on_horizontalSlider_brillance_valueChanged(int value){
    imageResultat = ImageHauteLumiere(imageOriginale, value) ;
    AffichageResultat(imageResultat, 1) ;
}

// -------------Details-------------

// Initialiser
void MainWindow::on_groupBox_details_clicked(){
    AffichageResultat(imageOriginale, 1) ;                      // Image originale
    // Si le box est choisi
    if(ui->groupBox_details->isChecked()){
        // Desactiver les autres fonctionnalites
        ReinitialiserContour() ;                // Contours
        ReinitialiserFiltre() ;                 // Filtres
        ReinitialiserExtraction() ;             // Extraction
        ReinitialiserSeuillageSegmentation() ;  // Seuillage et segmentation
        ReinitialiserResolution() ;             // Resolution
        ReinitialiserLuminosite() ;             // Luminosite
        ReinitialiserCouleur() ;                // Couleur
        ReinitialiserDebruitage() ;             // Debruitage
    // Sinon : Reinitialiser
    }else{
        ReinitialiserDetail() ;
    }
}

// Bouton nettete
void MainWindow::on_radioButton_nettete_clicked(){
    if(ui->radioButton_nettete->isChecked()){
        // Desactiver les autres corrections
        ui->radioButton_luminosite->setChecked(false) ;     // Luminosite
        ui->radioButton_contraste->setChecked(false) ;      // Contraste
        ui->radioButton_bruitage->setChecked(false) ;       // Bruitage

        // Activer et initialiser le slider
        ui->horizontalSlider_nettete->setEnabled(true) ;
        ui->horizontalSlider_nettete->setValue(0) ;

        // Remettre a zero les autres sliders
        ui->horizontalSlider_contraste->setValue(0) ;       // Contraste
        ui->horizontalSlider_contraste->setEnabled(0) ;
        ui->horizontalSlider_luminosite->setValue(0) ;      // Luminosite
        ui->horizontalSlider_luminosite->setEnabled(false) ;
        ui->horizontalSlider_Bruitage->setValue(0) ;        // Bruitage
        ui->horizontalSlider_Bruitage->setEnabled(false) ;

        // Initialiser l'image traitee
        AffichageResultat(imageOriginale, 1) ;
    }
}

// Modifier la nettete de l'image
void MainWindow::on_horizontalSlider_nettete_valueChanged(int value){
    if(ui->radioButton_nettete->isChecked()){
        // Rendre flou
        if(value < 0){
            // imageResultat = imageTemp[abs(value)-1] ;
            imageResultat = ImageLissage(imageOriginale, abs(value)) ;
            if(value%2 == 0){
                imageResultat = ImageBGRRGB(imageResultat) ;
            }
        // Rehaussement de contours
        }else if(value > 0){
            imageResultat = ImageRehaussementContour(imageOriginale, value*10, 2) ;
        // Image de depart
        }else{
            imageResultat = ImageBGRRGB(imageOriginale) ;
        }

        // Affichage du resultat
        AffichageResultat(imageResultat, 0) ;
    }
}

// Bouton bruitage
void MainWindow::on_radioButton_bruitage_clicked(){
    if(ui->radioButton_bruitage->isChecked()){
        // Desactiver les autres corrections
        ui->radioButton_nettete->setChecked(false) ;        // Nettete
        ui->radioButton_luminosite->setChecked(false) ;     // Luminosite
        ui->radioButton_contraste->setChecked(false) ;      // Contraste

        // Activer et initialiser le slider
        ui->horizontalSlider_Bruitage->setEnabled(true) ;
        ui->horizontalSlider_Bruitage->setValue(0) ;

        // Remettre a zero les autres sliders
        ui->horizontalSlider_nettete->setValue(0) ;         // Nettete
        ui->horizontalSlider_nettete->setEnabled(false) ;
        ui->horizontalSlider_luminosite->setValue(0) ;      // Luminosite
        ui->horizontalSlider_luminosite->setEnabled(false) ;
        ui->horizontalSlider_contraste->setValue(0) ;       // Contraste
        ui->horizontalSlider_contraste->setEnabled(false) ;

        // Initialiser l'image traitee
        AffichageResultat(imageOriginale, 1) ;
    }
}

// Bruiter l'image
void MainWindow::on_horizontalSlider_Bruitage_valueChanged(int value){
    // Bruiter l'image
    imageResultat = ImageBruitage(imageOriginale, value) ;

    // Affichage du resultat
    AffichageResultat(imageResultat, 0) ;
}

// -------------Filtres de couleur-------------

// Initialiser
void MainWindow::on_groupBox_filtres_clicked(){
    AffichageResultat(imageOriginale, 1) ;                      // Image originale
    // Si le box est choisi
    if(ui->groupBox_filtres->isChecked()){
        // Desactiver les autres fonctionnalites
        ReinitialiserLuminosite() ;             // Luminosite
        ReinitialiserCouleur() ;                // Couleur
        ReinitialiserDetail() ;                 // Details
        ReinitialiserResolution() ;             // Resolution
        ReinitialiserContour() ;                // Contours
        ReinitialiserExtraction() ;             // Extraction
        ReinitialiserDebruitage() ;             // Debruitage
        ReinitialiserSeuillageSegmentation() ;  // Seuillage et segmentation
    // Sinon : Reinitialiser
    }else{
        ReinitialiserFiltre() ;
    }
}

// Originale
void MainWindow::on_radioButton_originale_clicked(){
    if(ui->radioButton_originale->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_niveauGris->setChecked(false) ;     // Niveau de gris
        ui->radioButton_sepia->setChecked(false) ;          // Sepia
        ui->radioButton_inversement->setChecked(false) ;    // Inversement
        ui->radioButton_rouge->setChecked(false) ;          // Rouge
        ui->radioButton_vert->setChecked(false) ;           // Vert
        ui->radioButton_bleu->setChecked(false) ;           // Bleu
        ui->radioButton_cyan->setChecked(false) ;           // Cyan
        ui->radioButton_jaune->setChecked(false) ;          // Jaune
        ui->radioButton_magenta->setChecked(false) ;        // Magenta
        ui->radioButton_rgb->setChecked(false) ;            // RGB
        ui->radioButton_cmj->setChecked(false) ;            // CMJ

        imageResultat = imageOriginale ;
        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// Image monochrome
void MainWindow::on_radioButton_niveauGris_clicked(){
    ui->radioButton_niveauGris->setChecked(true) ;
    if(ui->radioButton_niveauGris->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_originale->setChecked(false) ;              // Image originale
        ui->radioButton_sepia->setChecked(false) ;                  // Sepia
        ui->radioButton_inversement->setChecked(false) ;            // Inversement
        ui->radioButton_rouge->setChecked(false) ;                  // Rouge
        ui->radioButton_vert->setChecked(false) ;                   // Vert
        ui->radioButton_bleu->setChecked(false) ;                   // Bleu
        ui->radioButton_cyan->setChecked(false) ;                   // Cyan
        ui->radioButton_jaune->setChecked(false) ;                  // Jaune
        ui->radioButton_magenta->setChecked(false) ;                // Magenta
        ui->radioButton_rgb->setChecked(false) ;                    // RGB
        ui->radioButton_cmj->setChecked(false) ;                    // CMJ

        // Convertir l'image en niveau de gris
        if(ui->radioButton_niveauGris->isChecked()){
            imageResultat = MonoCouleur(ImageMonochrome(imageOriginale)) ;
        }

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// Image sepia
void MainWindow::on_radioButton_sepia_clicked(){
    ui->radioButton_sepia->setChecked(true) ;
    if(ui->radioButton_sepia->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_originale->setChecked(false) ;              // Image originale
        ui->radioButton_niveauGris->setChecked(false) ;             // Monochrome
        ui->radioButton_inversement->setChecked(false) ;            // Inversement
        ui->radioButton_rouge->setChecked(false) ;                  // Rouge
        ui->radioButton_vert->setChecked(false) ;                   // Vert
        ui->radioButton_bleu->setChecked(false) ;                   // Bleu
        ui->radioButton_cyan->setChecked(false) ;                   // Cyan
        ui->radioButton_jaune->setChecked(false) ;                  // Jaune
        ui->radioButton_magenta->setChecked(false) ;                // Magenta
        ui->radioButton_rgb->setChecked(false) ;                    // RGB
        ui->radioButton_cmj->setChecked(false) ;                    // CMJ

        // Convertir l'image en sepia
        imageResultat = ImageSepia(imageOriginale) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// Image inversee
void MainWindow::on_radioButton_inversement_clicked(){
    ui->radioButton_inversement->setChecked(true) ;
    if(ui->radioButton_inversement->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_originale->setChecked(false) ;              // Image originale
        ui->radioButton_niveauGris->setChecked(false) ;             // Monochrome
        ui->radioButton_sepia->setChecked(false) ;                  // Sepia
        ui->radioButton_rouge->setChecked(false) ;                  // Rouge
        ui->radioButton_vert->setChecked(false) ;                   // Vert
        ui->radioButton_bleu->setChecked(false) ;                   // Bleu
        ui->radioButton_cyan->setChecked(false) ;                   // Cyan
        ui->radioButton_jaune->setChecked(false) ;                  // Jaune
        ui->radioButton_magenta->setChecked(false) ;                // Magenta
        ui->radioButton_rgb->setChecked(false) ;                    // RGB
        ui->radioButton_cmj->setChecked(false) ;                    // CMJ

        // Inverser les niveaux d'intensite de l'image
        imageResultat = ImageInversement(imageOriginale) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// Image rouge
void MainWindow::on_radioButton_rouge_clicked(){
    ui->radioButton_rouge->setChecked(true) ;
    if(ui->radioButton_rouge->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_originale->setChecked(false) ;              // Image originale
        ui->radioButton_niveauGris->setChecked(false) ;             // Monochrome
        ui->radioButton_sepia->setChecked(false) ;                  // Sepia
        ui->radioButton_inversement->setChecked(false) ;            // Inversement
        ui->radioButton_vert->setChecked(false) ;                   // Vert
        ui->radioButton_bleu->setChecked(false) ;                   // Bleu
        ui->radioButton_cyan->setChecked(false) ;                   // Cyan
        ui->radioButton_jaune->setChecked(false) ;                  // Jaune
        ui->radioButton_magenta->setChecked(false) ;                // Magenta
        ui->radioButton_rgb->setChecked(false) ;                    // RGB
        ui->radioButton_cmj->setChecked(false) ;                    // CMJ

        // Image rouge
        imageResultat = ImageRouge(imageOriginale) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 0) ;
    }
}

// Image verte
void MainWindow::on_radioButton_vert_clicked(){
    ui->radioButton_vert->setChecked(true) ;
    if(ui->radioButton_vert->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_originale->setChecked(false) ;              // Image originale
        ui->radioButton_niveauGris->setChecked(false) ;             // Monochrome
        ui->radioButton_sepia->setChecked(false) ;                  // Sepia
        ui->radioButton_inversement->setChecked(false) ;            // Inversement
        ui->radioButton_rouge->setChecked(false) ;                  // Rouge
        ui->radioButton_bleu->setChecked(false) ;                   // Bleu
        ui->radioButton_cyan->setChecked(false) ;                   // Cyan
        ui->radioButton_jaune->setChecked(false) ;                  // Jaune
        ui->radioButton_magenta->setChecked(false) ;                // Magenta
        ui->radioButton_rgb->setChecked(false) ;                    // RGB
        ui->radioButton_cmj->setChecked(false) ;                    // CMJ

        // Image verte
        imageResultat = ImageVert(imageOriginale) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 0) ;
    }
}

// Image bleue
void MainWindow::on_radioButton_bleu_clicked(){
    ui->radioButton_bleu->setChecked(true) ;
    if(ui->radioButton_bleu->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_originale->setChecked(false) ;              // Image originale
        ui->radioButton_niveauGris->setChecked(false) ;             // Monochrome
        ui->radioButton_sepia->setChecked(false) ;                  // Sepia
        ui->radioButton_inversement->setChecked(false) ;            // Inversement
        ui->radioButton_rouge->setChecked(false) ;                  // Rouge
        ui->radioButton_vert->setChecked(false) ;                   // Vert
        ui->radioButton_cyan->setChecked(false) ;                   // Cyan
        ui->radioButton_jaune->setChecked(false) ;                  // Jaune
        ui->radioButton_magenta->setChecked(false) ;                // Magenta
        ui->radioButton_rgb->setChecked(false) ;                    // RGB
        ui->radioButton_cmj->setChecked(false) ;                    // CMJ

        // Image bleue
        imageResultat = ImageBleu(imageOriginale) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 0) ;
    }
}

// Image jaune
void MainWindow::on_radioButton_jaune_clicked(){
    ui->radioButton_jaune->setChecked(true) ;
    if(ui->radioButton_jaune->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_originale->setChecked(false) ;              // Image originale
        ui->radioButton_niveauGris->setChecked(false) ;             // Monochrome
        ui->radioButton_sepia->setChecked(false) ;                  // Sepia
        ui->radioButton_inversement->setChecked(false) ;            // Inversement
        ui->radioButton_rouge->setChecked(false) ;                  // Rouge
        ui->radioButton_vert->setChecked(false) ;                   // Vert
        ui->radioButton_bleu->setChecked(false) ;                   // Bleu
        ui->radioButton_cyan->setChecked(false) ;                   // Cyan
        ui->radioButton_magenta->setChecked(false) ;                // Magenta
        ui->radioButton_rgb->setChecked(false) ;                    // RGB
        ui->radioButton_cmj->setChecked(false) ;                    // CMJ

        // Image jaune
        imwrite("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png", imageOriginale) ;
        imageResultat = ImageJaune(imread("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png")) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// Image cyane
void MainWindow::on_radioButton_cyan_clicked(){
    ui->radioButton_cyan->setChecked(true) ;
    if(ui->radioButton_cyan->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_originale->setChecked(false) ;              // Image originale
        ui->radioButton_niveauGris->setChecked(false) ;             // Monochrome
        ui->radioButton_sepia->setChecked(false) ;                  // Sepia
        ui->radioButton_inversement->setChecked(false) ;            // Inversement
        ui->radioButton_rouge->setChecked(false) ;                  // Rouge
        ui->radioButton_vert->setChecked(false) ;                   // Vert
        ui->radioButton_bleu->setChecked(false) ;                   // Bleu
        ui->radioButton_jaune->setChecked(false) ;                  // Jaune
        ui->radioButton_magenta->setChecked(false) ;                // Magenta
        ui->radioButton_rgb->setChecked(false) ;                    // RGB
        ui->radioButton_cmj->setChecked(false) ;                    // CMJ

        // Image cyane
        imwrite("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png", imageOriginale) ;
        imageResultat = ImageCyan(imread("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png")) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// Image magenta
void MainWindow::on_radioButton_magenta_clicked(){
    ui->radioButton_magenta->setChecked(true) ;
    if(ui->radioButton_magenta->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_originale->setChecked(false) ;              // Image originale
        ui->radioButton_niveauGris->setChecked(false) ;             // Monochrome
        ui->radioButton_sepia->setChecked(false) ;                  // Sepia
        ui->radioButton_inversement->setChecked(false) ;            // Inversement
        ui->radioButton_rouge->setChecked(false) ;                  // Rouge
        ui->radioButton_vert->setChecked(false) ;                   // Vert
        ui->radioButton_bleu->setChecked(false) ;                   // Bleu
        ui->radioButton_jaune->setChecked(false) ;                  // Jaune
        ui->radioButton_cyan->setChecked(false) ;                   // Cyan
        ui->radioButton_rgb->setChecked(false) ;                    // RGB
        ui->radioButton_cmj->setChecked(false) ;                    // CMJ

        // Image magenta
        imwrite("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png", imageOriginale) ;
        imageResultat = ImageMagenta(imread("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png")) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// Image RGB
void MainWindow::on_radioButton_rgb_clicked(){
    ui->radioButton_rgb->setChecked(true) ;
    if(ui->radioButton_rgb->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_originale->setChecked(false) ;              // Image originale
        ui->radioButton_niveauGris->setChecked(false) ;             // Monochrome
        ui->radioButton_sepia->setChecked(false) ;                  // Sepia
        ui->radioButton_inversement->setChecked(false) ;            // Inversement
        ui->radioButton_rouge->setChecked(false) ;                  // Rouge
        ui->radioButton_vert->setChecked(false) ;                   // Vert
        ui->radioButton_bleu->setChecked(false) ;                   // Bleu
        ui->radioButton_jaune->setChecked(false) ;                  // Jaune
        ui->radioButton_cyan->setChecked(false) ;                   // Cyan
        ui->radioButton_magenta->setChecked(false) ;                // Magenta
        ui->radioButton_cmj->setChecked(false) ;                    // CMJ

        // Image RGB
        imwrite("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png", imageOriginale) ;
        imageResultat = ImageRGB(imread("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png")) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// -------------Extraction du canal de couleur-------------

// Initialiser
void MainWindow::on_groupBox_extractionRVB_clicked(){
    AffichageResultat(imageOriginale, 1) ;                      // Image originale
    // Si le box est choisi
    if(ui->groupBox_extractionRVB->isChecked()){
        // Desactiver les autres fonctionnalites
        ReinitialiserLuminosite() ;             // Luminosite
        ReinitialiserCouleur() ;                // Couleur
        ReinitialiserDetail() ;                 // Details
        ReinitialiserResolution() ;             // Resolution
        ReinitialiserContour() ;                // Contours
        ReinitialiserDebruitage() ;             // Debruitage
        ReinitialiserSeuillageSegmentation() ;  // Seuillage et segmentation
        ReinitialiserFiltre() ;                 // Filtres

        // Activer les fonctionnalites
        ui->radioButton_extractionR->setEnabled(true) ;             // Rouge
        ui->radioButton_extractionV->setEnabled(true) ;             // Vert
        ui->radioButton_extractionB->setEnabled(true) ;             // Bleu
    // Sinon
    }else{
        ReinitialiserExtraction() ;
    }
}

// Extraction du canal rouge de l'image
void MainWindow::on_radioButton_extractionR_clicked(){
    if(ui->radioButton_extractionR->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_extractionB->setChecked(false) ;    // Canal bleu
        ui->radioButton_extractionV->setChecked(false) ;    // Canal vert

        // Extraction du canal rouge
        imageResultat = MonoCouleur(ImageExtractionCouleur(imageOriginale, 3)) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// Extraction du canal vert de l'image
void MainWindow::on_radioButton_extractionV_clicked(){
    if(ui->radioButton_extractionV->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_extractionR->setChecked(false) ;    // Canal rouge
        ui->radioButton_extractionB->setChecked(false) ;    // Canal bleu

        // Extraction du canal vert
        imageResultat = MonoCouleur(ImageExtractionCouleur(imageOriginale, 2)) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// Extraction du canal bleu de l'image
void MainWindow::on_radioButton_extractionB_clicked(){
    if(ui->radioButton_extractionB->isChecked()){
        // Desactiver les autres filtres
        ui->radioButton_extractionR->setChecked(false) ;    // Canal rouge
        ui->radioButton_extractionV->setChecked(false) ;    // Canal vert

        // Extraction du canal bleu
        imageResultat = MonoCouleur(ImageExtractionCouleur(imageOriginale, 1)) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// -------------Seuillage & Segmentation-------------

// Initialiser
void MainWindow::on_groupBox_seuillageSegmentation_clicked(){
    AffichageResultat(imageOriginale, 1) ;                      // Image originale
    // Si le box est choisi
    if(ui->groupBox_seuillageSegmentation->isChecked()){
        // Desactiver les autres fonctionnalites
        ReinitialiserLuminosite() ;             // Luminosite
        ReinitialiserCouleur() ;                // Couleur
        ReinitialiserDetail() ;                 // Details
        ReinitialiserResolution() ;             // Resolution
        ReinitialiserContour() ;                // Contours
        ReinitialiserExtraction() ;             // Extraction
        ReinitialiserDebruitage() ;             // Debruitage
        ReinitialiserFiltre() ;                 // Filtres
    // Sinon : Reinitialiser
    }else{
        ReinitialiserSeuillageSegmentation() ;
    }
}

// Initialiser le seuillage
void MainWindow::on_radioButton_seuillage_clicked(){
    // Si l'utilisateur choisit le seuillage
    if(ui->radioButton_seuillage->isChecked()){
        ui->radioButton_segmentation->setChecked(false) ;       // Desactiver la segmentation
        ui->groupBox_simpleHysteresis->setEnabled(true) ;       // Activer la zone de choix du type de seuils
        ui->groupBox_seuilBas->setEnabled(true) ;               // Activer les sliders des seuils bas

        // Initialiser les sliders
        // Seuils bas
        ui->verticalSlider_seuilBasR_2->setValue(0) ;           // Rouge
        ui->verticalSlider_seuilBasV_2->setValue(0) ;           // Vert
        ui->verticalSlider_seuilBasB_2->setValue(0) ;           // Bleu
        // Seuils hauts
        ui->verticalSlider_seuilHautR_2->setValue(256) ;        // Rouge
        ui->verticalSlider_seuilHautV_2->setValue(256) ;        // Vert
        ui->verticalSlider_seuilHautB_2->setValue(256) ;        // Bleu
    }
}

// Initialiser la segmentation
void MainWindow::on_radioButton_segmentation_clicked(){
    if(ui->radioButton_segmentation->isChecked()){
        ui->radioButton_seuillage->setChecked(false) ;
        ui->groupBox_simpleHysteresis->setEnabled(true) ;       // Activer la zone de choix du type de seuils
        ui->groupBox_seuilBas->setEnabled(true) ;               // Activer les sliders des seuils bas

        // Initialiser les sliders
        // Seuils bas
        ui->verticalSlider_seuilBasR_2->setValue(0) ;           // Rouge
        ui->verticalSlider_seuilBasV_2->setValue(0) ;           // Vert
        ui->verticalSlider_seuilBasB_2->setValue(0) ;           // Bleu
        // Seuils hauts
        ui->verticalSlider_seuilHautR_2->setValue(256) ;        // Rouge
        ui->verticalSlider_seuilHautV_2->setValue(256) ;        // Vert
        ui->verticalSlider_seuilHautB_2->setValue(256) ;        // Bleu
    }
}

// Initialiser le sueillage par seuils simples
void MainWindow::on_radioButton_seuillageSimple_clicked(){
    // Si l'utilisateur choisit d'appliquer les seuils simples
    if(ui->radioButton_seuillageSimple->isChecked()){
        // Desactiver le seuillage par hysteresis
        ui->radioButton_seuillageHysteresis->setChecked(false) ;
        // Desactiver les sliders des seuils hauts
        ui->groupBox_seuilHaut->setEnabled(false) ;
        // Reinitialiser les seuils hauts
        seuilHaut[2] = 256 ;    // Rouge
        seuilHaut[1] = 256 ;    // Vert
        seuilHaut[0] = 256 ;    // Bleu
    }
}

// Initialiser le seuillage par seuils par hysteresis
void MainWindow::on_radioButton_seuillageHysteresis_clicked(){
    // Si l'utilisateur choisit d'appliquer les seuils hysteresis
    if(ui->radioButton_seuillageHysteresis->isChecked()){
        // Desactiver le seuillage simple
        ui->radioButton_seuillageSimple->setChecked(false) ;
        // Activer les sliders des seuils hauts
        ui->groupBox_seuilHaut->setEnabled(true) ;
    }
}

// Seuil bas rouge
void MainWindow::on_verticalSlider_seuilBasR_2_valueChanged(int value){
    // Si l'image est en niveau de gris, les trois seuils sont egaux
    if(VerifierImage(imageOriginale, imageResultat)){
        ui->verticalSlider_seuilBasV_2->setSliderPosition(value) ;      // Regler slider du seuil bas - vert
        ui->verticalSlider_seuilBasB_2->setSliderPosition(value) ;      // Regler slider du seuil bas - bleu
        // Relever les valeurs des seuils
        seuilBas[2] = value ;                                           // Seuil bas rouge
        seuilBas[1] = value ;                                           // Seuil bas vert
        seuilBas[0] = value ;                                           // Seuil bas bleu
    // Si seuillage par hysteresis
    }else{
        seuilBas[2] = value ;                                           // Seuil bas rouge
    }

    // Definir l'intervalle du seuil bas
    // Si seuillage simple
    if(ui->radioButton_seuillageSimple->isChecked()){
        ui->verticalSlider_seuilBasR_2->setRange(0, 256) ;
    // Si seuillage par hysteresis
    }else if(ui->radioButton_seuillageHysteresis->isChecked()){
        ui->verticalSlider_seuilBasR_2->setRange(0, ui->verticalSlider_seuilHautR_2->value()) ;
    }

    // Image resultante
    // Seuillage
    if(ui->radioButton_seuillage->isChecked()){
        imageResultat = ImageSeuillage(imageOriginale, seuilBas, seuilHaut) ;
    // Segmentation
    }else if(ui->radioButton_segmentation->isChecked()){
        imageResultat = ImageSegmentation(imageOriginale, seuilBas, seuilHaut) ;
    }

    // Affichage du resultat
    AffichageResultat(imageResultat, 1) ;
}

// Seuil bas vert
void MainWindow::on_verticalSlider_seuilBasV_2_valueChanged(int value){
    // Si l'image est en niveau de gris, les trois seuils sont egaux
    if(VerifierImage(imageOriginale, imageResultat)){
        ui->verticalSlider_seuilBasR_2->setSliderPosition(value) ;      // Regler slider du seuil bas - rouge
        ui->verticalSlider_seuilBasB_2->setSliderPosition(value) ;      // Regler slider du seuil bas - bleu
        // Relever les valeurs des seuils
        seuilBas[2] = value ;                                           // Seuil bas rouge
        seuilBas[1] = value ;                                           // Seuil bas vert
        seuilBas[0] = value ;                                           // Seuil bas bleu
    // Si seuillage par hysteresis
    }else{
        seuilBas[1] = value ;                                           // Seuil bas vert
    }

    // Si seuillage simple
    // Definir l'intervalle du seuil bas
    if(ui->radioButton_seuillageSimple->isChecked()){
        ui->verticalSlider_seuilBasV_2->setRange(0, 256) ;
    // Si seuillage par hysteresis
    }else if(ui->radioButton_seuillageHysteresis->isChecked()){
        ui->verticalSlider_seuilBasV_2->setRange(0, ui->verticalSlider_seuilHautV_2->value()) ;
    }

    // Image resultante
    // Seuillage
    if(ui->radioButton_seuillage->isChecked()){
        imageResultat = ImageSeuillage(imageOriginale, seuilBas, seuilHaut) ;
    // Segmentation
    }else if(ui->radioButton_segmentation->isChecked()){
        imageResultat = ImageSegmentation(imageOriginale, seuilBas, seuilHaut) ;
    }

    // Affichage du resultat
    AffichageResultat(imageResultat, 1) ;
}

// Seuil bas bleu
void MainWindow::on_verticalSlider_seuilBasB_2_valueChanged(int value){
    // Si l'image est en niveau de gris, les trois seuils sont egaux
    if(VerifierImage(imageOriginale, imageResultat)){
        ui->verticalSlider_seuilBasR_2->setSliderPosition(value) ;      // Regler slider du seuil bas - rouge
        ui->verticalSlider_seuilBasV_2->setSliderPosition(value) ;      // Regler slider du seuil bas - vert
        // Relever les valeurs des seuils
        seuilBas[2] = value ;                                           // Seuil bas rouge
        seuilBas[1] = value ;                                           // Seuil bas vert
        seuilBas[0] = value ;                                           // Seuil bas bleu
    }else{
        seuilBas[0] = value ;                                           // Seuil bas bleu
    }

    // Si seuillage simple
    // Definir l'intervalle du seuil bas
    if(ui->radioButton_seuillageSimple->isChecked()){
        ui->verticalSlider_seuilBasB_2->setRange(0, 256) ;
    // Si seuillage par hysteresis
    }else if(ui->radioButton_seuillageHysteresis->isChecked()){
        ui->verticalSlider_seuilBasB_2->setRange(0, ui->verticalSlider_seuilHautB_2->value()) ;
    }

    // Image resultante
    // Seuillage
    if(ui->radioButton_seuillage->isChecked()){
        imageResultat = ImageSeuillage(imageOriginale, seuilBas, seuilHaut) ;
    // Seuillage
    }else if(ui->radioButton_segmentation->isChecked()){
        imageResultat = ImageSegmentation(imageOriginale, seuilBas, seuilHaut) ;
    }

    // Affichage du resultat
    AffichageResultat(imageResultat, 1) ;
}

// Seuil haut rouge
void MainWindow::on_verticalSlider_seuilHautR_2_valueChanged(int value){
    // Si l'image est en niveau de gris, les trois seuils sont egaux
    if(VerifierImage(imageOriginale, imageResultat)){
        ui->verticalSlider_seuilHautV_2->setSliderPosition(value) ;     // Regler slider du seuil haut - vert
        ui->verticalSlider_seuilHautB_2->setSliderPosition(value) ;     // Regler slider du seuil haut - bleu
        // Relever les valeurs des seuils
        seuilHaut[2] = value ;                                          // Seuil haut rouge
        seuilHaut[1] = value ;                                          // Seuil haut vert
        seuilHaut[0] = value ;                                          // Seuil haut bleu
    }else{
        seuilHaut[2] = value ;                                          // Seuil haut rouge
    }

    // Si seuillage hysteresis
    // Definir l'intervalle du seuil haut
    if(ui->radioButton_seuillageHysteresis->isChecked()){
        ui->verticalSlider_seuilHautR_2->setRange(ui->verticalSlider_seuilBasR_2->value(), 256) ;
    }

    // Image resultante
    // Seuillage
    if(ui->radioButton_seuillage->isChecked()){
        imageResultat = ImageSeuillage(imageOriginale, seuilBas, seuilHaut) ;
    // Segmentation
    }else if(ui->radioButton_segmentation->isChecked()){
        imageResultat = ImageSegmentation(imageOriginale, seuilBas, seuilHaut) ;
    }

    // Affichage du resultat
    AffichageResultat(imageResultat, 1) ;
}

// Seuil haut vert
void MainWindow::on_verticalSlider_seuilHautV_2_valueChanged(int value){
    // Si l'image est en niveau de gris, les trois seuils sont egaux
    if(VerifierImage(imageOriginale, imageResultat)){
        ui->verticalSlider_seuilHautR_2->setSliderPosition(value) ;     // Regler slider du seuil haut - rouge
        ui->verticalSlider_seuilHautB_2->setSliderPosition(value) ;     // Regler slider du seuil haut - bleu
        // Relever les valeurs des seuils
        seuilHaut[2] = value ;                                          // Seuil haut rouge
        seuilHaut[1] = value ;                                          // Seuil haut vert
        seuilHaut[0] = value ;                                          // Seuil haut bleu
    }else{
        seuilHaut[1] = value ;                                          // Seuil haut vert
    }

    // Definir l'intervalle du seuil haut
    // Si seuillage hysteresis
    if(ui->radioButton_seuillageHysteresis->isChecked()){
        ui->verticalSlider_seuilHautV_2->setRange(ui->verticalSlider_seuilBasV_2->value(), 256) ;
    }

    // Image resultante
    // Seuillage
    if(ui->radioButton_seuillage->isChecked()){
        imageResultat = ImageSeuillage(imageOriginale, seuilBas, seuilHaut) ;
    // Seuillage
    }else if(ui->radioButton_segmentation->isChecked()){
        imageResultat = ImageSegmentation(imageOriginale, seuilBas, seuilHaut) ;
    }

    // Affichage du resultat
    AffichageResultat(imageResultat, 1) ;
}

// Seuil haut bleu
void MainWindow::on_verticalSlider_seuilHautB_2_valueChanged(int value){
    // Si l'image est en niveau de gris, les trois seuils sont egaux
    if(VerifierImage(imageOriginale, imageResultat)){
        ui->verticalSlider_seuilHautR_2->setSliderPosition(value) ;     // Regler slider du seuil haut - rouge
        ui->verticalSlider_seuilHautV_2->setSliderPosition(value) ;     // Regler slider du seuil haut - ver
        // Relever les valeurs des seuils
        seuilHaut[2] = value ;                                          // Seuil haut rouge
        seuilHaut[1] = value ;                                          // Seuil haut vert
        seuilHaut[0] = value ;                                          // Seuil haut bleu
    }else{
        seuilHaut[0] = value ;                                          // Seuil haut bleu
    }

    // Si seuillage hysteresis
    // Definir l'intervalle du seuil haut
    if(ui->radioButton_seuillageHysteresis->isChecked()){
        ui->verticalSlider_seuilHautB_2->setRange(ui->verticalSlider_seuilBasB_2->value(), 256) ;
    }

    // Image resultante
    // Seuillage
    if(ui->radioButton_seuillage->isChecked()){
        imageResultat = ImageSeuillage(imageOriginale, seuilBas, seuilHaut) ;
    // Segmentation
    }else if(ui->radioButton_segmentation->isChecked()){
        imageResultat = ImageSegmentation(imageOriginale, seuilBas, seuilHaut) ;
    }

    // Affichage du resultat
    AffichageResultat(imageResultat, 1) ;
}

// Reinitialiser seuil bas rouge
void MainWindow::on_pushButton_seuilBasR_clicked(){
    ui->verticalSlider_seuilBasR_2->setRange(0, 255) ;          // Intervalle
    ui->verticalSlider_seuilBasR_2->setValue(0) ;               // Valeur
}

// Reinitialiser seuil bas vert
void MainWindow::on_pushButton_seuilBasV_clicked(){
    ui->verticalSlider_seuilBasV_2->setRange(0, 255) ;          // Intervalle
    ui->verticalSlider_seuilBasV_2->setValue(0) ;               // Valeur
}

// Reinitialiser seuil bas bleu
void MainWindow::on_pushButton_seuilBasB_clicked(){
    ui->verticalSlider_seuilBasB_2->setRange(0, 255) ;          // Intervalle
    ui->verticalSlider_seuilBasB_2->setValue(0) ;               // Valeur
}

// Reinitialiser seuil haut rouge
void MainWindow::on_pushButton_seuilHautR_clicked(){
    ui->verticalSlider_seuilHautR_2->setRange(0, 255) ;         // Intervalle
    ui->verticalSlider_seuilHautR_2->setValue(255) ;            // Valeur
}

// Reinitialiser seuil haut vert
void MainWindow::on_pushButton_seuilHautV_clicked(){
    ui->verticalSlider_seuilHautV_2->setRange(0, 255) ;         // Intervalle
    ui->verticalSlider_seuilHautV_2->setValue(255) ;            // Valeur
}

// Reinitialiser seuil haut bleu
void MainWindow::on_pushButton_seuilHautB_clicked(){
    ui->verticalSlider_seuilHautB_2->setRange(0, 255) ;         // Intervalle
    ui->verticalSlider_seuilHautB_2->setValue(255) ;            // Valeur
}

// -------------Contours-------------

// Initialiser
void MainWindow::on_groupBox_contours_clicked(){
    AffichageResultat(imageOriginale, 1) ;                      // Image originale
    // Si le box est choisi
    if(ui->groupBox_contours->isChecked()){
        // Desactiver les autres fonctionnalites
        ReinitialiserLuminosite() ;             // Luminosite
        ReinitialiserCouleur() ;                // Couleur
        ReinitialiserDetail() ;                 // Detais
        ReinitialiserResolution() ;             // Resolution
        ReinitialiserExtraction() ;             // Extraction
        ReinitialiserDebruitage() ;             // Devruitage
        ReinitialiserSeuillageSegmentation() ;  // Seuillage et segmentation
        ReinitialiserFiltre() ;                 // Filtres
    // Sinon : Reinitialiser
    }else{
        ReinitialiserContour() ;
    }
}

// Detection de contours - Gradient
void MainWindow::on_radioButton_contoursGradient_clicked(){
    if(ui->radioButton_contoursGradient->isChecked()){
        imageResultat = MonoCouleur(ImageContour(imageOriginale, 1)) ;
        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// Detection de contours - Laplacien
void MainWindow::on_radioButton_contoursLaplacien_clicked(){
    if(ui->radioButton_contoursLaplacien->isChecked()){
        if(ui->groupBox_contours->isChecked()){
            imageResultat = MonoCouleur(ImageContour(imageOriginale, 2)) ;
            // Affichage du resultat
            AffichageResultat(imageResultat, 1) ;
        }
    }
}

// -------------Resolution-------------

// Initialiser
void MainWindow::on_groupBox_resolutionQuantification_clicked(){
    AffichageResultat(imageOriginale, 1) ;                      // Image originale
    // Si le box est choisi
    if(ui->groupBox_resolutionQuantification->isChecked()){
        // Desactiver les autres fonctionnalites
        ReinitialiserLuminosite() ;             // Luminosite
        ReinitialiserCouleur() ;                // Couleur
        ReinitialiserDetail() ;                 // Details
        ReinitialiserContour() ;                // Contours
        ReinitialiserExtraction() ;             // Extraction
        ReinitialiserDebruitage() ;             // Debruitage
        ReinitialiserSeuillageSegmentation() ;  // Seuillage et segmentation
        ReinitialiserFiltre() ;                 // Filtres
    // Sinon : Reinitialiser
    }else{
        ReinitialiserResolution() ;
    }
}

// Bouton : Resolution
void MainWindow::on_radioButton_resolution_clicked(){
    if(ui->radioButton_resolution->isChecked()){
        // Desactiver la quantification
        ui->radioButton_quantification->setChecked(false) ;
        ui->horizontalSlider_quantification->setValue(8) ;
        ui->horizontalSlider_quantification->setEnabled(false) ;

        // Initialiser la zone de reglage
        ui->groupBox_interpolation->setEnabled(true) ;
        ui->horizontalSlider_resolution->setValue(0) ;
        ui->radioButton_PPP->setChecked(true) ;
        AffichageResultat(imageOriginale, 1) ;
    // Sinon : Reinitialiser
    }else{
        ui->groupBox_interpolation->setEnabled(false) ;
        ui->horizontalSlider_resolution->setValue(0) ;
        ui->radioButton_PPP->setChecked(true) ;
        AffichageResultat(imageOriginale, 1) ;
    }
}

// Bouton : Pixel le plus proche
void MainWindow::on_radioButton_PPP_clicked(){
    if(ui->radioButton_PPP->isChecked()){
        ui->horizontalSlider_resolution->setValue(0) ;
    }
}

// Bouton : Bilineaire
void MainWindow::on_radioButton_bipolaire_clicked(){
    if(ui->radioButton_bipolaire->isChecked()){
        ui->horizontalSlider_resolution->setValue(0) ;
    }
}

// Resolution
void MainWindow::on_horizontalSlider_resolution_valueChanged(int value){
    // Reduction de resolution
    if(value < 0){
        imageResultat = ImageResolutionReduction(imageOriginale, abs(value)) ;
    // Agrandissement
    }else if(value > 0){
        // Pixel le plus proche
        if(ui->radioButton_PPP->isChecked()){
            imageResultat = InterpolationPPP(imageOriginale, value) ;
        }else if(ui->radioButton_bipolaire->isChecked()){
            imageResultat = InterpolationBilineaire(imageOriginale, value) ;
        }
    }else{
        imageResultat = imageOriginale ;
    }

    // Affichage du resultat
    AffichageResultat(imageResultat, 1) ;
    // Affichage de la nouvelle resolution
    string nbLigne = to_string((int)imageResultat.size().height) ;
    string nbColonne = to_string((int)imageResultat.size().width) ;
    string resolution = "Resolution : [" + nbLigne + " x " + nbColonne + "]" ;
    ui->label_resolutionTraitee->setText(QString::fromStdString(resolution)) ;
}

// Bouton : Quantification
void MainWindow::on_radioButton_quantification_clicked(){
    if(ui->radioButton_quantification->isChecked()){
        // Desactiver le redimensionnement
        ui->radioButton_resolution->setChecked(false) ;
        ui->horizontalSlider_resolution->setValue(0) ;
        ui->groupBox_interpolation->setEnabled(false) ;

        // Initialiser la zone de reglage
        ui->horizontalSlider_quantification->setEnabled(true) ;
        ui->horizontalSlider_quantification->setValue(8) ;
        AffichageResultat(imageOriginale, 1) ;
    // Sinon : Reinitialiser
    }else{
        ui->horizontalSlider_quantification->setEnabled(false) ;
        ui->horizontalSlider_quantification->setValue(8) ;
        AffichageResultat(imageOriginale, 1) ;
    }
}

// Quantification
void MainWindow::on_horizontalSlider_quantification_valueChanged(int value){
    if(ui->radioButton_quantification->isChecked()){
        imageResultat = ImageQuantification(imageOriginale, value) ;

        // Affichage du resultat
        AffichageResultat(imageResultat, 1) ;
    }
}

// -------------Debruitage-------------

// Initialiser
void MainWindow::on_groupBox_debruitage_clicked(){
    AffichageResultat(imageOriginale, 1) ;                      // Image originale
    // Si le box est choisi
    if(ui->groupBox_debruitage->isChecked()){
        // Desactiver les aures fonctionnalites
        ReinitialiserLuminosite() ;             // Luminosite
        ReinitialiserCouleur() ;                // Couleur
        ReinitialiserDetail() ;                 // Details
        ReinitialiserResolution() ;             // Resolution
        ReinitialiserExtraction() ;             // Extraction
        ReinitialiserContour() ;                // Contours
        ReinitialiserSeuillageSegmentation() ;  // Seuillage et segmentation
        ReinitialiserFiltre() ;                 // Filtres
    // Sinon : Reinitialiser
    }else{
        ReinitialiserDebruitage() ;
    }
}

// Filtre moyeneur
void MainWindow::on_radioButton_moyenneur_clicked(){
    if(ui->radioButton_moyenneur->isChecked()){
        imageResultat = ImageFiltrage(imageOriginale, 1) ;
        AffichageResultat(imageResultat, 0) ;
    }
}

// Filtre gaussien
void MainWindow::on_radioButton_gaussien_clicked(){
    if(ui->radioButton_gaussien->isChecked()){
        imageResultat = ImageFiltrage(imageOriginale, 2) ;
        AffichageResultat(imageResultat, 0) ;
    }
}

// Filtre median
void MainWindow::on_radioButton_median_clicked(){
    if(ui->radioButton_median->isChecked()){
        imageResultat = ImageMedian(imageOriginale) ;
        AffichageResultat(imageResultat, 1) ;
    }
}

// Kuwahara-Nagao
void MainWindow::on_radioButton_kuwahara_clicked(){
    imageResultat = ImageKuwahara(imageOriginale) ;
    AffichageResultat(imageResultat, 1) ;
}

// -------------Couleur-------------

// Initialiser
void MainWindow::on_groupBox_couleur_clicked(){
    AffichageResultat(imageOriginale, 1) ;                      // Image originale
    // Si le box est choisi
    if(ui->groupBox_couleur->isChecked()){
        // Desactiver les autres fonctionnalites
        ReinitialiserLuminosite() ;             // Luminosite
        ReinitialiserDetail() ;                 // Details
        ReinitialiserResolution() ;             // Resolution
        ReinitialiserExtraction();              // Extraction
        ReinitialiserContour() ;                // Contours
        ReinitialiserDebruitage() ;             // Debruitage
        ReinitialiserSeuillageSegmentation() ;  // Seuillage et segmentation
        ReinitialiserFiltre() ;                 // Filtres
    // Sinon : Reinitialiser
    }else{
        ReinitialiserCouleur() ;
    }
}

// Bouton : Temperature
void MainWindow::on_radioButton_temperature_clicked(){
    // Si la case est cochee
    if(ui->radioButton_temperature->isChecked()){
        // Reinitialiser les autres sliders
        // Teinte
        ui->horizontalSlider_teinte->setValue(0) ;
        ui->horizontalSlider_teinte->setEnabled(false) ;
        // Saturation
        ui->horizontalSlider_saturation->setValue(0) ;
        ui->horizontalSlider_saturation->setEnabled(false) ;
        // Vividite
        ui->horizontalSlider_vividite->setValue(0) ;
        ui->horizontalSlider_vividite->setEnabled(false) ;

        // Activer le slider
        ui->horizontalSlider_temperature->setEnabled(true) ;
    }
}

// Temperature
void MainWindow::on_horizontalSlider_temperature_valueChanged(int value){
    imageResultat = ImageTemperature(imageOriginale, value) ;
    AffichageResultat(imageResultat, 1);
}

// Bouton : Vividite
void MainWindow::on_radioButton_vividite_clicked(){
    // Si la case est cochee
    if(ui->radioButton_vividite->isChecked()){
        // Reinitialiser les autres sliders
        // Temperature
        ui->horizontalSlider_temperature->setValue(0) ;
        ui->horizontalSlider_temperature->setEnabled(false) ;
        // Saturation
        ui->horizontalSlider_saturation->setValue(0) ;
        ui->horizontalSlider_saturation->setEnabled(false) ;
        // Teinte
        ui->horizontalSlider_teinte->setValue(0) ;
        ui->horizontalSlider_teinte->setEnabled(false) ;

        // Activer le slider
        ui->horizontalSlider_vividite->setEnabled(true) ;
    }
}

// Vividite
void MainWindow::on_horizontalSlider_vividite_valueChanged(int value){
    imageResultat = ImageVividite(imageOriginale, value) ;
    AffichageResultat(imageResultat, 1) ;
}

// Bouton : Teinte
void MainWindow::on_radioButton_teinte_clicked(){
    // Si la case est cochee
    if(ui->radioButton_teinte->isChecked()){
        // Reinitialiser les autres sliders
        // Temperature
        ui->horizontalSlider_temperature->setValue(0) ;
        ui->horizontalSlider_temperature->setEnabled(false) ;
        // Saturation
        ui->horizontalSlider_saturation->setValue(0) ;
        ui->horizontalSlider_saturation->setEnabled(false) ;
        // Vividite
        ui->horizontalSlider_vividite->setValue(0) ;
        ui->horizontalSlider_vividite->setEnabled(false) ;

        // Activer le slider
        ui->horizontalSlider_teinte->setEnabled(true) ;
    }
}

// Teinte
void MainWindow::on_horizontalSlider_teinte_valueChanged(int value){
    imageResultat = ImageTeinte(imageOriginale, value) ;
    AffichageResultat(imageResultat, 1) ;
}

// Bouton : Saturation
void MainWindow::on_radioButton_saturation_clicked(){
    // Si la case est cochee
    if(ui->radioButton_saturation->isChecked()){
        // Reinitialiser les autres sliders
        // Teinte
        ui->horizontalSlider_teinte->setValue(0) ;
        ui->horizontalSlider_teinte->setEnabled(false) ;
        // Temperature
        ui->horizontalSlider_temperature->setValue(0) ;
        ui->horizontalSlider_temperature->setEnabled(false) ;
        // Vividite
        ui->horizontalSlider_vividite->setValue(0) ;
        ui->horizontalSlider_vividite->setEnabled(false) ;

        // Activer le slider
        ui->horizontalSlider_saturation->setEnabled(true) ;
        ui->horizontalSlider_saturation->setValue(0) ;
    }
}

// Saturation
void MainWindow::on_horizontalSlider_saturation_valueChanged(int value){
    imwrite("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png", imageOriginale) ;
    imageResultat = ImageSaturation(imread("/home/vm/M2SIA-projet-QT/DATA/Temp/imageOriginale.png"), value) ;
    AffichageResultat(imageResultat, 1) ;
}

// -------------Autres-------------

// Generer les icones
void MainWindow::GenererIcone(){
    // Preparer les icones pour l'espace de travail
    //string cheminExemple = "/home/vm/M2SIA-projet-QT/DATA/Images/rgbexample.jpeg" ;
    //Mat exemple = imread(cheminExemple) ;
    //imwrite("/home/vm/M2SIA-projet-QT/DATA/icon/exempleMono.png", ImageMonochrome(exemple)) ;
    //imwrite("/home/vm/M2SIA-projet-QT/DATA/icon/exempleNeg.png", ImageInversement(exemple)) ;
    //imwrite("/home/vm/M2SIA-projet-QT/DATA/icon/exempleR.png", ImageSegmentation(exemple, {255,255,0})) ;
    //imwrite("/home/vm/M2SIA-projet-QT/DATA/icon/exempleV.png", ImageSegmentation(exemple, {255,0,255})) ;
    //imwrite("/home/vm/M2SIA-projet-QT/DATA/icon/exempleB.png", ImageSegmentation(exemple, {0,255,255})) ;
    //imwrite("/home/vm/M2SIA-projet-QT/DATA/icon/exempleJ.png", ImageJaune(exemple)) ;
    //imwrite("/home/vm/M2SIA-projet-QT/DATA/icon/exempleC.png", ImageCyan(exemple)) ;
    //imwrite("/home/vm/M2SIA-projet-QT/DATA/icon/exempleM.png", ImageMagenta(exemple)) ;
    //imwrite("/home/vm/M2SIA-projet-QT/DATA/icon/exempleSepia.png", ImageSepia(exemple)) ;
    //imwrite("/home/vm/M2SIA-projet-QT/DATA/icon/exempleRGB.png", ImageRGB(exemple)) ;

    // Dimensions des fenetre exemplaires
    int hauteur = ui->label_mono->height() ;    // Hauteur de la fenetre d'affichage
    int largeur = ui->label_mono->width() ;     // Largeur de la fenetre d'affichage
    // Originale
    QPixmap exempleOriginale("/home/vm/M2SIA-projet-QT/DATA/icon/rgbexample.jpeg") ;
    ui->label_original->setPixmap(exempleOriginale.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_original->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    // Mono
    QPixmap exempleMono("/home/vm/M2SIA-projet-QT/DATA/icon/exempleMono.png") ;
    ui->label_mono->setPixmap(exempleMono.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_mono->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    // Sepia
    QPixmap exempleS("/home/vm/M2SIA-projet-QT/DATA/icon/exempleSepia.png") ;
    ui->label_sepia->setPixmap(exempleS.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_sepia->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    // Inversement
    QPixmap exempleNeg("/home/vm/M2SIA-projet-QT/DATA/icon/exempleNeg.png") ;
    ui->label_negatif->setPixmap(exempleNeg.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_negatif->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    // Rouge
    QPixmap exempleR("/home/vm/M2SIA-projet-QT/DATA/icon/exempleR.png") ;
    ui->label_rouge->setPixmap(exempleR.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_rouge->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    // Vert
    QPixmap exempleV("/home/vm/M2SIA-projet-QT/DATA/icon/exempleV.png") ;
    ui->label_vert->setPixmap(exempleV.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_vert->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    // Bleu
    QPixmap exempleB("/home/vm/M2SIA-projet-QT/DATA/icon/exempleB.png") ;
    ui->label_bleu->setPixmap(exempleB.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_bleu->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    // Jaune
    QPixmap exempleJ("/home/vm/M2SIA-projet-QT/DATA/icon/exempleJ.png") ;
    ui->label_jaune->setPixmap(exempleJ.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_jaune->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    // Cyan
    QPixmap exempleC("/home/vm/M2SIA-projet-QT/DATA/icon/exempleC.png") ;
    ui->label_cyan->setPixmap(exempleC.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_cyan->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    // Magenta
    QPixmap exempleM("/home/vm/M2SIA-projet-QT/DATA/icon/exempleM.png") ;
    ui->label_magenta->setPixmap(exempleM.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_magenta->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    // RGB
    QPixmap exempleRGB("/home/vm/M2SIA-projet-QT/DATA/icon/exempleRGB.png") ;
    ui->label_rgb->setPixmap(exempleRGB.scaled(largeur, hauteur, Qt::KeepAspectRatio));
    ui->label_rgb->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;

    // Icones zoom
    int hauteurZoom = ui->label_Zoom->height() ;    // Hauteur de la fenetre d'affichage
    int largeurZoom = ui->label_Zoom->width() ;     // Largeur de la fenetre d'affichage
    QPixmap zoom("/home/vm/M2SIA-projet-QT/DATA/icon/zoom.png") ;
    ui->label_Zoom->setPixmap(zoom.scaled(largeurZoom, hauteurZoom, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->label_Zoom->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    ui->label_ZoomNonModifiable->setPixmap(zoom.scaled(largeurZoom, hauteurZoom, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->label_ZoomNonModifiable->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    ui->label_zoomImageOriginale->setPixmap(zoom.scaled(largeurZoom, hauteurZoom, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->label_zoomImageOriginale->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
    ui->label_zoomImageTraitee->setPixmap(zoom.scaled(largeurZoom, hauteurZoom, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->label_zoomImageTraitee->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
}

// Afficher l'image resultante apres un traitement avec inversement les canaux de couleur
void MainWindow::AffichageResultat(const Mat image, const int choix){
    // Declaration des variables
    Mat imageAffichage = image ;

    // Histogramme de l'image resultante
    histoImageResultat = Normalisation(plot_histogram(imageAffichage), 255) ;

    // Echanger les composantes suivant la norme du QT
    if(choix != 0){
        imageAffichage = ImageBGRRGB(imageAffichage) ;
    }
    // Convertir en format QT
    QImage imageResultatQT = QImage((uchar*) imageAffichage.data, imageAffichage.cols, imageAffichage.rows, imageAffichage.step, QImage::Format_RGB888) ;
    QImage histoImageResultatQT = QImage((uchar*) histoImageResultat.data, histoImageResultat.cols, histoImageResultat.rows, histoImageResultat.step, QImage::Format_RGB888) ;

    // Affichage : Image resultante
    QGraphicsScene* scene = new QGraphicsScene() ;
    scene->addPixmap(QPixmap::fromImage(imageResultatQT)) ;
    ui->graphicsView_imageTraitee->setScene(scene) ;
    ui->graphicsView_imageTraitee->show() ;
    ui->graphicsView_imageTraitee->fitInView(scene->sceneRect(), Qt::KeepAspectRatio) ;
    // Affichage : Histogramme
    QPixmap histogrammeTraitee(QPixmap::fromImage(histoImageResultatQT)) ;
    int hauteur = ui->label_histogrammeImageTraitee->height() ;       // Hauteur de la fenetre d'affichage
    int largeur = ui->label_histogrammeImageTraitee->width() ;        // Largeur de la fenetre d'affichage
    ui->label_histogrammeImageTraitee->setPixmap(histogrammeTraitee.scaled(largeur, hauteur, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    ui->label_histogrammeImageTraitee->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter) ;
}

// Messages d'aide
void MainWindow::AfficherMessageAide(){
    // Box : Luminosite
    AfficherMessageAideLuminosite() ;
    // Box : Couleur
    AfficherMessageAideCouleur() ;
    // Box : Resolution
    AfficherMessageAideResolution() ;
    // Box : Details
    AfficherMessageAideDetail() ;
    // Box : Extraction
    AfficherMessageAideExtraction() ;
    // Box : Contours
    AfficherMessageAideContour() ;
    // Box : Debruitage
    AfficherMessageAideDebruitage() ;
    // Box : Seuillage et segmentation
    AfficherMessageAideSeuillageSegmentation() ;
    // Box : Filtres
    AfficherMessageAideFiltre() ;

    // Zone d'affichage
    // Image de départ
    ui->groupBox_imageOriginale->setToolTip("Image de départ :\nContenu, résolution, histogramme") ;
    ui->graphicsView_imageOriginale->setToolTip("Image de départ") ;
    ui->label_resolutionOriginale->setToolTip("Résolution de l'image de départ") ;
    ui->label_zoomImageOriginale->setToolTip("Agrandissement de l'image de départ") ;
    ui->horizontalSlider_imageOriginale->setToolTip("Tirer vers la droite pour agrandir l'image") ;
    ui->label_histogrammeImageOriginale->setToolTip("Histogramme de l'image de départ") ;

    // Image traitée
    ui->groupBox_imageTraitee->setToolTip("Image de départ :\nContenu, résolution, histogramme") ;
    ui->graphicsView_imageTraitee->setToolTip("Image traitée") ;
    ui->label_resolutionTraitee->setToolTip("Résolution de l'image traitée") ;
    ui->label_zoomImageTraitee->setToolTip("Agrandissement de l'image traitée") ;
    ui->horizontalSlider_imageTraitee->setToolTip("Tirer vers la droite pour agrandir l'image") ;
    ui->label_histogrammeImageTraitee->setToolTip("Histogramme de l'image traitée") ;

    // Boutons
    ui->pushButton_retour->setToolTip("Retourner à la page précédente (choisir l'image à traiter)") ;
    ui->pushButton_traitementAppliquer->setToolTip("Appliquer le traitement actuel :\nL'image de départ sera remplacé par l'image traitée en cours d'affichage") ;
    ui->pushButton_traitementReinitialiser->setToolTip("Réinitialiser l'image de départ par l'image choisie dans la page précédente") ;
    ui->pushButton_traitementSauvegarder->setToolTip("Sauvegarder l'image traitée") ;
}

// Messages d'aide : Luminosite
void MainWindow::AfficherMessageAideLuminosite(){
    ui->groupBox_correction->setToolTip("Modifier les paramètres liés à la luminosité de l'image :\nIntensité, contraste, ombres hautes lumières") ;
    // Intensité
    ui->radioButton_luminosite->setToolTip("Modifier l'intensité lumineuse de l'image") ;
    ui->horizontalSlider_luminosite->setToolTip("Tirer à gauche : Atténuer l'intensité lumineuse\nTirer à droite : Augmenter l'intensité lumineuse") ;
    // Contraste
    ui->radioButton_contraste->setToolTip("Modifier le contraste de l'image") ;
    ui->horizontalSlider_contraste->setToolTip("Tirer à gauche : Atténuer le contraste\nTirer à droite : Augmenter le contraste") ;
    // Ombres
    ui->radioButton_ombre->setToolTip("Modifier les ombres (shadows) de l'image") ;
    ui->horizontalSlider_ombre->setToolTip("Tirer à gauche : Atténuer les ombres\nTirer à droite : Augmenter les ombres") ;
    // Hautes lumières
    ui->radioButton_brillance->setToolTip("Modifier les hautes lumières (highlights) de l'image") ;
    ui->horizontalSlider_brillance->setToolTip("Tirer à gauche : Atténuer les hautes lumières\nTirer à droite : Augmenter les hautes lumières") ;
}

// Messages d'aide : Couleur
void MainWindow::AfficherMessageAideCouleur(){
    ui->groupBox_couleur->setToolTip("Modifier les paramètres liés aux couleurs de l'image :\nTempérature, vividité, teinte, saturation") ;
    // Température
    ui->radioButton_temperature->setToolTip("Modifier la température de l'image") ;
    ui->horizontalSlider_temperature->setToolTip("Tirer à gauche : Couleur froide\nTirer à droite : Couleur chaude") ;
    // Vividité
    ui->radioButton_vividite->setToolTip("Modifier la vividité de l'image") ;
    ui->horizontalSlider_vividite->setToolTip("Tirer à gauche : Atténuer la vividité\nTirer à droite : Augmenter la vividité") ;
    // Teinte
    ui->radioButton_teinte->setToolTip("Modifier la teinte de l'image") ;
    // Saturation
    ui->radioButton_saturation->setToolTip("Modifier la saturation de l'image") ;
    ui->horizontalSlider_saturation->setToolTip("Tirer à gauche : Atténuer la saturation\nTirer à droite : Augmenter la saturation") ;
}

// Messages d'aide : Details
void MainWindow::AfficherMessageAideDetail(){
    ui->groupBox_details->setToolTip("Modifier la nettete de l'image\nBruiter l'image (bruit uniforme)") ;
    // Nettete
    ui->radioButton_nettete->setToolTip("Modifier la netteté de l'image") ;
    ui->horizontalSlider_nettete->setToolTip("Tirer à gauche : Lisser l'image\nTirer à droite : Réhausser les contours dans l'image") ;
    // Bruitage
    ui->radioButton_bruitage->setToolTip("Ajouter du bruit additif (bruit uniforme) à l'image") ;
    ui->horizontalSlider_Bruitage->setToolTip("Tirer à droite : Augmenter l'intensité du bruit") ;
}

// Messages d'aide : Resolution
void MainWindow::AfficherMessageAideResolution(){
    ui->groupBox_resolutionQuantification->setToolTip("Modifier la resolution & Quantification") ;
    // Resolution
    ui->radioButton_resolution->setToolTip("Redimensionner l'image") ;
    ui->radioButton_PPP->setToolTip("Interpolation par pixel le plus proche") ;
    ui->radioButton_bipolaire->setToolTip("Interpolation bilinéaire") ;
    ui->horizontalSlider_resolution->setToolTip("Tirer à gauche : Dininuer a résolution\nTirer à droite : Augmenter la résolution (interpolation)") ;
    // Quantification
    ui->radioButton_quantification->setToolTip("Quantification :\nMax : 8 bits\nMin : 1 bit") ;
    ui->horizontalSlider_quantification->setToolTip("Tirer à gauche : Atténuer le nombre de nuances") ;
}

// Messages d'aide : Extraction
void MainWindow::AfficherMessageAideExtraction(){
    ui->groupBox_extractionRVB->setToolTip("Extraire une composante de couleur de l'image (rouge, verte, bleue)") ;
    // Canal rouge
    ui->radioButton_extractionR->setToolTip("Extraction de la composante rouge de l'image") ;
    // Canal vert
    ui->radioButton_extractionV->setToolTip("Extraction de la composante verte de l'image") ;
    // Canal bleu
    ui->radioButton_extractionB->setToolTip("Extraction de la composante bleue de l'image") ;
}

// Messages d'aide : Contours
void MainWindow::MainWindow::AfficherMessageAideContour(){
    ui->groupBox_contours->setToolTip("Détecter les contours de l'image par différents méthodes :\nFiltres gradients, filtre laplacien, transformée de Hough") ;
    // Filtrage de type gradient
    ui->radioButton_contoursGradient->setToolTip("Détection de contours par la norme du gradient") ;
    // Filtrage de type laplacien
    ui->radioButton_contoursLaplacien->setToolTip("Détection de contours par filtre laplacien") ;
    // Transformée de Hough
    ui->radioButton_contoursHough->setToolTip("Détection de contours par la transformée de Hough") ;
}

// Messages d'aide : Debruitage
void MainWindow::AfficherMessageAideDebruitage(){
    ui->groupBox_debruitage->setToolTip("Débruiter l'image par différents types de filtre :\nMoyenneur, gaussien (filtres linéaires)\nMédian, Kuwahara-Nagao (non-linéaire)") ;
    // Filtres lineaires
    ui->radioButton_moyenneur->setToolTip("Filtre moyenneur (linéaire)") ;
    ui->radioButton_gaussien->setToolTip("Filtre gaussien (linéaire)") ;
    // Filtres non lineaires
    ui->radioButton_median->setToolTip("Filtre médian (non linéaire)") ;
    ui->radioButton_kuwahara->setToolTip("Filtre de Kuwahara-Nagao (non linéaire)") ;
}

// Messages d'aide : Seuillage et segmentation
void MainWindow::AfficherMessageAideSeuillageSegmentation(){
    ui->groupBox_seuillageSegmentation->setToolTip("Seuiller ou segmenter l'image") ;
    ui->radioButton_seuillage->setToolTip("Seuillage simple ou à hystérésis") ;
    ui->radioButton_segmentation->setToolTip("Segmentation par seuillage simple ou à hystérésis") ;
    ui->radioButton_seuillageSimple->setToolTip("Seuillage simple (conserver les valeurs supérieures au seuil)") ;
    ui->radioButton_seuillageHysteresis->setToolTip("Seuillage à hystérésis (conserver les valeurs supérieures au seuil bas et inférieures au seuil haut)") ;
    // Seuils bas
    ui->groupBox_seuilBas->setToolTip("Seuils (rouge, vert, bleu) du seuillage simple\nSeuils (rouge, vert, bleu) bas du seuillage à hystérésis\n"
                                      "Pour une image en niveau de gris, la valeur du seuil est la même pour les trois composantes") ;
    ui->verticalSlider_seuilBasR_2->setToolTip("Seuil de la composante rouge") ;
    ui->verticalSlider_seuilBasV_2->setToolTip("Seuil de la composante verte") ;
    ui->verticalSlider_seuilBasB_2->setToolTip("Seuil de la composante bleue") ;
    ui->pushButton_seuilBasR->setToolTip("Réinitialiser le seuil de la composante rouge à 0") ;
    ui->pushButton_seuilBasV->setToolTip("Réinitialiser le seuil de la composante verte à 0") ;
    ui->pushButton_seuilBasB->setToolTip("Réinitialiser le seuil de la composante bleue à 0") ;
    // Seuils hauts
    ui->groupBox_seuilHaut->setToolTip("Seuils hauts(rouge, vert, bleu) du seuillage à hystérésis\nPour une image en niveau de gris, la valeur du seuil est la même pour les trois composantes") ;
    ui->verticalSlider_seuilHautR_2->setToolTip("Seuil de la composante rouge") ;
    ui->verticalSlider_seuilHautV_2->setToolTip("Seuil de la composante verte") ;
    ui->verticalSlider_seuilHautB_2->setToolTip("Seuil de la composante bleue") ;
    ui->pushButton_seuilHautR->setToolTip("Réinitialiser le seuil de la composante rouge à 256") ;
    ui->pushButton_seuilHautV->setToolTip("Réinitialiser le seuil de la composante verte à 256") ;
    ui->pushButton_seuilHautB->setToolTip("Réinitialiser le seuil de la composante bleue à 256") ;
}

// Messages d'aide : Filtres
void MainWindow::AfficherMessageAideFiltre(){
    ui->groupBox_filtres->setToolTip("Appliquer les filtres de couleurs") ;
    // Niveau de gris
    ui->radioButton_niveauGris->setToolTip("Niveau de gris") ;
    ui->label_mono->setToolTip("Niveau de gris") ;
    // Inversement
    ui->radioButton_inversement->setToolTip("Inversement des intensités lumineuses");
    ui->label_negatif->setToolTip("Inversement des intensités lumineuses") ;
    // Sepia
    ui->radioButton_sepia->setToolTip("Sepia") ;
    ui->label_sepia->setToolTip("Sepia") ;
    // Rouge
    ui->radioButton_rouge->setToolTip("Rouge") ;
    ui->label_rouge->setToolTip("Rouge") ;
    // Vert
    ui->radioButton_vert->setToolTip("Vert") ;
    ui->label_vert->setToolTip("Vert") ;
    // Bleu
    ui->radioButton_bleu->setToolTip("Bleu") ;
    ui->label_bleu->setToolTip("Bleu") ;
    // RGB
    ui->radioButton_rgb->setToolTip("Couleur extrême RGB") ;
    ui->label_rgb->setToolTip("Couleur extrême RGB") ;
    // Cyan
    ui->radioButton_cyan->setToolTip("Cyan") ;
    ui->label_cyan->setToolTip("Cyan") ;
    // Magenta
    ui->radioButton_magenta->setToolTip("Magenta") ;
    ui->label_magenta->setToolTip("Magenta") ;
    // Jaune
    ui->radioButton_jaune->setToolTip("Jaune") ;
    ui->label_jaune->setToolTip("Jaune") ;
}

// Reinitialisation generale
void MainWindow::Reinitialiser(){
    ReinitialiserLuminosite() ;
    ReinitialiserLuminosite() ;
    ReinitialiserResolution() ;
    ReinitialiserDetail() ;
    ReinitialiserExtraction() ;
    ReinitialiserContour() ;
    ReinitialiserDebruitage() ;
    ReinitialiserSeuillageSegmentation() ;
    ReinitialiserFiltre() ;
    AffichageResultat(imageOriginale, 1) ;
}

// Reinitialiser : Box Luminosite
void MainWindow::ReinitialiserLuminosite(){
    ui->radioButton_luminosite->setChecked(false) ;
    ui->radioButton_contraste->setChecked(false) ;
    ui->radioButton_brillance->setChecked(false) ;
    ui->radioButton_ombre->setChecked(false) ;
    ui->horizontalSlider_luminosite->setValue(0) ;
    ui->horizontalSlider_contraste->setValue(0) ;
    ui->horizontalSlider_brillance->setValue(0) ;
    ui->horizontalSlider_ombre->setValue(0) ;
    ui->groupBox_correction->setChecked(false) ;
}

// Reinitialiser : Box Couleur
void MainWindow::ReinitialiserCouleur(){
    ui->horizontalSlider_temperature->setValue(0) ;
    ui->horizontalSlider_vividite->setValue(0) ;
    ui->horizontalSlider_teinte->setValue(0) ;
    ui->horizontalSlider_saturation->setValue(0) ;
    ui->radioButton_temperature->setChecked(false) ;
    ui->radioButton_vividite->setChecked(false) ;
    ui->radioButton_teinte->setChecked(false) ;
    ui->radioButton_saturation->setChecked(false) ;
    ui->groupBox_couleur->setChecked(false) ;
}

// Reinitialiser : Box Resolution
void MainWindow::ReinitialiserResolution(){
    ui->radioButton_resolution->setChecked(false) ;
    ui->radioButton_PPP->setChecked(false) ;
    ui->radioButton_bipolaire->setChecked(false) ;
    ui->radioButton_quantification->setChecked(false) ;
    ui->horizontalSlider_resolution->setValue(0) ;
    ui->horizontalSlider_quantification->setValue(8) ;
    ui->groupBox_resolutionQuantification->setChecked(false) ;
}

// Reinitialiser : Box Details
void MainWindow::ReinitialiserDetail(){
    ui->radioButton_nettete->setChecked(false) ;
    ui->radioButton_bruitage->setChecked(false) ;
    ui->horizontalSlider_nettete->setValue(0) ;
    ui->horizontalSlider_Bruitage->setValue(0) ;
    ui->groupBox_details->setChecked(false) ;
}

// Reinitialiser : Box Extraction
void MainWindow::ReinitialiserExtraction(){
    ui->radioButton_extractionR->setChecked(false) ;
    ui->radioButton_extractionV->setChecked(false) ;
    ui->radioButton_extractionB->setChecked(false) ;
    ui->groupBox_extractionRVB->setChecked(false) ;
}

// Reinitialiser : Box Contours
void MainWindow::ReinitialiserContour(){
    ui->radioButton_contoursGradient->setChecked(false) ;
    ui->radioButton_contoursLaplacien->setChecked(false) ;
    ui->radioButton_contoursHough->setChecked(false) ;
    ui->groupBox_contours->setChecked(false) ;
}

// Reinitialiser : Box Debruitage
void MainWindow::ReinitialiserDebruitage(){
    ui->radioButton_moyenneur->setChecked(false) ;
    ui->radioButton_gaussien->setChecked(false) ;
    ui->radioButton_median->setChecked(false) ;
    ui->radioButton_kuwahara->setChecked(false) ;
    ui->groupBox_debruitage->setChecked(false) ;
}

// Reinitialiser : Box Seuillage et segmentation
void MainWindow::ReinitialiserSeuillageSegmentation(){
    ui->radioButton_seuillage->setChecked(false) ;
    ui->radioButton_seuillageSimple->setChecked(false) ;
    ui->radioButton_segmentation->setChecked(false) ;
    ui->radioButton_seuillageHysteresis->setChecked(false) ;
    ui->verticalSlider_seuilBasB_2->setValue(0) ;
    ui->verticalSlider_seuilBasR_2->setValue(0) ;
    ui->verticalSlider_seuilBasV_2->setValue(0) ;
    ui->verticalSlider_seuilHautB_2->setValue(256) ;
    ui->verticalSlider_seuilHautR_2->setValue(256) ;
    ui->verticalSlider_seuilHautV_2->setValue(256) ;
    ui->groupBox_seuillageSegmentation->setChecked(false) ;
}

// Reinitialiser : Box Filtres
void MainWindow::ReinitialiserFiltre(){
    ui->radioButton_originale->setChecked(false) ;
    ui->radioButton_niveauGris->setChecked(false) ;
    ui->radioButton_sepia->setChecked(false) ;
    ui->radioButton_inversement->setChecked(false) ;
    ui->radioButton_rouge->setChecked(false) ;
    ui->radioButton_vert->setChecked(false) ;
    ui->radioButton_bleu->setChecked(false) ;
    ui->radioButton_rgb->setChecked(false) ;
    ui->radioButton_cyan->setChecked(false) ;
    ui->radioButton_magenta->setChecked(false) ;
    ui->radioButton_jaune->setChecked(false) ;
    ui->radioButton_cmj->setChecked(false) ;
    ui->groupBox_filtres->setChecked(false) ;
}





// Transformee de Fourier
void MainWindow::on_radioButton_fourier_clicked(){
    imageResultat = Normalisation(MonoCouleur(ImageFourier(imageOriginale)), 255) ;
    AffichageResultat(imageResultat, 0) ;
}
