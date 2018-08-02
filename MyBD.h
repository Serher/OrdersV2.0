//---------------------------------------------------------------------------

#ifndef MyBDH
#define MyBDH
//---------------------------------------------------------------------------
#include <ADODB.hpp>
#include <DBGrids.hpp>
#include <IdTCPServer.hpp>



class MyDB
{
    //Private elements
    TADOConnection *Connection;
    TDataSource *DSource;
    TDBGrid *DBGrid;
    TDBNavigator *Nav; 
    TMemo *Memo;

    //Private funcs
    //void Log(AnsiString sMess);

    

    public:

    TADOQuery *Que;
    AnsiString LastCommand;  //Я не помню нахрен это мне было нужно, но пока оставлю

    //Constructor
    MyDB();
    MyDB(TADOConnection *Con, TADOQuery *Query, TDataSource *Sou=0, TDBGrid *Grid=0, TDBNavigator *Navi=0, TMemo *Log=0);
    
    void SetConnectionFile(AnsiString sPath);    
    void Connect();


    AnsiString ExecuteCommand(AnsiString sCommand);
    AnsiString GetFieldValue(int nY=1, int nX=0);
    AnsiString GetAutoIncrement(AnsiString sTable);
    


    //Temp
    void InsertIntoStates(AnsiString sState, int nPop);
    void Log(AnsiString sMess);
};







#endif



