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
void clone(const T& src, T& trg)
{
    stringstream stream;
    boost::archive::binary_oarchive out(stream);
    boost::archive::binary_iarchive in(stream);
    out << src;
    in >> trg;
}


void MainWindow::on_actionEditFilms_triggered()
{
    vector<shared_ptr<films>> clonedFilmList;
    clone(ui->myWidgetGerdt->filmList, clonedFilmList);

    EditDialog dlg(this, clonedFilmList);


    connect(&dlg, &EditDialog::filmListChanged, this, [this](const vector<shared_ptr<films>>& updatedFilmList){
        clone(updatedFilmList, ui->myWidgetGerdt->filmList);
        ui->myWidgetGerdt->update();
    });

    if (dlg.exec() == QDialog::Accepted) {}

}



