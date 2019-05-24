#include "pch.h"
#include "Bill.h"

LISTBORROW *CreateNodeBorrow(BORROWBILL data)
{
	LISTBORROW *p = new LISTBORROW;
	p->data = data;
	p->pNext = NULL;
	return p;
}

void AddFirstBorrow(LISTBORROW *&pHeadBorrow, LISTBORROW *p)
{
	if (pHeadBorrow == NULL)
	{
		pHeadBorrow = p;
	}
	else
	{
		p->pNext = pHeadBorrow;
		pHeadBorrow = p;
	}
}

void AddLastBorrow(LISTBORROW *&pHeadBorrow, LISTBORROW *p)
{
	if (pHeadBorrow == NULL)
	{
		pHeadBorrow = p;
	}
	else
	{
		AddLastBorrow(pHeadBorrow->pNext, p);
	}
}



void ImportBorrowBill(LISTBORROW *&pHeadBorrow)
{

	FILE *stream = fopen("borrow.txt", "r");
	if (stream == NULL) return;
	char *Num = new char[10];
	char *buff = new char[450];
	char tmpISBN[400];
	while (!feof(stream))
	{
		BORROWBILL tmp;
		fgets(buff, 450, stream);
		char *pch;
		pch = strtok(buff, ",");
		strcpy(tmp.BillID, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.ReaderID, pch);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.BorrowDate.Date = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.BorrowDate.Month = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.BorrowDate.Year = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ExpectedReturn.Date = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ExpectedReturn.Month = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ExpectedReturn.Year = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.NumberofBook = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(tmpISBN, pch);
		if (IdentifyEndLineTok(tmpISBN))
			RemoveLastChar(tmpISBN);
		_flushall();
		char *ISBN;
		ISBN = strtok(tmpISBN, " ");
		strcpy(tmp.ISBN[0], ISBN);
		for (int i = 1; i < tmp.NumberofBook; i++)
		{
			ISBN = strtok(NULL, " ");
			strcpy(tmp.ISBN[i], ISBN);
		}
		LISTBORROW *p = CreateNodeBorrow(tmp);
		AddLastBorrow(pHeadBorrow, p);
	}
	delete[]buff; delete[]Num;
	fclose(stream);
}

int IdentifyEndLineTok(char *string) //Tim ki tu xuong dong
{
	int i = -1;
	do
	{
		i++;
		if (string[i] == '\n')
			return 1;
	} while (string[i] != '\n' && string[i] != '\0');
	return 0;
}

void BorrowBillInput(BORROWBILL &data)
{
	printf("Ma phieu: "); scanf("%s", &data.BillID);
	printf("Ma doc gia: "); scanf("%s", &data.ReaderID);
	printf("So sach muon: "); scanf("%d", &data.NumberofBook);
	printf("ISBN tung sach\n");
	for (int i = 0; i < data.NumberofBook; i++)
	{
		printf("%d: ", i+1); scanf("%s", &data.ISBN[i]);
	}
	printf("Ngay muon: "); data.BorrowDate = DateInput();
	printf("Ngay tra du kien: "); data.ExpectedReturn = DateInput();
}

void WriteBorrowBill(FILE *stream, BORROWBILL data)
{
	fprintf(stream, "%s,%s,%d,%d,%d,%d,%d,%d,%d,", data.BillID, data.ReaderID, data.BorrowDate.Date, data.BorrowDate.Month, data.BorrowDate.Year, data.ExpectedReturn.Date, data.ExpectedReturn.Month, data.ExpectedReturn.Year, data.NumberofBook);
	for (int i = 0; i < data.NumberofBook; i++)
	{
		fprintf(stream, "%s", data.ISBN[i]);
		if (i != data.NumberofBook - 1) fprintf(stream, " ");
	}
}

void AddtoEOFBorrow(BORROWBILL data)
{
	char *filename = new char[50]; strcpy(filename, "borrow.txt");
	if (is_emp(filename) || !is_exist(filename))
	{
		FILE *stream = fopen(filename, "a");
		if (stream == NULL) return;
		WriteBorrowBill(stream, data);
		fclose(stream);
	}
	else
	{
		FILE *stream = fopen(filename, "a");
		if (stream == NULL) return;
		fprintf(stream, "\n");
		WriteBorrowBill(stream, data);
		fclose(stream);
	}
	delete[]filename;
}

