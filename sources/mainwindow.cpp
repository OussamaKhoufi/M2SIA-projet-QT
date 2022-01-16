#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

AppMainWindow::AppMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppMainWindow)
{
    ui->setupUi(this);
    connect(ui->tableWidgetBiblio, SIGNAL(cellClicked(int, int)), this,SLOT(on_tableBiblioRowClicked(int , int)));          // connecter la selection d'une ligne avec la selection d'un numero d'image
    connect(ui->comboBoxTrier,SIGNAL(currentIndexChanged(int)),this,SLOT(on_comboBoxTrierIndexChanged(int)));               // connecter la selection d'un critère de tri avec le tri
    connect(ui->comboBoxCritereCout,SIGNAL(activated(int)),this,SLOT(on_comboBoxCritereCoutIndexChanged(int)));             // connecter la selection d'un critère cout de creation de sous liste avec la creation d'une sous liste
    connect(ui->comboBoxCritereDateAjout,SIGNAL(activated(int)),this,SLOT(on_comboBoxCritereDateAjoutIndexChanged(int)));   // connecter la selection d'un critère date d'ajout de creation de sous liste avec la creation d'une sous liste
}

AppMainWindow::~AppMainWindow()
{
    delete ui;
}

void AppMainWindow::on_pushButtonIdentifier_clicked()
{
    QString userMdp = ui->lineEditMdp->text();
    QStringRef codeDroitAcces(&userMdp, 4, 2);
    QFile userIdFile("/home/vm/M2SIA-projet-QT/DATA/idUsers.txt");
    bool idFound=false;

   // tester l'ouverture du fichier
    if(!userIdFile.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::information(this,"error",userIdFile.errorString());
    }

    QTextStream in(&userIdFile);
    QString line = in.readLine();

    while (!line.isNull())
    {
        if (userMdp==line){
            idFound = true;
            break;
        }
        line = in.readLine();
    }
    if (idFound){
        if (codeDroitAcces=="11"){
            _droitAcces = true;
        }else if (codeDroitAcces=="00"){
            _droitAcces = false;
        }
        //QMessageBox::information(this,"Identification","Identification Réussite !");
        if (_droitAcces) {
            ui->statusbar->showMessage("Utilisateur de Niveau 2.");
        } else {
            ui->statusbar->showMessage("Utilisateur de Niveau 1.");
        }
        ui->stackedWidget->setCurrentIndex(1);
    }else {
        QMessageBox::information(this,"Identification","Le mot de passe est incorrect.");
    }
    // Mettre à jour l'application suivant le niveau de l'utilisateur
    ui->pushButtonCreerBiblio->setEnabled(_droitAcces);
    ui->pushButtonAjouterImage->setEnabled(_droitAcces);
    ui->pushButtonSauvegarder->setEnabled(_droitAcces);
    ui->pushButtonSauvegarderSousListe->setEnabled(_droitAcces);





}

void AppMainWindow::on_pushButtonQuitter_clicked()
{
    qApp->quit();
}

void AppMainWindow::on_pushButtonChargerBiblio_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Charger la bibliothèque","/home/vm/M2SIA-projet-QT/DATA/Bibliothèques","*.json"); // Ouvrir une fenetre pour que l'utilisateur choisisse un fichier .json
    QFile fileBiblio(fileName);
    // test sur l'ouverture du fichier
    if(!fileBiblio.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this,"error",fileBiblio.errorString());
    }else {
        // Chargement de la bibliothèque
        _objBiblio = Bibliotheque(fileName.toStdString());                                 // Chargement de la bibliotheque : construction d'un objet de classe bibliothèque à partir du fichier json choisi
        _objBiblio.majBiblioSuivantDroitAcces(_droitAcces);                                // mettre à jour l'objet bibliotheque suivant le niveau de l'utilisateur
        updateTableWidgetBiblio();                                                         // mettre à jour la table des descripteurs de la bibliotheque
        ui->stackedWidget->setCurrentIndex(2);                                             // Aller au Menu Bibliothèque (page 2)
        // extraire le nom de la bibliotheque du chemin d acces du fichier .json
        QString biblioName;                                                                // Nom de la bibliothèque
        int i=6;
        do {
            biblioName.push_front(fileName[fileName.length()-i]);
            i++;
        }while(fileName[fileName.length()-i]!='/');
        ui->labelBiblioName->setText(biblioName);
    }

}


void AppMainWindow::on_pushButtonRetourIdentification_clicked()
{
    ui->statusbar->showMessage("");                     // Vider le message de la statusbar
    ui->lineEditMdp->clear();                           // Vider le champ du mot de passe
    ui->stackedWidget->setCurrentIndex(0);              // Retour au Menu Identification (page 0)
}

