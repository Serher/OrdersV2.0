//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>


#include "MyUtils.h"
#include "VariantFuncs.h"
#include "MyQSLBaseManager.h"


//---------------------------------------------------------------------------


const AnsiString F_PATH = "D:\\C++\\Borland Projects\\Manual tests\\OrdersV2.0\\Base.xlsx";




class TForm2 : public TForm
{
__published:	// IDE-managed Components
    TStringGrid *SG1;
    TComboBox *CMon;
    TComboBox *COffice;
    TComboBox *CTovar;
    TButton *Button1;
    TButton *Button2;
    TComboBox *CCompany;
    TButton *Button3;
    TMemo *Memo1;
    TButton *Button4;
    TPanel *Pan1;
    TButton *Button5;
    TComboBox *CB1;
    TLabel *Label1;
    TLabeledEdit *LE2;
    TComboBox *CB2;
    TLabel *Label2;
    TLabeledEdit *LE1;
    TButton *Button6;
    TGroupBox *GroupBox3;
    TLabeledEdit *LE3;
    TLabeledEdit *LE4;
    TGroupBox *GroupBox1;
    TListBox *Sorter;
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall Button6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations


    int nItogo;
    __fastcall TForm2(TComponent* Owner);


    DBManager *DBMan2;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
