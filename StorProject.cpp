#include "StorProject.h"

StorProject::StorProject(const QString &tPath)
{
  QString tFileProject = QString::fromLocal8Bit("%1").arg(tPath);
  QFile *v_file_project = new  QFile(tFileProject);

    if (!v_file_project->open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug () << "Error open file : " << v_file_project;
            exit(0);
        }
 //-------------------------------------------------------------------

    Xml_SettingProject.setContent(v_file_project);

//----Установка значений пути к папке данных
    /*
    QDomNodeList lpathData = Xml_SettingProject.elementsByTagName("PathBase");
    pathData = QString::fromLocal8Bit("%1").arg(lpathData.item(0).toElement().text());

    QDomNodeList lpathCash = Xml_SettingProject.elementsByTagName("PathCash");
    pathCache =  QString::fromLocal8Bit("%1/").arg(lpathCash.item(0).toElement().text());
*/
//----Установка значений для подключения к базе данных
     QDomNodeList ListBaseAdress = Xml_SettingProject.elementsByTagName("BaseAdress");
     pathBaseAdress = QString::fromLocal8Bit("%1").arg(ListBaseAdress.item(0).toElement().text());

     QDomNodeList ListBaseName = Xml_SettingProject.elementsByTagName("BaseName");
     pathBaseName =  QString::fromLocal8Bit("%1").arg(ListBaseName.item(0).toElement().text());

     QDomNodeList ListBaseSql = Xml_SettingProject.elementsByTagName("BaseSql");
     tBaseSql =  QString::fromLocal8Bit("%1").arg(ListBaseSql.item(0).toElement().text());

     QDomNodeList ListBaseSqlLevel = Xml_SettingProject.elementsByTagName("BaseSqlLevel");
     tBaseSqlLevel =  QString::fromLocal8Bit("%1").arg(ListBaseSqlLevel.item(0).toElement().text());


//----Установка значений времени обновления
    QDomNodeList ltTimeOut = Xml_SettingProject.elementsByTagName("TimeOut");
    tTimeOut =  ltTimeOut.item(0).toElement().text().toInt();

//----Получение списка Диалогов
    QDomNodeList lDialog = Xml_SettingProject.elementsByTagName("Dialog");

//----Получение списка Полей он же порядковый номер поля
    QDomNodeList lField = Xml_SettingProject.elementsByTagName("Field");

//----Получение списка Документов
    QDomNodeList lDocum = Xml_SettingProject.elementsByTagName("Docum");

//----Получение списка Документов Диалогов от Документа
    QDomNodeList lDFiles = Xml_SettingProject.elementsByTagName("DField");


//----Получение списка Документов Диалогов от Документа
     QDomNodeList lFFiles = Xml_SettingProject.elementsByTagName("FField");

//---Установка значений для Dialog


     for (int i = 0; i < lDialog.length(); i++)
     {

     l_vv_DialogName.append(lDialog.item(i).toElement().attributeNode("name").value());
     l_vv_DialogCod.append(lDialog.item(i).toElement().attributeNode("cod").value());

     QString tCodDial = QString::fromLocal8Bit("%1.%2")
             .arg(lDialog.item(i).toElement().attributeNode("cod").value())
             .arg(lDialog.item(i).toElement().attributeNode("name").value());


     l_vv_DialogCodName.append(tCodDial);

     }
//---Установка значений для Field

     for (int i = 0; i < lField.length(); i++)
     {
//--Имя поля
         l_vv_FieldName.append(lField.item(i).toElement().attributeNode("name").value());

//--Код поля
        l_vv_FieldCod.append(lField.item(i).toElement().attributeNode("cod").value());

//--Тип поля
        l_vv_FieldType.append(lField.item(i).toElement().attributeNode("type").value());

//--Ширина поля
        l_vv_FieldWidth.append(lField.item(i).toElement().attributeNode("width").value().toInt());

//--Путь кэша и документов
        l_vv_FieldCache.append(lField.item(i).toElement().text());
     }

//--количество Полей.
     int tCountField = 0;

//--Установка значений для Dialog структура по диалогам

     for (int i = 0; i < lDialog.length(); i++)
     {

         QStringList templ_vv_FieldName; //Поля. Имя поля
         QStringList templ_vv_FieldCod; //Поля. Код
         QStringList templ_vv_FieldType; //Поля. Тип
         QList<int> templ_vv_FieldWidth; //Поля. Ширина
         QList<int> templ_vv_FieldIndex; //Поля. Порядковый номер


         QDomNodeList temp = lDialog.item(i).childNodes();

        for (int ii = 0; ii < temp.length(); ii++)
        {

           templ_vv_FieldName.append(temp.item(ii).toElement().attributeNode("name").value());
           templ_vv_FieldCod.append(temp.item(ii).toElement().attributeNode("cod").value());
           templ_vv_FieldType.append(temp.item(ii).toElement().attributeNode("type").value());
           templ_vv_FieldWidth.append(temp.item(ii).toElement().attributeNode("width").value().toInt());
           templ_vv_FieldIndex.append(tCountField);
           tCountField = tCountField + 1; //Считает общее количество полей и разбивает по диалогам

        }

        ll_vv_FieldName.append(templ_vv_FieldName);
        ll_vv_FieldCod.append(templ_vv_FieldCod);
        ll_vv_FieldType.append(templ_vv_FieldType);
        ll_vv_FieldWidth.append(templ_vv_FieldWidth);
        ll_vv_FieldIndex.append(templ_vv_FieldIndex);

     }

//--Установка значений для Docum

for (int i = 0; i < lDocum.length(); i++)
   {

    l_vv_DocName.append(lDocum.item(i).toElement().attributeNode("name").value());
    l_vv_DocCod.append(lDocum.item(i).toElement().attributeNode("cod").value());
    l_vv_DocLevel.append(lDocum.item(i).toElement().attributeNode("level").value());

    QList<int> tempCurrentDocField;

    QDomNodeList temp = lDocum.item(i).childNodes();

    for (int ii = 0; ii < temp.length(); ii++)
        {
            QString tCurrentDocField = temp.item(ii).toElement().attributeNode("cod").value();

            for (int iii = 0; iii < l_vv_FieldCod.length(); iii++)
            {
                if (tCurrentDocField == l_vv_FieldCod.value(iii))
                tempCurrentDocField.append(iii);

            }


        }


    l_vv_DocFieldIndex.append(tempCurrentDocField);
   }


//----Загрузка в панель Info

for (int i=0; i<l_vv_FieldName.length();i++)
   {
       QStringList l_Temp;
       l_Temp.append(l_vv_FieldName.value(i));
       l_Temp.append("");
       l_vv_FielInfo.append(l_Temp);
   }

}