void AppMainWindow::updateTableWidgetBiblio() {
    Json::Value biblio = _objBiblio.getBilbiotheque() ;        // Objet Json
    ui->tableWidgetBiblio->setRowCount(biblio["nbImages"].asInt());           // Mettre à jour le nombre de lignes du tableWidgetBiblio suivant le Nombre d'images existantes dans la bibliotheque chargée
    for (int i = 0 ; i < ui->tableWidgetBiblio->rowCount() ; i++)
    {
        QTableWidgetItem *item ;
        for (int j = 0 ; j < ui->tableWidgetBiblio->columnCount() ; j++)
        {
            item = new QTableWidgetItem;
            if (j==0){item->setText(QString::fromStdString((biblio["images"][i]["titre"].asString())));}
            if (j==1){item->setText(QString::fromStdString((biblio["images"][i]["cout"].asString())));}
            if (j==2){item->setText(QString::fromStdString((biblio["images"][i]["numero"].asString())));}
            if (j==3){item->setText(QString::fromStdString((biblio["images"][i]["source"].asString())));}
            if (j==4){item->setText(QString::fromStdString((biblio["images"][i]["dateCreation"].asString())));}
            if (j==5){item->setText(QString::fromStdString((biblio["images"][i]["dateAjout"].asString())));}
            if (j==6){item->setText(QString::fromStdString((biblio["images"][i]["acces"].asString())));}
            ui->tableWidgetBiblio->setItem(i,j,item);
        }
    }
}

void AppMainWindow::updateTableWidgetSousListeBiblio(Json::Value biblio) {
    ui->tableWidgetSousListeBiblio->setRowCount(biblio["nbImages"].asInt());           // Mettre à jour le nombre de lignes du tableWidgetBiblio suivant le Nombre d'images existantes dans la bibliotheque chargée
    for (int i = 0 ; i < ui->tableWidgetSousListeBiblio->rowCount() ; i++)
    {
        QTableWidgetItem *item ;
        for (int j = 0 ; j < ui->tableWidgetSousListeBiblio->columnCount() ; j++)
        {
            item = new QTableWidgetItem;
            if (j==0){item->setText(QString::fromStdString((biblio["images"][i]["titre"].asString())));}
            if (j==1){item->setText(QString::fromStdString((biblio["images"][i]["cout"].asString())));}
            if (j==2){item->setText(QString::fromStdString((biblio["images"][i]["numero"].asString())));}
            if (j==3){item->setText(QString::fromStdString((biblio["images"][i]["source"].asString())));}
            if (j==4){item->setText(QString::fromStdString((biblio["images"][i]["dateCreation"].asString())));}
            if (j==5){item->setText(QString::fromStdString((biblio["images"][i]["dateAjout"].asString())));}
            if (j==6){item->setText(QString::fromStdString((biblio["images"][i]["acces"].asString())));}
            ui->tableWidgetSousListeBiblio->setItem(i,j,item);
        }
    }
}

void AppMainWindow::on_pushButtonSauvegarder_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Sauvegarder bibliothèque d'images"), "", tr("*.json"));
    //QMessageBox::information(this,"Sauvegarge bibliothèque",fileName);
    if (!fileName.isEmpty()){
        string fileNameStr = fileName.toStdString();
        VerifierExtension(fileNameStr);
        _objBiblio.Sauvegarder(fileNameStr);
    }
}


void AppMainWindow::on_tableBiblioRowClicked(int row, int ){
    ui->pushButtonSupprimerImage->setEnabled(_droitAcces);
    ui->pushButtonOuvrirImage->setEnabled(_droitAcces);
    QTableWidgetItem *item = ui->tableWidgetBiblio->item(row,2);
    _numImageSelected = item->text().toInt();
}

void AppMainWindow::on_pushButtonSupprimerImage_clicked()
{
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Supprression de l'image", "Etes-vous sûr de vouloir supprimer cette image?",QMessageBox::Yes | QMessageBox::No);
      if (reply == QMessageBox::Yes) {
          _objBiblio.SupprimerImage(_numImageSelected);
          updateTableWidgetBiblio();
      }
}

void AppMainWindow::on_pushButtonRetourMenuPrincipal_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);              // Retour au Menu Principal (page 1)
}

void AppMainWindow::on_lineEditMdp_returnPressed()
{
    emit ui->pushButtonIdentifier->click();            // emettre signal click du pushButtonIdentifier
}

void AppMainWindow::on_comboBoxTrierIndexChanged(int index){
    _objBiblio.Trier(index);
    updateTableWidgetBiblio();
}

void AppMainWindow::on_comboBoxCritereCoutIndexChanged(int index){
    ui->comboBoxCritereDateAjout->setCurrentIndex(0); // Reinitialiser le critere cout
    // Initialisation de la sous liste bibliothèque
    _objSousListeBiblio=Bibliotheque(_objBiblio.getBilbiotheque());
    Json::Value sousListeJson;

    if (index==5){
        sousListeJson = _objSousListeBiblio.ConstruireAfficherSousListeCout(ui->doubleSpinBoxMin->value(),ui->doubleSpinBoxMax->value());
    }else{
    sousListeJson = _objSousListeBiblio.ConstruireAfficherSousListeCout(index);
    }
    updateTableWidgetSousListeBiblio(sousListeJson);
    // Metre à jour l'objet _objSousListeBiblio
    _objSousListeBiblio = Bibliotheque(sousListeJson);
}

