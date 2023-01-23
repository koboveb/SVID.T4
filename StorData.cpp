#include "StorData.h"

StorData::StorData(const QString &tPath): StorProject(tPath)
{

//-----------------------------------------------------------------------------------------------------

for (int i = 0; i < l_vv_FieldCod.length(); i++)
     {
     if (i == 0)
        tNameField = QString::fromLocal8Bit("%1").arg(l_vv_FieldCod.value(i));
     else
        tNameField = QString::fromLocal8Bit("%1, %2").arg(tNameField).arg(l_vv_FieldCod.value(i));
     }
//------------------------------------------------------------------------------------------------------



//--Подключение базы

QSqlDatabase tdatabase = QSqlDatabase::addDatabase("QIBASE");


    tdatabase.setHostName(pathBaseAdress);
    tdatabase.setDatabaseName(pathBaseName);
    tdatabase.setUserName("sysdba");
    tdatabase.setPassword("RDBserverTO82911");

//--Открытие базы

 if(!tdatabase.open())
 {
    qDebug() << "database open. Error" << pathBaseAdress;
    exit(0);

 }
 else

{
    q_BaseCount = QSqlQuery(tdatabase);
    q_BaseData = QSqlQuery(tdatabase);
    qDebug() << "Успешное соеденение с базой " << pathBaseAdress;
 }


 LoadSql();
 LoadDataCount();

// LoadDataCachCount();
// LoadDataCach();

}

//---------------------------------------------------------------------
void StorData::LoadSql()
{

    QStringList tlTeloZaprosa = tBaseSql.split("FROM");
    tTeloSqlFrom = tlTeloZaprosa.value(1).replace("\n", "");

    tTeloSqlWhere = "";
    tTeloSqlOreder = "";


}
//---------------------------------------------------------------------
void StorData::LoadSql(int i, QString tValue)
{
    // разбираем текст относительно пробел+
        QStringList lTextForFind = tValue.split("+");
        QString tFiltr;

    if (tTeloSqlWhere.contains("WHERE"))
    {

        tTeloSqlWhere.append(" AND ");


        if (lTextForFind.length()>1)
        {
            tTeloSqlWhere.append(" (");

            tFiltr = QString::fromLocal8Bit("%1 like '%%2%' ")

            .arg(l_vv_FieldCod.value(i))
            .arg(lTextForFind.value(0));
            tTeloSqlWhere.append(tFiltr);


            for (int ii = 1; ii < lTextForFind.length(); ii++ )
            {
                tTeloSqlWhere.append(" OR ");

            tFiltr = QString::fromLocal8Bit("%1 like '%%2%' ")
                .arg(l_vv_FieldCod.value(i))
                .arg(lTextForFind.value(ii));

            tTeloSqlWhere.append(tFiltr);
            }

            tTeloSqlWhere.append(") ");

        }
        else
        {
            tFiltr = QString::fromLocal8Bit("%1 like '%%2%' ")
            .arg(l_vv_FieldCod.value(i))
            .arg(tValue);
            tTeloSqlWhere.append(tFiltr);

        }


    }

    else
    {

        tTeloSqlWhere.append(" WHERE ");

        if (lTextForFind.length()>1)
        {
            tTeloSqlWhere.append(" (");

            tFiltr = QString::fromLocal8Bit("%1 like '%%2%' ")
            .arg(l_vv_FieldCod.value(i))
            .arg(lTextForFind.value(0));

            tTeloSqlWhere.append(tFiltr);

            for (int ii = 1; ii < lTextForFind.length(); ii++ )
            {
                tTeloSqlWhere.append(" OR ");

            tFiltr = QString::fromLocal8Bit("%1 like '%%2%' ")
                .arg(l_vv_FieldCod.value(i))
                .arg(lTextForFind.value(ii));

            tTeloSqlWhere.append(tFiltr);

            }

            tTeloSqlWhere.append(") ");
        }
        else
        {
            tFiltr = QString::fromLocal8Bit("%1 like '%%2%' ")
            .arg(l_vv_FieldCod.value(i))
            .arg(tValue);
            tTeloSqlWhere.append(tFiltr);

        }


    }



}
//--Сортировка

void StorData::LoadSort(int i)
{

    QString tSort;

    if (tTeloSqlOreder.contains("ORDER BY"))

    {

        if (tTeloSqlOreder.contains(l_vv_FieldCod.value(i)))

            tSort = QString::fromLocal8Bit(" %1 ")
                    .arg("DESC");
        else

            tSort = QString::fromLocal8Bit(", %1 ")
                        .arg(l_vv_FieldCod.value(i));


        tTeloSqlOreder.append(tSort);

    }
    else
    {
        tSort = QString::fromLocal8Bit("ORDER BY %1 ")
                    .arg(l_vv_FieldCod.value(i));

        tTeloSqlOreder.append(tSort);
    }


}

