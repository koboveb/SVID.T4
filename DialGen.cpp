#include "DialGen.h"


DialGen::DialGen(QString Path, QTextEdit *tInfoGen, QWidget *parent)
{

    tInfoGenLocal = tInfoGen;

    flagChangeSlot = false;

    bForSeach = 0;
    countSearch = 0;

//--Установка типа работы

    TypeDial = BASE_GEN;

tStorDate = new StorData(Path);
//tStorage = tStorDate->GetStorProject();


tTimerLoadData = new QTimer;
tTimerLoadData->setInterval(tStorDate->Get_TimeOut());

tTimerLoadUpdate = new QTimer;
tTimerLoadUpdate->setInterval(tStorDate->Get_TimeOut()/3);


tTimerUpdate = new QTimer;
tTimerUpdate->setInterval(66);

//-----Создание моделей

          ModelInfo = new ModelUni(INFO, tStorDate);
          ModelData = new ModelUni(DATA, tStorDate);
          ModelDocum = new ModelUni(DOCUM, tStorDate);


            vDoc = new QTableView();


            vBase = new QListView();



//--Создаем и определяем текстовое поле
            StakeText = new QStackedWidget;
                tTextEdit = new TTextEdit(parent);
                tTextEdit->setMinimumHeight(20);

             StakeText->addWidget(tTextEdit);


//устанавливаем размер массива

           // parChangeTextBit.resize(tStorDate->GetFieldCod().length());



//Создание Форм


             StakeGenSub = new QStackedWidget;

             StakeGenSubBase = new QStackedWidget;
                StakeGenSubBaseGen = new QStackedWidget;
                StakeGenSubBaseCache = new QStackedWidget;

                /*
             StakeGenSubNewFiltr = new QStackedWidget;
                StakeGenSubNewFiltrGen = new QStackedWidget;
                StakeGenSubNewFiltrCache = new QStackedWidget;
*/

             StakeGenSubNewDocum = new QStackedWidget;
                StakeGenSubNewDocumGen = new QStackedWidget;
                StakeGenSubNewDocumCache = new QStackedWidget;


             StakeInfo = new QStackedWidget;

             SplitHor = new QSplitter(Qt::Horizontal);
             SplitVer = new QSplitter(Qt::Vertical);
             SplitInfo = new QSplitter(Qt::Vertical);

             TableViewInfo =new QTableView(parent);
             tLabelInfo = new QTextEdit(parent);
             tLabelInfo->setMinimumHeight(60);

             TableViewInfo->setWordWrap(false);
             TableViewInfo->setShowGrid(false);

             tabsRd = new QTabWidget(parent);
             tabsRd->setTabPosition(QTabWidget::South);

//--------------------------------------------------------

             SplitHor->addWidget(StakeInfo);
             SplitHor->addWidget(SplitVer);

//---------------------------------------------------------

             SplitHor->setStretchFactor(0, 0);
             SplitHor->setStretchFactor(1, 1);

             SplitVer->addWidget(StakeText);
             SplitVer->addWidget(StakeGenSub);

             StakeInfo->addWidget(SplitInfo);

//----------------------------------------------------------
             SplitInfo->addWidget(tLabelInfo);
             SplitInfo->addWidget(TableViewInfo);



             SplitInfo->setStretchFactor(0, 1);
             SplitInfo->setStretchFactor(1, 50);



//-------Добавление закладок
             StakeGenSub->addWidget(StakeGenSubBase);
                StakeGenSubBase->addWidget(StakeGenSubBaseGen);
                StakeGenSubBase->addWidget(StakeGenSubBaseCache);

             StakeGenSub->addWidget(StakeGenSubNewDocum);
                StakeGenSubNewDocum->addWidget(StakeGenSubNewDocumGen);
                StakeGenSubNewDocum->addWidget(StakeGenSubNewDocumCache);



//--Установка представлений в закладки
             StakeGenSubBaseGen->addWidget(vBase);
             StakeGenSubBaseCache->addWidget(tabsRd);

             StakeGenSubNewDocumGen->addWidget(vDoc);



             SplitVer->setStretchFactor(0, 50);
             SplitVer->setStretchFactor(1, 50);

//--Другое место. Устанавлимаем массив представлений для кэша.

             for (int k = 0 ; k < tStorDate->GetFieldCod().length(); k++)
              {

                    if (tStorDate->GetFieldType().at(k) == "Txt")
                    {
/*
                        QListView* lvT = new QListView();

                        lListFiltrCacheTxt.append(lvT);

                        lListFiltrCacheBin.append(0);
                        lListFiltrCacheNum.append(0);
                        lListFiltrCacheDtd.append(0);

                        StakeGenSubNewFiltrCache->addWidget(lvT);
                        */
                    }


                    if (tStorDate->GetFieldType().at(k) == "Lst")
                    {
/*
                        QListView* lvT = new QListView();


                        lListFiltrCacheTxt.append(0);

                        lListFiltrCacheBin.append(lvT);
                        lListFiltrCacheNum.append(0);
                        lListFiltrCacheDtd.append(0);

                        StakeGenSubNewFiltrCache->addWidget(lvT);
*/

                    }


                    if (tStorDate->GetFieldType().at(k) == "Num")
                    {
/*
                        QListView* lvT = new QListView();

                        lListFiltrCacheTxt.append(0);

                        lListFiltrCacheBin.append(0);
                        lListFiltrCacheNum.append(lvT);
                        lListFiltrCacheDtd.append(0);

                        StakeGenSubNewFiltrCache->addWidget(lvT);
                        */
                    }

                    if (tStorDate->GetFieldType().at(k) == "Dtd")
                    {

                        /*QListView* lvT = new QListView();


                        lListFiltrCacheTxt.append(0);

                        lListFiltrCacheBin.append(0);
                        lListFiltrCacheNum.append(0);
                        lListFiltrCacheDtd.append(lvT);

                        StakeGenSubNewFiltrCache->addWidget(lvT);
                        */
                    }



              }





// Установка моделей в Info

             TableViewInfo->setModel(ModelInfo);


// Скрытие всех полей Info
             for (int k = 0 ; k < tStorDate->GetFieldCod().length(); k++)
             TableViewInfo->hideRow(k);


//--Установка модели выбора Info
             SelecInfo  = TableViewInfo->selectionModel();



//--Создание вкладок и Установка моделей в BASECACHE


             for(int i = 0; i < tStorDate->GetDialogName().length(); i++)
                 {
                     QTableView  *TableViewGen =new QTableView(parent);
                     TableViewGen->setModel(ModelData);

                     tabsRd->addTab(TableViewGen, tStorDate->GetDialogCodName().value(i));

                     TableViewGen->setWordWrap(false);
                     TableViewGen->setShowGrid(false);


// Скртие колонок
                     for (int k = 0 ; k < tStorDate->GetFieldName().length(); k++)
                           TableViewGen->setColumnWidth(k, 0); //ширина колонок

//--Показ необходимых колонок
                     for (int k = 0 ; k < tStorDate->ll_vv_FieldIndexN().value(i).length(); k++)
                     {
                            int tt = tStorDate->ll_vv_FieldIndexN().value(i).value(k);
                             TableViewGen->setColumnWidth(tt, tStorDate->GetFieldWidth().value(tt)); //ширина колонок
                     }


// Действие. Изменение выделения

                            connect(TableViewGen->selectionModel(), &QItemSelectionModel::selectionChanged,this, &DialGen::SlotCurrentChangedBaseCache);


// Установка модели выбора Gen. Из первой вкладки берем модель выбора. В другие устанавливаем из первой вкладки
                 if (i==0)
                     SelecGen  =  TableViewGen->selectionModel();
                 else
                    TableViewGen->setSelectionModel(SelecGen);


  lTableViewGen << TableViewGen;

  }





// Установка на первую запись
             tCurrentRowInfo = 0;
             tCurrentRowInfoPrev = 0;

// Переход на последнюю запись
                   SlotKeyEnd();


//--Создание вкладок и Установка моделей в FILTR_GEN

vDoc->setModel(ModelDocum);
SelecDocum = vDoc->selectionModel();


// Установка горячих клавиш

            keyCtrlDPgUp = new QShortcut(parent); // Инициализируем объект
            keyCtrlDPgUp->setKey(Qt::Key_PageUp); // Устанавливаем сочетание клавиш
                connect(keyCtrlDPgUp, &QShortcut::activated, this, &DialGen::SlotKeyPgUp);

            keyCtrlDPgDown = new QShortcut(parent); // Инициализируем объект
            keyCtrlDPgDown->setKey(Qt::Key_PageDown); // Устанавливаем сочетание клавиш
                connect(keyCtrlDPgDown, &QShortcut::activated, this, &DialGen::SlotKeyPgDown);

            keyCtrlDRight = new QShortcut(parent); // Инициализируем объект
            keyCtrlDRight->setKey(Qt::SHIFT + Qt::Key_PageDown); // Устанавливаем сочетание клавиш
                connect(keyCtrlDRight, &QShortcut::activated, this, &DialGen::SlotKeyMyRight);

            keyCtrlDLeft = new QShortcut(parent); // Инициализируем объект
            keyCtrlDLeft->setKey(Qt::SHIFT + Qt::Key_PageUp); // Устанавливаем сочетание клавиш
                connect(keyCtrlDLeft, &QShortcut::activated, this, &DialGen::SlotKeyMyLeft);

           keyEnter = new QShortcut(parent); // Инициализируем объект
           keyEnter->setKey(Qt::Key_Return); // Устанавливаем сочетание клавиш
                 connect(keyEnter, &QShortcut::activated, this, &DialGen::SlotInfoNext);


           keyEnterShift = new QShortcut(parent); // Инициализируем объект
           keyEnterShift->setKey(Qt::SHIFT + Qt::Key_Return); // Устанавливаем сочетание клавиш
                connect(keyEnterShift, &QShortcut::activated, this, &DialGen::SlotInfoPrev);






           keyCtrlD = new QShortcut(parent); // Инициализируем объект
           keyCtrlD->setKey(Qt::CTRL + Qt::Key_N); // Устанавливаем сочетание клавиш
                    connect(keyCtrlD, &QShortcut::activated, this, &DialGen::SlotKeyNewDoc);


           keyCtrlPlus = new QShortcut(parent); // Инициализируем объект
           keyCtrlPlus->setKey(Qt::CTRL + Qt::Key_Plus); // Устанавливаем сочетание клавиш
                    connect(keyCtrlPlus, &QShortcut::activated, this, &DialGen::SlotFontPlus);

           keyCtrlMinus = new QShortcut(parent); // Инициализируем объект
           keyCtrlMinus->setKey(Qt::CTRL + Qt::Key_Minus); // Устанавливаем сочетание клавиш
                    connect(keyCtrlMinus, &QShortcut::activated, this, &DialGen::SlotFontMinus);



//--Старт поиск
           keyCtrlFilter = new QShortcut(parent); // Инициализируем объект
           keyCtrlFilter->setKey(Qt::CTRL + Qt::Key_F); // Устанавливаем сочетание клавиш
                    connect(keyCtrlFilter, &QShortcut::activated, this, &DialGen::OperFind);

           keyCtrlSort = new QShortcut(parent); // Инициализируем объект
           keyCtrlSort->setKey(Qt::CTRL + Qt::Key_S); // Устанавливаем сочетание клавиш
                     connect(keyCtrlSort, &QShortcut::activated, this, &DialGen::OperSort);

           /*
           keyEnterShiftCtrl = new QShortcut(parent); // Инициализируем объект
           keyEnterShiftCtrl->setKey(Qt::CTRL + Qt::SHIFT + Qt::Key_Return); // Устанавливаем сочетание клавиш
                    connect(keyEnterShiftCtrl, &QShortcut::activated, this, &DialGen::SlotKeyCtrlShiftReturn);
*/

//--Отмена поиска

            keyCntrEsc = new QShortcut(parent); // Инициализируем объект
            keyCntrEsc->setKey(Qt::CTRL + Qt::Key_Escape); // Устанавливаем сочетание клавиш
                     connect(keyCntrEsc, &QShortcut::activated, this, &DialGen::OperFindBack);


//--Переход на последнюю запись
           keyEnd = new QShortcut(parent); // Инициализируем объект
           keyEnd->setKey(Qt::Key_End); // Устанавливаем сочетание клавиш
                    connect(keyEnd, &QShortcut::activated, this, &DialGen::SlotKeyEnd);


//-----------------------------------------------------------------------------------------------------------


// Действие. Изменение вкладки
        connect(tabsRd,  &QTabWidget::currentChanged,this, &DialGen::SlotCurrentChangedTab);

// Действие. Изменение строки

        connect(TableViewInfo->selectionModel(), &QItemSelectionModel::selectionChanged,this, &DialGen::SlotCurrentChangedInfo);


// Действие над полем Text

        connect(tTextEdit, &TTextEdit::sKRight, this, &DialGen::SlotKeyRight);
        connect(tTextEdit, &TTextEdit::sKLeft, this, &DialGen::SlotKeyLeft);

        connect(tTextEdit, &TTextEdit::sReturn, this, &DialGen::SlotInfoNext);
        connect(tTextEdit, &TTextEdit::sShiftReturn, this, &DialGen::SlotInfoPrev);

        connect(tTextEdit, &TTextEdit::sKUp, this, &DialGen::SlotKeyUP);
        connect(tTextEdit, &TTextEdit::sKDown, this, &DialGen::SlotKeyDown);

        connect(tTextEdit, &TTextEdit::textChanged, this, &DialGen::SlotChangedText);
        connect(tTextEdit, &TTextEdit::sKTab, this, &DialGen::SlotKeyTab);

        connect(tTextEdit, &TTextEdit::sKEnd, this, &DialGen::SlotKeyEnd);

 //Включение таймера для отслеживания изменений данных

   connect(tTimerLoadData, &QTimer::timeout, this, &DialGen::LoadData);
   tTimerLoadData->start();

   connect(tTimerLoadUpdate, &QTimer::timeout, this, &DialGen::LoadUpdate);
   tTimerLoadUpdate->start();

   connect(tTimerUpdate, &QTimer::timeout, this, &DialGen::LoadCurent);
   tTimerUpdate->start();

}