void CreateBorrowBill(LISTBORROW *pHeadBorrow, LISTBOOK *pHeadBook, LISTREADER *pHeadReader)
{
	BORROWBILL tmp; BorrowBillInput(tmp);
	if (NumberOfDays(tmp.BorrowDate, tmp.ExpectedReturn) > 7)
	{
		printf("Khong duoc muon qua 7 ngay\n");
		system("pause");
		return;
	}
	LISTREADER *reader = FindReaderReaderID(pHeadReader, tmp.ReaderID);
	if (reader == NULL)
	{
		printf("Khong ton tai doc gia %s\n", tmp.ReaderID);
		system("pause");
		return;
	}
	for (int i = 0; i < tmp.NumberofBook; i++)
	{
		/*char *ISBN = new char[20];
		strcpy(ISBN, tmp.ISBN[i]);*/
		LISTBOOK *book = FindBookISBN(pHeadBook, tmp.ISBN[i]);
		if (book == NULL)
		{
			printf("Khong ton tai sach co ma %s trong thu vien\n", tmp.ISBN[i]);
			/*delete[]ISBN;*/
			system("pause");
			return;
		}
		if (!book->data.NumberOf)
		{
			printf("Sach %s da duoc muon het\n", tmp.ISBN[i]);
			//delete[]ISBN;
			system("pause");
			return;
		}
		book->data.NumberOf--;
	}
	LISTBORROW *p = CreateNodeBorrow(tmp);
	AddLastBorrow(pHeadBorrow, p);
	AddtoEOFBorrow(p->data);
}

int is_emp(char *file_name)
{
	FILE *f;
	int i;
	if (is_exist(file_name))
	{
		f = fopen(file_name, "r");
		fseek(f, 0L, SEEK_END);
		i = ftell(f);
		fclose(f);

		if (i == 0)
			return 1;
	}
	return 0;
}

int is_exist(char *file_name)
{
	FILE *f = fopen(file_name, "r");
	if (f == NULL)
	{
		return 0;
	}
	else
	{
		fclose(f);
		return 1;
	}
}

LISTRETURN *CreateNodeReturn(RETURNBILL data)
{
	LISTRETURN *p = new LISTRETURN;
	p->data = data;
	p->pNext = NULL;
	return p;
}

void AddFirstReturn(LISTRETURN *&pHeadReturn, LISTRETURN *p)
{
	if (pHeadReturn == NULL)
	{
		pHeadReturn = p;
	}
	else
	{
		p->pNext = pHeadReturn;
		pHeadReturn = p;
	}
}

void AddLastReturn(LISTRETURN *&pHeadReturn, LISTRETURN *p)
{
	if (pHeadReturn == NULL)
	{
		pHeadReturn = p;
	}
	else
	{
		AddLastReturn(pHeadReturn->pNext, p);
	}
}

void ImportReturnBill(LISTRETURN *&pHeadReturn)
{

	FILE *stream = fopen("return.txt", "r");
	if (stream == NULL) return;
	char *Num = new char[10];
	char *buff = new char[460];
	char tmpISBN[400];
	while (!feof(stream))
	{
		RETURNBILL tmp;
		fgets(buff, 460, stream);
		char *pch;
		pch = strtok(buff, ",");
		strcpy(tmp.BillID, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.ReaderID, pch);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.BorrowDate.Date = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.BorrowDate.Month = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.BorrowDate.Year = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ExpectedReturn.Date = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ExpectedReturn.Month = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ExpectedReturn.Year = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ActualReturn.Date = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ActualReturn.Month = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.ActualReturn.Year = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.NumberofBook = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(tmpISBN, pch);
		_flushall();
		char *ISBN;
		ISBN = strtok(tmpISBN, " ");
		strcpy(tmp.ISBN[0], ISBN);
		for (int i = 1; i < tmp.NumberofBook; i++)
		{
			ISBN = strtok(NULL, " ");
			strcpy(tmp.ISBN[i], ISBN);
		}
		LISTRETURN *p = CreateNodeReturn(tmp);
		AddLastReturn(pHeadReturn, p);
	}
	delete[]buff; delete[]Num;
	fclose(stream);
}

