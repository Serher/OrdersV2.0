//---------------------------------------------------------------------------


#pragma hdrstop

#include "MyQSLBaseManager.h"
#include "VariantFuncs.h"
#include "MyUtils.h"
//---------------------------------------------------------------------------


#pragma package(smart_init)




//ORDER
//------------------------------------------------------------------------------
Order::Order()
{
    nID = 0;
    sDate = "";
    sOffice = "";
    sDocs = "";
    sPositions.clear();
    sAmounts.clear();
}
//------------------------------------------------------------------------------
void Order::SetDate(AnsiString sDateToSet)
{
    if(sDateToSet == "")
        sDate = Now().DateString();
    else
        sDate = sDateToSet;
}
//------------------------------------------------------------------------------
AnsiString Order::DateForMySQL()
{
    StringsContainer strCont;
    strCont.BreakString(sDate, ".");
    return strCont.Vector[2] + "." + strCont.Vector[1] + "." + strCont.Vector[0];
}
//------------------------------------------------------------------------------
void Order::AddPosition(AnsiString sPos, AnsiString sAmo, AnsiString sMea)
{
    if(sPos != "" && sAmo != "")
    {
        sPositions.push_back(sPos);
        sAmounts.push_back(sAmo);
        sMeasures.push_back(sMea);
    }
}
//------------------------------------------------------------------------------
void Order::GetOrderFromExcel(Variant vSheet, int nY)
{
    sDate = GetValue(vSheet, nY, 2);
    sOffice = GetValue(vSheet, nY, 3);
    sDocs = GetValue(vSheet, nY, 4);

    StringsContainer strCont;
    int nX = 5;
    AnsiString sAmount, sName, str = GetValue(vSheet, 1, nX);
    while(str != "")
    {
        sAmount = GetValue(vSheet, nY, nX);
        if(sAmount != "")
        {
            strCont.BreakString(sAmount, " ");
            sAmount = strCont.Vector[0];

            strCont.BreakString(str, ", ");
            sName = strCont.Vector[0];

            AddPosition(sName, sAmount);
        }
        str = GetValue(vSheet, 1, ++nX);
    }
}
//------------------------------------------------------------------------------
void Order::GetOrderFromMySQL(MyDB *MyDB1, AnsiString sCompany, int nNumber)
{
    // вычисляем ID компании
    MyDB1->ExecuteCommand("select id from companies where name like '" + sCompany + "'");
    AnsiString sID = MyDB1->GetFieldValue();

    // возьмем заранее названия позиций компании
    std::vector<AnsiString> vPosNames;
    std::vector<AnsiString> vMeasures;
    MyDB1->ExecuteCommand("select name, measure from positions_of_company_" + sID);
    for(int nY=1; nY <= MyDB1->Que->RecordCount; nY++)
    {
        vPosNames.push_back(MyDB1->GetFieldValue(nY));
        vMeasures.push_back(MyDB1->GetFieldValue(nY, 1));
    }

    // находим заказ
    MyDB1->ExecuteCommand("select * from orders_of_company_" + sID + " where id = " + IntToStr(nNumber));
    if(MyDB1->Que->RecordCount<=0)//Заказа с таким номером не существует
        nID = 0;
    else
    {
        // заполняем объект Order даными
        nID = nNumber;
        sDate = MyDB1->GetFieldValue(1, 1);
        sOffice = MyDB1->GetFieldValue(1, 2);
        sDocs = MyDB1->GetFieldValue(1, 3);
        // заполняем позиции
        AnsiString str;
        for(int nX = 4; nX < MyDB1->Que->FieldCount; nX++)
        {
            str = MyDB1->GetFieldValue(1, nX);
            if(str != "")
                AddPosition(vPosNames[nX-4], str, vMeasures[nX-4]);
        }
    }
}
//------------------------------------------------------------------------------
void Order::GetOrderFromGrid(TStringGrid *SG, int nNumber)
{
    AnsiString sName, sAmount;

    nID = nNumber; // Задаем номер заказа
    for(int i = 3; i < SG->RowCount; i++)
    {
        sName = SG->Cells[0][i];
        sAmount = SG->Cells[1][i];
        AddPosition(sName, sAmount);
    }
}
//------------------------------------------------------------------------------
void Order::ShowOnSG(TStringGrid *SG, TMemo *Memo)
{
    if(!nID) return;

    SG->RowCount = 4;
    SG->Rows[0]->Clear();
    SG->Rows[1]->Clear();
    SG->Rows[2]->Clear();
    SG->Rows[3]->Clear();

    SG->Cells[0][0] = "Заказ №" + IntToStr(nID) + " от " + sDate;
    SG->Cells[0][1] = "Офис: " + sOffice;

    for(unsigned i=0; i<sPositions.size(); i++)
    {
        SG->Cells[0][i+3] = sPositions[i];
        SG->Cells[1][i+3] = sAmounts[i];
        SG->Cells[2][i+3] = sMeasures[i];

        SG->RowCount++;
        SG->Rows[SG->RowCount-1]->Clear();
    }
    ShowScheta(Memo);
}
//------------------------------------------------------------------------------
void Order::ShowScheta(TMemo *Memo)
{
    StringsContainer strCont;
    strCont.BreakString(sDocs, " || ");

    Memo->Clear();
    for(unsigned int i = 0; i<strCont.Vector.size(); i++)
        Memo->Lines->Add(strCont.Vector[i]);
}
//------------------------------------------------------------------------------









