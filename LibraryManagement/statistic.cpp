#include "pch.h"
#include "statistic.h"

time_t CURRENT = time(0);
tm *ltm = localtime(&CURRENT);
DATE CURRENTTIME = { ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year };

int CountBook(LISTBOOK *pHeadBook)
{
	if (pHeadBook == NULL) return 0;
	return pHeadBook->data.NumberOf + CountBook(pHeadBook->pNext);
}

int CountBookBaseOnGenre(LISTBOOK *pHeadBook, char *genre)
{
	if (pHeadBook == NULL) return 0;
	if (strcmp(pHeadBook->data.Genre, genre) == 0)
		return pHeadBook->data.NumberOf + CountBookBaseOnGenre(pHeadBook->pNext, genre);
	else
		return CountBookBaseOnGenre(pHeadBook->pNext, genre);
}

int CountReader(LISTREADER *pHeadReader)
{
	if (pHeadReader == NULL) return 0;
	return CountReader(pHeadReader->pNext) + 1;
}

int CountReaderBaseOnGender(LISTREADER *pHeadReader, int gender)
{
	if (pHeadReader == NULL) return 0;
	if (pHeadReader->data.Gender == gender)
		return CountReaderBaseOnGender(pHeadReader->pNext, gender) + 1;
	else
		return CountReaderBaseOnGender(pHeadReader->pNext, gender);
}

int CountBookInBorrowList(LISTBORROW *pHeadBorrow)
{
	if (pHeadBorrow == NULL) return 0;
	return pHeadBorrow->data.NumberofBook + CountBookInBorrowList(pHeadBorrow->pNext);
}

int CountBookInReturnList(LISTRETURN *pHeadReturn)
{
	if (pHeadReturn == NULL) return 0;
	return pHeadReturn->data.NumberofBook + CountBookInReturnList(pHeadReturn->pNext);
}

int CountBookBeingBorrowed(LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn	)
{
	return CountBookInBorrowList(pHeadBorrow) - CountBookInReturnList(pHeadReturn);
}

LISTREADER *FindOverdueReaderNotReturn(LISTBORROW *BorrowBill, LISTREADER *pHeadReader, LISTRETURN *pHeadReturn)
{
	LISTRETURN *ReturnBill = FindReturnBill(pHeadReturn, BorrowBill->data.BillID);
	if (ReturnBill == NULL)
	{
		if (NumberOfDays(BorrowBill->data.ExpectedReturn, CURRENTTIME) > 0)
		{
			LISTREADER *Reader = FindReaderReaderID(pHeadReader, BorrowBill->data.ReaderID);
			if (Reader == NULL) return NULL;
			return Reader;
		}
	}
	return NULL;
}

LISTREADER *FindOverdueReaderReturned(LISTBORROW *BorrowBill, LISTREADER *pHeadReader, LISTRETURN *pHeadReturn)
{
	LISTRETURN *ReturnBill = FindReturnBill(pHeadReturn, BorrowBill->data.BillID);
	if (ReturnBill != NULL)
	{
		if (NumberOfDays(ReturnBill->data.ExpectedReturn, ReturnBill->data.ActualReturn) > 0)
		{
			LISTREADER *Reader = FindReaderReaderID(pHeadReader, BorrowBill->data.ReaderID);
			if (Reader == NULL) return NULL;
			return Reader;
		}
	}
	return NULL;
}

void OverdueReaderNotReturnYet(LISTBORROW *pHeadBorrow, LISTRETURN *pHeadReturn, LISTREADER *pHeadReader, bool DK) //Neu DK = true : Tim doc gia tre han chua tra sach, DK = false: tim doc gia tre han da tra sach
{
	printf("Danh sach cac doc gia bi tre han: \n");
	
	if (pHeadBorrow == NULL)
	{
		printf("Danh sach muon rong\n");
		return;
	}
	LISTBORROW *BorrowBill = pHeadBorrow;
	do
	{
		LISTREADER *Reader = (DK?FindOverdueReaderNotReturn(BorrowBill, pHeadReader, pHeadReturn): FindOverdueReaderReturned(BorrowBill, pHeadReader, pHeadReturn));
		if (Reader != NULL)
		{
			printf("%s\n", Reader->data.FullName);
		}
		BorrowBill = BorrowBill->pNext;
	} while (BorrowBill != NULL);
}