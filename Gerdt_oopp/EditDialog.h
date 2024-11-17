#pragma once

#include <QDialog>
#include "pch.h"
#include "films.h"
#include "AnimatedFilm.h"

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    vector<shared_ptr<films>> filmList;
    explicit EditDialog(QWidget *parent, vector<shared_ptr<films>> filmList);
    ~EditDialog();


private:
    Ui::EditDialog *ui;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_cancel_clicked();
    void on_pushButton_save_clicked();
    void closeEvent(QCloseEvent *event);
    void on_pushButton_delete_clicked();
    void on_listWidget_currentRowChanged(int currentRow);
    void on_pushButton_add_clicked();
};
