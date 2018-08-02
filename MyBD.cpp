//---------------------------------------------------------------------------


#pragma hdrstop

#include "MyBD.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



/* Функция для чтения инфы с сервера и корректной записи в StringGrid
Пример использования:
    AnsiString sMess = Edit1->Text;
    IdTCPClient1->Write(sMess); // Отправляем MySQL-комманду
    RecieveReplyToGrid(Form1);  // Ждем ответа



void RecieveReplyToGrid(TForm1 *Form1, int nPart = 0)
{
    AnsiString str = Form1->IdTCPClient1->CurrentReadBuffer();

    if(str == "Сервер занят")
    {
        Form1->Memo1->Lines->Add(str);
        return;
    }
    nPart++;

    if(nPart == 1)//Принимаем Y-размер таблицы
    {
        Form1->SG->RowCount = StrToInt(str);
        Form1->IdTCPClient1->Write("+");
        RecieveReplyToGrid(Form1, nPart);
    }
    else if(nPart == 2)//Принимаем X-размер таблицы
    {
        Form1->SG->ColCount = StrToInt(str);
        Form1->IdTCPClient1->Write("+");
        RecieveReplyToGrid(Form1, nPart);
    }
    else //Принимаем основную инфу для таблицы
    {
        int nY = (nPart-3) / Form1->SG->ColCount;
        int nX = (nPart-3) % Form1->SG->ColCount;
        Form1->SG->Cells[nX][nY] = str;


        if( ((nY+1) < Form1->SG->RowCount)   ||   ((nX+1) < Form1->SG->ColCount) )
        {
            Form1->IdTCPClient1->Write("+");
            RecieveReplyToGrid(Form1, nPart);
        }
        else // вся таблица заполнена
        {
            //nPart = 0;
            Form1->Memo1->Lines->Add("Finish");
        }
    }
}
*/













//------------------------------------------------------------------------------
MyDB::MyDB()
{
    Connection = 0;
    Que = 0;
    DSource = 0;
    DBGrid = 0;
    Nav = 0;
    Memo = 0;
}
//------------------------------------------------------------------------------
MyDB::MyDB(TADOConnection *Con, TADOQuery *Query, TDataSource *Sou, TDBGrid *Grid, TDBNavigator *Navi, TMemo *Log)
{
    Connection = Con;
    Que = Query;
    DSource = Sou;
    DBGrid = Grid;
    Nav = Navi;
    Memo = Log;

    Que->Connection = Connection;
    if(DSource)
        DSource->DataSet = Que;
    if(DBGrid)
        DBGrid->DataSource = DSource;
    if(Nav)
        Nav->DataSource = DSource;
}
//------------------------------------------------------------------------------
void MyDB::Log(AnsiString sMess)
{
    if(Memo)
        Memo->Lines->Add(sMess);
}
//------------------------------------------------------------------------------
void MyDB::SetConnectionFile(AnsiString sPath)
{
    sPath = "FILE NAME=" + sPath;
    WideString WS;
    WS.SetLength(sPath.Length());

    for(int i = 1; i <= sPath.Length(); i++)
    {
        WS[i] = sPath[i];
    }
    Connection->ConnectionString = WS;
}
//------------------------------------------------------------------------------
void MyDB::Connect()
{
    Connection->Connected = true;
    Log("Connection OK");
}
//------------------------------------------------------------------------------
AnsiString MyDB::ExecuteCommand(AnsiString sCommand)
{
    AnsiString sResult;
    Log("ExecuteCommand: " + sCommand);
    LastCommand = sCommand;

    Que->Close();
    Que->SQL->Clear();
    Que->SQL->Text = AnsiToUtf8(sCommand);

    try
    {
        if(sCommand.LowerCase().AnsiPos("use ") || sCommand.LowerCase().AnsiPos("insert ") || sCommand.LowerCase().AnsiPos("delete ") || sCommand.LowerCase().AnsiPos("set ") || sCommand.LowerCase().AnsiPos("create ") || sCommand.LowerCase().AnsiPos("alter ") || sCommand.LowerCase().AnsiPos("drop "))
            Que->ExecSQL();
        else
            Que->Open();
    }
    catch(Exception &exception)
    {
        if(exception.Message.AnsiPos("You have an error in your SQL syntax"))
            sResult = "Неверный систаксис";
        else if(exception.Message.AnsiPos("Table") && exception.Message.AnsiPos("doesn't exist"))
            sResult = "В выбранной базе нет указанной таблицы!";
        else if(exception.Message.AnsiPos("MySQL server has gone away"))
        {
            Log("MySQL сервер разорвао соединение. Переподключение");
            Connection->Close();
            Connection->Open();
            ExecuteCommand("Use test");
            ExecuteCommand(sCommand);
        }
        else
            sResult = exception.Message;
    }
    catch(...)
    {
        Log("Какая-то куета");
    }

    if(sResult != "")
        Log(sResult);
return sResult;
}
//------------------------------------------------------------------------------
AnsiString MyDB::GetFieldValue(int nY, int nX)
{
    if(nY > Que->RecordCount)
        nY = Que->RecordCount;
    else if(nY<=0)
        nY = 1;

    if(nX>=Que->FieldCount)
        nX = Que->FieldCount - 1;
    if(nX < 0)
        nX = 0;
    
    Que->RecNo = nY;

    //Log("GetFieldValue: nY = " + IntToStr(nY) + ", nX = " + IntToStr(nX));
    //Log("GetFieldValue Result: " + Utf8ToAnsi(Que->Fields->Fields[nX]->Text));
return Utf8ToAnsi(Que->Fields->Fields[nX]->Text);
}
//------------------------------------------------------------------------------
AnsiString MyDB::GetAutoIncrement(AnsiString sTable)
{
    ExecuteCommand("show table status like '" + sTable + "'");
    return GetFieldValue(1, 10);
}
//------------------------------------------------------------------------------









//TEMP
//------------------------------------------------------------------------------
void MyDB::InsertIntoStates(AnsiString sState, int nPop)
{
    AnsiString sCommand = "insert into states (state, population) values ('" + sState + "', " + IntToStr(nPop) + ")";
    ExecuteCommand(sCommand);
}
//------------------------------------------------------------------------------