//---------------------------------------------------------------------
void StorData::LoadDataCount()
{


    QString tTeloSQL_Count = QString::fromLocal8Bit("SELECT COUNT(%1) FROM %2 %3")

            .arg(l_vv_FieldCod.value(0))
            .arg(tTeloSqlFrom)
            .arg(tTeloSqlWhere);

   q_BaseCount.prepare(tTeloSQL_Count);
   q_BaseCount.exec();

   q_BaseCount.next();

 tDataCount = q_BaseCount.value(0).toInt();


}

void StorData::LoadDataCachCount()
{

//------Открытие файла Кэша


 for (int i = 0; i<l_vv_FieldCache.length();i++)
 {

     QStringList tlcount = l_vv_FieldCache.value(i).split("|");

     if (tlcount.value(0).contains("SELECT", Qt::CaseInsensitive) )
     {

         QString tTeloSQL_Count;

         if ( tlcount.value(3) == "" && tlcount.value(4) == "")

         {
         tTeloSQL_Count = QString::fromLocal8Bit("%1 COUNT(DISTINCT %2) FROM %3")
                                                        .arg(tlcount.value(0))
                                                        .arg(tlcount.value(1))
                                                        .arg(tlcount.value(2));
         }


         if ( tlcount.value(3) != "" && tlcount.value(4) == "")
         {
         tTeloSQL_Count = QString::fromLocal8Bit("%1 COUNT(DISTINCT %2) FROM %3 WHERE %4")
                                                        .arg(tlcount.value(0))
                                                        .arg(tlcount.value(1))
                                                        .arg(tlcount.value(2))
                                                        .arg(tlcount.value(3));
         }



         if ( tlcount.value(3) == "" && tlcount.value(4) != "")
         {
         tTeloSQL_Count = QString::fromLocal8Bit("%1 COUNT(DISTINCT %2) FROM %3 ORDER ID %4")
                                                        .arg(tlcount.value(0))
                                                        .arg(tlcount.value(1))
                                                        .arg(tlcount.value(2))
                                                        .arg(tlcount.value(4));
         }



         if (tlcount.value(3) != "" && tlcount.value(4) != "")
         {
         tTeloSQL_Count = QString::fromLocal8Bit("%1 COUNT(DISTINCT %2) FROM %3 WHERE %4 ORDER ID %5")
                                                        .arg(tlcount.value(0))
                                                        .arg(tlcount.value(1))
                                                        .arg(tlcount.value(2))
                                                        .arg(tlcount.value(3))
                                                        .arg(tlcount.value(4));
         }




             QSqlQuery q_BaseCountCache;

                     q_BaseCountCache.prepare(tTeloSQL_Count);
                     q_BaseCountCache.exec();

                     q_BaseCountCache.next();
                     lDataCachCount << q_BaseCountCache.value(0).toInt();

     }
     else
     {

         if (tlcount.length() > 0)
            lDataCachCount << tlcount.length();
         else
             lDataCachCount << 0;


     }

 }

}


void StorData::LoadData()
{
    if (fUpdate == 1)
    {

        LoadDataCount();
        tMin = tFirstValue;

    l_vv_FieldData.clear();



           tTeloSQL_Data = QString::fromLocal8Bit("SELECT FIRST %1 SKIP %2 %3 FROM %4 %5 %6" )

                                   .arg(tSizeListRow)
                                   .arg(tMin)
                                   .arg(tNameField)
                                   .arg(tTeloSqlFrom)
                                   .arg(tTeloSqlWhere)
                                   .arg(tTeloSqlOreder);



q_BaseData.prepare(tTeloSQL_Data);
           q_BaseData.exec();


           while (q_BaseData.next())

           {
               QStringList lTemp;

               for (int i =0; i < l_vv_FieldCod.length(); i++)
                   lTemp.append(q_BaseData.value(i).toString());

               l_vv_FieldData.append(lTemp);

           }

        fUpdate = 0;


    }


}

void StorData::LoadUpdate()
{
    if (lLoadData.length() > 0)
    {

        if (lLoadData.value(tSizeListRow - 1) == tFirstValue + tSizeListRow - 1)
        {
    tFirstValuePrev = tFirstValue;
    tSizeListRowPrev = tSizeListRow;
        }

    tFirstValue  = lLoadData.value(0);
    tSizeListRow = lLoadData.length();


    if (fUpdate == 0 && lLoadData.value(tSizeListRow - 1) == tFirstValue + tSizeListRow - 1)
        {
            int deltatFirstValue = tFirstValue - tFirstValuePrev;
            int deltatSizeListRow = tSizeListRow - tSizeListRowPrev;

            if(deltatFirstValue != 0 || deltatSizeListRow != 0 )
            fUpdate = 1;
        }

     }

}