//DBManager
//------------------------------------------------------------------------------
AnsiString DBManager::GetLastInsertID()
{
    MyDB1->ExecuteCommand("select last_insert_id()");
    return MyDB1->GetFieldValue(1, 0);
}
//------------------------------------------------------------------------------
AnsiString DBManager::GetCompanyID(AnsiString sCompany)
{
    MyDB1->ExecuteCommand("select id from companies where name like '" + sCompany + "'");
    return MyDB1->GetFieldValue(1, 0);
}
//------------------------------------------------------------------------------
AnsiString DBManager::RecountAndSetAutoIncrement(AnsiString sTable, AnsiString sField)
{
    AnsiString sID;
    MyDB1->ExecuteCommand("select max(" + sField + ") from " + sTable);
    if(MyDB1->GetFieldValue(1, 0) != "")
    {
        int nID = StrToInt(MyDB1->GetFieldValue(1, 0));
        nID++;
        sID = IntToStr(nID);
    }
    else //Table is empty 
        sID = "1";

    MyDB1->ExecuteCommand("alter table " + sTable + " auto_increment = " + sID);
    return sID;
}
//------------------------------------------------------------------------------






//------------------------------------------------------------------------------
void DBManager::AddNewCompany(AnsiString sCompany)
{
    MyDB1->ExecuteCommand("insert into companies (name) values ('" + sCompany + "')");
    AnsiString sID = GetLastInsertID();
    MyDB1->ExecuteCommand("create table " + TabPosName(sID) + "(id smallint unsigned NOT NULL PRIMARY KEY auto_increment, name varchar(100), measure varchar(20), posinlist smallint unsigned)");
    MyDB1->ExecuteCommand("create table " + TabOrdName(sID) + "(id smallint unsigned NOT NULL PRIMARY KEY auto_increment, date date, office varchar(100), docs varchar(100))");
}
//------------------------------------------------------------------------------
void DBManager::AddNewPosition(AnsiString sCompany, AnsiString sName, AnsiString sMeasure)
{
    //находим IDшник компании по имени
    AnsiString sID = GetCompanyID(sCompany);
    //добавляем новую позицию в таблицу позиций компании
    AnsiString sAutoIncr = MyDB1->GetAutoIncrement(TabPosName(sID));
    MyDB1->ExecuteCommand("insert into " + TabPosName(sID) + " (name, measure, posinlist) values ('" + sName + "', '" + sMeasure + "', " + sAutoIncr + ")");
    //Добавляем колонку с номером позиции в таблицу заказов компании
    AnsiString sPosID = GetLastInsertID();
    MyDB1->ExecuteCommand("ALTER TABLE " + TabOrdName(sID) + " ADD COLUMN position_" + sPosID + " smallint unsigned");
}
//------------------------------------------------------------------------------
void DBManager::SetCompanyActive(AnsiString sCompany, bool bActive)
{
    AnsiString sID = GetCompanyID(sCompany);
    MyDB1->ExecuteCommand("update companies set active = '" + IntToStr(bActive) + "' where id = " + sID);
}
//------------------------------------------------------------------------------
void DBManager::DeleteCompany(AnsiString sCompany)
{
    AnsiString sID = GetCompanyID(sCompany);
    MyDB1->ExecuteCommand("delete from companies where id = " + sID);
    RecountAndSetAutoIncrement("companies");

    MyDB1->ExecuteCommand("drop table " + TabPosName(sID));
    MyDB1->ExecuteCommand("drop table " + TabOrdName(sID));
}
//------------------------------------------------------------------------------
void DBManager::DeletePosition(AnsiString sCompany, AnsiString sPos)
{
    AnsiString sPosID, sID = GetCompanyID(sCompany);
    if(sPos != "")
        MyDB1->ExecuteCommand("select id from " + TabPosName(sID) + " where name like '" + sPos + "')");
    else // If no pos specified the last one would be deleted
        MyDB1->ExecuteCommand("select max(id) from " + TabPosName(sID));
    sPosID = MyDB1->GetFieldValue(1, 0);

    MyDB1->ExecuteCommand("delete from " + TabPosName(sID) + " where id = " + sPosID);
    MyDB1->ExecuteCommand("alter table " + TabOrdName(sID) + " drop column position_" + sPosID);
    RecountAndSetAutoIncrement(TabPosName(sID));
}
//------------------------------------------------------------------------------
AnsiString DBManager::GetMeasure(AnsiString sCompany, AnsiString sPos)
{
    AnsiString sID = GetCompanyID(sCompany);
    MyDB1->ExecuteCommand("select measure from " + TabPosName(sID) + " where name like '" + sPos + "'");
    return MyDB1->GetFieldValue(1, 0);
}
//------------------------------------------------------------------------------
AnsiString DBManager::GetPositionID(AnsiString sCompanyID, AnsiString sPos)
{
    MyDB1->ExecuteCommand("select id from " + TabPosName(sCompanyID) + " where name like '" + sPos + "'");
    if(MyDB1->Que->RecordCount)
        return MyDB1->GetFieldValue(1, 0);
return "";
}
//------------------------------------------------------------------------------
void DBManager::SavePositionsOrder(AnsiString sCompany, TListBox *List)
{
    AnsiString sPos, sID = GetCompanyID(sCompany);
    for(int i = 0; i < List->Items->Count; i++)
    {
        sPos = List->Items->Strings[i];
        MyDB1->ExecuteCommand("update " + TabPosName(sID) + " set posinlist = " + IntToStr(i+1) + " where name like '" + sPos + "'");
    }
}
//------------------------------------------------------------------------------
void DBManager::SaveNewPositionsName(AnsiString sCompany, AnsiString sNewName, AnsiString sOldName)
{
    if(sNewName == "" || sOldName == "")
        return;
    AnsiString sID = GetCompanyID(sCompany);
    MyDB1->ExecuteCommand("update " + TabPosName(sID) + " set name = '" + sNewName + "' where name like '" + sOldName + "'");
}
//------------------------------------------------------------------------------
AnsiString DBManager::GetNewOrderNumber(AnsiString sCompany)
{
    AnsiString sID = GetCompanyID(sCompany);
    return MyDB1->GetAutoIncrement(TabOrdName(sID));
}
//------------------------------------------------------------------------------
AnsiString DBManager::AddNewOrder(AnsiString sCompany, Order ord)
{
    AnsiString sWarnings, sPos, sPosID, sID = GetCompanyID(sCompany);
    AnsiString sPart1 = "insert into " + TabOrdName(sID) + " (date, office";
    AnsiString sPart2 = " values ('" + ord.DateForMySQL() + "', '" + ord.sOffice + "'";

    if(ord.sDocs != "")
    {
        sPart1 += ", docs";
        sPart2 += ", '" + ord.sDocs + "'";
    }

    for(unsigned i = 0; i<ord.sPositions.size(); i++)
    {
        sPos = ord.sPositions[i];
        sPosID = GetPositionID(sID, sPos);
        if(sPosID != "")// Позиция есть в таблице
        {
            sPart1 += ", position_" + sPosID;
            sPart2 += ", " + ord.sAmounts[i];
        }
        else
        {
            if(sWarnings == "")
                sWarnings = "Отсутствуют позиции: " + sPos;
            else
                sWarnings += ", " + sPos;
        }
    }
    sPart1 += ")";
    sPart2 += ")";
    MyDB1->ExecuteCommand(sPart1 + sPart2);
    //MyDB1.Log(sPart1 + sPart2);
return sWarnings;
}
//------------------------------------------------------------------------------
void DBManager::UpdateOrder(AnsiString sCompany, Order ord)
{
    AnsiString sCommand, sID = GetCompanyID(sCompany);
    for(unsigned i = 0; i<ord.sPositions.size(); i++)
    {
        MyDB1->ExecuteCommand("select id from " + TabPosName(sID) + " where name like '" + ord.sPositions[i] + "'"); // Берем номер позиции
        if(sCommand != "")
            sCommand += ", ";
        sCommand += "position_" + MyDB1->GetFieldValue() + " = " + ord.sAmounts[i];  // Пример: position_1 = 80
    }
    sCommand = "update " + TabOrdName(sID) + " set " + sCommand + " where id = " + IntToStr(ord.nID);
    MyDB1->ExecuteCommand(sCommand);
}
//------------------------------------------------------------------------------
void DBManager::DeleteLastOrder(AnsiString sCompany)
{
    AnsiString sID = GetCompanyID(sCompany);
    MyDB1->ExecuteCommand("select max(id) from " + TabOrdName(sID));
    AnsiString sLastID = MyDB1->GetFieldValue();

    MyDB1->ExecuteCommand("delete from " + TabOrdName(sID) + " where id = " + sLastID);
    RecountAndSetAutoIncrement(TabOrdName(sID));
}
//------------------------------------------------------------------------------
void DBManager::AddDocsToTheOrder(AnsiString sCompany, AnsiString sOrdNumber, AnsiString sDocs)
{
    AnsiString sID = GetCompanyID(sCompany);
    MyDB1->ExecuteCommand("select docs from " + TabOrdName(sID) + " where id = " + sOrdNumber);
    AnsiString sOldVal = MyDB1->GetFieldValue();
    if(sOldVal != "")
        sDocs = sOldVal + " || " + sDocs;

    MyDB1->ExecuteCommand("update " + TabOrdName(sID) + " set docs = '" + sDocs + "' where id = " + sOrdNumber);
}
//------------------------------------------------------------------------------
AnsiString DBManager::FindOrdersWithSchet(AnsiString sCompany, AnsiString sSchet)
{
    AnsiString sID = GetCompanyID(sCompany);
    MyDB1->ExecuteCommand("select id from " + TabOrdName(sID) + " where docs like '%" + sSchet + "%'");
    AnsiString sResult, sValue;
    for(int nY = 1; nY <= MyDB1->Que->RecordCount; nY++)
    {
        sValue = MyDB1->GetFieldValue(nY);
        if(sResult != "")
            sResult += ", ";
        sResult += sValue;
    }
return sResult;
}
//------------------------------------------------------------------------------




