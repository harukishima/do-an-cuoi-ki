#include "pch.h"
#include "Reader.h"

LISTREADER *CreateNodeReader(READER data)
{
	LISTREADER *p = new LISTREADER;
	p->data = data;
	p->pNext = NULL;
	return p;
}

void AddFirstReader(LISTREADER *&pHeadReader, LISTREADER *p)
{
	if (pHeadReader == NULL)
		pHeadReader = p;
	else
	{
		p->pNext = pHeadReader;
		pHeadReader = p;
	}
}

void AddLastReader(LISTREADER *&pHeadReader, LISTREADER *p)
{
	if (pHeadReader == NULL)
		pHeadReader = p;
	else
		AddLastReader(pHeadReader->pNext, p);
}

DATE DateInput()
{
	DATE NewDate;
	scanf("%d", &NewDate.Date); scanf("%d", &NewDate.Month); scanf("%d", &NewDate.Year);
	return NewDate;
}

void DateOutput(DATE day)
{
	printf("%d/%d/%d", day.Date, day.Month, day.Year);
}

void ImportReaderList(LISTREADER *&pHeadReader)
{
	FILE *stream = fopen("reader.txt", "r");
	if (stream == NULL) return;
	READER tmp;
	char *Num = new char[10];
	char *buff = new char[250];
	_flushall(); std::cin.ignore();
	while (!feof(stream))
	{
		fgets(buff, 250, stream);
		char *pch;
		pch = strtok(buff, ",");
		strcpy(tmp.ReaderID, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.FullName, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.ID, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.Email, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.Address, pch);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.Gender = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.BirthDay.Date = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.BirthDay.Month = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.BirthDay.Year = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ValidFrom.Date = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ValidFrom.Month = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ValidFrom.Year = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.GoodThru.Date = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.GoodThru.Month = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.GoodThru.Year = atoi(Num);
		LISTREADER *p = CreateNodeReader(tmp);
		AddLastReader(pHeadReader, p);
	}
	delete[]Num; delete[]buff;
	fclose(stream);
}

void UpdateReader(FILE *stream, READER tmp)
{
	fprintf(stream, "%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", tmp.ReaderID, tmp.FullName, tmp.ID, tmp.Email, tmp.Address, tmp.Gender, tmp.BirthDay.Date, tmp.BirthDay.Month, tmp.BirthDay.Year, tmp.ValidFrom.Date, tmp.ValidFrom.Month, tmp.ValidFrom.Year, tmp.GoodThru.Date, tmp.GoodThru.Month, tmp.GoodThru.Year);
}

void UpdateFileReader(LISTREADER *pHeadReader)
{
	FILE *stream = fopen("reader.txt", "w");
	if (stream == NULL) return;
	LISTREADER *p = pHeadReader;
	while (p != NULL)
	{
		READER tmp = p->data;
		UpdateReader(stream, tmp);
		if (p->pNext != NULL) fprintf(stream, "\n");
		p = p->pNext;
	}
	fclose(stream);
}

void PrintReaderNODE(LISTREADER *p)
{
	READER data = p->data;
	printf("Ma doc gia: %s\n", data.ReaderID);
	printf("Ho va ten: %s\n", data.FullName);
	printf("CMND: %s\n", data.ID);
	printf("Email: %s\n", data.Email);
	printf("Dia chi: %s\n", data.Address);
	printf("Gioi tinh: %s\n", (data.Gender ? "Nam" : "Nu"));
	printf("Ngay sinh: %d/%d/%d\n", data.BirthDay.Date, data.BirthDay.Month, data.BirthDay.Year);
	printf("Ngay lap the: %d/%d/%d\n", data.ValidFrom.Date, data.ValidFrom.Month, data.ValidFrom.Year);
	printf("Ngay het han: %d/%d/%d\n", data.GoodThru.Date, data.GoodThru.Month, data.GoodThru.Year);
	printf("\n");
}

