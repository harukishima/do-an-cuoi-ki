#include "pch.h"
#include "statistic.h"


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