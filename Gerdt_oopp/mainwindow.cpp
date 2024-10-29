#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>

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
    // Prompt the user to select a save location
    QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save"), QDir::currentPath(), tr("File (*.dat)"));

    if (!saveFileName.isEmpty()) {
        qDebug() << "Saving file:" << saveFileName;

        // Open the file for writing in binary mode
        std::ofstream out(saveFileName.toStdString(), std::ofstream::binary);

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