StorProject::~StorProject()
{    
}

//--выдача Кодов полей

const QStringList &StorProject::GetFieldCod() const
    {
       return l_vv_FieldCod;
     }


const QList<QStringList> &StorProject::GetFieldCodN() const
    {
       return ll_vv_FieldCod;
     }



//--выдача Типов полей
        const QStringList &StorProject::GetFieldType() const
        {
            return l_vv_FieldType;
        }

//--выдача Имен полей
        const QStringList &StorProject::GetFieldName() const
        {
            return l_vv_FieldName;
        }

//--выдача Ширины полей
        const QList<int> &StorProject::GetFieldWidth() const
        {
            return l_vv_FieldWidth;
        }

//--выдача Путей кэша полей
        const QStringList &StorProject::GetFieldPath() const
        {
            return l_vv_FieldCache;
        }



//--Блок Диалогов

//--выдача Имен диалогов
const QStringList &StorProject::GetDialogName() const
      {
         return l_vv_DialogName;
      }


//--выдача Код + Имя диалогов
        const QStringList &StorProject::GetDialogCodName() const
        {

          return l_vv_DialogCodName;
        }


const QStringList &StorProject::GetDocCodN() const
       {
               return l_vv_DocCod;
       }



const QStringList &StorProject::GetDocNameN() const
        {
            return l_vv_DocName;
        }



const QStringList &StorProject::GetDocLevelN() const
        {
            return l_vv_DocLevel;
        }


const QList<QList<int> > &StorProject::GetDocFieldN() const
     {
            return l_vv_DocFieldIndex;
     }



//--Размер страницы

const int &StorProject::Get_TimeOut() const
{

    return tTimeOut;

}

//--Для Инфо

const QList<QStringList> &StorProject::GetFieldInfo() const
{

    return l_vv_FielInfo;

}

void StorProject::SetFieldInfo (int i, QString tVal)
{

    QStringList tList = l_vv_FielInfo.at(i);
    tList.replace(1, tVal);
    l_vv_FielInfo.replace(i,tList);

}


const QList<QList<int>> &StorProject::GetFieldWidthN() const
{
    return ll_vv_FieldWidth;
}

const QList<QList<int>> &StorProject::ll_vv_FieldIndexN() const
{
    return ll_vv_FieldIndex;
}



