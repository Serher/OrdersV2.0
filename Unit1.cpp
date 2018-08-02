//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


#include "MyUtils.h"
#include "VariantFuncs.h"



void Filler::Copy()
{
    ExcelInfo eFile(F_PATH);
    Variant vSheet;
    AnsiString sName, sAdres, sPerson, email, sCompany;
    AnsiString str;

    /*
    //Копирование оффисов
    vSheet = eFile.GetSheet(4);
    int i = 2;
    str = GetValue(vSheet, i, 1);
    while(str != "")
    {
        sAdres = str;
        sName = GetValue(vSheet, i, 2);
        sPerson = GetValue(vSheet, i, 3);
        email = GetValue(vSheet, i, 4);
        DBMan1->MyDB1->ExecuteCommand("insert into offices (name, adres, person, email) values ('" + sName + "', '" + sAdres + "', '" + sPerson + "', '" + email +"')");

        str = GetValue(vSheet, ++i, 1);
    }*/

    // Копировать компании
    for(int k=1; k<=3; k++)
    {
        vSheet = eFile.GetSheet(k);
        sCompany = vSheet.OlePropertyGet("Name");
        DBMan1->AddNewCompany(sCompany);
    }


    // Позиции товаров
    int nX;
    StringsContainer strCont;
    AnsiString sMeasure;
    for(int k=1; k<=3; k++)
    {
        vSheet = eFile.GetSheet(k);
        sCompany = vSheet.OlePropertyGet("Name");
        nX = 5;
        str = GetValue(vSheet, 1, nX);
        while(str != "")
        {
            strCont.BreakString(str, ", ");
            if(strCont.Vector.size()>1)
                sMeasure = strCont.Vector[1];
            else
                sMeasure = "шт.";
            DBMan1->AddNewPosition(sCompany, strCont.Vector[0], sMeasure);

            str = GetValue(vSheet, 1, ++nX);
        }
    }

    //Добавление заказов из Эксельки
    Order ord;
    int nY;
    for(int k=1; k<=3; k++)
    {
        vSheet = eFile.GetSheet(k);
        sCompany = vSheet.OlePropertyGet("Name");
        nY = 2;
        str = GetValue(vSheet, nY, 1);
        while(str != "")
        {
            ord = Order(); // Обнуляем значение
            ord.GetOrderFromExcel(vSheet, nY);
            DBMan1->AddNewOrder(sCompany, ord);
            str = GetValue(vSheet, ++nY, 1);
        }
    }
    //Закрываем файл
    eFile.CloseExFile();
}















//------------------------------------------------------------------------------
FloatingPanel::FloatingPanel(TPanel *iPan)
{
    Pan = iPan;
    Height = 0;
    Width = 0;
    Top = 0;
    Left = 0;

    Visible = 0;
}
//------------------------------------------------------------------------------
void FloatingPanel::ShowPanel()
{
    Pan->Height = Height;
    Pan->Width = Width;
    Pan->Top = Top;
    Pan->Left = Left;

    Pan->Visible = true;
    Visible = 1;
}
//------------------------------------------------------------------------------
void FloatingPanel::HidePanel()
{
    Pan->Visible = false;
    Visible = 0;
}
//------------------------------------------------------------------------------