QSplitter* DialGen::GetIDSplitter()
{

 return SplitHor;
}

void DialGen::SlotCurrentChangedTab()
{

}

void DialGen::SlotCurrentChangedBaseCache(const QItemSelection & selected)
{

    //--Скрытие всех полей
           for (int k = 0 ; k < tStorDate->GetFieldCod().length(); k++)
             TableViewInfo->hideRow(k);

           QModelIndexList indexest = selected.indexes();
           tCurrentRowBaseCache = indexest.value(0).row();

    //--Выделение строки полностью

           QModelIndex  tGenIndexL = ModelData->index(tCurrentRowBaseCache, 0, QModelIndex());
           QModelIndex  tGenIndexR = ModelData->index(tCurrentRowBaseCache, tStorDate->GetFieldCod().length()-1, QModelIndex());

           SelecGen->setCurrentIndex(tGenIndexL, QItemSelectionModel::Select);

           QItemSelection tSelGen(tGenIndexL,tGenIndexR);
           SelecGen->select(tSelGen,QItemSelectionModel::Select);

    //--Установка значения в таблицу инфо

           for (int k = 0 ; k < tStorDate->GetFieldCod().length(); k++)
            {

               QModelIndex ttt = ModelData->index(indexest.value(0).row(),k, QModelIndex());
               QString ttText = ModelData->data(ttt, Qt::DisplayRole).toString();




    //-------если не пусто, то показываем
               if (ttText != "")

                 {
                       TableViewInfo->showRow(k);
                      tStorDate->SetFieldInfo(k,ttText);

                 }

            }


           TableViewInfo->resizeColumnsToContents();
           TableViewInfo->reset();

    //--Устанавливает выделение в Инфо
           QModelIndex tMasLeftS = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
           QModelIndex tMasRightS = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
           QItemSelection tSelInfoS(tMasLeftS, tMasRightS);
           SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);

}


