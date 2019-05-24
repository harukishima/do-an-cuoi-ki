#include "pch.h"
#include "Book.h"

LISTBOOK *CreateNodeBook(BOOK data)
{
	LISTBOOK *p = new LISTBOOK;
	p->data = data;
	p->pNext = NULL;
	return p;
}

void AddFirstBook(LISTBOOK *&pHeadBook, LISTBOOK *p)
{
	if (pHeadBook == NULL)
	{
		pHeadBook = p;
	}
	else
	{
		p->pNext = pHeadBook;
		pHeadBook = p;
	}
}

void AddLastBook(LISTBOOK *&pHeadBook, LISTBOOK *p)
{
	if (pHeadBook == NULL)
	{
		pHeadBook = p;
	}
	else
	{
		AddLastBook(pHeadBook->pNext, p);
	}
}

void ImportBookFile(LISTBOOK *&pHeadBook)
{
	FILE *stream = fopen("book.txt", "r");
	if (stream == NULL) return;
	BOOK tmp;
	char *Num = new char[10];
	char *buff = new char[300];
	while (!feof(stream))
	{
		fgets(buff, 300, stream);
		char *pch;
		pch = strtok(buff, ",");
		strcpy(tmp.ISBN, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.Name, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.Author, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.Publisher, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.Genre, pch);
		pch = strtok(NULL, ",");
		strcpy(tmp.Shelf, pch);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.YearPublish = atoi(Num);
		pch = strtok(NULL, ",");
		strcpy(Num, pch); tmp.NumberOf = atoi(Num);
		LISTBOOK *p = CreateNodeBook(tmp);
		AddLastBook(pHeadBook, p);
	}
	delete[]Num; delete[]buff;
	fclose(stream);
}

void DestroyListBook(LISTBOOK *&pHeadBook)
{
	while (pHeadBook != NULL)
	{
		LISTBOOK *p = pHeadBook;
		pHeadBook = p->pNext;
		delete p;
	}
}

void PrintBook(BOOK data)
{
	printf("ISBN: %s\n", data.ISBN);
	printf("Ten sach: %s\n", data.Name);
	printf("Tac gia: %s\n", data.Author);
	printf("Nha xuat ban: %s\n", data.Publisher);
	printf("The loai: %s\n", data.Genre);
	printf("Nam xuat ban: %d\n", data.YearPublish);
	printf("So luong: %d\n", data.NumberOf);
}

void PrintListBook(LISTBOOK *pHeadBook)
{
	if (pHeadBook != NULL)
	{
		PrintBook(pHeadBook->data);
		PrintListBook(pHeadBook->pNext);
	}
}

void UpdateBook(FILE *stream, LISTBOOK *p)
{
	fprintf(stream, "%s,%s,%s,%s,%s,%s,%d,%d", p->data.ISBN, p->data.Name, p->data.Author, p->data.Publisher, p->data.Genre, p->data.Shelf, p->data.YearPublish, p->data.NumberOf);
}

void UpdateBookFile(LISTBOOK *pHeadBook)
{
	FILE *stream = fopen("book.txt", "w");
	if (stream == NULL) return;
	LISTBOOK *p = pHeadBook;
	while (p != NULL)
	{
		UpdateBook(stream, p);
		if (p->pNext != NULL) fprintf(stream, "\n");
		p = p->pNext;
	}
	fclose(stream);
}

void AddBook(LISTBOOK *&pHeadBook)
{
	BOOK NewBook;
	std::cin.ignore();
	_flushall();
	printf("ISBN: ");
	gets_s(NewBook.ISBN, 20);
	printf("Ten sach: ");
	gets_s(NewBook.Name, 50);
	printf("Tac gia: ");
	gets_s(NewBook.Author, 50);
	printf("Nha xuat ban: ");
	gets_s(NewBook.Publisher, 50);
	printf("The loai: ");
	gets_s(NewBook.Genre, 20);
	printf("Ke sach: ");
	gets_s(NewBook.Shelf, 20);
	printf("Nam xuat ban: ");
	scanf("%d", &NewBook.YearPublish);
	printf("So luong: ");
	scanf("%d", &NewBook.NumberOf);
	LISTBOOK *p = CreateNodeBook(NewBook);
	AddLastBook(pHeadBook, p);
	AddtoEOFBook(p);
}