// Positioner
//------------------------------------------------------------------------------
Positioner::Positioner() : FloatingPanel()
{
    List = 0;
    FieldName = 0;
    FieldPos = 0;
    nSelPos = -1;
    DBMan1 = 0;
    Arrows = 0;

    Height = 169;
    Width = 281;
    Top = 216;
    Left = 304;
}
//------------------------------------------------------------------------------
Positioner::Positioner(TPanel *iPan, TListBox *iList, TEdit *iFieldName, TLabeledEdit *iFieldPos, DBManager *iDBMan1, TUpDown *iArrows) : FloatingPanel(iPan)
{
    List = iList;
    FieldName = iFieldName;
    FieldPos = iFieldPos;
    nSelPos = -1;
    DBMan1 = iDBMan1;
    Arrows = iArrows;
    
    Height = 169;
    Width = 281;
    Top = 216;
    Left = 304;
}
//------------------------------------------------------------------------------
void Positioner::OnPosSelect()
{
    Arrows->Position = nSelPos = List->ItemIndex;
    FieldName->Text = List->Items->Strings[nSelPos];
    FieldPos->Text = nSelPos;
}
//------------------------------------------------------------------------------
void Positioner::SetPosition()
{
    int nNewPos = StrToInt(FieldPos->Text);
    if(nNewPos >= List->Items->Count)
        nNewPos = List->Items->Count-1;
    if(nNewPos < 0)
        nNewPos = 0;

    if(nNewPos != nSelPos)
    {
        List->Items->Delete(nSelPos);
        List->Items->Insert(nNewPos, FieldName->Text);
        List->ItemIndex = nNewPos;
        FieldPos->SelectAll();
        Arrows->Position = nSelPos = nNewPos;
    }
}
//------------------------------------------------------------------------------
void Positioner::SaveOrder()
{
    DBMan1->SavePositionsOrder(ActualCompany, List);
}
//------------------------------------------------------------------------------
void Positioner::SavePosName()
{
    AnsiString sOldName = List->Items->Strings[nSelPos];
    AnsiString sNewName = FieldName->Text;
    List->Items->Strings[nSelPos] = sNewName;

    DBMan1->SaveNewPositionsName(ActualCompany, sNewName, sOldName);
}
//------------------------------------------------------------------------------







// InfoPan
//------------------------------------------------------------------------------
InfoPan::InfoPan() : FloatingPanel()
{
    Name = 0;
    Manager = 0;
    Email = 0;
    ChB = 0;
    MyDB1 = 0;

    Height = 217;
    Width = 249;
    Top = 96;
    Left = 640;
}
//------------------------------------------------------------------------------
InfoPan::InfoPan(TPanel *iPan, TLabeledEdit *iName, TLabeledEdit *iManager, TLabeledEdit *iEmail, TCheckBox *iChB, MyDB *iMyDB1) : FloatingPanel(iPan)
{
    Name = iName;
    Manager = iManager;
    Email = iEmail;
    ChB = iChB;
    MyDB1 = iMyDB1;

    Height = 217;
    Width = 249;
    Top = 96;
    Left = 640;
}
//------------------------------------------------------------------------------
void InfoPan::Open(AnsiString isCompany)
{
    if(isCompany == "")
        return;
    sCompany = isCompany;
    MyDB1->ExecuteCommand("select * from companies where name like '" + isCompany + "'");
    Name->Text = MyDB1->GetFieldValue(1, 1);
    Manager->Text = MyDB1->GetFieldValue(1, 3);
    Email->Text = MyDB1->GetFieldValue(1, 4);
    ChB->Checked = StrToInt(MyDB1->GetFieldValue(1, 2));
}
//------------------------------------------------------------------------------
void InfoPan::Save()
{
    MyDB1->ExecuteCommand("update companies set name = '" + Name->Text + "', manager = '" + Manager->Text + "', email = '" + Email->Text + "', active = " + IntToStr(ChB->Checked) + " where name like '" + sCompany + "'");
}











