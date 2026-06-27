//файл dbmsLib.h
#pragma once
#ifndef _dbmsLib_
#define _dbmsLib_
#include <iostream>
#include <fstream>
#include <strstream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

using namespace std;
namespace dbmsLib
{
//====================класс DBDate======================
  class DBDate
  {	
		friend string DateToStr(DBDate& date);
		friend ostream& operator<<(ostream& out,DBDate& date);
		int day, month, year;
		bool IsLeapYear (int year); //год високосный?
		int GetDaysInMonth(int month,int year);//Количество дней в месяце
		int DaysInCurYear();//Количество дней от начала года до текущей даты
	public:
		DBDate(string date);//формат строки: dd.mm.yyyy
		DBDate(int d,int m,int y);
		DBDate():day(0),month(0),year(0){};//???конструктор по умолчанию
		DBDate(DBDate& dat):day(dat.day),month(dat.month),year(dat.year){}
		int GetDay();
		int GetMonth();
		int GetYear();
		bool operator==(DBDate& date);
		bool operator<(DBDate& date); 
		bool operator>(DBDate& date);
		bool operator<= (DBDate& date);
		bool operator>= (DBDate& date);
		bool operator!= (DBDate& date);
		DBDate& operator+=(int days);//Прибавляет к текущей дате days дней
		DBDate& operator-=(int days);//Вычитает из текущей даты days дней
		int operator-(DBDate& date);	//Количество дней между текущей датой и date
									//Если текущая дата > date, результат < 0.
  };
//DBType-перечисление типов полей таблиц БД:
enum  DBType{ NoType, Int32, Double, String, Date};
//typeNames - массив имен типов. 
//Используется для преобразования имени типа (char*) в объект DBType 
static const char* typeNames[]={
	"NoType",
	"Int32",
	"Double",
	"String",
	"DBDate"
};
//Condition-перечисление условий, по которым могут сравниваються поля таблиц БД:
enum Condition{Undefined,Equal,NotEqual,Less,Greater,LessOrEqual,GreaterOrEqual};
const int LENGTH = 24;//длина имени таблицы и имени столбца.
//ColumnDesc - описание данных в столбце таблицы 
//данные типа string имеют одинаковую длину (length) внутри одного столбца, 
//но в разных столбцах их длина может отличаться
struct ColumnDesc { 
	char colName[LENGTH];//имя столбца
	DBType colType;//тип данных в столбце таблицы
	int length; //максимальное число символов, допустимое 
	//для представления данных в столбце
}; 
struct Strip{//полоса распечатки таблицы
	int nField;//число полей 
	int* fieldWidth;//ширина полей в полосе (массив)
};
  typedef map<string, void*> Row;
  typedef map<string, ColumnDesc> Header;
//-----------------класс DBDate----------------------------
class DBTable{
public:
	DBType GetType(char* columnName);
	const char* TypeName(DBType type);
	virtual ~DBTable(){};//виртуальный деструктор
	virtual Header GetHeader()=0;
	virtual vector<int> IndexOfRecord(void* keyValue,string keyColumnName)=0;
	//по значению ключа определяет 
	//порядковый номер (индекс) строки (записи) в data.
	// keyValue-значение ключа (указатель на string, int или DBDate)
	// keyColumnName-имя ключевого столбца (первичный или вторичный ключ)
	//в таблице может быть несколько записей с одинаковым значением вторичного ключа.
	virtual Row& GetRow(int index)=0;
	virtual Row operator[](int index)=0;
	virtual string valueToString(Row& row,string columnName)=0;
	virtual int GetSize()=0;
	virtual void SetHeader(Header& hdr)=0;
	virtual void ReadDBTable(string fileName)=0;//fileName="..\\"+dbName+"\\"+tableName+".bin"|".txt"											
	virtual void WriteDBTable(string fileName)=0;
	virtual void SetTableName(string tName)=0;
	virtual void SetPrimaryKey(string key)=0;
	virtual string GetTableName()=0;
	virtual string GetPrimaryKey()=0;
	virtual void SetFileName(string path)=0;
	virtual string GetFileName()=0;
	virtual void PrintTable(int screenWidth)=0;
	virtual Row CreateRow()=0;
	virtual void AddRow(Row row,int index)=0;
	virtual DBTable* SelfRows(string colName,Condition cond, void* value)=0;
};

string GetTabNameFromPath(string path);
string ignoreBlanc(const string str);
void* GetValue(string value, string columnName, Header hdr);
void* SetValue(string value, string columnName,Header hdr);
bool comparator(/*TableDataType*/DBType type,void *obj1,Condition condition,void *obj);
int GetLength(ColumnDesc colDesc);

//===============class DBTableTxt=============================
class DBTableTxt:public DBTable{
public:
	Header columnHeaders;
	string tableName;
	string primaryKey;
	vector<Row> data;
	string fileName;
public:
	DBTableTxt(){}
	DBTableTxt(string tabName);/*: DBTable(tabName){}*/
	DBTableTxt(string tabName,Header hdr,string primKey);/*:DBTable(tabName,hdr,primKey){}*/
	~DBTableTxt();//!!!деструктор перегружен,чтобы память,выделенная void*,не утекала
	vector<int> IndexOfRecord(void* keyValue, string keyColumnName);// возвращает вектор из индексов data, у которых в столбце keyColumnName значение совпадает с keyValue
 	string valueToString(Row& row,string columnName);// возвращает из Row значение в виде строки по названию столбца
	void ReadDBTable(string tabName);//tabName=path+tableName
	void ReadTableBin(string tabName);//чтение таблицы из бинарного файла
	void PrintTable(int screenWidth);
	void WriteDBTable(string tabName);//tabName=path+tableName	
	void WriteTableBin(string tabName);//запись таблицы в бинарный файл
	int GetSize();
	Row operator[](int ind);
	void SetFileName(string path);
	void SetTableName(string tName);
	void SetPrimaryKey(string key);
	string GetFileName();
	string GetTableName();
	string GetPrimaryKey(){return primaryKey;}
	Header GetHeader();
	void SetHeader(Header& hdr);
	Row CreateRow();
	Row& GetRow(int index);
	void AddRow(Row row,int index); // заменяет в векторе data элемент с индексом index
	DBTable* SelfRows(string columnName,Condition cond, void* value);
	//Макет распечатки таблицы:
	//screenWidth - ширина экрана (входной параметр)
	//nStrips - число полос в распечатке (выходной параметр)
	//strips[nStrips] - описание полос таблицы: 
	//число столбцов и ширина каждого столбца в полосе (выходной параметр)
	void CreateTableMaket(Strip* &strips,int &nStrips,int screenWidth);
	friend void ReadDBTable1(DBTableTxt& tab,string tabName);//tabName=path+tableName
	friend void WriteDBTable1(DBTableTxt& tab,string tabName);
	friend void PrintTable1(DBTableTxt& tab,int screenWidth);
	//запись таблицы в бинарный файл:
	friend void WriteTableBin1(DBTableTxt& tab, string tabName);
	//чтение таблицы из бинарного файла:
	friend void ReadTableBin1(DBTableTxt& tab,string tabName);
	friend void CreateTableMaket1(Strip* &strips,int &nStrips,int screenWidth);
  };
//=====================Класс DBTableBin=====================================
class DBTableBin: public DBTable{
	char tabName[LENGTH];
	char primaryKey[LENGTH];//имя столбца со значениями первичного ключа
	int nColumn;
	ColumnDesc* header;				
	int nRows; 
	int RowLength();
	int DataBegin();
	int FieldPosition(string colName);//смещение поля colName от начала строки в байтах
	int FieldLength(string colName);//длина поля colName в байтах
	void ResizeData(int deltaRows);
	char** data;		
	int maxRows;//число строк в data с учетом DELTA (при считывании таблицы//????int maxRows()
	//из файла устанавливается равным nRows+DELTA).В файл не записывается
	char fileName[80];//В файл не записывается. Используется в методах для
	//обращения к файлу
	void CreateTableMaket(Strip *&strips,int &nStrips,int screenWidth);
public:
	DBTableBin(){}
	DBTableBin(string tableName);
	DBTableBin(string tableName,Header hdr,string primKey);		
	~DBTableBin(){/*cout<<"~DBTableBin()"<<endl;*/}
	Header GetHeader();
	vector<int> IndexOfRecord(void* keyPtr,string keyName);
	//по значению ключа определяет 
	//порядковый номер (индекс) строки (записи) в data.
	// keyPtr-значение ключа (указатель на string, int или DBDate)
	// keyName-имя ключевого столбца (первичный или вторичный ключ)
	//в таблице может быть несколько записей с одинаковым значением вторичнего ключа.
	int FieldPosInFile(int rowIndex,string columnName);
	Row& GetRow(int index);
	Row operator[](int index);
	string valueToString(Row& row,string columnName);
	int GetSize(){return nRows;}
	void SetHeader(Header& hdr);
	void ReadDBTable(string fileName);//fileName="..\\"+dbName+"\\"+tableName+".bin"											
	void WriteDBTable(string fileName);
	void SetTableName(string tName);
	void SetPrimaryKey(string key);
	string GetTableName(){return tabName;}
	string GetPrimaryKey(){return primaryKey;}
	void SetFileName(string path){
		strcpy_s(fileName,80,(path+"//"+tabName+".bin").c_str());
	} 
	string GetFileName(){return fileName;}
	void PrintTable(int screenWidth);
	Row CreateRow();
	void AddRow(Row row,int index);
	DBTable* SelfRows(string colName,Condition cond, void* value);
};
//==============Класс DBTableSet============================
struct Relation {//описывает связь двух таблиц
	string relationName;
	string parentTable;
	string parentPrimaryKey;
	string childTable;
	string childSecondaryKey;
};
void PrintRow(Row row,DBTable* tab);
//-------------------------класс DBTableSet---------------------
class DBTableSet
{
public:
	string dbName;
	map<string, DBTable*> db;
public: 
	DBTableSet(){};
	DBTableSet(string name);
	string FileType();//".Txt" или ".Bin" 
	int ReadDB();
	void PrintDB(int numcol);
	void WriteDB();
	string GetDBName(){return dbName;}
	DBTable* operator[](string tableName); 
	Relation GetRelation(string relationName);
	Row ParentRow(Relation& relation,Row& childRow);
	DBTable* ChildRows(Relation& relation,Row& parentRow);
};
const int DELTA = 10;//запас в 10 строк для новых записей в таблицу. 
//Если запас израсходован, то для его восстановления нужно увеличить
//на DELTA размер динамического массива char* data[]. 
//const int LENGTH = 24;//длина имени таблицы и имени столбца.

string GetTabNameFromPath(string path);
string ignoreBlanc(const string str);
void* GetValue(string value, string columnName,Header hdr);// записывает в ОП value и возвращает адрес ОП
void* SetValue(string value, string columnName,Header hdr);
bool comparator(/*TableDataType*/DBType type,void *obj1,Condition condition,void *obj);
int GetLength(ColumnDesc colDesc);
}

#endif //конец _dbmsLib_
