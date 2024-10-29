#pragma once

#include <QMainWindow>
#include "films.h"
#include "AnimatedFilm.h"
#include "MyWidgetGerdt.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QString fileName;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionClean_triggered();
    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
};