void DialGen::SlotCurrentChangedInfo(const QItemSelection & selected)
{
   switch (TypeDial)
   {

   case BASE_GEN:
   {

   }
       break;

   case BASE_CACHE:
   {
      // if(tCurrentRowInfo >= 0)
      // {}

       QModelIndexList indexest = selected.indexes();
       tCurrentRowInfo = indexest.value(0).row();

       QModelIndex  tInfoIndexL = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
       SelecInfo->setCurrentIndex(tInfoIndexL, QItemSelectionModel::Select);

       StakeGenSub->update();

       QModelIndex ttt = ModelInfo->index(indexest.value(0).row(),1, QModelIndex());
       QString ttText = ModelInfo->data(ttt, Qt::DisplayRole).toString();

       tTextEdit->setText(ttText);
       tTextEdit->setFocus();
       tTextEdit->selectAll();

   }
        break;


   case DOCUM_GEN:
   {

       QModelIndexList indexest = selected.indexes();
       tCurrentRowInfo = indexest.value(0).row();

       QModelIndex  tInfoIndexL = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
       SelecInfo->setCurrentIndex(tInfoIndexL, QItemSelectionModel::Select);

       StakeGenSub->update();

       QModelIndex ttt = ModelInfo->index(indexest.value(0).row(),1, QModelIndex());
       QString ttText = ModelInfo->data(ttt, Qt::DisplayRole).toString();

       tTextEdit->setText(ttText);
       tTextEdit->setFocus();
       tTextEdit->selectAll();

   }
       break;

   case DOCUM_CACHE:
   {

   }
       break;


   default:
   {

   }

   }
}


void DialGen::SlotKeyPgUp()
{

    tCurrentRowBaseCache = SelecGen->currentIndex().row();

    QModelIndex  tMasLeftD = ModelData->index(tCurrentRowBaseCache, 0, QModelIndex());
    QModelIndex  tMasRightD = ModelData->index(tCurrentRowBaseCache, tStorDate->GetFieldCod().length()-1, QModelIndex());

    QItemSelection tSelGenD(tMasLeftD, tMasRightD);

 while (tCurrentRowBaseCache - 1 >= 0)
    {
        tCurrentRowBaseCache = tCurrentRowBaseCache - 1;
        //if ( !lTableViewGen[tabsRd->currentIndex()]->isRowHidden(tCurrentRowBaseCache))
        if ( !lTableViewGen[tabsRd->currentIndex()]->isRowHidden(tCurrentRowBaseCache))

        {
            QModelIndex tMasLeftS = ModelData->index(tCurrentRowBaseCache, 0, QModelIndex());
            QModelIndex tMasRightS = ModelData->index(tCurrentRowBaseCache, tStorDate->GetFieldCod().length()-1, QModelIndex());


            QItemSelection tSelGenS(tMasLeftS, tMasRightS);

            SelecGen->select(tSelGenD, QItemSelectionModel::Deselect);

            emit  SelecGen->selectionChanged(tSelGenS, tSelGenD); //эммитирует сигнал для изменения select
            break;

        }

    }


}