//Load
//------------------------------------------------------------------------------
void DBManager::LoadToList(TStrings *tsList, MyDB *MyDB1, bool bClear)
{
    if(bClear)
        tsList->Clear();
    for(int i=1; i<=MyDB1->Que->RecordCount; i++)
        tsList->Add(MyDB1->GetFieldValue(i, 0));
}
//------------------------------------------------------------------------------
void DBManager::LoadCompanies(TStrings *tsList, bool bOnlyActive)
{
    AnsiString sCommand = "select name from companies";
    if(bOnlyActive)
        sCommand += " where active = 1";

    MyDB1->ExecuteCommand(sCommand);
    LoadToList(tsList, MyDB1);
}
//------------------------------------------------------------------------------
void DBManager::LoadPositionsOfCompany(TStrings *tsList, AnsiString sCompany, bool bClear)
{
    AnsiString sID = GetCompanyID(sCompany);
    MyDB1->ExecuteCommand("select name from " + TabPosName(sID) + " order by posinlist");
    LoadToList(tsList, MyDB1, bClear);
}
//------------------------------------------------------------------------------
void DBManager::LoadAllPositions(TStrings *tsList)
{
    MyDB1->ExecuteCommand("select max(id) from companies");
    AnsiString sMaxID = MyDB1->GetFieldValue();
    if(sMaxID != "")
    {
        //Загружаем позиции первой компании без проверок
        MyDB1->ExecuteCommand("select name from " + TabPosName("1") + " order by posinlist");
        LoadToList(tsList, MyDB1);

        AnsiString str;
        int nMaxID = StrToInt(sMaxID);
        if(nMaxID>1)
        {
            for(int i=2; i<=nMaxID; i++)// i - IDшник компании. Т.е. идем по компаниям
            {
                MyDB1->ExecuteCommand("select name from " + TabPosName(IntToStr(i)));
                for(int k=1; k<=MyDB1->Que->RecordCount; k++)//Идем по списку позиций
                {
                    str = MyDB1->GetFieldValue(k, 0);
                    if(tsList->IndexOf(str) == -1)
                        tsList->Add(str);
                }
            }
        }
    }
}
//------------------------------------------------------------------------------
void DBManager::LoadOffices(TStrings *tsList)
{
    MyDB1->ExecuteCommand("select name from offices");
    LoadToList(tsList, MyDB1);
}





