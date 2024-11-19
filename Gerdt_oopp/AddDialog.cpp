#include "AddDialog.h"
#include "ui_AddDialog.h"


AddDialog::AddDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddDialog)
    , newFilm(nullptr)
    , editedFilm(nullptr)
    , isEditMode(false)
{
    ui->setupUi(this);

    ui->textEdit_7->hide();
    ui->textEdit_8->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->radioButton_base->setChecked(true);
}

void AddDialog::setEditMode(shared_ptr<films> film) {
    isEditMode = true;
    editedFilm = film;

    // Заполнение полей данными редактируемого фильма
    if (film) {
        ui->textEdit->setText(QString::fromLocal8Bit(film->getTitle()));
        ui->textEdit_2->setText(QString::number(film->getYear()));
        ui->textEdit_3->setText(QString::fromLocal8Bit(film->getGenre()));
        ui->textEdit_4->setText(QString::number(film->getRating()));
        ui->textEdit_country->setText(QString::fromLocal8Bit(film->getCountry()));
        ui->textEdit_5->setText(QString::fromLocal8Bit(film->getDirector()));
        ui->checkbox_yes->setChecked(film->isAvailable());
        ui->checkbox_no->setChecked(!film->isAvailable());
        ui->radioButton_child->setEnabled(false);
        ui->radioButton_base->setEnabled(false);


        auto* animatedFilm = dynamic_cast<AnimatedFilm*>(film.get());
        if (animatedFilm) {
            ui->radioButton_child->setChecked(true);
            ui->textEdit_7->setText(QString::fromLocal8Bit(animatedFilm->getVoiceActors()));
            ui->textEdit_8->setText(QString::fromLocal8Bit(animatedFilm->getAnimationStyle()));
            on_radioButton_child_clicked();
            ui->radioButton_base->setEnabled(false);
        } else {
            ui->radioButton_base->setChecked(true);
            on_radioButton_base_clicked();
        }
    }
}

void AddDialog::on_pushButton_save_clicked() {
    // Сохранение общих данных (как в текущей реализации)
    QString title = ui->textEdit->toPlainText().trimmed();
    int year = ui->textEdit_2->toPlainText().toInt();
    QString genre = ui->textEdit_3->toPlainText().trimmed();
    double rating = ui->textEdit_4->toPlainText().toDouble();
    QString country = ui->textEdit_country->toPlainText().trimmed();
    QString director = ui->textEdit_5->toPlainText().trimmed();
    bool isAvailable = ui->checkbox_yes->isChecked();

    bool isYesChecked = ui->checkbox_yes->isChecked();
    bool isNoChecked = ui->checkbox_no->isChecked();

    if (isYesChecked && isNoChecked) {
        QMessageBox::warning(this, "Ошибка ввода", "Нельзя выбирать одновременно оба варианта 'Да' и 'Нет'.");
        return;
    }
    if (!isYesChecked && !isNoChecked) {
        QMessageBox::warning(this, "Ошибка ввода", "Выберите один из вариантов доступности: 'Да' или 'Нет'.");
        return;
    }

    // Проверка корректности других данных
    if (title.isEmpty()) {
        QMessageBox::warning(this, "Ошибка ввода", "Поле 'Название' не может быть пустым.");
        return;
    }
    if (year < 1895 || year > QDate::currentDate().year()) {
        QMessageBox::warning(this, "Ошибка ввода", "Год выпуска должен быть в диапазоне от 1895 до текущего года.");
        return;
    }
    if (!rating || rating < 0 || rating > 10) {
        QMessageBox::warning(this, "Ошибка ввода", "Рейтинг должен быть в диапазоне от 0 до 10.");
        return;
    }

    if (isEditMode) {

        editedFilm->setTitle(title.toLocal8Bit().constData());
        editedFilm->setYear(year);
        editedFilm->setGenre(genre.toLocal8Bit().constData());
        editedFilm->setRating(rating);
        editedFilm->setCountry(country.toLocal8Bit().constData());
        editedFilm->setDirector(director.toLocal8Bit().constData());

        auto* animatedFilm = dynamic_cast<AnimatedFilm*>(editedFilm.get());
        if (animatedFilm && ui->radioButton_child->isChecked()) {
            animatedFilm->setVoiceActors(ui->textEdit_7->toPlainText().toLocal8Bit().constData());
            animatedFilm->setAnimationStyle(ui->textEdit_8->toPlainText().toLocal8Bit().constData());
        }
    } else {

        if (ui->radioButton_child->isChecked()) {
            auto childFilm = make_shared<AnimatedFilm>();
            childFilm->setVoiceActors(ui->textEdit_7->toPlainText().toLocal8Bit().constData());
            childFilm->setAnimationStyle(ui->textEdit_8->toPlainText().toLocal8Bit().constData());
            newFilm = childFilm;
        } else {
            newFilm = make_shared<films>();
        }

        newFilm->setTitle(title.toLocal8Bit().constData());
        newFilm->setYear(year);
        newFilm->setGenre(genre.toLocal8Bit().constData());
        newFilm->setRating(rating);
        newFilm->setCountry(country.toLocal8Bit().constData());
        newFilm->setDirector(director.toLocal8Bit().constData());
        newFilm->setAvailable(isAvailable);
    }

    accept();

}


shared_ptr<films> AddDialog::getNewFilm() const {
    if (result() == QDialog::Accepted && newFilm) {
        qDebug() << "Возвращаемый фильм:" << QString::fromLocal8Bit(newFilm->getTitle());
        return newFilm;
    }
    qDebug() << "Фильм не был создан.";
    return nullptr;
}

AddDialog::~AddDialog() {
    delete ui;
}



void AddDialog::on_pushButton_cancel_clicked()
{
    newFilm.reset();
    reject();
}


void AddDialog::on_radioButton_base_clicked()
{
    ui->textEdit_7->hide();
    ui->textEdit_8->hide();
    ui->label_7->hide();
    ui->label_8->hide();

}


void AddDialog::on_radioButton_child_clicked()
{
    ui->textEdit_7->show();
    ui->textEdit_8->show();
    ui->label_7->show();
    ui->label_8->show();
}

void AddDialog::closeEvent(QCloseEvent *event)
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