void DialGen::SlotKeyPgDown()
{
   if (TypeDial == BASE_CACHE )
{
    tCurrentRowBaseCache = SelecGen->currentIndex().row();

    QModelIndex  tMasLeftD = ModelData->index(tCurrentRowBaseCache, 0, QModelIndex());
    QModelIndex  tMasRightD = ModelData->index(tCurrentRowBaseCache, tStorDate->GetFieldCod().length()-1, QModelIndex());

    QItemSelection tSelGenD(tMasLeftD, tMasRightD);

 while (tCurrentRowBaseCache + 1 < ModelData->rowCount(QModelIndex()))
    {
        tCurrentRowBaseCache = tCurrentRowBaseCache + 1;
        //if ( !lTableViewGen[tabsRd->currentIndex()]->isRowHidden(tCurrentRowBaseCache))
        if ( !lTableViewGen[tabsRd->currentIndex()]->isRowHidden(tCurrentRowBaseCache))

        {
            QModelIndex tMasLeftS = ModelData->index(tCurrentRowBaseCache, 0, QModelIndex());
            QModelIndex tMasRightS = ModelData->index(tCurrentRowBaseCache, tStorDate->GetFieldCod().length()-1, QModelIndex());
            QItemSelection tSelGenS(tMasLeftS, tMasRightS);

            SelecGen->select(tSelGenD, QItemSelectionModel::Deselect);

            emit  SelecGen->selectionChanged(tSelGenS, tSelGenD); //эммитирует сигнал для изменения select
            break;

        }

    }
}

if (TypeDial == DOCUM_GEN )
{



    tCurrentRowDocumGen = SelecGen->currentIndex().row();

    QModelIndex  tMasLeftD = ModelData->index(tCurrentRowBaseCache, 0, QModelIndex());
    QModelIndex  tMasRightD = ModelData->index(tCurrentRowBaseCache, tStorDate->GetFieldCod().length()-1, QModelIndex());

    QItemSelection tSelGenD(tMasLeftD, tMasRightD);

 while (tCurrentRowBaseCache + 1 < ModelData->rowCount(QModelIndex()))
    {
        tCurrentRowBaseCache = tCurrentRowBaseCache + 1;
       // if ( !lTableViewGen[tabsRd->currentIndex()]->isRowHidden(tCurrentRowBaseCache))
        if ( !lTableViewGen[tabsRd->currentIndex()]->isRowHidden(tCurrentRowBaseCache))

        {
            QModelIndex tMasLeftS = ModelData->index(tCurrentRowBaseCache, 0, QModelIndex());
            QModelIndex tMasRightS = ModelData->index(tCurrentRowBaseCache, tStorDate->GetFieldCod().length()-1, QModelIndex());
            QItemSelection tSelGenS(tMasLeftS, tMasRightS);

            SelecGen->select(tSelGenD, QItemSelectionModel::Deselect);

            emit  SelecGen->selectionChanged(tSelGenS, tSelGenD); //эммитирует сигнал для изменения select
            break;

        }

    }




}


}

void DialGen::SlotKeyMyRight()
{
    tabsRd->setCurrentIndex(tabsRd->currentIndex()+1);
}

void DialGen::SlotKeyMyLeft()
{
     tabsRd->setCurrentIndex(tabsRd->currentIndex()-1);
}


void DialGen::SlotInfoNext()
{


    switch (TypeDial)
    {

    case BASE_GEN:
    {
       StakeGenSubBase->setCurrentIndex(1);
       tLabelInfo->setText("BASE");
       TypeDial = BASE_CACHE;
    }
        break;

    case BASE_CACHE:
    {

   QModelIndex  tMasLeftD = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
                QModelIndex  tMasRightD = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
                QItemSelection tSelInfoD(tMasLeftD, tMasRightD);


    while (tCurrentRowInfo + 1 < tStorDate->GetFieldCod().length())
          {
                    tCurrentRowInfo = tCurrentRowInfo + 1;
                    if ( !TableViewInfo->isRowHidden(tCurrentRowInfo))

                    {

                        QModelIndex tMasLeftS = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
                        QModelIndex tMasRightS = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
                        QItemSelection tSelInfoS(tMasLeftS, tMasRightS);


                        SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);
                        SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);
                        emit  SelecInfo->selectionChanged(tSelInfoS, tSelInfoD); //эммитирует сигнал для изменения select

                        break;


                    }



         }


    }
        break;

    case DOCUM_GEN:
    {

        /*
        tStorDate->SetCachCurrentCountData(tCurrentRowInfo);
        lListViewCache.at(tCurrentRowInfo)->update(QModelIndex());

       TextSearch.clear();
       countSearch = 0;
        //bool ok2;


        QModelIndex  tMasLeftD = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
        QModelIndex  tMasRightD = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
        QItemSelection tSelInfoD(tMasLeftD, tMasRightD);


        //Установка значения в таблицу инфо


        QString ttText = listTextEditGen.at(tCurrentRowInfoPrev)->toPlainText();
        QModelIndex MMIndex = TableViewInfo->model()->index(tCurrentRowInfoPrev,1);
        TableViewInfo->model()->setData(MMIndex,ttText, Qt::EditRole);


        //Если новая запись, то в кэш

           // NewRowsInCash(listTextEdit.at(tCurrentRowInfo)->toPlainText().replace(",", "."));

        if(tCurrentRowInfo == 0)

        {


//Зависимость документа от уровня

            QString tText = listTextEditGen.at(tCurrentRowInfo)->toPlainText().replace(",", ".");
            QStringList stText = tText.split(".");

//--Устанавливаем таблицу вкоторой содержатся список документов всех уровней
            StakeGenSub->setCurrentIndex(2);

            if (listTextEditGen.at(tCurrentRowInfo)->toPlainText() == "" )
                StakeGenSubNewDocumGen->setCurrentIndex(0);

            else if(stText.length()== 1)
                StakeGenSubNewDocumGen->setCurrentIndex(1);

            else if(stText.length()== 2)
                StakeGenSubNewDocumGen->setCurrentIndex(2);

        }

        if (tCurrentRowInfo == 1)

        {

            for (int i=0; i < tStorDate->GetDocNameN().length(); i++ )
            {
                if (tStorDate->GetDocNameN().value(i) == listTextEditGen.at(tCurrentRowInfo)->toPlainText())
                {
                   for (int ii=0; ii < tStorDate->GetDocFieldN().value(i).length(); ii++)
                   {
                        lfShow.append(tStorDate->GetDocFieldN().value(i).value(ii));

                   }
                }
             //lfShow = tStorage->GetFieldDocumForShow(listTextEdit.at(tCurrentRowInfo)->toPlainText());

            }

             for(int k=2; k<lfShow.length(); k++)
              {

                 if (lfShow.value(k) == 0) // если 0, то скрываем. Показываем 1
                    TableViewInfo->setRowHidden(k,true);

                 else
                    TableViewInfo->setRowHidden(k, false);

              }

//--Устанавливаем StakeGenCache видимым
                StakeGenSub->setCurrentIndex(3);


       }



       while (tCurrentRowInfo + 1 < tStorDate->GetFieldCod().length())
                    {

                        StakeGenSubCache->widget(tCurrentRowInfo);

                        tCurrentRowInfo = tCurrentRowInfo + 1;
                        if ( !TableViewInfo->isRowHidden(tCurrentRowInfo))

                        {

//--Доделать Вывод типа поля

                                tCurrentRowInfoPrev = tCurrentRowInfo;
                                QModelIndex tMasLeftS = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
                                QModelIndex tMasRightS = ModelProj->index(tCurrentRowInfo, 1, QModelIndex());
                                QItemSelection tSelInfoS(tMasLeftS, tMasRightS);

                                SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);
                                SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);

                               emit  SelecInfo->selectionChanged(tSelInfoS, tSelInfoD); //эммитирует сигнал для изменения select
                               break;
                        }

                    }
*/
    }
        break;

    default:
    {

        QModelIndex  tMasLeftD = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
        QModelIndex  tMasRightD = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
        QItemSelection tSelInfoD(tMasLeftD, tMasRightD);


     while (tCurrentRowInfo + 1 < tStorDate->GetFieldCod().length())
        {
            tCurrentRowInfo = tCurrentRowInfo + 1;
            if ( !TableViewInfo->isRowHidden(tCurrentRowInfo))

            {

                QModelIndex tMasLeftS = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
                QModelIndex tMasRightS = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
                QItemSelection tSelInfoS(tMasLeftS, tMasRightS);

                SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);
                SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);


                emit  SelecInfo->selectionChanged(tSelInfoS, tSelInfoD); //эммитирует сигнал для изменения select
                break;


            }

        }


    }
        break;
    }


}

