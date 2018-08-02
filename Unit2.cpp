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
    for(int i=1; i<nSheetsCount; i++) //��������� ���� �� ��������� - ��� Data
    {
        vSheet = eFile.GetSheet(i);
        nX = 5;
        sValue = GetValue(GetCell(vSheet, 1, nX));
        while(sValue != "")
        {
            //strCont.BreakString(sValue, ", "); //��������� ������ �� ��� ������, ��."������" � ������� ���������, ��."��."
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
    SG1->Cells[0][0] = "�";
    SG1->Cells[1][0] = "�����";
    SG1->Cells[2][0] = "����";
    SG1->Cells[3][0] = "�����";
    SG1->Cells[4][0] = "���������";

    //�������� ������ ��������
    CCompany->Items = Form1->CB5->Items;
    DBMan2 = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormActivate(TObject *Sender)
{
    if(!DBMan2)
    {
        //������� ���� ����
        ExcelInfo eFile(F_PATH);
        Variant vSheet2 = eFile.GetSheet(eFile.GetSheetsCount());

        //��������� ������������ ������ �� ����
        LoadPositions(eFile);

        //��������� �����
        LoadColumn(vSheet2, COffice->Items, 2, 2);

        //��������� ����
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
    if(nMonth<0) return "";//����� �� ������

    nMonth++; //0 - ��� ������, ������� �������
    AnsiString sResult;
    if(nMonth<10)
        sResult = ".0" + IntToStr(nMonth) + "."; //�������� ���-�� �����: ".01."(������)
    else
        sResult = "." + IntToStr(nMonth) + "."; //�������� ���-�� �����: ".11."(������)
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

        for(int i=1; i<nSheetsCount; i++)//��������� ���� �� ��������� - ��� Data
        {
            //nY = 2;
            vSheet = eFile.GetSheet(i);
            sSheetName = vSheet.OlePropertyGet("Name");

            if(sCompany != "" && sSheetName != sCompany)//� ���������� ������ ������ ���������� ��������-���������
                continue;

            sNumber = GetValue(GetCell(vSheet, nY=2, 1));//����� ������
            while(sNumber != "")
            {
                if(GetLineHasMonth(vSheet, nY, sMonth))
                {
                    if(GetLineHasOffice(vSheet, nY, sOffice))
                    {
                        if(CTovar->ItemIndex>=0)//� ������� ������ ���������� �����
                            nX = FindXofValue(vSheet, 1, sTovar);
                        else
                            nX = 5;//����� �� �����, ���� � ������ �� ���� ��������

                        if(nX) //����� ����� 0, ���� ����� ����� � �������, �� � ������� �����(� ������� ����������) ������ ������ ���
                        {
                            do
                            {
                                sTempTovar = GetValue(GetCell(vSheet, 1, nX));
                                if(GetLineHasTovar(vSheet, nY, nX))
                                {
                                    //��������� � ������ � �����
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
                            }while(sTovar != sTempTovar);   //���� ����� ����� ������ � �����, �� ��� ������� ���������� ��� ������ �� ��������
                                                            //���� �� ����� �� ����� ������, ������� ���������� ��� ��������� ������ ������, �.�. ������� ���� ������ �������
                        }
                    }
                }
                sNumber = GetValue(GetCell(vSheet, ++nY, 1));
            }

        }

        SG1->Rows[nEmptyRow]->Clear();
        SG1->Cells[3][nEmptyRow] = "�����: " + IntToStr(nItogo);

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
        Button3->Caption = "�����";
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
                if(k < (SG1->ColCount - 1))  // ���� ������ ������ ��� ��� �� ��������� �������, � ����� �������� ���������
                    str+="\t";
            }
            Memo1->Lines->Add(str);
        }
        Button3->Caption = "�������";
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

    for(int i=1; i<nSheetsCount; i++)//��������� ���� �� ��������� - ��� Data
    {
        vSheet = eFile.GetSheet(i);
        sNumber = GetValue(GetCell(vSheet, nY=2, 1));//����� ������
        while(sNumber != "")
        {
            if(GetLineHasMonth(vSheet, nY, sMonth))
            {
                if(GetLineHasMonth(vSheet, nY, LE2->Text))//��� ������� ������������ ��� �������� ����
                {
				    if(GetLineHasOffice(vSheet, nY, sOffice))
                    {
                        //������� 4 ���� � ���������� �����
                        nX = FindXofValue(vSheet, 1, "������ 4 ����, ����");
                        if(nX)
                        {
                            GetLineHasTovar(vSheet, nY, nX); // ��� ������� ������� ����� ����������
                            //n4pair += nItogo;
                            nItogo = 0;
                        }
                        //������� 2 ���� � ���������� �����
                        nX = FindXofValue(vSheet, 1, "������ 2 ����, ����");
                        if(nX)
                        {
                            GetLineHasTovar(vSheet, nY, nX); // ��� ������� ������� ����� ����������
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

    //����
    Memo1->Lines->Add("����: " + sOffice);
    //�� ����� �� ����� ���������� �����������: ������� ��
    Memo1->Lines->Add("�� " + CB2->Text + " ����� ���������� �����������: " + LE1->Text);
    //������������� ������: ������� �� ������������, ������� �� ���������, ����� ������ ������� ��
    Memo1->Lines->Add("������������� ������: " + IntToStr(n2pairUsed) + " ���� ���������, " + IntToStr(n4pairUsed) + " ���� ������������. ����� ������: " + IntToStr(nMettersUsed) + "�");
    //������� ������
    Memo1->Lines->Add("������� ������: " + IntToStr((int)(nMettersUsed / StrToInt(LE1->Text))) + "�");


    //Memo1->Lines->Add("� ������� ������ ��������: " + IntToStr(n2pair) + " ���� ���������, " + IntToStr(n4pair) + " ���� ������������.");
    //Memo1->Lines->Add("��������: " + LE4->Text + " ���� ���������, " + LE6->Text + " ���� ������������.");
    //Memo1->Lines->Add("����������� ����������: " + LE1->Text);
    //Memo1->Lines->Add("����� ������ ��������������� ������: " + IntToStr(n2pairUsed) + " * 305� + " + IntToStr(n4pairUsed) + " * 2 * 305� = " + IntToStr(nMettersUsed) + "�");
    //Memo1->Lines->Add("������� ������: " + IntToStr((int)(nMettersUsed / StrToInt(LE1->Text))) + "�");
}
//---------------------------------------------------------------------------

