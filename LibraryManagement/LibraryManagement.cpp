// LibraryManagement.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"


int main()
{
	LISTUSER *pHeadUser = NULL;
	LISTREADER *pHeadReader = NULL;
	LISTBOOK *pHeadBook = NULL;
	LISTBORROW *pHeadBorrow = NULL;
	LISTRETURN *pHeadReturn = NULL;
	char *CurrentUser = new char[50];
	int Status = 0, Type = 0;
	puts("--Quan li thu vien--\nNhan Enter de vao chuong trinh");
	ImportUserFile(pHeadUser);
	ImportReaderList(pHeadReader);
	ImportBookFile(pHeadBook);
	ImportBorrowBill(pHeadBorrow);
	ImportReturnBill(pHeadReturn);
	int Program = 1;
	int Command;
	do
	{
		if (!Status)
			LogIn(pHeadUser, Status, Type, CurrentUser);
		else
		{
			MainMenu();
			scanf("%d",&Command);
			MainFuntion(pHeadUser, pHeadReader, pHeadBook, pHeadBorrow, pHeadReturn, Status, Type, CurrentUser, Command, Program);
		}
	} while (Program);
	UpdateUserFile(pHeadUser);
	DestroyListUser(pHeadUser);
	UpdateFileReader(pHeadReader);
	UpdateBookFile(pHeadBook);
	DestroyListBook(pHeadBook);
	delete[]CurrentUser;
	system("pause");

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