void DialGen::SlotInfoPrev()
{

    TextSearch.clear();
    countSearch = 0;

    QModelIndex  tMasLeftD = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
    QModelIndex  tMasRightD = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
    QItemSelection tSelInfoD(tMasLeftD, tMasRightD);


 while (tCurrentRowInfo - 1 >= 0)
    {
        tCurrentRowInfo = tCurrentRowInfo - 1;
        if ( !TableViewInfo->isRowHidden(tCurrentRowInfo))

        {

            QModelIndex tMasLeftS = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
            QModelIndex tMasRightS = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
            QItemSelection tSelInfoS(tMasLeftS, tMasRightS);

            SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);
            SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);


            emit  SelecInfo->selectionChanged(tSelInfoS, tSelInfoD); //эммитирует сигнал для изменения select
            break;


        }

    }

}
//--
void DialGen::OperFind()
{

    tSpeed.start();


     QString tFiltr = tTextEdit->toPlainText();

     tStorDate->LoadSql(tCurrentRowInfo, tFiltr);
     tStorDate->LoadDataCount();
     tStorDate->LoadData();

     ModelUpdate();
     SlotKeyEnd();

   tSpeedUpdate = tSpeed.elapsed();


}


void DialGen::OperSort()
{

    tSpeed.start();



     tStorDate->LoadSort(tCurrentRowInfo);
     tStorDate->LoadDataCount();
     tStorDate->LoadData();

     ModelUpdate();

   SlotKeyEnd();

   tSpeedUpdate = tSpeed.elapsed();

}


void DialGen::OperFindBack()
{

    tSpeed.start();


    tStorDate->Set_DataCountSqlRem();
    tStorDate->LoadDataCount();
    tStorDate->LoadData();

    ModelUpdate();

   SlotKeyEnd();


   tSpeedUpdate = tSpeed.elapsed();


}



//--Добавление нового документа

void DialGen::SlotKeyNewDoc()
{

     if (TypeDial == BASE_CACHE )

    {

       TypeDial = DOCUM_GEN;


//--Установка модели и вьюверов Cache для документов


//-------Скрытие строк в инфо


        for(int k=1;k<TableViewInfo->model()->rowCount(QModelIndex());k++)
        {
           TableViewInfo->setRowHidden(k, true);

        }


       // tTextEdit->clear();
        tTextEdit->setFocus();
        tTextEdit->selectAll();

       StakeGenSub->setCurrentIndex(1);
       StakeGenSubNewDocum->setCurrentIndex(0);


//Переход на первую запись в инфо

       QModelIndex  tMasLeftD = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
       QModelIndex  tMasRightD = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
                    QItemSelection tSelInfoD(tMasLeftD, tMasRightD);
                    SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);


        tCurrentRowInfo = 0;

        QModelIndex tMasLeftS = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
        QModelIndex tMasRightS = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
        QItemSelection tSelInfoS(tMasLeftS, tMasRightS);

        SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);
        SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);
        emit  SelecInfo->selectionChanged(tSelInfoS, tSelInfoD);

int Level = tStorDate->Get_Level_Base(tTextEdit->toPlainText());
QString stLevel = QString::fromLocal8Bit("%1").arg(Level);

vDoc->setWordWrap(false);
vDoc->setShowGrid(false);
vDoc->setColumnWidth(0, 1200);

for (int i = 0; i <= tStorDate->GetDocLevelN().length() - 1; i++ )
       vDoc->showRow(i);

//--Скрытие строк списка документов в зависимости от уровня
for (int i = 0; i <= tStorDate->GetDocLevelN().length() - 1; i++ )
if (tStorDate->GetDocLevelN().value(i) != stLevel )
       vDoc->hideRow(i);

 }

    else

    {

        //if (flagChangeSlot == true)
            NewRowsSave();


       StakeGenSub->setCurrentIndex(0);
       TypeDial = BASE_CACHE;

    }



}


void DialGen::SlotKeyNewFiltr()
{

    if (TypeDial == BASE_CACHE)

    {


        tTextEdit->clear();
        tTextEdit->setFocus();
        tTextEdit->selectAll();

//StakeText->setCurrentIndex(1);
StakeGenSub->setCurrentIndex(1);

//-----------------------------

    }

    else

    {

      // StakeText->setCurrentIndex(0);
       StakeGenSub->setCurrentIndex(0);
       TypeDial = BASE_CACHE;

    }
}


void DialGen::SlotKeyNewFind()
{

    if (flagNewViewFind == 0 )

    {

    //-------Скрытие строк


        for(int k=2;k<TableViewInfo->model()->rowCount(QModelIndex());k++)
        {
           TableViewInfo->setRowHidden(k, true);

        }

//--Активируем формы Cache
            StakeGenSub->setCurrentIndex(3);

//Переход на первую запись в инфо


            QModelIndex  tMasLeftD = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
            QModelIndex  tMasRightD = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
            QItemSelection tSelInfoD(tMasLeftD, tMasRightD);

             tCurrentRowInfo = 0;

            QModelIndex tMasLeftS = ModelInfo->index(tCurrentRowInfo, 0, QModelIndex());
            QModelIndex tMasRightS = ModelInfo->index(tCurrentRowInfo, 1, QModelIndex());
            QItemSelection tSelInfoS(tMasLeftS, tMasRightS);

            SelecInfo->select(tSelInfoS, QItemSelectionModel::Select);
            SelecInfo->select(tSelInfoD, QItemSelectionModel::Deselect);

            emit  SelecInfo->selectionChanged(tSelInfoS, tSelInfoD); //эммитирует сигнал для изменения select

//-----------------------------

        TypeDial = DOCUM_GEN;

    }

    else

    {

            NewRowsSave();


       StakeGenSub->setCurrentIndex(0);
       TypeDial = BASE_CACHE;

    }



}







void DialGen::SlotKeyRight()
{

    QTextCursor cursor = tTextEdit->textCursor();

    cursor.clearSelection();

    tTextEdit->setTextCursor(cursor);

    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);
    tTextEdit->setTextCursor(cursor);


}

void DialGen::SlotKeyLeft()
{

    QTextCursor cursor = tTextEdit->textCursor();

    cursor.clearSelection();

    tTextEdit->setTextCursor(cursor);


    cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
    tTextEdit->setTextCursor(cursor);

}

