// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed

#include "pch.h"

// In general, ignore this file, but keep it around if you are using pre-compiled headers.


void MainMenu()
{
	printf("MAIN MENU\n");
	printf("1. Quan li tai khoan\n");
	printf("2. Quan li doc gia\n");
	printf("3. Quan li sach\n");
	printf("4. Lap phieu muon sach\n");
	printf("5. Lap phieu tra sach\n");
	printf("6. Thong ke\n");
	printf("7. Dang xuat\n");
	printf("Chon phim khac de thoat\n");
	printf("Nhap: ");
}

void AdminAccountMenu()
{
	printf("QUAN LI TAI KHOAN\n");
	printf("1. Doi mat khau\n");
	printf("2. Cap nhat thong tin ca nhan\n");
	printf("3. Tao nguoi dung\n");
	printf("4. Phan quyen nguoi dung\n");
	printf("Chon phim khac de tro ve\n");
	printf("Nhap: ");
}

void AdminAccountFunction(LISTUSER *&pHeadUser, int Command, char *CurrentUser)
{
	char *NewPassword = new char[20];
	switch (Command)
	{
	case 1:
		printf("Nhap mat khau moi: ");
		scanf("%s", NewPassword);
		ChangePassword(pHeadUser, NewPassword, CurrentUser);
		break;
	case 2:
		UpdatePreference(pHeadUser, CurrentUser);
		break;
	case 3:
		AddUser(pHeadUser);
		break;
	case 4:
		ChangeUserType(pHeadUser);
		break;
	default:
		break;
	}
}

void AccountMenu()
{
	printf("QUAN LI TAI KHOAN\n");
	printf("1. Doi mat khau\n");
	printf("2. Cap nhat thong tin ca nhan\n");
	printf("Chon phim khac de tro ve\n");
	printf("Nhap: ");
}

void AccountFunction(LISTUSER *&pHeadUser, int Command, char *CurrentUser)
{
	char *NewPassword = new char[20];
	switch (Command)
	{
	case 1:
		printf("Nhap mat khau moi: ");
		scanf("%s", NewPassword);
		ChangePassword(pHeadUser, NewPassword, CurrentUser);
		break;
	case 2:
		UpdatePreference(pHeadUser, CurrentUser);
		break;
	default:
		break;
	}
}

void MainFuntion(LISTUSER *&pHeadUser, LISTREADER *&pHeadReader, LISTBOOK *&pHeadBook, LISTBORROW *&pHeadBorrow, LISTRETURN *&pHeadReturn, int &Status, int &Type, char *CurrentUser, int Command, int &Program)
{
	switch (Command)
	{
	case 1:
		if (Type == 2)
		{
			AdminAccountMenu();
			scanf("%d", &Command);
			system("cls");
			AdminAccountFunction(pHeadUser, Command, CurrentUser);
		}
		else
		{
			AccountMenu();
			scanf("%d", &Command);
			system("cls");
			AccountFunction(pHeadUser, Command, CurrentUser);
		}
		break;
	case 2:
		if (Type)
		{
			ReaderConfigMenuAdmin();
			scanf("%d", &Command);
			system("cls");
			ReaderConfigAdmin(pHeadReader, Command, pHeadBorrow, pHeadReturn, pHeadBook);
		}
		else
		{
			ReaderConfigMenuStaff();
			scanf("%d", &Command);
			system("cls");
			ReaderConfigStaff(pHeadReader, Command, pHeadBorrow, pHeadReturn, pHeadBook);
		}
		break;
	case 3:
		if (Type)
		{
			BookConfigMenuAdmin();
			scanf("%d", &Command);
			system("cls");
			BookConfigAdmin(pHeadBook, Command);
		}
		else
		{
			BookConfigMenuStaff();
			scanf("%d", &Command);
			system("cls");
			BookConfigStaff(pHeadBook, Command);
		}
		break;
	case 4:
		CreateBorrowBill(pHeadBorrow, pHeadBook, pHeadReader);
		break;
	case 5:
		CreateReturnBill(pHeadReturn, pHeadBorrow, pHeadBook);
		break;
	case 6:
		if (Type)
		{
			StatisMenuAdmin();
			scanf("%d", &Command);
			system("cls");
			StatisFunctionAdmin(pHeadReader, pHeadBook, pHeadBorrow, pHeadReturn, Command);
		}
		else
		{
			StatisMenuStaff();
			scanf("%d", &Command);
			system("cls");
			StatisFunctionStaff(pHeadReader, pHeadBorrow, pHeadReturn, Command);
		}
		break;
	case 7:
		LogOut(Status, Type);
		break;
	default:
		Program = 0;
		printf("Da thoat thanh cong\n");
		break;
	}
}