void PrintReaderList(LISTREADER *pHeadReader)
{
	if (pHeadReader != NULL)
	{
		PrintReaderNODE(pHeadReader);
		PrintReaderList(pHeadReader->pNext);
	}
}

LISTREADER *FindReaderReaderID(LISTREADER *pHeadReader, char *ReaderID)
{
	LISTREADER *p = pHeadReader;
	while (p != NULL)
	{
		if (strcmp(p->data.ReaderID, ReaderID) == 0)
		{
			return p;
		}
		else
			p = p->pNext;
	}
	return NULL;
}

void UpdateReaderPreference(LISTREADER *pHeadReader, char *ReaderID)
{
	LISTREADER *p = NULL;
	p = FindReaderReaderID(pHeadReader, ReaderID);
	if (p == NULL) { printf("Khong tim thay doc gia\n"); return; }
	while (1)
	{
		printf("Chon thong tin can thay doi: ");
		printf("1. Ma doc gia\n");
		printf("2. Ho ten\n");
		printf("3. Ngay sinh\n");
		printf("4. CMND\n");
		printf("5. Dia chi\n");
		printf("6. Gioi tinh\n");
		printf("7. Email\n");
		printf("Chon so khac de huy\n");
		int Command;
		scanf("%d", &Command);
		std::cin.ignore();
		_flushall();
		switch (Command)
		{
		case 1:
			printf("Nhap ma moi: ");
			gets_s(p->data.ReaderID, 20);
			break;
		case 2:
			printf("Nhap ho ten moi: ");
			gets_s(p->data.FullName, 50);
			break;
		case 3:
			printf("Nhap ngay sinh moi: ");
			p->data.BirthDay = DateInput();
			break;
		case 4:
			printf("CMND moi: ");
			gets_s(p->data.ID, 20);
			break;
		case 5:
			printf("Dia chi moi");
			gets_s(p->data.Address, 100);
			break;
		case 6:
			printf("Gioi tinh(1 la nam, 0 la nu): ");
			scanf("%d", &p->data.Gender);
			break;
		case 7:
			printf("Email moi: ");
			gets_s(p->data.Email, 50);
			break;
		default:
			return;
			break;
		}
	}
}

void DeleteFirstReader(LISTREADER *&pHeadReader)
{
	LISTREADER *p = pHeadReader;
	if (p->pNext == NULL)
		delete p;
	else
	{
		if (pHeadReader != NULL)
		{
			pHeadReader = p->pNext;
			delete p;
		}
	}
}

void DeleteReaderNODE(LISTREADER *&pHeadReader, char *ReaderID)
{
	LISTREADER *p = pHeadReader;
	if (pHeadReader != NULL)
	{
		if (strcmp(pHeadReader->data.ReaderID, ReaderID)==0)
			DeleteFirstReader(pHeadReader);
		else
		{
			while (p != NULL)
			{
				if (p->pNext == NULL) break;
				if (strcmp(p->pNext->data.ReaderID, ReaderID)==0)
				{
					if (p->pNext->pNext == NULL)
					{
						LISTREADER *d = p->pNext;
						delete d;
						p->pNext = NULL;
					}
					else
					{
						LISTREADER *d = p->pNext;
						p->pNext = p->pNext->pNext;
						delete d;
					}
				}
				p = p->pNext;
			}
		}
	}
}

LISTREADER *FindReaderBaseonID(LISTREADER *pHeadReader, char *ID)
{
	LISTREADER *p = pHeadReader;
	while (p != NULL)
	{
		if (strcmp(p->data.ID, ID)==0)
		{
			return p;
		}
		p = p->pNext;
	}
	return NULL;
}