void DialGen::SlotKeyUP()
{

    flagChangeSlot = true;
    QModelIndex  tMIndexCurrent;

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

        tMIndexCurrent  =  vDoc->selectionModel()->currentIndex();


        if (tCurrentRowInfo == 1)
        {

            int CurrentRow = tMIndexCurrent.row(); //текущая запись

            QModelIndex  tMIndex = vDoc->model()->index(CurrentRow - 1,0, QModelIndex());

            vDoc->selectionModel()->clearSelection();
            vDoc->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

            tTextEdit->setText(vDoc->model()->data(tMIndex, Qt::DisplayRole).toString());
            tTextEdit->selectAll();

            CurrentData = vDoc->model()->data(tMIndex, Qt::DisplayRole).toString();


        }

        else
        {

            QModelIndex  tMIndexCurrent =  lListViewCache.at(tCurrentRowInfo)->selectionModel()->currentIndex();
            QModelIndex  tMIndex;

            int ddd = tMIndexCurrent.row();

            if (ddd < 0)

                tMIndex  = lListViewCache.at(tCurrentRowInfo)->model()->index(0,0, QModelIndex());

             else

               tMIndex = lListViewCache.at(tCurrentRowInfo)->model()->index(ddd - 1,0, QModelIndex());


            lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
            lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);


            tTextEdit->setText(lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString());
            tTextEdit->selectAll();



            CurrentData = lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString();

       }

    }
        break;

    case DOCUM_CACHE:
    {
    }
        break;


   }


flagChangeSlot = false;
}



void DialGen::SlotKeyDown()
{
    flagChangeSlot = true;
    QModelIndex  tMIndexCurrent;


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

        tMIndexCurrent  =  vDoc->selectionModel()->currentIndex();


       if (tCurrentRowInfo == 1)
       {


           int CurrentRow = tMIndexCurrent.row(); //текущая запись


           QModelIndex  tMIndex = vDoc->model()->index(CurrentRow + 1,0, QModelIndex());

           vDoc->selectionModel()->clearSelection();
           vDoc->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

           tTextEdit->setText(vDoc->model()->data(tMIndex, Qt::DisplayRole).toString());
           tTextEdit->selectAll();

           CurrentData = vDoc->model()->data(tMIndex, Qt::DisplayRole).toString();



       }

       else

       {

              //Определяет выделение строки
                   QModelIndex  tMIndexCurrent =  lListViewCache.at(tCurrentRowInfo)->selectionModel()->currentIndex();
                   QModelIndex  tMIndex;

                   int ddd = tMIndexCurrent.row();

                   if (ddd < 0)

                       tMIndex  = lListViewCache.at(tCurrentRowInfo)->model()->index(0,0, QModelIndex());

                    else

                      tMIndex = lListViewCache.at(tCurrentRowInfo)->model()->index(ddd + 1,0, QModelIndex());


                   lListViewCache.at(tCurrentRowInfo)->selectionModel()->clearSelection();
                   lListViewCache.at(tCurrentRowInfo)->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

                   tTextEdit->setText(lListViewCache.at(tCurrentRowInfo)->model()->data(tMIndex, Qt::DisplayRole).toString());
                   tTextEdit->selectAll();

       }


            }
        break;


        case DOCUM_CACHE:
                {
                }
        break;



    }
flagChangeSlot = false;



}


