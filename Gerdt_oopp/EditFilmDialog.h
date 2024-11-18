#pragma once

#include "pch.h"
#include "films.h"
#include "AnimatedFilm.h"

namespace Ui {
class EditFilmDialog;
}

class EditFilmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditFilmDialog(QWidget *parent = nullptr, std::shared_ptr<films> film = nullptr);
    ~EditFilmDialog();


private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_save_clicked();
    void closeEvent(QCloseEvent *event);
private:
    Ui::EditFilmDialog *ui;
    shared_ptr<films> film;
};
