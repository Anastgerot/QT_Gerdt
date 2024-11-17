#include "EditDialog.h"
#include "ui_EditDialog.h"
#include "EditFilmDialog.h"

extern QString FilmToString(const shared_ptr<films>& film);


EditDialog::EditDialog(QWidget *parent, const vector<shared_ptr<films>> filmList)
    : QDialog(parent)
    , filmList(filmList)
    , ui(new Ui::EditDialog)
{
    ui->setupUi(this);
    for(auto namefilm: filmList)
    {
        ui->listWidget->addItem(FilmToString(namefilm));
    }
    connect(ui->listWidget, &QListWidget::currentRowChanged, this, &EditDialog::on_listWidget_currentRowChanged);
}

EditDialog::~EditDialog()
{
    delete ui;
}


void EditDialog::on_listWidget_currentRowChanged(int currentRow) {
    if (currentRow < 0 || currentRow >= filmList.size()) {
        ui->textEdit->clear();
        ui->textEdit_2->clear();
        ui->textEdit_3->clear();
        ui->textEdit_4->clear();
        ui->textEdit_5->clear();
        ui->textEdit_6->clear();
        ui->textEdit_7->clear();
        ui->textEdit_8->clear();
        ui->textEdit_7->setVisible(false);
        ui->textEdit_8->setVisible(false);
        ui->label_7->setVisible(false);
        ui->label_8->setVisible(false);
        return;
    }

    const auto& film = filmList[currentRow];
    if (film) {
        // Обновляем поля информации о фильме
        ui->textEdit->setText(QString::fromLocal8Bit(film->getTitle()));
        ui->textEdit_2->setText(QString::number(film->getYear()));
        ui->textEdit_3->setText(QString::fromLocal8Bit(film->getGenre()));
        ui->textEdit_4->setText(QString::number(film->getRating()));
        ui->textEdit_5->setText(QString::fromLocal8Bit(film->getDirector()));
        ui->textEdit_6->setText(film->isAvailable() ? "Да" : "Нет");


        // Проверяем, является ли фильм анимационным
        auto* animatedFilm = dynamic_cast<AnimatedFilm*>(film.get());
        if (animatedFilm) {
            ui->textEdit_7->setText(QString::fromLocal8Bit(animatedFilm->getVoiceActors()));
            ui->textEdit_8->setText(QString::fromLocal8Bit(animatedFilm->getAnimationStyle()));

            // Показываем элементы для анимационного фильма
            ui->textEdit_7->setVisible(true);
            ui->textEdit_8->setVisible(true);
            ui->label_7->setVisible(true);
            ui->label_8->setVisible(true);
        } else {
            // Скрываем элементы, если фильм не анимационный
            ui->textEdit_7->setVisible(false);
            ui->textEdit_8->setVisible(false);
            ui->label_7->setVisible(false);
            ui->label_8->setVisible(false);
        }

        ui->textEdit->setReadOnly(true);
        ui->textEdit_2->setReadOnly(true);
        ui->textEdit_3->setReadOnly(true);
        ui->textEdit_4->setReadOnly(true);
        ui->textEdit_5->setReadOnly(true);
        ui->textEdit_6->setReadOnly(true);
        ui->textEdit_7->setReadOnly(true);
        ui->textEdit_8->setReadOnly(true);
    }
}



void EditDialog::on_pushButton_clicked() {
    int currentRow = ui->listWidget->currentRow();
    if (currentRow < 0 || currentRow >= filmList.size()) {
        return;
    }

    auto film = filmList[currentRow];
    if (film) {

        // Создаем диалог редактирования фильма
        EditFilmDialog editFilmDialog(this, film);
        if (editFilmDialog.exec() == QDialog::Accepted) {

            // Обновление текста элемента в списке
            ui->listWidget->item(currentRow)->setText(FilmToString(film));

            on_listWidget_currentRowChanged(currentRow);
        }
    }
}



void EditDialog::on_pushButton_cancel_clicked() {
    reject();
}

void EditDialog::on_pushButton_save_clicked() {
    accept();
}

void EditDialog::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        tr("Подтверждение закрытия"),
        tr("Вы хотите сохранить изменения?"),
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
        QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
        on_pushButton_save_clicked();
        event->accept();
    } else if (reply == QMessageBox::No) {
        on_pushButton_cancel_clicked();
        event->accept();
    } else {
        event->ignore();
    }
}


void EditDialog::on_pushButton_delete_clicked() {
    int currentRow = ui->listWidget->currentRow();
    if (currentRow < 0 || currentRow >= static_cast<int>(filmList.size())) {
        return;
    }

    filmList.erase(filmList.begin() + currentRow);
    delete ui->listWidget->takeItem(currentRow);

    // Обновляем текущий элемент
    on_listWidget_currentRowChanged(ui->listWidget->currentRow());
}

void EditDialog::on_pushButton_add_clicked()
{

}

