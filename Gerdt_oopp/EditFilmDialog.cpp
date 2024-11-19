
#include "EditFilmDialog.h"
#include "ui_AddDialog.h"

EditFilmDialog::EditFilmDialog(QWidget *parent, shared_ptr<films> film)
    : QDialog(parent),
    film(film),
    ui(Ui::AddDialog)
{
    ui->setupUi(this);

    if (film) {
        ui->textEdit->setText(QString::fromLocal8Bit(film->getTitle()));
        ui->textEdit_2->setText(QString::number(film->getYear()));
        ui->textEdit_3->setText(QString::fromLocal8Bit(film->getGenre()));
        ui->textEdit_4->setText(QString::number(film->getRating()));
        ui->textEdit_country->setText(QString::fromLocal8Bit(film->getCountry()));
        ui->textEdit_5->setText(QString::fromLocal8Bit(film->getDirector()));
        bool isAvailable = film->isAvailable();
        ui->checkbox_yes->setChecked(isAvailable);
        ui->checkbox_no->setChecked(!isAvailable);

        auto* animatedFilm = dynamic_cast<AnimatedFilm*>(film.get());
        if (animatedFilm) {
            ui->textEdit_7->setText(QString::fromLocal8Bit(animatedFilm->getVoiceActors()));
            ui->textEdit_8->setText(QString::fromLocal8Bit(animatedFilm->getAnimationStyle()));
            ui->textEdit_7->setVisible(true);
            ui->textEdit_8->setVisible(true);
            ui->label_7->setVisible(true);
            ui->label_8->setVisible(true);
        } else {
            ui->textEdit_7->setVisible(false);
            ui->textEdit_8->setVisible(false);
            ui->label_7->setVisible(false);
            ui->label_8->setVisible(false);
        }
    }
}

EditFilmDialog::~EditFilmDialog()
{
    delete ui;
}



void EditFilmDialog::on_pushButton_save_clicked()
{
    if (film) {

        bool yearOk;
        int year = ui->textEdit_2->toPlainText().toInt(&yearOk);
        if (!yearOk || year < 1895 || year > QDate::currentDate().year()) {
            QMessageBox::warning(this, "Ошибка ввода",
                                 "Год выпуска должен быть в диапазоне от 1895 до текущего года.");
            return;
        }

        bool ratingOk;
        double rating = ui->textEdit_4->toPlainText().toDouble(&ratingOk);
        if (!ratingOk || rating < 0 || rating > 10) {
            QMessageBox::warning(this, "Ошибка ввода",
                                 "Рейтинг должен быть числом от 0 до 10.");
            return;
        }

        // Обновление данных фильма
        film->setTitle(ui->textEdit->toPlainText().toLocal8Bit().constData());
        film->setYear(year);
        film->setGenre(ui->textEdit_3->toPlainText().toLocal8Bit().constData());
        film->setRating(rating);
        film->setCountry(ui->textEdit_country->toPlainText().toLocal8Bit().constData());
        film->setDirector(ui->textEdit_5->toPlainText().toLocal8Bit().constData());

        if (ui->checkbox_yes->isChecked() && ui->checkbox_no->isChecked()) {
            QMessageBox::warning(this, "Ошибка ввода",
                                 "Нельзя выбирать одновременно оба варианта 'Да' и 'Нет'.");
            return;
        } else if (ui->checkbox_yes->isChecked()) {
            film->setAvailable(true);
        } else if (ui->checkbox_no->isChecked()) {
            film->setAvailable(false);
        } else {
            QMessageBox::warning(this, "Ошибка ввода",
                                 "Выберите доступность: 'Да' или 'Нет'.");
            return;
        }

        auto* animatedFilm = dynamic_cast<AnimatedFilm*>(film.get());
        if (animatedFilm) {
            animatedFilm->setVoiceActors(ui->textEdit_7->toPlainText().toLocal8Bit().constData());
            animatedFilm->setAnimationStyle(ui->textEdit_8->toPlainText().toLocal8Bit().constData());
        }
    }

    accept();
}


void EditFilmDialog::on_pushButton_cancel_clicked()
{
    reject();
}

void EditFilmDialog::closeEvent(QCloseEvent *event)
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