//SEARCER
//------------------------------------------------------------------------------
void Searcher::FillTheFilter(AnsiString isFilterCompany, AnsiString isFilterDate, AnsiString isFilterOffice, AnsiString isFilterTovar)
{
    sFilterCompany = isFilterCompany;
    sFilterDate = isFilterDate;
    sFilterOffice = isFilterOffice;
    sFilterTovar = isFilterTovar;
}
//------------------------------------------------------------------------------
void Searcher::SearchOrders() // Цикл компаний
{
    nItogo = 0;
    Sorter->Clear();
    if(sFilterCompany != "")
    {
        sCompanyName = sFilterCompany; // Переменная-компонент класса. Нужна для удобства выдачи финальной инфы
        MyDB1->ExecuteCommand("select id from companies where name like '" + sFilterCompany + "'");
        SearchOrdersOfCompany(MyDB1->GetFieldValue());
    }
    else // Компания не задана, проверяем все по циклу
    {
        AnsiString sID;
        MyDB1->ExecuteCommand("select MAX(id) from companies");
        int nMaxCompanies = StrToInt(MyDB1->GetFieldValue());
        for(int i = 1; i<= nMaxCompanies; i++)
        {
            sID = IntToStr(i);
            MyDB1->ExecuteCommand("select name from companies where id = " + sID);
            sCompanyName = MyDB1->GetFieldValue(); // Переменная-компонент класса. Нужна для удобства выдачи финальной инфы

            SearchOrdersOfCompany(sID);
        }
    }
    MoveResultsToSG();
}
//------------------------------------------------------------------------------
void Searcher::SearchOrdersOfCompany(AnsiString sID)
{
    if(sFilterTovar != "")
        SearchOrdersWithPositionOfCompany(sID);
    else
    {
        MyDB1->ExecuteCommand("select max(id) from positions_of_company_" + sID);
        int nMaxPos = StrToInt(MyDB1->GetFieldValue());
        for(int i = 1; i<=nMaxPos; i++)
            SearchOrdersWithPositionOfCompany(sID, i);
    }
}
//------------------------------------------------------------------------------
void Searcher::SearchOrdersWithPositionOfCompany(AnsiString sID, int nTovarID)
{
    AnsiString sActualTovarName;
    AnsiString sActualTovarID;
    AnsiString sActualTovarMeasure;

    if(!nTovarID)
    {
        sActualTovarName = sFilterTovar;
        MyDB1->ExecuteCommand("select id, measure from positions_of_company_" + sID + " where name like '" + sActualTovarName + "'");
        //Товар задан и нужно проверить есть ли он у данной компании
        if(MyDB1->Que->RecordCount)
        {
            sActualTovarID = MyDB1->GetFieldValue();
            sActualTovarMeasure =  MyDB1->GetFieldValue(1, 1);
        }
        else
            return;
    }
    else
    {
        sActualTovarID = IntToStr(nTovarID);
        MyDB1->ExecuteCommand("select name, measure from positions_of_company_" + sID + " where id = " + sActualTovarID);
        sActualTovarName = MyDB1->GetFieldValue();
        sActualTovarMeasure =  MyDB1->GetFieldValue(1, 1);
    }
    // Теперь заданы основные переменные: sActualTovarName, sActualTovarID, sActualTovarMeasure, sID
    // Можно генерировать команду для поиска заказов

    AnsiString sTovarColName = "position_" + sActualTovarID;
    AnsiString sCommand = "select date, id, office, " + sTovarColName + " from orders_of_company_" + sID + " where " + sTovarColName + " != 0";
    if(sFilterDate != "")
        sCommand += " && date like '%" + sFilterDate + "'";
    if(sFilterOffice != "")
        sCommand += " && office like '" + sFilterOffice + "'";

    // Команда сгенерирована, выполняем 
    MyDB1->ExecuteCommand(sCommand);
    AnsiString str;
    for(int nY=1; nY<=MyDB1->Que->RecordCount; nY++)// Каждую запись преобразуем в строку и пишем в лист
    {
        MyDB1->Que->RecNo = nY;
        for(int nX=0; nX < MyDB1->Que->FieldCount; nX++)
        {
            if(nX == 0)
                str = MyDB1->GetFieldValue(nY, nX);
            else
                str += "||" + MyDB1->GetFieldValue(nY, nX);

            if(nX+1 == MyDB1->Que->FieldCount)
                nItogo += StrToInt(MyDB1->GetFieldValue(nY, nX));
        }

        //Обработать строку(преобразовать формат времени, объединить наименование, количество, меру товара) и кинуть в лист
        str = StringForSort(str, sActualTovarName, sActualTovarMeasure);
        Sorter->Items->Add(str);
    }
}
//------------------------------------------------------------------------------
AnsiString Searcher::StringForSort(AnsiString str, AnsiString sTovarName, AnsiString sMeasure) // sCompanyName является переменной класса, задается раньше
{
    //Исходник
    // 22.04.2017||id заказа||office||колво товара
    //Должно быть
    // 2017.04.22||id заказа||office||Название товара - колво мера||компания

    AnsiString sResult;
    StringsContainer strCont;
    strCont.BreakString(str, "||");

    sResult = DateFormatForSort(strCont.Vector[0]); // 2017.04.22
    sResult+= "||" + strCont.Vector[1] + "||" + strCont.Vector[2]; // 2017.04.22||id заказа||office
    sResult+= "||" + sTovarName + " - " + strCont.Vector[3] + " " + sMeasure; // 2017.04.22||id заказа||office||Название товара - колво мера
    sResult+= "||" + sCompanyName; // 2017.04.22||id заказа||office||Название товара - колво мера||компания
return sResult;
}
//------------------------------------------------------------------------------
AnsiString Searcher::DateFormatForSort(AnsiString sDate)
{
    StringsContainer strCont;
    strCont.BreakString(sDate, ".");
    return strCont.Vector[2] + "." + strCont.Vector[1] + "." + strCont.Vector[0];
}
//------------------------------------------------------------------------------
void Searcher::MoveResultsToSG()
{
    // Вид строки:
    // 2017.04.22||id заказа||office||Название товара - колво мера||компания

    SG->RowCount = 2;
    SG->Rows[1]->Clear();
    StringsContainer strCont;
    AnsiString str;
    for(int i=0; i<Sorter->Items->Count; i++)
    {
        str = Sorter->Items->Strings[i];
        strCont.BreakString(str, "||");
        SG->Cells[0][i+1] = strCont.Vector[1]; // ID Заказа
        SG->Cells[1][i+1] = DateFormatForSort(strCont.Vector[0]); // Дата
        SG->Cells[2][i+1] = strCont.Vector[2]; // Офис
        SG->Cells[3][i+1] = strCont.Vector[3]; // Товар
        SG->Cells[4][i+1] = strCont.Vector[4]; // Компания

        SG->RowCount++;
        SG->Rows[SG->RowCount-1]->Clear();
    }
    SG->Cells[3][SG->RowCount-1] = "ИТОГО: " + IntToStr(nItogo);
}














