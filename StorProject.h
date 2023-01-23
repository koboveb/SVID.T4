#include <QFile>
#include <QtXml>


#ifndef STORPROJECT_H
#define STORPROJECT_H

class StorProject
{
public:
     StorProject(const QString &tPath);
    ~StorProject();

//-------Get Выдача. Поля

const QStringList &GetFieldCod() const;//выдача Кодов полей
const QStringList &GetFieldType() const;//выдача Типов полей
const QStringList &GetFieldName() const;//выдача Имен полей
const QList<int> &GetFieldWidth() const;//выдача Ширины полей
//const QStringList &GetFieldDialogName() const;//выдача Диалогов полей

const QList<QList<int>> &GetFieldWidthN() const;//выдача Ширины полей
const QList<QList<int>> &ll_vv_FieldIndexN() const;//выдача Индексовввв полей


const QList<QStringList> &GetFieldCodN() const;//выдача Кодов полей


const QStringList &GetFieldPath() const;//выдача Путей полей

//--Get Выдача. Диалоги

const QStringList &GetDialogName() const; //Диалоги. Выдача. Имен
const QStringList &GetDialogCodName() const; //Диалоги. Выдача. Код + Имя


//--Get Выдача. Документы. Получение кодов.
const QStringList &GetDocCodN() const;

//--Get Выдача. Документы. Получение имен.
const QStringList &GetDocNameN() const;



//--Get Выдача. Документы. Получение уровня.
const QStringList &GetDocLevelN() const;


//--Get Выдача. Документы. Списка полей.
const QList<QList<int>> &GetDocFieldN() const;



//--Get Выдача.Документы.Имя. В зависимости от уровня
QList<int> &GetFieldDocumForShow(QString tNameDocum );//выдача полей документов для отображения


const int  &Get_TimeOut() const; //размер страницы
const QList<QStringList> &GetFieldInfo() const; // данные для инфо


//---------Set Установка

void SetFieldInfo (int i, QString tVal); // установка значений в инфо


//private:
protected:

//--Общий текст для SQL

QString tTeloSqlFrom;
//QString tTeloSortBase;

QString tTeloSqlWhere;
QString tTeloSqlOreder;


//--Пути
    // QString path;
    // QString pathData;
    // QString pathCache;

//--База данных

     QString pathBaseAdress;
     QString pathBaseName;

     QString tBaseSql;
     QString tBaseSqlLevel;

//--файл проекта
    QFile* v_file_project;


//--размер страницы
    int tTimeOut;

//--Переменные для хранения параметров проекта
    QDomDocument Xml_SettingProject;



//--Переменные для Диалогов

    QStringList l_vv_DialogName; //Диалоги Имена
    QStringList l_vv_DialogCod; //Диалоги Код
    QStringList l_vv_DialogCodName; //Диалоги Код + Имя



//--Переменные для Полей

    QStringList l_vv_FieldName; //Поля. Имя поля
    QStringList l_vv_FieldCod; //Поля. Код
    QStringList l_vv_FieldType; //Поля. Тип
    QList<int> l_vv_FieldWidth; //Поля. Ширина
    QStringList l_vv_FieldCache;//Поля. Cache

//--Переменные для Полей структура по диалогам

    QList<QStringList> ll_vv_FieldName; //Поля. Имя поля
    QList<QStringList> ll_vv_FieldCod; //Поля. Код
    QList<QStringList> ll_vv_FieldType; //Поля. Тип
    QList<QList<int>> ll_vv_FieldWidth; //Поля. Ширина
    QList<QList<int>> ll_vv_FieldIndex; //Поля. Порядковый номер поля



//--Переменные для Документов

    QStringList l_vv_DocName; //Документ. Имя
    QStringList l_vv_DocCod;  //Документ. Код
    QStringList l_vv_DocLevel;//Документ. Уровень

    QList<QList<int>> l_vv_DocFieldIndex;  //Документ.Порядковый номер Поля.


//--Cписок для инфо
QList<QStringList> l_vv_FielInfo;

};

#endif // STORPROJECT_H