void AddReader(LISTREADER *&pHeadReader)
{
	READER NewReader;
	std::cin.ignore();
	_flushall();
	printf("Ma doc gia: ");
	gets_s(NewReader.ReaderID, 20);
	printf("Ho va ten: ");
	gets_s(NewReader.FullName, 50);
	printf("CMND: ");
	gets_s(NewReader.ID, 20);
	printf("Email: ");
	gets_s(NewReader.Email, 50);
	printf("Dia chi: ");
	gets_s(NewReader.Address, 100);
	printf("Gioi tinh(1 la nam, 0 la nu): ");
	scanf("%d", &NewReader.Gender);
	printf("Ngay sinh(DD MM YYYY): ");
	NewReader.BirthDay = DateInput();
	printf("Ngay lap the: ");
	NewReader.ValidFrom = DateInput();
	NewReader.GoodThru = NewReader.ValidFrom; NewReader.GoodThru.Year += 4;
	LISTREADER *p = CreateNodeReader(NewReader);
	AddLastReader(pHeadReader, p);
	AddtoEOFReader(p->data);
}

void AddtoEOFReader(READER data)
{
	char *filename = new char[50]; strcpy(filename, "reader.txt");
	if (is_emp(filename) || !is_exist(filename))
	{
		FILE *stream = fopen(filename, "a");
		if (stream == NULL) return;
		UpdateReader(stream, data);
		fclose(stream);
	}
	else
	{
		FILE *stream = fopen(filename, "a");
		if (stream == NULL) return;
		fprintf(stream, "\n");
		UpdateReader(stream, data);
		fclose(stream);
	}
	delete[]filename;
}

LISTREADER *FindReaderBaseOnName(LISTREADER *pHeadReader, char *FullName)
{
	LISTREADER *p = pHeadReader;
	while (p != NULL)
	{
		if (strcmp(p->data.FullName, FullName) == 0)
		{
			return p;
		}
		p = p->pNext;
	}
	return NULL;
}

void FindBookBaseOnReaderName(char *FullName, LISTREADER *pHeadReader, LISTBORROW *pHeadBorrow, LISTBOOK *pHeadBook) //Tim cac sach da muon
{
	LISTREADER *Reader = FindReaderBaseOnName(pHeadReader, FullName);
	LISTBORROW *BorrowBill = pHeadBorrow;
	int count = 0;
	bool first = true;
	while (BorrowBill != NULL)
	{
		LISTBORROW *tmp = FindBorrowBillBaseOnReaderID(BorrowBill, Reader->data.ReaderID);
		if (tmp == NULL && first)
		{
			printf("Doc gia nay chua bao gio muon sach\n");
			return;
		}
		if (tmp == NULL)
			return;
		if (first)
			printf("Cac sach da muon:\n");
		for (int i = 0; i < tmp->data.NumberofBook; i++)
		{
			LISTBOOK *Book = FindBookISBN(pHeadBook, tmp->data.ISBN[i]);
			if (Book != NULL)
			{
				printf("%d %s\n", count + 1, Book->data.Name);
				count++;
			}
		}
		BorrowBill = BorrowBill->pNext;
		first = false;
	}
}

void FindBookBorrowing(char *FullName, LISTREADER *pHeadReader, LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn, LISTBOOK *pHeadBook)
{
	LISTREADER *Reader = FindReaderBaseOnName(pHeadReader, FullName);
	LISTBORROW *BorrowBill = pHeadBorrow;
	int count = 0;
	bool first = true;
	while (BorrowBill != NULL)
	{
		LISTBORROW *tmp = FindBorrowBillBaseOnReaderID(BorrowBill, Reader->data.ReaderID);
		LISTRETURN *Return = FindReturnBill(pHeadReturn, tmp->data.BillID);
		if (tmp == NULL && first)
		{
			printf("Chua muon sach\n");
			return;
		}
		if (Return == NULL)
		{
			if (tmp == NULL)
				return;
			if (first)
				printf("Cac sach dang muon:\n");
			for (int i = 0; i < tmp->data.NumberofBook; i++)
			{
				LISTBOOK *Book = FindBookISBN(pHeadBook, tmp->data.ISBN[i]);
				if (Book != NULL)
				{
					printf("%d %s\n", count + 1, Book->data.Name);
					count++;
				}
			}
		}
		first = false;
		BorrowBill = BorrowBill->pNext;
	}
}