#include "pch.h"
#include "User.h"

void LogOut(int &Status, int &Type)
{
	Status = Type = 0;
	printf("Dang xuat thanh cong\n");
	_flushall(); std::cin.ignore();
}

LISTUSER *CreatNodeUser(USER data)
{
	LISTUSER *p = new LISTUSER;
	p->data = data;
	p->pNext = NULL;
	return p;
}

void AddFirstUser(LISTUSER *&pHeadUser, LISTUSER *p)
{
	if (pHeadUser == NULL)
	{
		pHeadUser = p;
	}
	else
	{
		p->pNext = pHeadUser;
		pHeadUser = p;
	}
}

void AddLastUser(LISTUSER *&pHeadUser, LISTUSER *p)
{
	if (pHeadUser == NULL)
	{
		pHeadUser = p;
	}
	else
	{
		AddLastUser(pHeadUser->pNext, p);
	}
}

void ImportUserFile(LISTUSER *&pHeadUser)
{
	FILE *stream = fopen("user.txt", "r");
	if (stream == NULL) return;
	USER tmp;
	char *Num = new char[10];
	char *buff = new char[240];
	while (!feof(stream))
	{
		fgets(buff, 240, stream);
		char *pch;
		pch = strtok(buff, ",");
		strcpy(tmp.Username, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.Pass, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.FullName, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.ID, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.Address, pch);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); 
		tmp.Gender = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch);
		tmp.Status = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch);
		tmp.Type = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch);
		tmp.BirthDay.Date = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch);
		tmp.BirthDay.Month = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch);
		tmp.BirthDay.Year = atoi(Num);
		LISTUSER *p = CreatNodeUser(tmp);
		AddLastUser(pHeadUser, p);
	}
	delete[]buff; delete[]Num;
	fclose(stream);
}

void LogInQ(LISTUSER *pHeadUser, int &Status, int &Type, char id[], char pass[])
{
	LISTUSER *p = pHeadUser;
	while (p != NULL)
	{
		if (strcmp(id, p->data.Username)==0 && strcmp(pass, p->data.Pass)==0)
		{
			if (!p->data.Status)
				puts("Tai khoan da bi khoa\n");
			else
			{
				Status = 1;
				if (p->data.Type == 2)
					Type = 2;
				else if (p->data.Type)
					Type = 1;
				puts("Dang nhap thanh cong\n");
			}
			return;
		}
		else
			p = p->pNext;
	}
}

void LogIn(LISTUSER *pHeadUser, int &Status, int &Type, char *CurrentUser)
{
	char id[50], pass[50];
	puts("Ten dang nhap: \n");
	gets_s(id, 50);
	puts("Mat khau: \n");
	gets_s(pass, 50);
	LogInQ(pHeadUser, Status, Type, id, pass);
	if (!Status)
	{
		puts("Ten dang nhap hoac mat khau sai\n");
	}
	else
		strcpy(CurrentUser, id);
}

void DestroyListUser(LISTUSER *&pHeadUser)
{
	while (pHeadUser != NULL)
	{
		LISTUSER *p = pHeadUser;
		pHeadUser = p->pNext;
		delete p;
	}
}

void PrintUser(USER data)
{
	printf("Ten dang nhap: %s\n", data.Username);
	printf("Ngay sinh: %d/%d/%d\n", data.BirthDay.Date, data.BirthDay.Month, data.BirthDay.Year);
	printf("Ho va ten: %s\n", data.FullName);
	printf("Dia chi: %s\n", data.Address);
}

void PrintListUser(LISTUSER *pHeadUser)
{
	if (pHeadUser != NULL)
	{
		PrintUser(pHeadUser->data);
		PrintListUser(pHeadUser->pNext);
	}
}

void ChangePassword(LISTUSER *pHeadUser, char *NewPassword, char *CurrentUser)
{
	LISTUSER *p = FindUser(pHeadUser, CurrentUser);
	strcpy(p->data.Pass, NewPassword);
	puts("Doi mat khau thanh cong\n");
}

LISTUSER *FindUser(LISTUSER *pHeadUser, char *CurrentUser)
{
	LISTUSER *p = pHeadUser;
	while (p != NULL)
	{
		if (strcmp(CurrentUser ,p->data.Username)==0)
		{
			return p;
		}
		p = p->pNext;
	}
	return NULL;
}

void UpdateUserFile(LISTUSER *pHeadUser)
{
	FILE *stream = fopen("user.txt", "w");
	if (stream == NULL) return;
	LISTUSER *p = pHeadUser;
	while (p != NULL)
	{
		WriteUser(stream, p->data);
		if (p->pNext != NULL) fprintf(stream, "\n");
		p = p->pNext;
	}
	fclose(stream);
}

