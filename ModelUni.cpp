#include "ModelUni.h"

//ModelUni::ModelUni(typemodel TypeModel, StorProject *StPr)
ModelUni::ModelUni(typemodel TypeModel, StorData *StDt)
{



    TypeModelL = TypeModel;

    sStorData = StDt;
   // sStorProj = StDt->GetStorProject();

    /*
    for (int i = 0; i < sStorData->GetFieldCodN().length(); i++)
     CountField  = CountField + sStorData->GetFieldCodN().value(i).length();
    */

    CountField  = sStorData->GetFieldCod().length();

    lFieldName = sStorData->GetFieldName();

    CountDoc = sStorData->GetDocFieldN().length();

    lDocName = sStorData->GetDocNameN();

/*
    for (int i = 0; i < CountDoc; i++)
    {

        if (sStorData->GetDocLevelN().value(i) == "1")
        {
           CountDoc1 = CountDoc1 + 1;
           lDocName1.append(sStorData->GetDocNameN().value(i));
        }

        if (sStorData->GetDocLevelN().value(i) == "2")
         {
           CountDoc2 = CountDoc2 + 1;
           lDocName2.append(sStorData->GetDocNameN().value(i));
         }

        if (sStorData->GetDocLevelN().value(i) == "3")
         {
           CountDoc3 = CountDoc3 + 1;
           lDocName3.append(sStorData->GetDocNameN().value(i));
          }
    }
*/

}




int ModelUni::columnCount(const QModelIndex &parent) const
{
    switch (TypeModelL)
    {
    case INFO:

    {
        (void) parent;
        return 2;

    }
     break;

    case CACHE:
    {

        (void) parent;
        return 1;
     }
    break;

    case DOCUM:
    {
      (void) parent;
       return 1;
    }
    break;

    case DATA:
    {

      (void) parent;

      return CountField;
    }
    break;

    default:
    {
        (void) parent;
        return 2;


    }
    break;
    }





}

int ModelUni::rowCount(const QModelIndex &parent) const
{
    switch (TypeModelL)
    {
        case INFO:
            {
                (void) parent;
                return CountField;
            }
                break;

        case CACHE:
            {

                (void) parent;
                return sStorData->Get_DataCountCach();
            }
                break;

        case DATA:
            {
                (void) parent;

               // qDebug()<< sStorData->Get_DataCount();
                return sStorData->Get_DataCount();
            }
                break;
        case DOCUM:
        {
            (void) parent;

            return CountDoc;
        }
            break;

     default:
            {
                 (void) parent;
                 return 0;

            }
                break;
    }


}

QVariant ModelUni::data(const QModelIndex &index, int role) const
{


    switch (TypeModelL)
    {
    case INFO:

    {
        if (role == Qt::DisplayRole)
        {
         QString unswer = sStorData->GetFieldInfo().value(index.row()).value(index.column());
         return unswer;
        }
    return QVariant();
    }
    break;

    case CACHE:
    {
       if (role == Qt::DisplayRole)
        {

           QString unswer = sStorData->Get_DataCach().value(index.row());

           return unswer;

        }
        return QVariant();
    }
    break;

    case DOCUM:
    {

        if (role == Qt::DisplayRole)
         {

            QString unswer = lDocName.value(index.row());

            return unswer;
         }


         return QVariant();


    }

         break;


    case DATA:
    {



        if (role == Qt::DisplayRole)
         {
             QString unswer;

             if (index.column() == 0)
                 sStorData->SetCurentRow(index.row());

             unswer = sStorData->Get_FieldData().value(index.row() - sStorData->Get_Min()).value(index.column());

            return unswer;
         }
         return QVariant();


    }

        break;

    default:

        break;
    }


    return QVariant();




}


QVariant ModelUni::headerData(int section, Qt::Orientation orientation, int role) const
{


    switch (TypeModelL)
    {
    case INFO:

    {
        if (role != Qt::DisplayRole)
                 return QVariant();

        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                         case 0:
                             return tr("Name");

                         case 1:
                             return tr("Value");

                         default:
                             return QVariant();
                     }
        }
        return QVariant();

    }

        break;

    case CACHE:

    {

        if (role != Qt::DisplayRole)
                 return QVariant();

        if (orientation == Qt::Horizontal)
        {

 // Разобраться!!!

            switch (section)
                {
                         case 0:
                             return tr("N doc");

                         case 1:
                             return tr("N text");

                         default:
                             return QVariant();
                }


        }
        return QVariant();

    }

        break;

    case DOCUM:

    {

        if (role != Qt::DisplayRole)
                 return QVariant();

        if (orientation == Qt::Horizontal)
        {
            switch (section)
            {
                         case 0:
                             return tr("N doc");

                         default:
                             return QVariant();
                     }
        }
        return QVariant();

    }

         break;


    case DATA:

    {

        if (role != Qt::DisplayRole)
                 return QVariant();

        if (orientation == Qt::Horizontal)

            return QString("%1").arg(lFieldName.value(section));

       else

          return QString("%1").arg(section + 1);

       return QVariant();

   }

        break;


  default:

       break;
   }

   return QVariant();

}