void StorData::SetCurentRow(int Row)
{
lLoadData.append(Row);
CurentRow = Row;

}


void StorData::LoadDataClear()
{

lLoadData.clear();

}

void StorData::LoadDataCach()
{

    for (int i = 0; i<l_vv_FieldCache.length();i++)
    {

        QStringList tlsql = l_vv_FieldCache.value(i).split("|");
        if (tlsql.value(0).contains("SELECT", Qt::CaseInsensitive) )
        {


            QString tTeloSQL_Data;

            if ( tlsql.value(3) == "" && tlsql.value(4) == "")

            {
            tTeloSQL_Data = QString::fromLocal8Bit("%1 DISTINCT %2 FROM %3")
                                                           .arg(tlsql.value(0))
                                                           .arg(tlsql.value(1))
                                                           .arg(tlsql.value(2));
            }


            if ( tlsql.value(3) != "" && tlsql.value(4) == "")
            {
            tTeloSQL_Data = QString::fromLocal8Bit("%1 DISTINCT %2 FROM %3 WHERE %4")
                                                           .arg(tlsql.value(0))
                                                           .arg(tlsql.value(1))
                                                           .arg(tlsql.value(2))
                                                           .arg(tlsql.value(3));
            }



            if ( tlsql.value(3) == "" && tlsql.value(4) != "")
            {
            tTeloSQL_Data = QString::fromLocal8Bit("%1 DISTINCT %2 FROM %3 ORDER ID %4")
                                                           .arg(tlsql.value(0))
                                                           .arg(tlsql.value(1))
                                                           .arg(tlsql.value(2))
                                                           .arg(tlsql.value(4));
            }



            if (tlsql.value(3) != "" && tlsql.value(4) != "")
            {
            tTeloSQL_Data = QString::fromLocal8Bit("%1 DISTINCT %2 FROM %3 WHERE %4 ORDER ID %5")
                                                           .arg(tlsql.value(0))
                                                           .arg(tlsql.value(1))
                                                           .arg(tlsql.value(2))
                                                           .arg(tlsql.value(3))
                                                           .arg(tlsql.value(4));
            }

        }
        else
        {

            if (tlsql.length() > 0)
            {

                QStringList lTemp;

                for(int ii = 0; ii<tlsql.length(); ii++)
                    lTemp.append(tlsql.value(ii));

                l_vv_Cache.append(lTemp);

            }


            else
            {
                QStringList lTemp;
                lTemp.append("TEMP");
                l_vv_Cache.append(lTemp);
            }

        }


    }

}

//--Список данных
const QList<QStringList> &StorData::Get_FieldData() const
{
    return  l_vv_FieldData;
}


//--Интервал подгрузки

const int &StorData::Get_Min() const
{
    return tMin;
}


const int &StorData::Get_CurrentRow() const
{
    return CurentRow;
}

//--установка текущего количества кэш
void StorData::SetCachCurrentCountData(int i)
{
 CachCurrentCount = lDataCachCount.value(i);
 CachCurrentData = l_vv_Cache.value(i);

}

const QStringList &StorData::Get_DataCach() const
{

    return CachCurrentData;
}

//--Количество записей кэша
const int &StorData::Get_DataCountCach() const
{

    return CachCurrentCount;

}

//--------Количество записей данных
const int &StorData::Get_DataCount() const
{
    return tDataCount;
}

void StorData::Set_DataCountSqlRem()
{

    tTeloSqlWhere = "";
    tTeloSqlOreder = "";

}

QString StorData::Get_SqlText()
{

    return tTeloSQL_Data;

}


int StorData::Get_Level_Base(QString tID)
{
    QString ttID = tID;

    int tCount = 0;

    QString tBaseSqlLevelBlank = tBaseSqlLevel.replace("\n"," ");

    QString tBaseSqlLevelTemp = tBaseSqlLevelBlank;

    tBaseSqlLevelTemp.replace("%",ttID);

q_BaseData.prepare(tBaseSqlLevelTemp);
q_BaseData.exec();
q_BaseData.next();

if (q_BaseData.value(0).toString() != "")
    if (q_BaseData.value(0).toString() != ttID)
{

while(q_BaseData.value(0).toString() != "" && tCount < 10 )
    {

    tCount = tCount + 1;

    ttID = q_BaseData.value(0).toString();

    QString tBaseSqlLevelTempL = tBaseSqlLevelBlank;

    tBaseSqlLevelTempL.replace("%",ttID);

    q_BaseData.prepare(tBaseSqlLevelTempL);
    q_BaseData.exec();
    q_BaseData.next();

    }

}
  return tCount;

}

