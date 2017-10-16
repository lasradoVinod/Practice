#include <stdio.h>
#include <stdlib.h>

typedef struct __Node
{
	int data;
	struct __Node * next;
}Node;

int addNode(Node ** head, int data)
{
	if (head == NULL)
	{
		if ((*head = (Node *)malloc(sizeof (Node))) == NULL)
			return -1;
		(*head)->data = data;
		(*head)->next = NULL;
		return 0;
	}

	Node * temp = (Node *)malloc(sizeof (Node));

	if (temp == NULL)
		return -1;

	temp->data = data;
	temp->next = *head;
	* head = temp;

	return 0;
}

int displayList(Node * head)
{
	Node * p = head;

	while(p != NULL)
	{
		printf("%d\t",p->data);
		p = p->next;
	}
	printf("\n");
}

int reverseList(Node ** head)
{
	Node *curr, *prev, *next;
	prev = NULL;
	curr = *head;
	next = curr->next;

	while(curr != NULL)
	{
		curr->next = prev;
		prev = curr;
		curr = next;
		if (curr != NULL)
			next = curr->next;
	}
	*head = prev;
	return 0;
}

int main()
{
	Node * head = NULL, *head1 = NULL;

	addNode(&head,1);
	addNode(&head,3);
	addNode(&head,5);
	addNode(&head,7);
	addNode(&head,9);

	addNode(&head1,2);
	addNode(&head1,4);
	addNode(&head1,6);
	addNode(&head1,8);
	addNode(&head1,10);

	Node * head2 = mergeList(head1,head);

	displayList(head2);
}