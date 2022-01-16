#ifndef APPMAINWINDOW_H
#define APPMAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
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
    void on_pushButtonIdentifier_clicked();

    void on_pushButtonQuitter_clicked();

    void on_pushButtonChargerBiblio_clicked();

    void on_pushButtonRetourIdentification_clicked();

private:
    Ui::AppMainWindow *ui;
    Bibliotheque _objBiblio;
};

#endif // APPMAINWINDOW_H
