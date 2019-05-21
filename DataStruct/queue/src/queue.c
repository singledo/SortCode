#include "queue.h"

Queue * QueCreateNode(DataType data)
{
	Queue *pNewQueNode = (Queue *)malloc(sizeof(Queue));
	if (pNewQueNode == NULL)
	{
		return NULL;
	}
	pNewQueNode->next = pNewQueNode->last = NULL;
	pNewQueNode->data = data;
}

bool QueueInsertTail(Queue *queue, DataType data)
{
	QueueNode *pNodeTemp = queue;
	/*this the head node*/
	if (pNodeTemp->next == NULL && pNodeTemp->last == NULL)
	{
		queue->data = data;
		return true;
	}

	/*create new node for queue */
	QueueNode *pNewNode = QueCreateNode(data);
	if (pNewNode == NULL)
	{
		return false;
	}
	/*get the tail of the queue */
	while (pNodeTemp->next != NULL)
	{
		pNodeTemp = pNodeTemp->next;
	}
	pNodeTemp->next = pNewNode;
	pNewNode->last  = pNodeTemp;
	return true;
}

Queue * QueueDeleteHead(Queue *queue, DataType *data)
{
	if (queue == NULL)
	{
		return NULL;
	}
	Queue *pNodeTemp = queue->next;
	*data = queue->data;
	if (pNodeTemp != NULL)
	{
		pNodeTemp->last = NULL;
	}
	
	return pNodeTemp;
}

Queue * QueueHeadCreate(void)
{
	Queue *head = QueCreateNode(0);
	return head;
}

void QueueHeadFree(Queue *head)
{

}


