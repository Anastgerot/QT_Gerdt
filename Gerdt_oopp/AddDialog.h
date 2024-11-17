#pragma once
#include "pch.h"
#include "films.h"


namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent, const vector<shared_ptr<films>> filmList);
    ~AddDialog();

private:
    Ui::AddDialog *ui;
    vector<shared_ptr<films>> filmList;
private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_save_clicked();
};