void ReaderConfigAdmin(LISTREADER *&pHeadReader, int Command, LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn, LISTBOOK *pHeadBook)
{
	char *tmp = new char[50];
	LISTREADER *p;
	std::cin.ignore();
	switch (Command)
	{
	case 1:
		PrintReaderList(pHeadReader);
		break;
	case 2:
		AddReader(pHeadReader);
		break;
	case 3:
		printf("Nhap ma doc gia: "); scanf("%s", &*tmp);
		UpdateReaderPreference(pHeadReader, tmp);
		break;
	case 4:
		printf("Nhap ma doc gia: "); scanf("%s", &*tmp);
		DeleteReaderNODE(pHeadReader, tmp);
		break;
	case 5:
		printf("Nhap CMND: "); scanf("%s", &*tmp);
		p = FindReaderBaseonID(pHeadReader, tmp);
		PrintReaderNODE(p);
		break;
	case 6:
		printf("Nhap ten doc gia: "); gets_s(tmp, 50);
		FindBookBaseOnReaderName(tmp, pHeadReader, pHeadBorrow, pHeadBook);
		break;
	case 7:
		printf("Nhap ten doc gia: "); gets_s(tmp, 50);
		FindBookBorrowing(tmp, pHeadReader, pHeadBorrow, pHeadReturn, pHeadBook);
		break;
	default:
		break;
	}
	delete[]tmp;
}

void ReaderConfigMenuAdmin()
{
	printf("QUAN LI DOC GIA\n");
	printf("1. Xem danh sach doc gia\n");
	printf("2. Them doc gia\n");
	printf("3. Chinh sua thong tin doc gia\n");
	printf("4. Xoa thong tin doc gia\n");
	printf("5. Tim kiem doc gia theo CMND\n");
	printf("6. Tim kiem sach ma doc gia da muon\n");
	printf("7. Tim kiem sach doc gia dang muon\n");
	printf("Nhap so khac de thoat\n");
}

void ReaderConfigMenuStaff()
{
	printf("QUAN LI DOC GIA\n");
	printf("1. Xem danh sach doc gia\n");
	printf("2. Them doc gia\n");
	printf("3. Chinh sua thong tin doc gia\n");
	printf("4. Tim kiem doc gia theo CMND\n");
	printf("5. Tim kiem sach ma doc gia da muon\n");
	printf("6. Tim kiem sach doc gia dang muon\n");
	printf("Nhap so khac de thoat\n");
}

void ReaderConfigStaff(LISTREADER *&pHeadReader, int Command, LISTBORROW* pHeadBorrow, LISTRETURN* pHeadReturn, LISTBOOK* pHeadBook)
{
	char *tmp = new char[50];
	LISTREADER *p;
	switch (Command)
	{
	case 1:
		PrintReaderList(pHeadReader);
		break;
	case 2:
		AddReader(pHeadReader);
		break;
	case 3:
		printf("Nhap ma doc gia: "); scanf("%s", &*tmp);
		UpdateReaderPreference(pHeadReader, tmp);
		break;
	case 4:
		printf("Nhap CMND: "); scanf("%s", &*tmp);
		p = FindReaderBaseonID(pHeadReader, tmp);
		PrintReaderNODE(p);
		break;
	case 5:
		printf("Nhap ten doc gia: "); scanf("%s", &*tmp);
		FindBookBaseOnReaderName(tmp, pHeadReader, pHeadBorrow, pHeadBook);
		break;
	case 6:
		printf("Nhap ten doc gia: "); scanf("%s", &*tmp);
		FindBookBorrowing(tmp, pHeadReader, pHeadBorrow, pHeadReturn, pHeadBook);
		break;
	default:
		break;
	}
	delete[]tmp;
}

void BookConfigMenuAdmin()
{
	printf("QUAN LI SACH\n");
	printf("1. Xem danh sach cac sach\n");
	printf("2. Them sach\n");
	printf("3. Chinh sua thong tin sach\n");
	printf("4. Xoa thong tin sach\n");
	printf("5. Tim kiem sach theo ISBN\n");
	printf("6. Tim kiem sach theo ten sach\n");
	printf("Nhap so khac de thoat\n");
}

void BookConfigMenuStaff()
{
	printf("QUAN LI SACH\n");
	printf("1. Tim kiem sach theo ISBN\n");
	printf("2. Tim kiem sach theo ten sach\n");
	printf("Nhap so khac de thoat\n");
}

