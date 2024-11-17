#include "AddDialog.h"
#include "ui_AddDialog.h"


AddDialog::AddDialog(QWidget *parent, const vector<shared_ptr<films>> filmList)
    : QDialog(parent)
    , filmList(filmList)
    , ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::on_pushButton_cancel_clicked()
{
    reject();
}


void AddDialog::on_pushButton_save_clicked()
{
    accept();
}