void DialGen::SlotKeyTab()
{


    if (TypeDial == DOCUM_GEN )
    {


            if(TextSearch != "")
            {

                TextSearch = tTextEdit->toPlainText().replace(",", ".") ;

                QModelIndexList lSearch; //массив для найденых строк

                lSearch = vDoc->model()->match(vDoc->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, -1, Qt::MatchContains);

                /*

                                if (StakeGenSub->currentIndex() == 2)
                lSearch = vDoc1->model()->match(vDoc1->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, -1, Qt::MatchContains);

                                if (StakeGenSub->currentIndex() == 3)
                lSearch = vDoc2->model()->match(vDoc2->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, -1, Qt::MatchContains);


                                if (StakeGenSub->currentIndex() == 4)
                lSearch = vDoc3->model()->match(vDoc3->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, -1, Qt::MatchContains);
*/

                                QModelIndex  tMIndexS;
                                if (lSearch.length()>0)
                                {
                                    tMIndexS = lSearch.at(countSearch);

        vDoc->selectionModel()->clearSelection();
        vDoc->selectionModel()->setCurrentIndex(tMIndexS, QItemSelectionModel::Select);
        CurrentData = vDoc->model()->data(tMIndexS, Qt::DisplayRole).toString();

                                    /*
                                    if (StakeGenSub->currentIndex() == 2)
                                    {
                                    vDoc1->selectionModel()->clearSelection();
                                    vDoc1->selectionModel()->setCurrentIndex(tMIndexS, QItemSelectionModel::Select);
                                    CurrentData = vDoc1->model()->data(tMIndexS, Qt::DisplayRole).toString();
                                    }


                                    if (StakeGenSub->currentIndex() == 3)
                                    {
                                    vDoc2->selectionModel()->clearSelection();
                                    vDoc2->selectionModel()->setCurrentIndex(tMIndexS, QItemSelectionModel::Select);
                                    CurrentData = vDoc2->model()->data(tMIndexS, Qt::DisplayRole).toString();
                                    }


                                    if (StakeGenSub->currentIndex() == 4)
                                    {
                                    vDoc3->selectionModel()->clearSelection();
                                    vDoc3->selectionModel()->setCurrentIndex(tMIndexS, QItemSelectionModel::Select);
                                    CurrentData = vDoc3->model()->data(tMIndexS, Qt::DisplayRole).toString();
                                    }

*/


                                    if(countSearch == lSearch.length() - 1)
                                     countSearch = 0;
                                    else
                                    countSearch = countSearch + 1;
                                }

                //------------------------Выделение найденой строки

                                QModelIndex  tMIndexCurrent;

 tMIndexCurrent =  vDoc->selectionModel()->currentIndex();

                                /*
                        if (StakeGenSub->currentIndex() == 2)
                                 tMIndexCurrent =  vDoc1->selectionModel()->currentIndex();

                        if (StakeGenSub->currentIndex() == 3)
                                 tMIndexCurrent =  vDoc2->selectionModel()->currentIndex();

                        if (StakeGenSub->currentIndex() == 4)
                                 tMIndexCurrent =  vDoc3->selectionModel()->currentIndex();
*/



                               int dddd = tMIndexCurrent.row();
                               if (dddd >= 0)
                               {

                                 QModelIndex  tMIndex;

    tMIndex = vDoc->model()->index(dddd, 0, QModelIndex());

        vDoc->selectionModel()->clearSelection();
        vDoc->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

                                 /*

                                if (StakeGenSub->currentIndex() == 2)
                                {
                                tMIndex = vDoc1->model()->index(dddd, 0, QModelIndex());

                                vDoc1->selectionModel()->clearSelection();
                                vDoc1->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

                                }


                                if (StakeGenSub->currentIndex() == 3)
                                {
                                tMIndex = vDoc2->model()->index(dddd, 0, QModelIndex());

                                vDoc2->selectionModel()->clearSelection();
                                vDoc2->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

                                }


                                if (StakeGenSub->currentIndex() == 4)
                                {
                                tMIndex = vDoc3->model()->index(dddd, 0, QModelIndex());

                                vDoc3->selectionModel()->clearSelection();
                                vDoc3->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);

                                }

                                */

                                tTextEdit->selectAll();

                               }

            }

        else
        {

           TextSearch = tTextEdit->toPlainText().replace(",", ".") ;



           if(TextSearch != "") //Если поле для ввода не пустое

            {

                QModelIndexList lSearch; //массив для найденых строк

lSearch = vDoc->model()->match(vDoc->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, -1, Qt::MatchContains);

                /*
                if (StakeGenSub->currentIndex() == 2)
lSearch = vDoc1->model()->match(vDoc1->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, -1, Qt::MatchContains);

                if (StakeGenSub->currentIndex() == 3)
lSearch = vDoc2->model()->match(vDoc2->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, -1, Qt::MatchContains);


                if (StakeGenSub->currentIndex() == 4)
lSearch = vDoc3->model()->match(vDoc3->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, -1, Qt::MatchContains);
*/

                QModelIndex  tMIndexS;
                if (lSearch.length()>0)
                {
                    tMIndexS = lSearch.at(countSearch);

       vDoc->selectionModel()->clearSelection();
       vDoc->selectionModel()->setCurrentIndex(tMIndexS, QItemSelectionModel::Select);
       CurrentData = vDoc->model()->data(tMIndexS, Qt::DisplayRole).toString();

                    /*
                    if (StakeGenSub->currentIndex() == 2)
                    {
                    vDoc1->selectionModel()->clearSelection();
                    vDoc1->selectionModel()->setCurrentIndex(tMIndexS, QItemSelectionModel::Select);
                    CurrentData = vDoc1->model()->data(tMIndexS, Qt::DisplayRole).toString();
                    }


                    if (StakeGenSub->currentIndex() == 3)
                    {
                    vDoc2->selectionModel()->clearSelection();
                    vDoc2->selectionModel()->setCurrentIndex(tMIndexS, QItemSelectionModel::Select);
                    CurrentData = vDoc2->model()->data(tMIndexS, Qt::DisplayRole).toString();
                    }


                    if (StakeGenSub->currentIndex() == 4)
                    {
                    vDoc3->selectionModel()->clearSelection();
                    vDoc3->selectionModel()->setCurrentIndex(tMIndexS, QItemSelectionModel::Select);
                    CurrentData = vDoc3->model()->data(tMIndexS, Qt::DisplayRole).toString();
                    }
*/


                    if(countSearch == lSearch.length() - 1)
                     countSearch = 0;
                    else
                    countSearch = countSearch + 1;
                }

//------------------------Выделение найденой строки

                QModelIndex  tMIndexCurrent;

      tMIndexCurrent =  vDoc->selectionModel()->currentIndex();

                /*
        if (StakeGenSub->currentIndex() == 2)
                 tMIndexCurrent =  vDoc1->selectionModel()->currentIndex();

        if (StakeGenSub->currentIndex() == 3)
                 tMIndexCurrent =  vDoc2->selectionModel()->currentIndex();

        if (StakeGenSub->currentIndex() == 4)
                 tMIndexCurrent =  vDoc3->selectionModel()->currentIndex();

*/


               int dddd = tMIndexCurrent.row();
               if (dddd >= 0)
               {

                 QModelIndex  tMIndex;

                 tMIndex = vDoc->model()->index(dddd, 0, QModelIndex());

                 vDoc->selectionModel()->clearSelection();
                 vDoc->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);
                 tTextEdit->setText(vDoc->model()->data(tMIndex, Qt::DisplayRole).toString());

                 /*
                if (StakeGenSub->currentIndex() == 2)
                {
                tMIndex = vDoc1->model()->index(dddd, 0, QModelIndex());

                vDoc1->selectionModel()->clearSelection();
                vDoc1->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);
                tTextEdit->setText(vDoc1->model()->data(tMIndex, Qt::DisplayRole).toString());
                }


                if (StakeGenSub->currentIndex() == 3)
                {
                tMIndex = vDoc2->model()->index(dddd, 0, QModelIndex());

                vDoc2->selectionModel()->clearSelection();
                vDoc2->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);
                tTextEdit->setText(vDoc2->model()->data(tMIndex, Qt::DisplayRole).toString());
                }


                if (StakeGenSub->currentIndex() == 4)
                {
                tMIndex = vDoc3->model()->index(dddd, 0, QModelIndex());

                vDoc3->selectionModel()->clearSelection();
                vDoc3->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);
                tTextEdit->setText(vDoc3->model()->data(tMIndex, Qt::DisplayRole).toString());
                }
*/

                 tTextEdit->selectAll();

               }

            }

        }

    }

}


void DialGen::SetDataInfoLable()
{

    QString tForInfoLable = QString::fromLocal8Bit(
                                                   "Кол-во строк: %1 \n"
                                                   "Текущая запись: %2 \n"
                                                   "Время загрузки: %3 млс"
                                                   )
                            .arg(tStorDate->Get_DataCount())
                            .arg(SelecGen->currentIndex().row() + 1)
                            .arg(tSpeedUpdate);

    tLabelInfo->setText(tForInfoLable);
}

void DialGen::SetDataInfoConsol()
{
   tInfoGenLocal->setText(tStorDate->Get_SqlText());

}

void DialGen::SlotChangedText()
{

    SetDataInfoLable();
    SetDataInfoConsol();

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

        if (flagChangeSlot)
             return;


        QString TextSearchLocal = tTextEdit->toPlainText().replace(",", ".") ;

     QModelIndexList lSearch; //массив для найденых строк
   //  lSearch = lListViewCache.at(tCurrentRowInfo)->model()->match(lListViewCache.at(tCurrentRowInfo)->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearchLocal, 1, Qt::MatchStartsWith);

 lSearch = vDoc->model()->match(vDoc->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearchLocal, 1, Qt::MatchStartsWith);

     /*
     if (StakeGenSub->currentIndex() == 2)
     lSearch = vDoc1->model()->match(vDoc1->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearchLocal, 1, Qt::MatchStartsWith);

     if (StakeGenSub->currentIndex() == 3)
     lSearch = vDoc2->model()->match(vDoc2->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearchLocal, 1, Qt::MatchStartsWith);

     if (StakeGenSub->currentIndex() == 4)
     lSearch = vDoc3->model()->match(vDoc3->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearchLocal, 1, Qt::MatchStartsWith);
*/

     QModelIndex  tMIndex;
     if (lSearch.length()>0)
     {
       tMIndex = lSearch.at(0);

 vDoc->selectionModel()->clearSelection();
 vDoc->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);
 CurrentData = vDoc->model()->data(tMIndex, Qt::DisplayRole).toString();


       /*
       if (StakeGenSub->currentIndex() == 2)
       {
       vDoc1->selectionModel()->clearSelection();
       vDoc1->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);
       CurrentData = vDoc1->model()->data(tMIndex, Qt::DisplayRole).toString();
       }

       if (StakeGenSub->currentIndex() == 3)
       {
       vDoc2->selectionModel()->clearSelection();
       vDoc2->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);
       CurrentData = vDoc2->model()->data(tMIndex, Qt::DisplayRole).toString();
       }

       if (StakeGenSub->currentIndex() == 4)
       {
       vDoc3->selectionModel()->clearSelection();
       vDoc3->selectionModel()->setCurrentIndex(tMIndex, QItemSelectionModel::Select);
       CurrentData = vDoc3->model()->data(tMIndex, Qt::DisplayRole).toString();
       }
*/


            bForSeach = 1;
        }

      //  parChangeTextBit.setBit(tCurrentRowInfo);


        }
            break;

 }



}