//------------------------------------------------------------------------------
Sure::Sure()
{
    Pan = 0;
    oSender = 0;
    bOK = 0;
}
//------------------------------------------------------------------------------
Sure::Sure(TPanel * iPan)
{
    Pan = iPan;
    oSender = 0;
    bOK = 0;
}
//------------------------------------------------------------------------------
void Sure::ShowPanel()
{
    Pan->Top = 208;
    Pan->Left = 552;
    Pan->Height = 129;
    Pan->Width = 401;
    Pan->Visible = true;
}
//------------------------------------------------------------------------------
bool Sure::OK(TButton *ioSender)
{
    if(!bOK)
    {
        oSender = ioSender;
        ShowPanel();
    }
return bOK;
}
//------------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
    //Yes
    Sure1.Pan->Visible = false;
    Sure1.bOK = true;
    Sure1.oSender->OnClick(Form1);

    Sure1.bOK = false;
    Sure1.oSender = 0;
}
//------------------------------------------------------------------------------
void __fastcall TForm1::Button7Click(TObject *Sender)
{
    //No
    Sure1.oSender = 0;
    Sure1.Pan->Visible = false;
}
//------------------------------------------------------------------------------











void SetTabStopToAddition(bool bToAddition = true)
{
    Form1->CB1->TabStop = bToAddition;
    Form1->CB4->TabStop = bToAddition;
    Form1->Bt1->TabStop = bToAddition;

    Form1->LE2->TabStop = !bToAddition;
    Form1->LE3->TabStop = !bToAddition;
    Form1->Bt5->TabStop = !bToAddition;
}
//---------------------------------------------------------------------------

void InitCompanies(ExcelInfo eFile)
{
    Variant vSheet;
    AnsiString sName;
    int nCount = eFile.GetSheetsCount();
    for(int i=1; i<nCount; i++)
    {
        vSheet = eFile.GetSheet(i);
        sName = vSheet.OlePropertyGet("Name");
        Form1->CB5->Items->Add(sName);
    }
}
//---------------------------------------------------------------------------
void LoadPositionsAndUnits(Variant vSheet)
{
    int nX = 5;
    StringsContainer strCont;
    AnsiString sValue = GetValue(GetCell(vSheet, 1, nX));
    while(sValue != "")
    {
        strCont.BreakString(sValue, ", "); //Разбиваем строку на имя товара, пр."Стяжки" и единицу измерения, пр."уп."
        Form1->LB1->Items->Add(strCont.Vector[0]);
        if(strCont.Vector.size()>1)
            Form1->LB2->Items->Add(strCont.Vector[1]);
        else
            Form1->LB2->Items->Add("шт.");

        sValue = GetValue(GetCell(vSheet, 1, ++nX));
    }
}
//---------------------------------------------------------------------------













