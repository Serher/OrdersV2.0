//---------------------------------------------------------------------------

#ifndef MyQSLBaseManagerH
#define MyQSLBaseManagerH
//---------------------------------------------------------------------------
#include <vector>
#include "MyBD.h"


//------------------------------------------------------------------------------
class Order
{
    public:
    int nID;
    AnsiString sDate;
    AnsiString sOffice;
    AnsiString sDocs;
    std::vector<AnsiString> sPositions;
    std::vector<AnsiString> sAmounts;
    std::vector<AnsiString> sMeasures;

    Order();
    void SetDate(AnsiString sDateToSet = "");
    AnsiString DateForMySQL();
    void AddPosition(AnsiString sPos, AnsiString sAmo, AnsiString sMea = "");
    void GetOrderFromExcel(Variant vSheet, int nY);
    void GetOrderFromMySQL(MyDB *MyDB1, AnsiString sCompany, int nNumber);
    void GetOrderFromGrid(TStringGrid *SG, int nNumber);
    void ShowOnSG(TStringGrid *SG, TMemo *Memo);
    void ShowScheta(TMemo *Memo);

};
//------------------------------------------------------------------------------





class DBManager
{
    //Private Function
    AnsiString GetLastInsertID();
    AnsiString GetCompanyID(AnsiString sCompany);
    AnsiString RecountAndSetAutoIncrement(AnsiString sTable, AnsiString sField = "id");
    AnsiString TabPosName(AnsiString sID){return "positions_of_company_" + sID;}
    AnsiString TabOrdName(AnsiString sID){return "orders_of_company_" + sID;}
    void LoadToList(TStrings *tsList, MyDB *MyDB1, bool bClear = true);
    AnsiString GetPositionID(AnsiString sCompanyID, AnsiString sPos);


    public:
    //Cpmponents
    MyDB *MyDB1;

    //Constructors
    DBManager(){MyDB1 = 0;}
    DBManager(MyDB *iniMyDB1){MyDB1 = iniMyDB1;}

    
    //Functions
    void AddNewCompany(AnsiString sCompany);
    void SetCompanyActive(AnsiString sCompany, bool bActive = true);
    void DeleteCompany(AnsiString sName);

    void AddNewPosition(AnsiString sCompany, AnsiString sName, AnsiString sMeasure = "шт.");
    void DeletePosition(AnsiString sCompany, AnsiString sPos = ""); // If no pos specified the last one would be deleted
    AnsiString GetMeasure(AnsiString sCompany, AnsiString sPos);
    void SavePositionsOrder(AnsiString sCompany, TListBox *List);
    void SaveNewPositionsName(AnsiString sCompany, AnsiString sNewName, AnsiString sOldName);

    AnsiString GetNewOrderNumber(AnsiString sCompany);
    AnsiString AddNewOrder(AnsiString sCompany, Order ord); //Возвращает предупреждающее сообщение. Если возвращает "", значит все ОК.
    void UpdateOrder(AnsiString sCompany, Order ord);
    void DeleteLastOrder(AnsiString sCompany);
    void AddDocsToTheOrder(AnsiString sCompany, AnsiString sOrdNumber, AnsiString sDocs);
    AnsiString FindOrdersWithSchet(AnsiString sCompany, AnsiString sSchet);

    //Load
    void LoadCompanies(TStrings *tsList, bool bOnlyActive = true);
    void LoadPositionsOfCompany(TStrings *tsList, AnsiString sCompany, bool bClear = true);
    void LoadAllPositions(TStrings *tsList);
    void LoadOffices(TStrings *tsList);
};





#endif
