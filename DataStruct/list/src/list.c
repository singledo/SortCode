#include "list.h"

tListNode* NewNode(u32 data)
{
	tListNode *new = (tListNode*)malloc(sizeof(tListNode));
	if (new == NULL)
	{
		DEBUG("mallc failed");
		return NULL;
	}
	new->data = data;
	new->next = NULL;
	return new;
}


void ListInsert(tListNode *head, u4 data )
{
	tListNode *new = NewNode(data);
	tListNode *pHead = head;
	if (new == NULL)
	{
		return;
	}
	while (pHead->next != NULL)
	{
		pHead = pHead->next;
	}
	pHead->next = new;
}

void ListTraver(tListNode *head)
{
	tListNode *pHead = head->next;
	while (pHead != NULL)
	{
		printf ("[%02d] ", pHead->data);
		pHead = pHead->next;
	}
	printf ("\r\n");
}

u4 ListLen(tListNode *head)
{
	tListNode *pHead = head->next;
	u4 len = 0;

	while (pHead != NULL)
	{
		len += 1;
	}
	return len;
}

tListNode* ListObtainHead(tListNode *head)
{
	tListNode *obtain = head->next;
	if (obtain != NULL)
	{
		head->next = obtain->next;
	}
	return obtain;
}

tListNode* ListObtainTail(tListNode *head)
{
	tListNode *preObtain = head->next;
	if (preObtain == NULL)
	{
		return NULL;
	}
	tListNode *obtain = head->next;

	while (obtain!= NULL)
	{
		head = obtain->next;
	}
	return obtain;

}





