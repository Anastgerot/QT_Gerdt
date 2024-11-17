#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include "EditDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionOpen_triggered() {
    fileName = QFileDialog::getOpenFileName(this, tr("Open"), QDir::currentPath(), tr("File (*.dat)"));
    if (!fileName.isEmpty()) {
        qDebug() << "Opening file:" << fileName;
        ui->myWidgetGerdt->load(fileName);
    }
}
void MainWindow::on_actionClean_triggered() {
    ui->myWidgetGerdt->clean();
    fileName = "";
}
void MainWindow::on_actionSave_triggered() {
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save"), QDir::currentPath(), tr("File (*.dat)"));

    if (!saveFileName.isEmpty()) {
        qDebug() << "Saving file:" << saveFileName;

        ofstream out(saveFileName.toStdString(), ofstream::binary);

        if (out.is_open()) {
            boost::archive::binary_oarchive ar(out);
            ar << ui->myWidgetGerdt->getfilmList();

            out.close();
            qDebug() << "File saved successfully.";
        } else {
            qDebug() << "Failed to open file for writing.";
        }
    }
}

template<class T>
void clone(T& src, T& trg)
{
    stringstream stream;
    boost::archive::binary_oarchive out(stream);
    boost::archive::binary_iarchive in(stream);
    out << src;
    in >> trg;
}


void MainWindow::on_actionEditFilms_triggered()
{
    // Клонируем filmList в новый вектор для редактирования в диалоге
    vector<shared_ptr<films>> clonedFilmList;
    clone(ui->myWidgetGerdt->filmList, clonedFilmList);

    // Передаем клонированный список фильмов в конструктор EditDialog
    EditDialog dlg(this, clonedFilmList);

    // Если диалог завершен успешно
    if (dlg.exec() == QDialog::Accepted)
    {
        // Клонируем измененный список обратно в filmList
        clone(clonedFilmList, ui->myWidgetGerdt->filmList);
        ui->myWidgetGerdt->update();
    }
}


