#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE	10

struct node 
{
    int val;
    struct node* next;
};

int displaylist(struct node* list);
struct node* reverse (struct node* list);

int main()
{
	int i=0;
	struct node *mylist = (struct node*)malloc(LIST_SIZE*sizeof(struct node));
	if(mylist == NULL)
		printf("Malloc failed\n");

	struct node* head = mylist;
	struct node* current=mylist;

	for(i=0; i<LIST_SIZE-1; i++)
	{
		current->val = i;
		current->next = current+sizeof(struct node);

	}
	current->val = i;
	current->next = NULL;

	printf("%d, %p ==>", head->val, head->next);

	displaylist(head);
	current=reverse(mylist);
	displaylist(current);

	free(mylist);

	return 0;
}

int displaylist(struct node* mylist)
{
	struct node *head=mylist;
	
	if(head == NULL)
		return -1;

	while(head != NULL)
	{
		printf("%d, %p ==>", head->val, head->next);
		head=head->next;
	}
	return 0;
}

struct node* reverse (struct node* list)
{
    /* initialization */
    struct node *prev = 0;
    struct node *current = list;

    /* build up the reversed_list like a stack while the original list
       remains */
    while ( current != 0 )
    {
        struct node *saved_next_link = current->next;
        /* the head of the remainder of the original list will be the
           new head of the new list */
        current->next = prev;

        // Inc both prev and current
        prev = current;
        current = saved_next_link; // Like current = current->next
    }

    return current;
}
