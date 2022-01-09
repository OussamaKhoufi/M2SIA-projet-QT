#ifndef DIALOG_IDENTIFICATION_H
#define DIALOG_IDENTIFICATION_H

#include <QDialog>

namespace Ui {
class Dialog_identification;
}

class Dialog_identification : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_identification(QWidget *parent = 0);
    ~Dialog_identification();

private:
    Ui::Dialog_identification *ui;
};

#endif // DIALOG_IDENTIFICATION_H