//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    if(!mysql->Checked)
    {
        //Открыть файл базы
        ExcelInfo eFile(F_PATH);
        //Инициализация листов и загрузка поставщиков
        InitCompanies(eFile);

        Variant vSheet2 = eFile.GetSheet(eFile.GetSheetsCount());
        //Загрузить наименования товара из базы
        CB5->ItemIndex = 0;
        CB5Select(Form1);

        //Загружаем офисы
        LoadColumn(vSheet2, CB2->Items, 2, 2);
        //Загружаем компании на которые выставлять счета
        //LoadColumn(vSheet2, CB3->Items, 1, 2);

        //Закрываем файл
        eFile.CloseExFile();
    }
    else // V3.0
    {
        //LB1->Sorted = true; // Список позиций. При работе с экселькой сортировать нельзя - там дерьмовый код, есть привязка к позициям 
        MyDB1 = MyDB(ADOConnection1, ADOQuery1, 0, 0, 0, Memo1);
        DBMan1 = DBManager(&MyDB1);
        pPos = Positioner(Panel3, LB1, Ed1, LE6, &DBMan1, UD1);
        IPan = InfoPan(Panel4, LE7, LE8, LE9, ChB1, &MyDB1);


        MyDB1.ExecuteCommand("set names utf8");
        DBMan1.LoadCompanies(CB5->Items);
        DBMan1.LoadOffices(CB2->Items);

        Sure1 = Sure(Panel2);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CB1Exit(TObject *Sender)
{
    NormalizeCB(CB1, false, false);    
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Bt1Click(TObject *Sender)
{
    if(CB1->Text == "" || CB4->Text == "")
        return;

    int nRow = SG1->RowCount - 1;
    SG1->Cells[0][nRow] = CB1->Text;
    SG1->Cells[2][nRow] = CB4->Text;
    SG1->RowCount++; // Последний ряд всегда свободен

    //Memo1->Lines->Add(CB1->Text + " - " + Ed1->Text + " " + CB4->Text);
    if(CB1->ItemIndex<0) //Новая позиция
    {
        if(!mysql->Checked)
        {
            ExcelInfo eFile(F_PATH, false);
            Variant vSheet = eFile.GetSheet(CB5->ItemIndex+1);

            int nX = FindEmptyX(vSheet, 1);
            AnsiString sName = CB1->Text;
            if(CB4->Text != "шт.")
                sName += ", " + CB4->Text;
            SetValue(vSheet, 1, nX, sName.c_str());


			eFile.SaveFile();
			eFile.CloseExFile();
        }
		else //V3.0
			DBMan1.AddNewPosition(CB5->Text, CB1->Text, CB4->Text);

        LB1->Items->Add(CB1->Text);
	}
}
//---------------------------------------------------------------------------
/*
<Почта поставщика>
<Почта того, кто будет принимать>
manager@domen.ru

Заказ №<Номер заказа>

Приветствую, <имя>!

Нам нужно:
<Список>

Доставка в <офис, адрес>
Контактное лицо: <-||->
Счета на <Компания>.
Спасибо!

*/

void __fastcall TForm1::Bt2Click(TObject *Sender)
{
	if(!mysql->Checked)
    {
        // Тут был старый Excel-вариант 
	}
    else //V3.0
    {
        if(!Sure1.OK(Bt2))
            return;

        Order ord;
        StringsContainer contList;
        MyDB1.ExecuteCommand("select manager, email from companies where name like '" + CB5->Text + "'");
        AnsiString sManager = MyDB1.GetFieldValue(1, 0);
        AnsiString sManagerEmail = MyDB1.GetFieldValue(1, 1);

        MyDB1.ExecuteCommand("select adres, person, email from offices where name like '" + CB2->Text + "'");
        AnsiString sStoreEmail = MyDB1.GetFieldValue(1, 2);
        AnsiString sOffice = CB2->Text + ", " + MyDB1.GetFieldValue(1, 0);
        AnsiString sStoreKeeper = MyDB1.GetFieldValue(1, 1);
        AnsiString sOrderNumber = DBMan1.GetNewOrderNumber(CB5->Text);

        //Формирование заказа
        ord.SetDate(Now().DateString());
        ord.sOffice = CB2->Text;
        AnsiString str;
        for(int i = 0; i<SG1->RowCount-1; i++)
        {
            str = IntToStr(i+1) + ". " + SG1->Cells[0][i] + " - " + SG1->Cells[1][i] + " " + SG1->Cells[2][i];
            contList.Vector.push_back(str);
            ord.AddPosition(SG1->Cells[0][i], SG1->Cells[1][i]);
        }

        //Письмо
        Memo2->Clear();
        Memo2->Lines->Add(sManagerEmail);
        Memo2->Lines->Add(sStoreEmail);
        Memo2->Lines->Add("manager@domen.ru");
        Memo2->Lines->Add("");
        Memo2->Lines->Add("Заказ №" + sOrderNumber);
        Memo2->Lines->Add("");
        Memo2->Lines->Add("Приветствую, " + sManager + "!");
        Memo2->Lines->Add("");
        Memo2->Lines->Add("Нам нужно:");
        
        //Список
        for(unsigned i=0; i<contList.Vector.size(); i++)
            Memo2->Lines->Add(contList.Vector[i]);

        Memo2->Lines->Add("");
        Memo2->Lines->Add("Доставка в " + sOffice);
        Memo2->Lines->Add("Контактное лицо: " + sStoreKeeper);
        Memo2->Lines->Add("Спасибо!");

        DBMan1.AddNewOrder(CB5->Text, ord);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Bt3Click(TObject *Sender)
{
    if(!Sure1.OK(Bt3))
        return;

    if(!mysql->Checked)
    {
	    ExcelInfo eFile(F_PATH, false);
	    Variant vSheet = eFile.GetSheet(CB5->ItemIndex+1);

	    int nX = 1;
	    int nY = FindEmptyY(vSheet, 1)-1;
	    AnsiString sNumber = GetValue(vSheet, nY, 1); //Запомним номер заказа
	    AnsiString sValue = GetValue(vSheet, 1, nX); //Движемся по товарам и чистим поля в ряду nY
	    while(sValue != "")
	    {
		    SetValue(vSheet, nY, nX, "");
		    sValue = GetValue(vSheet, 1, ++nX);
	    }

	    eFile.SaveFile();
	    eFile.CloseExFile();

	    Memo2->Clear();
	    Memo2->Lines->Add("Заказ №" + sNumber + ", компании " + CB5->Text + " удален!");
    }
    else //v3.0
    {
        DBMan1.DeleteLastOrder(CB5->Text);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
	bool bOn = CheckBox1->Checked;

	//Кнопки удаления
    Bt3->Enabled = bOn;
    Bt4->Enabled = bOn;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Bt4Click(TObject *Sender)
{
    if(!Sure1.OK(Bt4))
        return;

    if(!mysql->Checked)
    {
        ExcelInfo eFile(F_PATH, false);
        Variant vSheet = eFile.GetSheet(CB5->ItemIndex+1);
        Variant vSheet2 = eFile.GetSheet(eFile.GetSheetsCount());


        int nX = FindEmptyX(vSheet, 1) - 1;
        AnsiString str = GetValue(vSheet, 1, nX);
        SetValue(vSheet, 1, nX, "");
        SetValue(vSheet2, 1, nX, "");
        Memo2->Lines->Add("Позиция " + str + " удалена.");

        eFile.SaveFile();
        eFile.CloseExFile();
    }
    else //V3.0
    {
        DBMan1.DeletePosition(CB5->Text);
    }
}
//---------------------------------------------------------------------------
void ShowScheta(Variant vSheet, int nY)
{
    AnsiString sValue = GetValue(GetCell(vSheet, nY, 4));
    StringsContainer strCont;
    strCont.BreakString(sValue, " || ");

    Form1->Memo3->Clear();
    for(unsigned int i = 0; i<strCont.Vector.size(); i++)
        Form1->Memo3->Lines->Add(strCont.Vector[i]);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LE1KeyPress(TObject *Sender, char &Key)
{
    StringsContainer strCont;
    if(Key == 13)
    {
        if(CB5->ItemIndex == -1)// Если не выбрана компания, прекращаем работу
            return;
        AnsiString str = LE1->Text;
        LeftDigitsOnly(str);
        LE1->Text = str;
        if(LE1->Text == "")
            return;

        if(!mysql->Checked)
        {
            //Memo1->Clear();
            SG1->Rows[0]->Clear();
            SG1->RowCount = 1;
        
            int nY = StrToInt(LE1->Text)+1;
            ExcelInfo eFile(F_PATH);
            Variant vSheet = eFile.GetSheet(CB5->ItemIndex+1);

            if(GetValue(vSheet, nY, 1) != "") //Существует ли заказ с таким номером?
            {
                AnsiString sCount, sValue;

                SG1->Rows[0]->Clear();
                SG1->Rows[1]->Clear();
                SG1->Rows[2]->Clear();
                SG1->RowCount = 4;
                SG1->Cells[0][0] = "Заказ №" + GetValue(vSheet, nY, 1) + ", от " + GetValue(vSheet, nY, 2);
                SG1->Cells[0][1] = "Офис: " + GetValue(vSheet, nY, 3);

                int nX = 5;  // Позиции начинаются с 5 столбца
                int nRow = 3; //Начинаем записывать позиции заказа с 4 строки
                sValue = GetValue(vSheet, 1, nX); //Движемся по товарам и проверяем количество в поле в ряду nY
                while(sValue != "")
                {
                    sCount = GetValue(vSheet, nY, nX);
                    if(sCount != "")
                    {
                        //Memo1->Lines->Add(sValue + " - " + sCount);
                        SG1->Cells[0][nRow] = sValue;
                        strCont.BreakString(sCount, " ");
                        SG1->Cells[1][nRow] = strCont.Vector[0];
                        SG1->Cells[2][nRow] = strCont.Vector[1];
                        nRow++;


                        SG1->RowCount = nRow+1;
                        SG1->Rows[nRow]->Clear();
                    }
                    sValue = GetValue(vSheet, 1, ++nX);
                }
                ShowScheta(vSheet, nY);
            }
            else
                SG1->Cells[0][0] = "Заказа с номером " + IntToStr(nY-1) + " не существует";
            eFile.CloseExFile();
        }
        else //v3.0
        {
            // str - номер заказа
            Order ord;
            ord.GetOrderFromMySQL(&MyDB1, CB5->Text, StrToInt(str));
            if(ord.nID)
                ord.ShowOnSG(SG1, Memo3);
            else // Заказа не существует
            {
                SG1->Cells[0][0] = "Заказа с номером " + str + " не существует";
            }
        }
        LE1->SelectAll();
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
    if(mysql->Checked)
        Form2->DBMan2 = &DBMan1; //v3.0
    Form2->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CB1Enter(TObject *Sender)
{
    SetTabStopToAddition();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Bt5Click(TObject *Sender)
{
    AnsiString sValue, sID = LE1->Text;
    LeftDigitsOnly(sID);

    if(sID == "" || LE2->Text == "" || LE3->Text == "")
        return;

    if(!mysql->Checked)
    {
        int nID = StrToInt(sID)+1;//Номер строки в базе

        ExcelInfo eFile(F_PATH, false);
        Variant vSheet = eFile.GetSheet(CB5->ItemIndex+1);
        sValue = GetValue(GetCell(vSheet, nID, 4));
        if(sValue != "")
            sValue+=" || ";
        sValue+= LE2->Text + " от " + LE3->Text;
        SetValue(vSheet, nID, 4, sValue.c_str());
        Memo3->Lines->Add(sValue);

        eFile.SaveFile();
        eFile.CloseExFile();
    }
    else //v3.0
    {
        sValue = LE2->Text + " от " + LE3->Text;
        DBMan1.AddDocsToTheOrder(CB5->Text, sID, sValue);
        Memo3->Lines->Add(sValue);
    }


    LE2->Text = "";
    LE3->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LE2Enter(TObject *Sender)
{
    SetTabStopToAddition(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    int nCount = SG1->RowCount;
    for(int i = nCount-1; i>=0; i--)
        SG1->Rows[i]->Clear();

    SG1->RowCount = 1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LE4KeyPress(TObject *Sender, char &Key)
{
    AnsiString str, sNum, sResult;
    if(Key == 13)
    {
        str = LE4->Text;
        LeftDigitsOnly(str);
        LE4->Text = str;
        if(LE4->Text == "")
            return;
        if(CB5->ItemIndex == -1) //Если не задано имя компании
            return;


        if(!mysql->Checked)
        {
            int nY = 2;
            ExcelInfo eFile(F_PATH);
            Variant vSheet = eFile.GetSheet(CB5->ItemIndex+1);
            sNum = GetValue(vSheet, nY, 1);
            while(sNum != "")
            {
                str = GetValue(vSheet, nY, 4);
                if(AnsiPos(LE4->Text, str))
                    sResult+= " " + sNum;

                sNum = GetValue(vSheet, ++nY, 1);
            }
            eFile.CloseExFile();
            LE5->Text = sResult;
        }
        else //v3.0
        {
            LE5->Text = DBMan1.FindOrdersWithSchet(CB5->Text, str);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LB1DblClick(TObject *Sender)
{
    int nRow = SG1->RowCount - 1;
    SG1->Cells[0][nRow] = LB1->Items->Strings[LB1->ItemIndex];

    if(!mysql->Checked)
    {
        SG1->Cells[2][nRow] = LB2->Items->Strings[LB1->ItemIndex];
    }
    else
    {
        SG1->Cells[2][nRow] = DBMan1.GetMeasure(CB5->Text, SG1->Cells[0][nRow]);
    }
    SG1->RowCount++; // Последний ряд всегда свободен
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CB5Select(TObject *Sender)
{
    if(!mysql->Checked)
    {
        LB1->Clear();
        LB2->Clear();

        ExcelInfo eFile(F_PATH);
        Variant vSheet = eFile.GetSheet(CB5->ItemIndex+1);

        //Загрузить наименования товара из базы и единицы
        LoadPositionsAndUnits(vSheet);

        //Закрываем файл
        eFile.CloseExFile();
    }
    else //V3.0
    {
        LB1->Clear();
        DBMan1.LoadPositionsOfCompany(LB1->Items, CB5->Text);

    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
    if(mysql->Checked) // v3.0
    {
        if(LE1->Text == "")//Не указан номер заказа
            return;
        if(CB5->ItemIndex == -1) // Не указана компания
            return;
        if(SG1->RowCount<4) // В списке ничего нет
            return;

        if(!Sure1.OK(Button3))
            return;

        Order ord;
        ord.GetOrderFromGrid(SG1, StrToInt(LE1->Text));
        DBMan1.UpdateOrder(CB5->Text, ord);
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
    if(!Sure1.OK(Button4))
        return;

    AnsiString sNewCompany = CB5->Text;
    DBMan1.AddNewCompany(sNewCompany);
    DBMan1.LoadCompanies(CB5->Items);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
    if(!Sure1.OK(Button5))
        return;

    AnsiString sNewCompany = CB5->Text;
    DBMan1.DeleteCompany(sNewCompany);
    DBMan1.LoadCompanies(CB5->Items);
    CB5->Text = "";
}
//---------------------------------------------------------------------------




void __fastcall TForm1::LB1Click(TObject *Sender)
{
    pPos.OnPosSelect();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N1Click(TObject *Sender)
{
    pPos.ActualCompany = CB5->Text;
    UD1->Max = pPos.List->Items->Count;
    UD1->Position = pPos.nSelPos;
    pPos.ShowPanel();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
    pPos.HidePanel();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LE6KeyPress(TObject *Sender, char &Key)
{
    if(Key == 13)
    {
        pPos.SetPosition();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Ed1KeyPress(TObject *Sender, char &Key)
{
    if(Key == 13)
    {
        pPos.SavePosName();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::UD1Click(TObject *Sender, TUDBtnType Button)
{
    pPos.FieldPos->Text = IntToStr(UD1->Position);
    pPos.SetPosition();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
    pPos.SaveOrder();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button8Click(TObject *Sender)
{
    IPan.ShowPanel();
    IPan.Open(CB5->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn4Click(TObject *Sender)
{
    IPan.HidePanel();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
    IPan.Save();
}
//---------------------------------------------------------------------------