void WriteReturnBill(FILE *stream, RETURNBILL data)
{
	fprintf(stream, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", data.BillID, data.ReaderID, data.BorrowDate.Date, data.BorrowDate.Month, data.BorrowDate.Year, data.ExpectedReturn.Date, data.ExpectedReturn.Month, data.ExpectedReturn.Year, data.ActualReturn.Date, data.ActualReturn.Month, data.ActualReturn.Year, data.NumberofBook);
	for (int i = 0; i < data.NumberofBook; i++)
	{
		fprintf(stream, "%s", data.ISBN[i]);
		if (i != data.NumberofBook - 1) fprintf(stream, " ");
	}
}

LISTBORROW *FindBorrowBill(LISTBORROW *pHeadBorrow, char *BillID)
{
	LISTBORROW *p = pHeadBorrow;
	while (p->pNext != NULL)
	{
		if (strcmp(p->data.BillID, BillID) == 0)
			return p;
		p = p->pNext;
	}
	return NULL;
}

void PrintBorrowBill(BORROWBILL data)
{
	printf("Ma phieu: %s\n", data.BillID);
	printf("Ma doc gia: %s\n", data.ReaderID);
	printf("Ngay muon: "); DateOutput(data.BorrowDate);
	printf("\nNgay tra du kien: "); DateOutput(data.ExpectedReturn);
	printf("\nSo luong sach: %d\n", data.NumberofBook);
	printf("ISBN: ");
	for (int i = 0; i < data.NumberofBook; i++)
	{
		printf("%s", data.ISBN[i]);
		if (i != data.NumberofBook - 1) printf(", ");
	}
}

void CreateReturnBill(LISTRETURN *&pHeadReturn, LISTBORROW *pHeadBorrow, LISTBOOK *pHeadBook)
{
	printf("Nhap ma phieu: ");
	char *BillID = new char[20];
	scanf("%s", &*BillID);
	LISTBORROW *p = NULL;
	p = FindBorrowBill(pHeadBorrow, BillID);
	if (p == NULL)
	{
		printf("Khong ton tai phieu muon sach tren\n");
		return;
	}
	printf("Tim thay phieu muon sach yeu cau\n");
	PrintBorrowBill(p->data);
	printf("\n");
	RETURNBILL tmp;
	strcpy(tmp.BillID, p->data.BillID);
	strcpy(tmp.ReaderID, p->data.ReaderID);
	tmp.BorrowDate = p->data.BorrowDate;
	tmp.ExpectedReturn = p->data.ExpectedReturn;
	tmp.NumberofBook = p->data.NumberofBook;
	for (int i = 0; i < p->data.NumberofBook; i++)
	{
		strcpy(tmp.ISBN[i], p->data.ISBN[i]);
		LISTBOOK *book = FindBookISBN(pHeadBook, tmp.ISBN[i]);
		if (book == NULL) return;
		book->data.NumberOf++;
	}
	printf("Ngay tra thuc te: "); tmp.ActualReturn = DateInput();
	LISTRETURN *NewBill = CreateNodeReturn(tmp);
	AddLastReturn(pHeadReturn, NewBill);
	AddtoEOFReturn(NewBill->data);
	delete[]BillID;
}

void AddtoEOFReturn(RETURNBILL data)
{
	char *filename = new char[50]; strcpy(filename, "return.txt");
	if (is_emp(filename) || !is_exist(filename))
	{
		FILE *stream = fopen(filename, "a");
		if (stream == NULL) return;
		WriteReturnBill(stream, data);
		fclose(stream);
	}
	else
	{
		FILE *stream = fopen(filename, "a");
		if (stream == NULL) return;
		fprintf(stream, "\n");
		WriteReturnBill(stream, data);
		fclose(stream);
	}
	delete[]filename;
}

int IdentifyEndTok(char *string) //Xac dinh vi tri \0 trong chuoi
{
	int i = 0;
	while (string[i] != '\0')
	{
		i++;
	}
	return i;
}

char *RemoveLastChar(char *string) //Xoa ki tu cuoi cua chuoi
{
	int i = IdentifyEndTok(string);
	string[i - 1] = '\0';
	return string;
}

int DateCal(DATE date)
{
	if (date.Month < 3) {
		date.Year--;
		date.Month += 12;
	}
	return 365 * date.Year + date.Year / 4 - date.Year / 100 + date.Year / 400 + (153 * date.Month - 457) / 5 + date.Date - 306;
}

int NumberOfDays(DATE start, DATE end)
{
	return DateCal(end) - DateCal(start);
}

LISTBORROW *FindBorrowBillBaseOnReaderID(LISTBORROW *pHeadBorrow, char *ReaderID)
{
	LISTBORROW *p = pHeadBorrow;
	while (p != NULL)
	{
		if (strcmp(p->data.ReaderID, ReaderID) == 0)
			return p;
		p = p->pNext;
	}
	return NULL;
}

LISTRETURN *FindReturnBill(LISTRETURN *pHeadReturn, char *BillID)
{
	LISTRETURN *p = pHeadReturn;
	while (p->pNext != NULL)
	{
		if (strcmp(p->data.BillID, BillID) == 0)
			return p;
		p = p->pNext;
	}
	return NULL;
}