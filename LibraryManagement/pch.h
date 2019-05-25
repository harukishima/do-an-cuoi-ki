// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#define _CRT_SECURE_NO_WARNINGS
// TODO: add headers that you want to pre-compile here

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>



struct DATE
{
	int Date, Month, Year;
};



struct USER
{
	char Username[50], Pass[20], FullName[50], ID[20], Address[100];
	int Gender; //1 = Man, 2 = Woman
	int Status; //1 = active, 0 = blocked
	int Type; //1 = Manager, 0 = Staff
	DATE BirthDay;
};

struct LISTUSER
{
	USER data;
	LISTUSER *pNext;
};

struct READER
{
	char ReaderID[20], FullName[50], ID[20], Email[50], Address[100]; //ReaderID = Ma doc gia, ID = CMND
	int Gender; //1 = Man, 0 = Woman
	DATE BirthDay, ValidFrom, GoodThru; //Ngay sinh, Ngay lap, Ngay het han
};

struct LISTREADER
{
	READER data;
	LISTREADER *pNext;
};

struct BOOK
{
	char ISBN[20], Name[50], Author[50], Publisher[50], Genre[20], Shelf[20];
	int YearPublish;
	int NumberOf; //Gia sach, So quyen sach
};

struct LISTBOOK
{
	BOOK data;
	LISTBOOK *pNext;
};

struct BORROWBILL
{
	char BillID[20]; //Ma phieu
	char ReaderID[20];
	DATE BorrowDate; DATE ExpectedReturn;
	int NumberofBook;
	char ISBN[20][20]; //So sach duoc muon toi da la 20
};

struct LISTBORROW
{
	BORROWBILL data;
	LISTBORROW *pNext;
};

struct RETURNBILL
{
	char BillID[20]; //Ma phieu
	char ReaderID[20];
	DATE BorrowDate, ExpectedReturn; 
	DATE ActualReturn;
	int NumberofBook;
	char ISBN[20][20];
};

struct LISTRETURN
{
	RETURNBILL data;
	LISTRETURN *pNext;
};

void LogOut(int &Status, int &Type);
LISTUSER *CreatNodeUser(USER data);
void AddFirstUser(LISTUSER *&pHeadUser, LISTUSER *p);
void AddLastUser(LISTUSER *&pHeadUser, LISTUSER *p);
void ImportUserFile(LISTUSER *&pHeadUser);
void LogInQ(LISTUSER *pHeadUser, int &Status, int &Type, char id[], char pass[]);
void LogIn(LISTUSER *pHeadUser, int &Status, int &Type, char *CurrentUser);
void DestroyListUser(LISTUSER *&pHeadUser);
void PrintUser(USER data);
void PrintListUser(LISTUSER *pHeadUser);
LISTUSER *FindUser(LISTUSER *pHeadUser, char *CurrentUser);
void ChangePassword(LISTUSER *pHeadUser, char *NewPassword, char *CurrentUser);
void UpdateUserFile(LISTUSER *pHeadUser);
void UpdatePreference(LISTUSER *pHeadUser, char *CurrentUser);
void AddUser(LISTUSER *&pHeadUser);
void ChangeUserType(LISTUSER *&pHeadUser);
void WriteUser(FILE *stream, USER data);
void AddtoEOFUser(USER data);

void MainMenu();
void AdminAccountMenu();
void AdminAccountFunction(LISTUSER *&pHeadUser, int Command, char *CurrentUser);
void AccountMenu();
void AccountFunction(LISTUSER *&pHeadUser, int Command, char *CurrentUser);
void ReaderConfigMenuStaff();
void ReaderConfigStaff(LISTREADER *&pHeadReader, int Command, LISTBORROW* pHeadBorrow, LISTRETURN* pHeadReturn, LISTBOOK* pHeadBook);
void MainFuntion(LISTUSER *&pHeadUser, LISTREADER *&pHeadReader, LISTBOOK *&pHeadBook, LISTBORROW *&pHeadBorrow, LISTRETURN *&pHeadReturn, int &Status, int &Type, char *CurrentUser, int Command, int &Program);
void ReaderConfigMenuAdmin();
void ReaderConfigAdmin(LISTREADER *&pHeadReader, int Command, LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn, LISTBOOK *pHeadBook);
void BookConfigMenuAdmin();
void BookConfigAdmin(LISTBOOK *&pHeadBook, int Command);
void BookConfigMenuStaff();
void BookConfigStaff(LISTBOOK *&pHeadBook, int Command);
void StatisMenuAdmin();
void StatisFunctionAdmin(LISTREADER *pHeadReader, LISTBOOK *pHeadBook, LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn, int Command);
void StatisMenuStaff();
void StatisFunctionStaff(LISTREADER *pHeadReader, LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn, int Command);

