#ifndef MODELUNI_H
#define MODELUNI_H

#include "StorData.h"


//enum typemodel { PROJECT, CACHE, DOCUM, DOCUM1, DOCUM2, DOCUM3, DATA, FILTR };
enum typemodel { INFO, CACHE, DOCUM, DATA };
class ModelUni: public QAbstractTableModel
{

//Q_OBJECT

public:

    ModelUni(typemodel TypeModel, StorData *StDt);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;


private:


StorData *sStorData;


    QStringList d1;
    QStringList d2;

    QList<QStringList> lPoleInfo;


//кол-во полей
    int CountField = 0;

//кол-во документов Всех
        int CountDoc = 0;

//кол-во документов 1-го уровня
       // int CountDoc1 = 0;

//кол-во документов 2-го уровня
       // int CountDoc2 = 0;

//кол-во документов 3-го уровня
      //  int CountDoc3 = 0;


//-------------------------------
//Имена документов
        QStringList lDocName;

//Имена документов 1-го уровня
        QStringList lDocName1;

//Имена документов 2-го уровня
        QStringList lDocName2;

//Имена документов 3-го уровня
         QStringList lDocName3;

//Имена фильтров
         QStringList lFiltrName;


//Имена полей
            QStringList lFieldName;

    typemodel TypeModelL;





signals:
  //  void numberPopulated(int number); //Разобраться

};

#endif // MODELUNI_H
