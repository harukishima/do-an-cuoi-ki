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
LISTUSER *FindUser(LISTUSER *pHeadUser, char CurrentUser[]);
void ChangePassword(LISTUSER *pHeadUser, char *NewPassword, char *CurrentUser);
void UpdateUserFile(LISTUSER *pHeadUser);
void UpdatePreference(LISTUSER *pHeadUser, char *CurrentUser);
void AddUser(LISTUSER *&pHeadUser);

void MainMenu();
void AdminAccountMenu();
void AdminAccountFunction(LISTUSER *&pHeadUser, int Command, char *CurrentUser);
void MainFuntion(LISTUSER *&pHeadUser, int &Status, int &Type, char *CurrentUser, int Command, bool &Program);




#endif //PCH_H
