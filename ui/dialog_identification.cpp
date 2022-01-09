#include "dialog_identification.h"
#include "ui_dialog_identification.h"

Dialog_identification::Dialog_identification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_identification)
{
    ui->setupUi(this);
}

Dialog_identification::~Dialog_identification()
{
    delete ui;
}