LISTBOOK *FindBookISBN(LISTBOOK *pHeadBook, char *ISBN)
{
	LISTBOOK *p = pHeadBook;
	while (p != NULL)
	{
		if (strcmp(p->data.ISBN, ISBN) == 0)
		{
			return p;
		}
		else
			p = p->pNext;
	}
	return NULL;
}

void UpdateBookInformation(LISTBOOK *pHeadBook, char *ISBN)
{
	LISTBOOK *p = NULL;
	p = FindBookISBN(pHeadBook, ISBN);
	if (p == NULL) { printf("Khong tim thay sach\n"); return; }
	while (1)
	{
		printf("Chon thong tin can thay doi: ");
		printf("1. ISBN\n");
		printf("2. Ten sach\n");
		printf("3. Tac gia\n");
		printf("4. Nha xuat ban\n");
		printf("5. The loai\n");
		printf("6. Ke sach\n");
		printf("7. Nam xuat ban\n");
		printf("8. So luong\n");
		printf("Chon so khac de huy\n");
		int Command;
		scanf("%d", &Command);
		std::cin.ignore();
		_flushall();
		switch (Command)
		{
		case 1:
			printf("Nhap ISBN moi: ");
			gets_s(p->data.ISBN, 20);
			break;
		case 2:
			printf("Nhap ten sach moi: ");
			gets_s(p->data.Name, 50);
			break;
		case 3:
			printf("Nhap tac gia moi: ");
			gets_s(p->data.Author, 50);
			break;
		case 4:
			printf("Nha xuat ban moi: ");
			gets_s(p->data.Publisher, 20);
			break;
		case 5:
			printf("The loai moi: ");
			gets_s(p->data.Genre, 20);
			break;
		case 6:
			printf("Ke sach moi: ");
			gets_s(p->data.Shelf, 20);
			break;
		case 7:
			printf("Nam xuat ban moi: ");
			scanf("%d", &p->data.YearPublish);
			break;
		case 8:
			printf("So luong sach: ");
			scanf("%d", &p->data.NumberOf);
			break;
		default:
			return;
		}
	}
}

void DeleteFirstBook(LISTBOOK *&pHeadBook)
{
	LISTBOOK *p = pHeadBook;
	if (p->pNext == NULL)
		delete p;
	else
	{
		if (pHeadBook != NULL)
		{
			pHeadBook = p->pNext;
			delete p;
		}
	}
}

void DeleteBookNODE(LISTBOOK *&pHeadBook, char *ISBN)
{
	LISTBOOK *p = pHeadBook;
	if (pHeadBook != NULL)
	{
		if (strcmp(pHeadBook->data.ISBN, ISBN) == 0)
			DeleteFirstBook(pHeadBook);
		else
		{
			while (p != NULL)
			{
				if (p->pNext == NULL) break;
				if (strcmp(p->pNext->data.ISBN, ISBN)==0)
				{
					if (p->pNext->pNext == NULL)
					{
						LISTBOOK *d = p->pNext;
						delete d;
						p->pNext = NULL;
					}
					else
					{
						LISTBOOK *d = p->pNext;
						p->pNext = p->pNext->pNext;
						delete d;
					}
				}
				p = p->pNext;
			}
		}
	}
}

LISTBOOK *FindBookBaseonName(LISTBOOK *pHeadBook, char *Name)
{
	LISTBOOK *p = pHeadBook;
	while (p != NULL)
	{
		if (strcmp(p->data.Name, Name) == 0)
		{
			return p;
		}
		else
			p = p->pNext;
	}
	return NULL;
}

void AddtoEOFBook(LISTBOOK *&p)
{
	char *filename = new char[50]; strcpy(filename, "book.txt");
	if (is_emp(filename) || !is_exist(filename))
	{
		FILE *stream = fopen(filename, "a");
		if (stream == NULL) return;
		UpdateBook(stream, p);
		fclose(stream);
	}
	else
	{
		FILE *stream = fopen(filename, "a");
		if (stream == NULL) return;
		fprintf(stream, "\n");
		UpdateBook(stream, p);
		fclose(stream);
	}
	delete[]filename;
}