void UpdatePreference(LISTUSER *pHeadUser, char *CurrentUser)
{
	LISTUSER *p = NULL;
	p = FindUser(pHeadUser, CurrentUser);
	if (p == NULL) { printf("Khong tim thay nguoi dung\n"); return; }
	puts("Chon thong tin can thay doi: \n");
	puts("1. Ho ten\n");
	puts("2. Ngay sinh\n");
	puts("3. CMND\n");
	puts("4. Dia chi\n");
	puts("5. Gioi tinh\n");
	puts("Chon so khac de huy\n");
	int Info;
	scanf("%d",&Info);
	_flushall();
	std::cin.ignore();
	switch (Info)
	{
	case 1:
		puts("Nhap ho ten moi: ");
		gets_s(p->data.FullName, 50);
		break;
	case 2:
		puts("Nhap ngay: ");
		scanf("%d",&p->data.BirthDay.Date);
		puts("Thang: ");
		scanf("%d",&p->data.BirthDay.Month);
		puts("Nam: ");
		scanf("%d",&p->data.BirthDay.Year);
		break;
	case 3:
		puts("Nhap CMND moi: ");
		scanf("%s",&p->data.ID);
		break;
	case 4:
		puts("Nhap dia chi moi: ");
		gets_s(p->data.Address,100);
		break;
	case 5:
		puts("Gioi tinh(1 la nam, 0 la nu): ");
		scanf("%d",&p->data.Gender);
		break;
	default:
		break;
	}
}

void AddUser(LISTUSER *&pHeadUser) //Tao nguoi dung moi
{
	USER NewUser;
	/*cout << "Tao nguoi dung moi" << endl;
	cout << "Ten dang nhap: "; cin >> NewUser.Username;
	cout << "Mat khau: "; cin >> NewUser.Pass;
	cout << "Ho va ten: "; getline(cin, NewUser.FullName);
	cout << "Gioi tinh (1 la nam, 0 la nu): "; cin >> NewUser.Gender;
	cout << "Ngay sinh (DD/MM/YYYY): "; cin >> NewUser.BirthDay.Date; cin >> NewUser.BirthDay.Month; cin >> NewUser.BirthDay.Year;
	cout << "CMND: "; cin >> NewUser.ID;
	cout << "Dia chi: "; getline(cin, NewUser.Address);
	cout << "Trang thai (1 la active, 0 la blocked): "; cin >> NewUser.Status;
	cout << "Loai nguoi dung (1 la quan li, 0 la nhan vien): "; cin >> NewUser.Type;*/
	_flushall();
	std::cin.ignore();
	printf("Tao nguoi dung moi\n");
	printf("Ten dang nhap: "); gets_s(NewUser.Username,50);
	printf("Mat khau: "); gets_s(NewUser.Pass,20);
	printf("Ho va ten: "); gets_s(NewUser.FullName,50);
	printf("CMND: "); gets_s(NewUser.ID,20);
	printf("Dia chi: "); gets_s(NewUser.Address,100);
	printf("Ngay sinh (DD/MM/YYYY): "); scanf("%d",&NewUser.BirthDay.Date); scanf("%d",&NewUser.BirthDay.Month); scanf("%d",&NewUser.BirthDay.Year);
	printf("Gioi tinh (1 la nam, 0 la nu): "); scanf("%d",&NewUser.Gender);
	printf("Trang thai (1 la active, 0 la blocked): "); scanf("%d",&NewUser.Status);
	NewUser.Type = 0; //Nguoi dung moi tao mac dinh la nhan vien
	LISTUSER *p = CreatNodeUser(NewUser);
	AddLastUser(pHeadUser, p);
	printf("Tao nguoi dung thanh cong\n");
	AddtoEOFUser(p->data);
}

void ChangeUserType(LISTUSER *&pHeadUser) //Phan quyen nguoi dung (admin only)
{
	char *username = new char[50];
	_flushall();
	printf("Nhap ten dang nhap cua nguoi dung can thay doi: ");
	gets_s(username,50);
	LISTUSER *p = FindUser(pHeadUser, username);
	printf("Phan quyen nguoi dung (1 la quan li, 0 la nhan vien): ");
	scanf("%d", &p->data.Type);
	printf("Phan quyen thanh cong\n");
}


void WriteUser(FILE *stream, USER data)
{
	fprintf(stream, "%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d", data.Username, data.Pass, data.FullName, data.ID, data.Address, data.Gender, data.Status, data.Type, data.BirthDay.Date, data.BirthDay.Month, data.BirthDay.Year);
}

void AddtoEOFUser(USER data)
{
	char *filename = new char[50]; strcpy(filename, "user.txt");
	if (is_emp(filename) || !is_exist(filename))
	{
		FILE *stream = fopen(filename, "a");
		if (stream == NULL) return;
		WriteUser(stream, data);
		fclose(stream);
	}
	else
	{
		FILE *stream = fopen(filename, "a");
		if (stream == NULL) return;
		fprintf(stream, "\n");
		WriteUser(stream, data);
		fclose(stream);
	}
	delete[]filename;
}