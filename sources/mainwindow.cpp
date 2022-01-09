#include "headers/mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/dialog_identification.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButtonIdentif_2_clicked()
{
    QString textSaisi = ui->textEdit_2->toPlainText();
    ui->lineEdit_2->insert(textSaisi);
    if (textSaisi=="test"){
        Dialog_identification dialog_win;
        dialog_win.setModal(true);
        dialog_win.exec();
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_pushButton_page_id_exit_clicked()
{

}

void MainWindow::on_pushButtonShowImage_clicked()
{
    //QImage image("../DATA/Images/flower.jpg");
    QGraphicsScene scene;
    //QGraphicsView view(&scene);
    ui->graphicsViewImageShow->setScene(&scene);
    QGraphicsPixmapItem item(QPixmap("DATA/Images/flower.jpg"));
    scene.addItem(&item);
    ui->graphicsViewImageShow->show();
}
