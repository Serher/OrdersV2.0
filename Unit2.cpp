//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;


//---------------------------------------------------------------------------
void LoadPositions(ExcelInfo eFile)
{
    Form2->CTovar->Clear();
    //Form2->CCompany->Clear();

    int nX;
    //StringsContainer strCont;
    AnsiString sValue;
    Variant vSheet;

    int nSheetsCount = eFile.GetSheetsCount();
    for(int i=1; i<nSheetsCount; i++) //Последний лист не считываем - это Data
    {
        vSheet = eFile.GetSheet(i);
        nX = 5;
        sValue = GetValue(GetCell(vSheet, 1, nX));
        while(sValue != "")
        {
            //strCont.BreakString(sValue, ", "); //Разбиваем строку на имя товара, пр."Стяжки" и единицу измерения, пр."уп."
            //sValue = strCont.Vector[0];
            if(Form2->CTovar->Items->IndexOf(sValue) == -1)
                Form2->CTovar->Items->Add(sValue);

            sValue = GetValue(GetCell(vSheet, 1, ++nX));
        }
    }
}


















//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner)
{
    SG1->Cells[0][0] = "№";
    SG1->Cells[1][0] = "Месяц";
    SG1->Cells[2][0] = "Офис";
    SG1->Cells[3][0] = "Товар";
    SG1->Cells[4][0] = "Поставщик";

    //Копируем список компаний
    CCompany->Items = Form1->CB5->Items;
    DBMan2 = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormActivate(TObject *Sender)
{
    if(!DBMan2)
    {
        //Открыть файл базы
        ExcelInfo eFile(F_PATH);
        Variant vSheet2 = eFile.GetSheet(eFile.GetSheetsCount());

        //Загрузить наименования товара из базы
        LoadPositions(eFile);

        //Загружаем офисы
        LoadColumn(vSheet2, COffice->Items, 2, 2);

        //Закрываем файл
        eFile.CloseExFile();
    }
    else //v3.0
    {
        DBMan2->LoadOffices(COffice->Items);
        DBMan2->LoadAllPositions(CTovar->Items);
    }
}
//---------------------------------------------------------------------------
AnsiString GetMonthStr(int nMonth)
{
    if(nMonth<0) return "";//Месяц не указан

    nMonth++; //0 - это Январь, поэтому плюсуем
    AnsiString sResult;
    if(nMonth<10)
        sResult = ".0" + IntToStr(nMonth) + "."; //получаем что-то вроде: ".01."(Январь)
    else
        sResult = "." + IntToStr(nMonth) + "."; //получаем что-то вроде: ".11."(Ноябрь)
    return sResult;
}
//---------------------------------------------------------------------------
bool GetLineHasMonth(Variant vSheet, int nLine, AnsiString sMonth)
{
    if(sMonth == "")
        return true;

    AnsiString sValue = GetValue(GetCell(vSheet, nLine, 2));
    if(AnsiPos(sMonth, sValue))
        return true;
return false;
}
//---------------------------------------------------------------------------
bool GetLineHasOffice(Variant vSheet, int nLine, AnsiString sOffice)
{
    if(sOffice == "")
        return true;

    AnsiString sValue = GetValue(GetCell(vSheet, nLine, 3));
    if(AnsiPos(sOffice, sValue))
        return true;
return false;
}
//---------------------------------------------------------------------------
bool GetLineHasTovar(Variant vSheet, int nLine, int nTovarX)
{
    AnsiString sValue = GetValue(GetCell(vSheet, nLine, nTovarX));
    if(sValue == "")
        return false;

    LeftDigitsOnly(sValue);
    Form2->nItogo+= StrToInt(sValue);
return true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
    if(CMon->ItemIndex <0 && COffice->ItemIndex <0 && CTovar->ItemIndex < 0 && CCompany->ItemIndex<0)
        return;
        
    SG1->Visible = true;
    Memo1->Visible = false;

    SG1->RowCount = 2;
    int nEmptyRow = 1;
    nItogo = 0;
    AnsiString sMonth = GetMonthStr(CMon->ItemIndex);
    AnsiString sOffice = COffice->Text;
    AnsiString sTovar = CTovar->Text;
    AnsiString sCompany = CCompany->Text;
    AnsiString sTempTovar;

    if(!DBMan2)
    {
        int nX, nY;
        ExcelInfo eFile(F_PATH);
        int nSheetsCount = eFile.GetSheetsCount();
        Variant vSheet;
        AnsiString sNumber, sSheetName;

        for(int i=1; i<nSheetsCount; i++)//Последний лист не проверяем - это Data
        {
            //nY = 2;
            vSheet = eFile.GetSheet(i);
            sSheetName = vSheet.OlePropertyGet("Name");

            if(sCompany != "" && sSheetName != sCompany)//В параметрах поиска задана конкретная компания-поставщик
                continue;

            sNumber = GetValue(GetCell(vSheet, nY=2, 1));//Номер заказа
            while(sNumber != "")
            {
                if(GetLineHasMonth(vSheet, nY, sMonth))
                {
                    if(GetLineHasOffice(vSheet, nY, sOffice))
                    {
                        if(CTovar->ItemIndex>=0)//В фильтре указан конкретный товар
                            nX = FindXofValue(vSheet, 1, sTovar);
                        else
                            nX = 5;//Товар не задан, идем с начала по всем позициям

                        if(nX) //Будет равен 0, если товар задан в фильтре, но в текущем листе(у данного поставщика) такого товара нет
                        {
                            do
                            {
                                sTempTovar = GetValue(GetCell(vSheet, 1, nX));
                                if(GetLineHasTovar(vSheet, nY, nX))
                                {
                                    //Добавляем в данные в отчет
                                    SG1->Cells[0][nEmptyRow] = sNumber;
                                    SG1->Cells[1][nEmptyRow] = GetValue(GetCell(vSheet, nY, 2));
                                    SG1->Cells[2][nEmptyRow] = GetValue(GetCell(vSheet, nY, 3));
                                    SG1->Cells[3][nEmptyRow] = sTempTovar + " - " + GetValue(GetCell(vSheet, nY, nX));
                                    SG1->Cells[4][nEmptyRow] = sSheetName;


                                    nEmptyRow++;
                                    if(SG1->RowCount == nEmptyRow)
                                        SG1->RowCount++;
                                }
                                nX++;
                            }while(sTovar != sTempTovar);   //Если товар будет указан в комбо, то это условие выполнится при первой же итерации
                                                            //Если же товар не будет указан, условие выполнится при нахождени пустой ячейки, т.е. пройдет весь список товаров
                        }
                    }
                }
                sNumber = GetValue(GetCell(vSheet, ++nY, 1));
            }

        }

        SG1->Rows[nEmptyRow]->Clear();
        SG1->Cells[3][nEmptyRow] = "ИТОГО: " + IntToStr(nItogo);

        eFile.CloseExFile();
    }
    else //v3.0
    {
        Searcher sear = Searcher(DBMan2->MyDB1, Sorter, SG1);
        sear.FillTheFilter(CCompany->Text, CMon->Text, COffice->Text, CTovar->Text);
        sear.SearchOrders();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button2Click(TObject *Sender)
{
    CMon->ItemIndex = -1;
    COffice->ItemIndex = -1;
    CTovar->ItemIndex = -1;
    CCompany->ItemIndex = -1;    
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button3Click(TObject *Sender)
{
    if(Memo1->Visible)
    {
        Button3->Caption = "Текст";
        Memo1->Visible = false;
        SG1->Visible = true;
    }
    else
    {
        AnsiString str;
        Memo1->Clear();
        for(int i = 0; i< SG1->RowCount; i++)
        {
            str = "";
            for(int k=0; k<SG1->ColCount; k++)
            {
                str+=SG1->Cells[k][i];
                if(k < (SG1->ColCount - 1))  // если меньше значит это еще не последний столбец, и нужно добавить табуляцию
                    str+="\t";
            }
            Memo1->Lines->Add(str);
        }
        Button3->Caption = "Таблица";
        Memo1->Visible = true;
        SG1->Visible = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Button4Click(TObject *Sender)
{
    SG1->Visible = false;
    Memo1->Visible = true;
    Pan1->Visible = true;

    CB1->Items = COffice->Items;
    LE2->Text = Now().DateString().SubString(7, 4);

        
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button5Click(TObject *Sender)
{
    SG1->Visible = true;
    Memo1->Visible = false;
    Pan1->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button6Click(TObject *Sender)
{
    if(CB1->ItemIndex <0 || CB2->ItemIndex <0 || LE1->Text == "" || LE2->Text == "" || LE3->Text == "" || LE4->Text == "")
        return;

    AnsiString sMonth = GetMonthStr(CB2->ItemIndex);
    AnsiString sOffice = CB1->Text;

    int nX, nY;
    int n2pairUsed = StrToInt(LE3->Text);
    int n4pairUsed = StrToInt(LE4->Text);
    //nItogo = 0;

    /*
    ExcelInfo eFile(F_PATH);
    int nSheetsCount = eFile.GetSheetsCount();
    Variant vSheet;
    AnsiString sNumber;

    for(int i=1; i<nSheetsCount; i++)//Последний лист не проверяем - это Data
    {
        vSheet = eFile.GetSheet(i);
        sNumber = GetValue(GetCell(vSheet, nY=2, 1));//Номер заказа
        while(sNumber != "")
        {
            if(GetLineHasMonth(vSheet, nY, sMonth))
            {
                if(GetLineHasMonth(vSheet, nY, LE2->Text))//Тут функция используется для проверки года
                {
				    if(GetLineHasOffice(vSheet, nY, sOffice))
                    {
                        //Считаем 4 пары в конкретном листе
                        nX = FindXofValue(vSheet, 1, "Кабель 4 пары, бухт");
                        if(nX)
                        {
                            GetLineHasTovar(vSheet, nY, nX); // Эта функция считает общее количество
                            //n4pair += nItogo;
                            nItogo = 0;
                        }
                        //Считаем 2 пары в конкретном листе
                        nX = FindXofValue(vSheet, 1, "Кабель 2 пары, бухт");
                        if(nX)
                        {
                            GetLineHasTovar(vSheet, nY, nX); // Эта функция считает общее количество
                            //n2pair += nItogo;
                            nItogo = 0;
                        }
				    }
                }
            }
            sNumber = GetValue(GetCell(vSheet, ++nY, 1));
        }
    }
    eFile.CloseExFile();
    */
    int nMettersUsed = n2pairUsed*305 + n4pairUsed*2*305;

    //Офис
    Memo1->Lines->Add("Офис: " + sOffice);
    //За такой то месяц выполненно подключений: столько то
    Memo1->Lines->Add("За " + CB2->Text + " месяц выполненно подключений: " + LE1->Text);
    //Использованно кабеля: столько то четырехпарки, столько то двухпарки, общий метраж столько то
    Memo1->Lines->Add("Использованно кабеля: " + IntToStr(n2pairUsed) + " бухт двухпарки, " + IntToStr(n4pairUsed) + " бухт четерехпарки. Общий метраж: " + IntToStr(nMettersUsed) + "М");
    //Средний расход
    Memo1->Lines->Add("Средний расход: " + IntToStr((int)(nMettersUsed / StrToInt(LE1->Text))) + "М");


    //Memo1->Lines->Add("В течение месяца заказано: " + IntToStr(n2pair) + " бухт двухпарки, " + IntToStr(n4pair) + " бухт четерехпарки.");
    //Memo1->Lines->Add("Осталось: " + LE4->Text + " бухт двухпарки, " + LE6->Text + " бухт четерехпарки.");
    //Memo1->Lines->Add("Подключений выполненно: " + LE1->Text);
    //Memo1->Lines->Add("Общий метраж использованного кабеля: " + IntToStr(n2pairUsed) + " * 305М + " + IntToStr(n4pairUsed) + " * 2 * 305М = " + IntToStr(nMettersUsed) + "М");
    //Memo1->Lines->Add("Средний расход: " + IntToStr((int)(nMettersUsed / StrToInt(LE1->Text))) + "М");
}
//---------------------------------------------------------------------------

