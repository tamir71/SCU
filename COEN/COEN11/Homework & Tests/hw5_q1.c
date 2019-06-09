/*
 *************************************************
 *
 *	Ordered Linked Lists
 *
 *************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE    struct node

struct node
{
        int     number;
        NODE    *next;
};


NODE    *head = (NODE *)NULL;


/*
 *************************************************
 *
 *	insert
 *
 *************************************************
 */
void
insert (int number)
{
	NODE	*p, *q;
	NODE	*temp;

	if ((temp = (NODE *) malloc (sizeof (NODE))) == NULL)
	{
		printf ("no memory\n");
		return;
	}

	temp->number = number;

	// find the first node with a greater number
	// the node will be pointed by p
	// q will be pointing to the previous node
	p = q = head;
	while (p !=  NULL)
	{
 		if (p->number > number)
			break;

		q = p;
		p = p->next;
	}

	// insert before p
	if (p == head)		// first, also works if the list was empty
	{
		temp->next = head;
		head = temp;
	}
	else if (p == NULL)	// last
	{
		temp->next = NULL;
		q->next = temp;
	}
	else			// middle
	{
		temp->next = p;
		q->next = temp;
	}

	return;
}


/*
 *************************************************
 *
 *	delete
 *
 *************************************************
 */
void
delete (int number)
{
	NODE	*p;
	NODE	*q;

	// find the node to delete
	p = q = head;
	while (p !=  NULL)
	{
		if (p->number >= number)
			break;

		q = p;
		p = p->next;
	}

	// check if the number was found
	if (p == NULL  ||  p->number != number)
	{
		printf ("%d is not in the list\n", number);
		return;
	}

	// fix the list
	if (p == head)			// first
		head = p->next;
	else				// last or middle
		q->next = p->next;

	// free memory
	free (p);
	return;
}

