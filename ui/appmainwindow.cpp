#include "appmainwindow.h"
#include "ui_appmainwindow.h"

AppMainWindow::AppMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AppMainWindow)
{
    ui->setupUi(this);
}

AppMainWindow::~AppMainWindow()
{
    delete ui;
}

void AppMainWindow::on_pushButtonIdentifier_clicked()
{
    QString userMdp = ui->lineEditMdp->text();
    QFile userIdFile("/home/vm/M2SIA-projet-QT/DATA/idUsers.txt");
    bool idFound=false;
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
        QMessageBox::information(this,"Identification","Identification Réussite !");
        ui->stackedWidget->setCurrentIndex(1);
    }else {
        QMessageBox::information(this,"Identification","Le mot de passe est incorrect.");
    }

}

void AppMainWindow::on_pushButtonQuitter_clicked()
{
    qApp->quit();
}

void AppMainWindow::on_pushButtonChargerBiblio_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Charger la bibliothèque","/home/vm/M2SIA-projet-QT/DATA/Bibliothèques","*.json");
    QFile fileBiblio(fileName);
    if(!fileBiblio.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this,"error",fileBiblio.errorString());
    }else {
        QMessageBox::information(this,"Chargement bibliothèque","Chargement de la bibliothèque réussie !");
        _objBiblio = Bibliotheque(fileName.toStdString());
        QMessageBox::information(this,"Chargement bibliothèque",QString::fromStdString(_objBiblio.getCheminJson()));
    }

}

void AppMainWindow::on_pushButtonRetourIdentification_clicked()
{
    ui->stackedWidget->setCurrentIndex(0); // Retour au Menu Identification (page 0)
}
