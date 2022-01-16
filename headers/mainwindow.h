#ifndef APPMAINWINDOW_H
#define APPMAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QTextStream>
#include "headers/image.h"
#include "headers/bibliotheque.h"
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

private:
    Ui::AppMainWindow *ui;
    Bibliotheque _objBiblio;                            // Objet de classe Bibliothèque
    bool _droitAcces;
    int _numImageSelected;
    string _newImageFileName;
    Bibliotheque _objSousListeBiblio ;
    void updateTableWidgetBiblio();                     // mise à jour du tableau des descripteurs après chargement de la bibliothèque
    void updateTableWidgetSousListeBiblio(Json::Value);            // mise à jour du tableau de la sous liste de la bibliothèque

};

#endif // APPMAINWINDOW_H
