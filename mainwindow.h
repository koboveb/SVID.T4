#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "StorProject.h"
#include "DialGen.h"


#include <QStackedWidget>
#include <QShortcut>
#include <QKeyEvent>





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString Path, QWidget *parent = 0);
    ~MainWindow();


private:


    int tt = 0;

QStackedWidget *StakeGen;
QSplitter *SplitVerGen;
DialGen *tDialGen;
QStackedWidget *StakeInfoGen;
QTextEdit *tInfoGen;

    Ui::MainWindow *ui;


    void SetCurrentWidjet();
};

#endif // MAINWINDOW_H
