#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "headers/image.h"
#include "headers/bibliotheque.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButtonIdentif_2_clicked();

    void on_pushButton_page_id_exit_clicked();

    void on_pushButtonShowImage_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
