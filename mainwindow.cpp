#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString Path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
       ui->setupUi(this);

  QString Path1 = QString::fromLocal8Bit("%1%2").arg(Path).arg("Svid.xml");
  //QString Path2 = QString::fromLocal8Bit("%1%2").arg(Path).arg("Svid.xml");
  //QString Path2 = QString::fromLocal8Bit("%1%2").arg(Path).arg("SvidSearch.ini");

StakeGen = new QStackedWidget;
StakeInfoGen = new QStackedWidget;

tInfoGen = new QTextEdit(parent);
tInfoGen->setMinimumHeight(20);


    SplitVerGen = new QSplitter(Qt::Vertical);
    tDialGen = new DialGen(Path1, tInfoGen, this);


    StakeInfoGen->addWidget(tInfoGen);




//--Включаем или выключаем клавиатуру в зависимости от окна
     tDialGen->fWidjetEnable(1);


//----


   StakeGen->addWidget(SplitVerGen);
   SplitVerGen->addWidget(tDialGen->GetIDSplitter());
   SplitVerGen->addWidget(StakeInfoGen);

 StakeGen->setCurrentIndex(0);

 SplitVerGen->setStretchFactor(0, 75);
 SplitVerGen->setStretchFactor(1, 10);


 //--горячии клавиши для поиска

//--Устанавливает базовый виджет в главное окно
      setCentralWidget(StakeGen);

 }
//--Выбор между главным окном и окном поиска
void MainWindow::SetCurrentWidjet()
{
   if (tt == 0)
   {
     tt = 1;
     tDialGen->fWidjetEnable(0);
   }
   else
    {
       tt = 0;

       tDialGen->fWidjetEnable(1);

    }


StakeGen->setCurrentIndex(tt);

}


MainWindow::~MainWindow()
{
    delete ui;
}

