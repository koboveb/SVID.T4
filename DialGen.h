#ifndef SVIDDIAGENN_H
#define SVIDDIAGENN_H


#include "ModelUni.h"

#include "TTextedit.h"


#include <QLabel>
#include <QTableView>
#include <QListView>


#include <QSplitter>


#include <QShortcut>
#include <QKeyEvent>

#include <QStackedWidget>

#include <QCalendarWidget>

#include <QScrollBar>

#include <QTimer>

enum typedial {BASE_GEN, BASE_CACHE, DOCUM_GEN, DOCUM_CACHE};

/* прототип выбора
switch (TypeDial)
    {

    case BASE_GEN:
    {
    }
        break;

    case BASE_CACHE:
    {
    }
        break;

    case DOCUM_GEN:
    {
    }
        break;

    case DOCUM_CACHE:
    {
    }
        break;

default:
    {
    }
        break;
}

*/

class DialGen: public QObject
{
   QOBJECT_H

public:
    DialGen(QString Path,QTextEdit *tInfoGen, QWidget *parent);
    QSplitter *GetIDSplitter();
    void sSetFocus();
    void mClearValinInfo();

    void fWidjetEnable(int tWidjetEnable);

private:



    int SizeFont = 1;

   QTimer *tTimerLoadData;
   QTimer *tTimerLoadUpdate;
   QTimer *tTimerUpdate;

   QElapsedTimer tSpeed;
   int tSpeedUpdate;



   QShortcut *keyCtrlDPgUp;
   QShortcut *keyCtrlDPgDown;
   QShortcut *keyCtrlDRight;
   QShortcut *keyCtrlDLeft;
   QShortcut *keyEnter;
   QShortcut *keyEnterShift;

   QShortcut *keyCtrlD;

   QShortcut *keyCtrlFilter;
   QShortcut *keyCtrlSort;

   QShortcut *keyEnd;

   QShortcut *keyCtrlPlus;
   QShortcut *keyCtrlMinus;

  // QShortcut *keyEnterShiftCtrl;

   QShortcut *keyCntrEsc;

   StorData *tStorDate;
   //StorProject *tStorage;


    ModelUni *ModelInfo;
    ModelUni *ModelData;
    ModelUni *ModelDocum;



//---Модели фильтров
   // ModelUni *ModelFiltr;

//--Представление Баз
    QListView *vBase;

//---Представления фильтров
  //  QListView *vFiltr;

//---------------------------------------------------------
    QStackedWidget *StakeGenSub;

//---------------------------------------------------------
    QStackedWidget *StakeGenSubBase;
        QStackedWidget *StakeGenSubBaseGen;
        QStackedWidget *StakeGenSubBaseCache;

//---------------------------------------------------------
    QStackedWidget *StakeGenSubNewFiltr;
        QStackedWidget *StakeGenSubNewFiltrGen;
        QStackedWidget *StakeGenSubNewFiltrCache;
//---------------------------------------------------------
    QStackedWidget *StakeGenSubNewDocum;
        QStackedWidget *StakeGenSubNewDocumGen;
        QStackedWidget *StakeGenSubNewDocumCache;

//---Представления документов по уровню
             //QListView *vDoc;
             QTableView *vDoc;

    QStackedWidget *StakeGenSubCache;

//---------------------------------------------------------
    QTextEdit *tLabelInfo;
    QStackedWidget *StakeInfo;

//---------------------------------
    QStackedWidget *StakeText;
        TTextEdit *tTextEdit;


//----------------------------------

    QSplitter *SplitVer;
    QSplitter *SplitHor;
    QSplitter *SplitInfo;


    QTableView *TableViewInfo;

    QItemSelectionModel *SelecGen;
    QItemSelectionModel *SelecInfo;

    QItemSelectionModel *SelecFiltr;
    QItemSelectionModel *SelecDocum;


    QTabWidget *tabsRd; //набор виджетов со вкладками

    QList <ModelUni*> lModelCach;
    QList <ModelUni*> lModelDocum;

//--------------------------------------------


    QList<QTableView*> lTableViewGen;

    QList<QListView*> lListViewCacheKey;
    QList<QListView*> lListViewCache;
    QList<QListView*> lListViewDocum;

    QList<QListView*> lListFiltrCacheTxt;
    QList<QListView*> lListFiltrCacheBin;
//--исправить тип
    QList<QListView*> lListFiltrCacheNum;
    QList<QListView*> lListFiltrCacheDtd;

//--------------------------------------------
    int tCurrentRowBaseGen;
    int ttCurrentRowBaseGenPrev;

    int tCurrentRowBaseCache;
    int ttCurrentRowBaseCachePrev;

//--------------------------------------------
    int tCurrentRowDocumGen;
    int ttCurrentRowDocumGenPrev;

    int tCurrentRowDocumCache;
    int ttCurrentRowDocumCachePrev;

//--------------------------------------------
    int tCurrentRowFiltrGen;
    int ttCurrentRowFiltrGenPrev;

    int tCurrentRowFiltrCache;
    int ttCurrentRowFiltrCachePrev;

//----------------------------------------------

    int tCurrentRowInfoPrev;
    int tCurrentRowInfo;

    bool flagNewViewFind;

    bool flagChangeSlot;
    bool bForSeach;

 //--Внешний Edit
    QTextEdit *tInfoGenLocal;

    QString CurrentData;
   // QBitArray parChangeTextBit; //вспомогательный массив для отслеживания изменений в базе
    QString TextSearch;


    int tlfShowLast;
    QList<int> lfShow; //массив строк для перемещения

    int countSearch; // счётчик для перехода по массиву найденных строк

    typedial TypeDial;

//Методы


    void SlotCurrentChangedTab();

    void SlotCurrentChangedBaseGen (const QItemSelection &selected);
    void SlotCurrentChangedBaseCache (const QItemSelection &selected);


    void SlotCurrentChangedInfo(const QItemSelection &selected);



    void SlotKeyPgUp();
    void SlotKeyPgDown();

    void SlotKeyMyRight();
    void SlotKeyMyLeft();


    void SlotInfoNext();
    void SlotInfoPrev();


    void OperFind();
    void OperFindBack();

    void OperSort();

    void SlotKeyNewDoc();
    void SlotKeyNewFiltr();
    void SlotKeyNewFind();

    void SlotKeyRight();
    void SlotKeyLeft();

    void SlotKeyUP();
    void SlotKeyDown();

    void SlotFontPlus();
    void SlotFontMinus();

    void SlotKeyTab();
    void SlotChangedText();

    void SlotKeyEnd();

    void NewRowsInCash(QString TextSearch);
    void NewRowsSave();

    void SetDataInfoLable();
    void SetDataInfoConsol();

    //void ScrollBarValueChanged();

    //void ScrollBarValueChangedUpDown();

    void LoadData();
    void LoadUpdate();
    void LoadCurent();

    void ModelUpdate();


};

#endif // SVIDDIAGENN_H