void AppMainWindow::on_comboBoxCritereDateAjoutIndexChanged(int index){
    ui->comboBoxCritereCout->setCurrentIndex(0); // Reinitialiser le critere cout
    // Initialisation de la sous liste bibliothèque
    _objSousListeBiblio=Bibliotheque(_objBiblio.getBilbiotheque());
    Json::Value sousListeJson;

    sousListeJson = _objSousListeBiblio.ConstruireAfficherSousListeDateAjout(index);
    updateTableWidgetSousListeBiblio(sousListeJson);
    // Metre à jour l'objet _objSousListeBiblio
    _objSousListeBiblio = Bibliotheque(sousListeJson);
}


void AppMainWindow::on_pushButtonAjouterImage_clicked()
{

            QString fileName = QFileDialog::getOpenFileName(this,tr("Choisir une image à ajouter"), "/home/vm/M2SIA-projet-QT/DATA/Bibliothèques" ,tr("Fichiers Images (*.png *.jpg *.bmp *.pgm *.jpeg *.tiff)"));
            if (!fileName.isEmpty()){
                _newImageFileName = fileName.toStdString();
                QPixmap pix(fileName);
                ui->labelImageAjoutee->setStyleSheet("image:url("+fileName+");");
                ui->labelImageAjoutee->setPixmap(pix.scaled(ui->labelImageAjoutee->width(),ui->labelImageAjoutee->height(),Qt::KeepAspectRatio));
                ui->labelImageAjoutee->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->stackedWidget->setCurrentIndex(3);          // Aller au menu Ajout Image
            }

}

void AppMainWindow::on_pushButtonAjoutImageAnnuler_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);          // Aller au menu bibliothèque
}


void AppMainWindow::on_pushButtonAjoutImageAjouter_clicked()
{
    QString titre = ui->lineEditAjoutImageTitre->text();
    int numero = ui->spinBoxAjoutImageNumero->value();
    double cout = ui->doubleSpinBoxAjoutImageCout->value();
    QString source = ui->lineEditAjoutImageSource->text();
    string acces = ui->checkBoxAjoutImageAcces->isChecked() ? "R" : "P";  // si restreint est coché acces = "R", "P" sinon
    QString dateAjout = ui->dateEditAjoutImageDateAjout->date().toString("dd/MM/yyyy");
    QString dateCreation = ui->dateEditAjoutImageDateCreation->date().toString("dd/MM/yyyy");

    if (VerifierNumero(numero,_objBiblio.getBilbiotheque())){
        QMessageBox::information(this,"Erreur Ajout Image","Le numéro que vous avez choisi existe dèjà!");
    }else if( ui->dateEditAjoutImageDateAjout->date() <= ui->dateEditAjoutImageDateCreation->date() ){
        QMessageBox::information(this,"Erreur Ajout Image","La date d'ajout ne doit pas etre inférieur à la date de création!");
    }else{
    _objBiblio.AjouterImage(_newImageFileName,titre.toStdString(),numero,cout,source.toStdString(),dateAjout.toStdString(),dateCreation.toStdString(),acces);
    updateTableWidgetBiblio();
    ui->stackedWidget->setCurrentIndex(2);          // Aller au menu bibliothèque
    }
}

void AppMainWindow::on_pushButtonCreerBiblio_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Sauvegarder bibliothèque d'images"), "", tr("*.json"));
    string fileNameStr = fileName.toStdString();
    if (!fileName.isEmpty()){
        VerifierExtension(fileNameStr);
        _objBiblio.Sauvegarder(fileNameStr);
    }
    // Chargement de la bibliothèque
    _objBiblio = Bibliotheque(fileNameStr);                                            // Chargement de la bibliotheque : construction d'un objet de classe bibliothèque à partir du fichier json choisi
    _objBiblio.majBiblioSuivantDroitAcces(_droitAcces);                                // mettre à jour l'objet bibliotheque suivant le niveau de l'utilisateur
    updateTableWidgetBiblio();                                                         // mettre à jour la table des descripteurs de la bibliotheque
    ui->stackedWidget->setCurrentIndex(2);                                             // Aller au Menu Bibliothèque (page 2)
    // extraire le nom de la bibliotheque du chemin d acces du fichier .json
    QString biblioName;                                                                // Nom de la bibliothèque
    int i=6;
    do {
        biblioName.push_front(fileName[fileName.length()-i]);
        i++;
    }while(fileName[fileName.length()-i]!='/');
    // ecrire le nom de la bibliotheque dans labelBiblioName
    ui->labelBiblioName->setText(biblioName);
}

void AppMainWindow::on_pushButtonSauvegarderSousListe_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Sauvegarder bibliothèque d'images"), "", tr("*.json"));
    if (!fileName.isEmpty()){
        string fileNameStr = fileName.toStdString();
        VerifierExtension(fileNameStr);
        _objSousListeBiblio.Sauvegarder(fileNameStr);
    }
}

void AppMainWindow::on_pushButtonOuvrirImage_clicked()
{
    //ui->stackedWidget->setCurrentIndex(4);
    QMessageBox::information(this,"Menu Image","Go to Dinh's work");
}
