#pragma once

#include "pch.h"
#include "films.h"
#include "AnimatedFilm.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent);
    ~AddDialog();
    shared_ptr<films> getNewFilm() const;
    void setEditMode(shared_ptr<films> film);
private:
    bool isEditMode;
    Ui::AddDialog *ui;
    shared_ptr<films> newFilm;
    shared_ptr<films> editedFilm;
private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_save_clicked();
    void on_radioButton_base_clicked();
    void on_radioButton_child_clicked();
    void closeEvent(QCloseEvent *event);
};
