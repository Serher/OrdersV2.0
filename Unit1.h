//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------



#include "MyQSLBaseManager.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//#include <tchar.h>
//#define _UNICODE


const AnsiString BASE = "orders";


//------------------------------------------------------------------------------

    
//------------------------------------------------------------------------------
class Filler   //Для переноса информации из Эксельки
{
    public:
    DBManager *DBMan1;

    Filler(){DBMan1 = 0;}
    Filler(DBManager *iDBMan1){DBMan1 = iDBMan1;}

    void Copy();
};







//------------------------------------------------------------------------------
class FloatingPanel
{
    public:
    TPanel *Pan;
    int Height;
    int Width;
    int Top;
    int Left;

    bool Visible;

    FloatingPanel(TPanel *iPan = 0);

    void ShowPanel();
    void HidePanel();
};
//------------------------------------------------------------------------------
class Positioner : public FloatingPanel
{
    public:
    TListBox *List;
    TEdit *FieldName;
    TLabeledEdit *FieldPos;
    DBManager *DBMan1;
    TUpDown *Arrows; 

    int nSelPos;
    AnsiString ActualCompany;

    // Constructors
    Positioner();
    Positioner(TPanel *iPan, TListBox *iList, TEdit *iFieldName, TLabeledEdit *iFieldPos, DBManager *iDBMan1, TUpDown *iArrows);

    //Funcs
    void OnPosSelect();
    void SetPosition();
    void SaveOrder();
    void SavePosName();
};
//------------------------------------------------------------------------------
class InfoPan : public FloatingPanel
{
    public:
    TLabeledEdit *Name;
    TLabeledEdit *Manager;
    TLabeledEdit *Email;
    TCheckBox *ChB;
    MyDB *MyDB1;

    AnsiString sCompany;

    InfoPan();
    InfoPan(TPanel *iPan, TLabeledEdit *iName, TLabeledEdit *iManager, TLabeledEdit *iEmail, TCheckBox *iChB, MyDB *iMyDB1);

    void Open(AnsiString isCompany);
    void Save();
};








//------------------------------------------------------------------------------
class Searcher
{
    //Private Funcs
    //AnsiString DateFormatForSort(AnsiString sDate);
    //AnsiString SortOrders(MyDB *MyDB1, TListBox *Sort);


    public:
    // Components
    MyDB *MyDB1;
    
    TListBox *Sorter;
    TStringGrid *SG;

    AnsiString sFilterCompany;
    AnsiString sFilterDate;
    AnsiString sFilterOffice;
    AnsiString sFilterTovar;
    int nItogo;

    // Help vars
    AnsiString sCompanyName;

    //Constructors
    Searcher(){MyDB1 = 0; Sorter = 0; SG = 0;}
    Searcher(MyDB *iMyDB1, TListBox *iSorter, TStringGrid *iSG){MyDB1 = iMyDB1; Sorter = iSorter; SG = iSG;}


    // Funcs
    void FillTheFilter(AnsiString isFilterCompany, AnsiString isFilterDate, AnsiString isFilterOffice, AnsiString isFilterTovar);//Наполнение фильтра для последующей работы
    void SearchOrdersOfTheCompany(); //Если в фильтре задана конкретная компания

    AnsiString DateFormatForSort(AnsiString sDate);
    AnsiString StringForSort(AnsiString str, AnsiString sTovarName, AnsiString sMeasure);
    void SearchOrdersWithPositionOfCompany(AnsiString sID, int nTovarID = 0);
    void SearchOrdersOfCompany(AnsiString sID);
    void SearchOrders();
    void MoveResultsToSG();

};
//------------------------------------------------------------------------------
class Sure
{
    public:
    TPanel *Pan;
    TButton *oSender;
    bool bOK;

    //Funcs
    Sure();
    Sure(TPanel * iPan);
    void ShowPanel();
    bool OK(TButton *ioSender);
};
//------------------------------------------------------------------------------



class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TComboBox *CB1;
    TButton *Bt1;
    TComboBox *CB2;
    TLabel *Label1;
    TLabel *Label3;
    TLabel *Label4;
    TMemo *Memo2;
    TButton *Bt2;
    TLabel *Label5;
    TComboBox *CB3;
    TComboBox *CB4;
    TButton *Bt3;
    TLabeledEdit *LE1;
    TCheckBox *CheckBox1;
    TButton *Bt4;
    TButton *Button1;
    TLabeledEdit *LE2;
    TLabeledEdit *LE3;
    TButton *Bt5;
    TMemo *Memo3;
    TLabel *Label6;
    TStringGrid *SG1;
    TButton *Button2;
    TLabeledEdit *LE4;
    TGroupBox *GroupBox1;
    TLabeledEdit *LE5;
    TLabel *Label7;
    TListBox *LB1;
    TListBox *LB2;
    TGroupBox *GroupBox2;
    TPanel *Panel1;
    TLabel *Label2;
    TComboBox *CB5;
    TButton *Button3;
    TCheckBox *mysql;
    TADOConnection *ADOConnection1;
    TADOQuery *ADOQuery1;
    TButton *Button4;
    TButton *Button5;
    TPanel *Panel2;
    TButton *Button6;
    TButton *Button7;
    TLabel *Label8;
    TPanel *Panel3;
    TEdit *Ed1;
    TLabeledEdit *LE6;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TPopupMenu *PM1;
    TMenuItem *N1;
    TUpDown *UD1;
    TButton *Button8;
    TPanel *Panel4;
    TLabeledEdit *LE7;
    TLabeledEdit *LE8;
    TLabeledEdit *LE9;
    TLabel *Label9;
    TBitBtn *BitBtn3;
    TBitBtn *BitBtn4;
    TCheckBox *ChB1;
    TMemo *Memo1;
    TCheckBox *ChB2;
    TIdTCPClient *IdTCPClient1;
    TStringGrid *SG2;
    void __fastcall CB1Exit(TObject *Sender);
    void __fastcall Bt1Click(TObject *Sender);
    void __fastcall Bt2Click(TObject *Sender);
    void __fastcall Bt3Click(TObject *Sender);
    void __fastcall CheckBox1Click(TObject *Sender);
    void __fastcall Bt4Click(TObject *Sender);
    void __fastcall LE1KeyPress(TObject *Sender, char &Key);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall CB1Enter(TObject *Sender);
    void __fastcall Bt5Click(TObject *Sender);
    void __fastcall LE2Enter(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall LE4KeyPress(TObject *Sender, char &Key);
    void __fastcall LB1DblClick(TObject *Sender);
    void __fastcall CB5Select(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall Button6Click(TObject *Sender);
    void __fastcall Button7Click(TObject *Sender);
    void __fastcall LB1Click(TObject *Sender);
    void __fastcall N1Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
    void __fastcall LE6KeyPress(TObject *Sender, char &Key);
    void __fastcall Ed1KeyPress(TObject *Sender, char &Key);
    void __fastcall UD1Click(TObject *Sender, TUDBtnType Button);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall Button8Click(TObject *Sender);
    void __fastcall BitBtn4Click(TObject *Sender);
    void __fastcall BitBtn3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);

    MyDB MyDB1;
    DBManager DBMan1;
    Sure Sure1;
    Positioner pPos;
    InfoPan IPan;
    
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