void DialGen::mClearValinInfo()
{
/*
  for (int i = 0; i < ModelProj->rowCount(QModelIndex()); i++)
  {
    if (parChangeTextBit.at(i) == true)
        lModelCach.at(i)->Save(listTextEdit.at(i)->toPlainText());

        QModelIndex MMIndex = TableViewInfo->model()->index(i,1);
        ModelProj->setData(MMIndex,"", Qt::EditRole);


  }

//--Установка на первую запись
  tCurrentRowInfo = 0;
  QModelIndex  tMasLeft = ModelProj->index(tCurrentRowInfo, 0, QModelIndex());
  SelecInfo->setCurrentIndex(tMasLeft, QItemSelectionModel::Select);


//---Обнуляем параметры изменения
  for (int i = 0; i < ModelProj->rowCount(QModelIndex()); i++)
   parChangeTextBit.clearBit(i);

*/
}

void DialGen::NewRowsInCash(QString TextSearch)
{



    QModelIndexList lSearch; //массив для найденых строк
    lSearch = lListViewCache.at(tCurrentRowInfo)->model()->match(lListViewCache.at(tCurrentRowInfo)->model()->index(0,0,QModelIndex()), Qt::DisplayRole, TextSearch, 1, Qt::MatchStartsWith);

    if (lSearch.length()==0)
    {


        lListViewCache.at(tCurrentRowInfo)->model()->insertRow(0, QModelIndex());
        int tCountRow = lListViewCache.at(tCurrentRowInfo)->model()->rowCount(QModelIndex());
        int tLastRow = tCountRow - 1;

        QModelIndex MMIndexNull = lListViewCache.at(tCurrentRowInfo)->model()->index(tLastRow,0);
        lListViewCache.at(tCurrentRowInfo)->model()->setData(MMIndexNull, TextSearch, Qt::EditRole);

        //Обновление
        lListViewCache.at(tCurrentRowInfo)->update(MMIndexNull);


    }

}

void DialGen::SlotKeyEnd()
{

//--Отменяем текущий выбор
  tCurrentRowBaseCache = SelecGen->currentIndex().row();


  // int tCurrentRowGenEnd = tStorDate->Get_DataCount() - 1;
  // int tCurrentColGenEnd = tStorDate->GetFieldCod().length() - 1;

   QModelIndex iDeselectL = ModelData->index(tCurrentRowBaseCache, 0, QModelIndex());
   QModelIndex iDeselectR = ModelData->index(tCurrentRowBaseCache, tStorDate->GetFieldCod().length() - 1, QModelIndex());

   QItemSelection tSelDeSelect(iDeselectL, iDeselectR);
   SelecGen->select(tSelDeSelect, QItemSelectionModel::Deselect);

//--Делаем новый выбор последней записи

   QModelIndex  iSelectL = ModelData->index(tStorDate->Get_DataCount() - 1, 0, QModelIndex());
   QModelIndex  iSelectR = ModelData->index(tStorDate->Get_DataCount() - 1, tStorDate->GetFieldCod().length() - 1, QModelIndex());

   QItemSelection tSelSelect(iSelectL, iSelectR);
   SelecGen->select(tSelSelect, QItemSelectionModel::Select);

  emit  SelecGen->selectionChanged(tSelSelect, tSelDeSelect); //эммитирует сигнал для изменения select


}

void DialGen::NewRowsSave()
{
/*
 qDebug()<<"NewRowsSave";

     QString tTextForWrite;

     QList<QString> mTextForWritre;

     for(int i=0; i<listTextEdit.length(); i++)
     {
         tTextForWrite.append(listTextEdit.at(i)->toPlainText());
         mTextForWritre<<listTextEdit.at(i)->toPlainText();

         if (i==0)
          tTextForWrite.append("-");

         if (i<listTextEdit.length()-1)
          tTextForWrite.append("|");
         else
            tTextForWrite.append("\r\n");
     }

     ModelData->Save(tTextForWrite);
*/
}

/*
void DialGen::ScrollBarValueChanged()
{
}
*/

void DialGen::SlotFontPlus()
{

    tTextEdit->zoomIn(SizeFont);

}

void DialGen::SlotFontMinus()
{

    tTextEdit->zoomOut(SizeFont);
}


void DialGen::LoadData()
{


    tStorDate->LoadData();

}

void DialGen::LoadUpdate()
{

    tStorDate->LoadUpdate();

 }


void DialGen::LoadCurent()
{

   tStorDate->LoadDataClear();

   lTableViewGen[tabsRd->currentIndex()]->viewport()->update();

}



void DialGen::fWidjetEnable(int tWidjetEnable)
{

    keyCtrlDPgUp->setEnabled(tWidjetEnable);
    keyCtrlDPgDown->setEnabled(tWidjetEnable);
    keyCtrlDRight->setEnabled(tWidjetEnable);
    keyCtrlDLeft->setEnabled(tWidjetEnable);
    keyEnter->setEnabled(tWidjetEnable);
    keyEnterShift->setEnabled(tWidjetEnable);
    keyCtrlD->setEnabled(tWidjetEnable);
    keyCtrlFilter->setEnabled(tWidjetEnable);
    keyEnd->setEnabled(tWidjetEnable);

}

void DialGen::ModelUpdate()
{
    delete ModelData;
    delete SelecGen;
    ModelData = new ModelUni(DATA, tStorDate);

    for(int i = 0; i < tStorDate->GetDialogName().length(); i++)

    {
        lTableViewGen.value(i)->setModel(ModelData);

        if (i==0)
            SelecGen  =  lTableViewGen.value(i)->selectionModel();
        else
            lTableViewGen.value(i)->setSelectionModel(SelecGen);

connect(lTableViewGen.value(i)->selectionModel(), &QItemSelectionModel::selectionChanged,this, &DialGen::SlotCurrentChangedBaseCache);

    }



}