LISTREADER *CreateNodeReader(READER data);
void AddFirstReader(LISTREADER *&pHeadReader, LISTREADER *p);
void AddLastReader(LISTREADER *&pHeadReader, LISTREADER *p);
DATE DateInput();
void ImportReaderList(LISTREADER *&pHeadReader);
void UpdateReader(FILE *stream, READER tmp);
void UpdateFileReader(LISTREADER *pHeadReader);
void PrintReaderNODE(LISTREADER *p);
void PrintReaderList(LISTREADER *pHeadReader);
LISTREADER *FindReaderReaderID(LISTREADER *pHeadReader, char *ReaderID);
void UpdateReaderPreference(LISTREADER *pHeadReader, char *ReaderID);
void DeleteFirstReader(LISTREADER *&pHeadReader);
void DeleteReaderNODE(LISTREADER *&pHeadReader, char *ReaderID);
LISTREADER *FindReaderBaseonID(LISTREADER *pHeadReader, char *ID);
void AddReader(LISTREADER *&pHeadReader);
void AddtoEOFReader(READER data);
void DateOutput(DATE day);
LISTREADER *FindReaderBaseOnName(LISTREADER *pHeadReader, char *FullName);
void FindBookBaseOnReaderName(char *FullName, LISTREADER *pHeadReader, LISTBORROW *pHeadBorrow, LISTBOOK *pHeadBook);
void FindBookBorrowing(char *FullName, LISTREADER *pHeadReader, LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn, LISTBOOK *pHeadBook);


LISTBOOK *CreateNodeBook(BOOK data);
void AddFirstBook(LISTBOOK *&pHeadBook, LISTBOOK *p);
void AddLastBook(LISTBOOK *&pHeadBook, LISTBOOK *p);
void ImportBookFile(LISTBOOK *&pHeadBook);
void DestroyListBook(LISTBOOK *&pHeadBook);
void PrintBook(BOOK data);
void PrintListBook(LISTBOOK *pHeadBook);
void UpdateBookFile(LISTBOOK *pHeadBook);
void AddBook(LISTBOOK *&pHeadBook);
LISTBOOK *FindBookISBN(LISTBOOK *pHeadBook, char *ISBN);
void UpdateBookInformation(LISTBOOK *pHeadBook, char *ISBN);
void DeleteFirstBook(LISTBOOK *&pHeadBook);
void DeleteBookNODE(LISTBOOK *&pHeadBook, char *ISBN);
LISTBOOK *FindBookBaseonName(LISTBOOK *pHeadBook, char *Name);
void UpdateBook(FILE *stream, LISTBOOK *p);
void AddtoEOFBook(LISTBOOK *&p);


LISTBORROW *CreateNodeBorrow(BORROWBILL data);
void AddFirstBorrow(LISTBORROW *&pHeadBorrow, LISTBORROW *p);
void AddLastBorrow(LISTBORROW *&pHeadBorrow, LISTBORROW *p);
void ImportBorrowBill(LISTBORROW *&pHeadBorrow);
void BorrowBillInput(BORROWBILL &data);
void WriteBorrowBill(FILE *stream, BORROWBILL data);
void AddtoEOFBorrow(BORROWBILL data);
void CreateBorrowBill(LISTBORROW *pHeadBorrow, LISTBOOK *pHeadBook, LISTREADER *pHeadReader);
int is_emp(char *file_name);
int is_exist(char *file_name);
LISTRETURN *CreateNodeReturn(RETURNBILL data);
void AddFirstReturn(LISTRETURN *&pHeadReturn, LISTRETURN *p);
void AddLastReturn(LISTRETURN *&pHeadReturn, LISTRETURN *p);
void ImportReturnBill(LISTRETURN *&pHeadReturn);
void WriteReturnBill(FILE *stream, RETURNBILL data);
LISTBORROW *FindBorrowBill(LISTBORROW *pHeadBorrow, char *BillID);
LISTRETURN *FindReturnBill(LISTRETURN *pHeadReturn, char *BillID);
void PrintBorrowBill(BORROWBILL data);
void CreateReturnBill(LISTRETURN *&pHeadReturn, LISTBORROW *pHeadBorrow, LISTBOOK *pHeadBook);
void AddtoEOFReturn(RETURNBILL data);
char *RemoveLastChar(char *string);
int IdentifyEndTok(char *string);
int IdentifyEndLineTok(char *string);
int DateCal(DATE date);
int NumberOfDays(DATE start, DATE end);
LISTBORROW *FindBorrowBillBaseOnReaderID(LISTBORROW *pHeadBorrow, char *ReaderID);


int CountBook(LISTBOOK *pHeadBook);
int CountBookBaseOnGenre(LISTBOOK *pHeadBook, char *genre);
int CountReader(LISTREADER *pHeadReader);
int CountReaderBaseOnGender(LISTREADER *pHeadReader, int gender);
int CountBookInBorrowList(LISTBORROW *pHeadBorrow);
int CountBookInReturnList(LISTRETURN *pHeadReturn);
int CountBookBeingBorrowed(LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn);
LISTREADER *FindOverdueReaderNotReturn(LISTBORROW *BorrowBill, LISTREADER *pHeadReader, LISTRETURN *pHeadReturn);
void OverdueReaderNotReturnYet(LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn, LISTREADER *pHeadReader, bool DK);
LISTREADER *FindOverdueReaderReturned(LISTBORROW *BorrowBill, LISTREADER *pHeadReader, LISTRETURN *pHeadReturn);

#endif //PCH_H
