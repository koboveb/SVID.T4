#include "StorProject.h"

#include <QSqlDatabase>
#include <QSqlQuery>

#ifndef STORDATA_H
#define STORDATA_H


class StorData: public StorProject
{
public:
    StorData(const QString &tPath);

//------------------------------------
  void LoadDataCount();
  void LoadSql();
  void LoadSql(int i, QString tValue);
  void LoadSort(int i);

  void LoadData ();
  void LoadUpdate ();

  void LoadDataClear();

  void LoadDataCachCount();
  void LoadDataCach();
//-------------------------------------
//основные данные
  const QList<QStringList> &Get_FieldData() const;


//--установка текущего количества кэша
  void SetCachCurrentCountData(int i);

//--установка текущей строки
  void SetCurentRow(int i);


//--данные кэша
const QStringList &Get_DataCach() const;
//количество записей в кэше
const int &Get_DataCountCach() const;

//количество записей в данных
const int &Get_DataCount() const;

//Интервал подгрузки. Первое значение интервала
const int &Get_Min() const;

//Интервал подгрузки. Текущее значение интервала
const int &Get_CurrentRow() const;

//количество запросов для истории
void Set_DataCountSqlRem();

//получение уровня документа из базы
int Get_Level_Base(QString tID);


//Информация о запросе
QString Get_SqlText();

private:

    QString tTeloSQL_Data;

    StorProject *tSroreProject;
    int tDataCount;

    QList< QStringList > l_vv_FieldData; //список полей


    int tMin;
    int CurentRow;

//--Переменные для отслеживания изменения в DialGen
    int tFirstValue;
    int tFirstValuePrev = 0;

    int tSizeListRow;
    int tSizeListRowPrev = 0;

  bool fUpdate = 0;

//--Переменные для кэша
    QList<QStringList> l_vv_Cache; //список полей

//--количество в текущем кэше
    int CachCurrentCount = 0;

//--данные в текущем кэше
    QStringList CachCurrentData;

//--количество записей данных кэша
    QList<int> lDataCachCount;

//--строки для подгрузки данных
    QList<int> lLoadData;

//--Запросы бд
    QSqlQuery q_BaseCount;
    QSqlQuery q_BaseData;

//--Отображаемые поля
   QString tNameField;

};

#endif // STORDATA_H