void BookConfigAdmin(LISTBOOK *&pHeadBook, int Command)
{
	char *tmp = new char[50];
	LISTBOOK *p = NULL;
	_flushall();
	std::cin.ignore();
	switch (Command)
	{
	case 1:
		PrintListBook(pHeadBook);
		break;
	case 2:
		AddBook(pHeadBook);
		break;
	case 3:
		printf("Nhap ISBN: "); scanf("%s", &*tmp);
		UpdateBookInformation(pHeadBook, tmp);
		break;
	case 4:
		printf("Nhap ISBN: "); scanf("%s", &*tmp);
		DeleteBookNODE(pHeadBook, tmp);
		break;
	case 5:
		printf("Nhap ISBN: "); scanf("%s", &*tmp);
		p = FindBookISBN(pHeadBook, tmp);
		PrintBook(p->data);
		break;
	case 6:
		printf("Nhap ten sach: "); gets_s(tmp, 50);
		p = FindBookBaseonName(pHeadBook, tmp);
		PrintBook(p->data);
		break;
	default:
		break;
	}
	delete[]tmp;
}

void BookConfigStaff(LISTBOOK *&pHeadBook, int Command)
{
	char *tmp = new char[50];
	LISTBOOK *p = NULL;
	_flushall();
	std::cin.ignore();
	switch (Command)
	{
	case 1:
		printf("Nhap ISBN: "); scanf("%s", &*tmp);
		p = FindBookISBN(pHeadBook, tmp);
		PrintBook(p->data);
		break;
	case 2:
		printf("Nhap ten sach: "); gets_s(tmp, 50);
		p = FindBookBaseonName(pHeadBook, tmp);
		PrintBook(p->data);
		break;
	default:
		break;
	}
	delete[]tmp;
}

void StatisMenuAdmin()
{
	printf("THONG KE\n");
	printf("1. Thong ke so luong sach trong thu vien\n");
	printf("2. Thong ke so luong sach theo the loai\n");
	printf("3. Thong ke so luong doc gia\n");
	printf("4. Thong ke so luong doc gia theo gioi tinh\n");
	printf("5. Thong ke so luong sach dang duoc muon\n");
	printf("6. Thong ke danh sach doc gia bi tre han chua tra sach\n");
	printf("7. Thong ke danh sach doc gia bi tre han da tra sach\n");
	printf("Chon so khac de tro ve\n");
	printf("Nhap lenh: ");
}

void StatisFunctionAdmin(LISTREADER *pHeadReader, LISTBOOK *pHeadBook, LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn, int Command)
{
	_flushall(); std::cin.ignore();
	int tmp;
	char *tmpstring = new char[20];
	switch (Command)
	{
	case 1:
		tmp = CountBook(pHeadBook);
		printf("So luong sach trong thu vien la: %d", tmp);
		break;
	case 2:
		printf("The loai: ");
		gets_s(tmpstring, 20);
		tmp = CountBookBaseOnGenre(pHeadBook, tmpstring);
		printf("So luong sach thuoc the loai %s: %d", tmpstring, tmp);
		break;
	case 3:
		tmp = CountReader(pHeadReader);
		printf("So luong doc gia: %d", tmp);
		break;
	case 4:
		printf("Gioi tinh(1 la nam, 0 la nu): ");
		scanf("%d", &tmp);
		tmp = CountReaderBaseOnGender(pHeadReader, tmp);
		printf("So luong doc gia: %d", tmp);
		break;
	case 5:
		tmp = CountBookBeingBorrowed(pHeadBorrow, pHeadReturn);
		printf("So luong sach dang duoc muon: %d", tmp);
		break;
	case 6:
		OverdueReaderNotReturnYet(pHeadBorrow, pHeadReturn, pHeadReader, true);
		break;
	case 7:
		OverdueReaderNotReturnYet(pHeadBorrow, pHeadReturn, pHeadReader, false);
		break;
	default:
		break;
	}
	printf("\n");
	delete[]tmpstring;
}

void StatisMenuStaff()
{
	printf("THONG KE\n");
	printf("1. Thong ke so luong sach dang duoc muon\n");
	printf("2. Thong ke danh sach doc gia bi tre han chua tra sach\n");
	printf("3. Thong ke danh sach doc gia bi tre han da tra sach\n");
	printf("Chon so khac de tro ve\n");
	printf("Nhap lenh: ");
}

void StatisFunctionStaff(LISTREADER *pHeadReader, LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn, int Command)
{
	_flushall(); std::cin.ignore();
	int tmp;
	char *tmpstring = new char[20];
	switch (Command)
	{
	case 1:
		tmp = CountBookBeingBorrowed(pHeadBorrow, pHeadReturn);
		printf("So luong sach dang duoc muon: %d", tmp);
		break;
	case 2:
		OverdueReaderNotReturnYet(pHeadBorrow, pHeadReturn, pHeadReader, true);
		break;
	case 3:
		OverdueReaderNotReturnYet(pHeadBorrow, pHeadReturn, pHeadReader, false);
		break;
	default:
		break;
	}
	printf("\n");
	delete[]tmpstring;
}