#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE	10
struct node
{
    int val;
    struct node* next;
};

void print_reverse( struct node* list )
{
    if ( list != 0 )
    {
        print_reverse( list->next );
        printf( "%d\n", list->val );
    }
}

int main()
{
	int i=0;
	struct node mylist[LIST_SIZE];
	struct node *pmylist=mylist;
	struct node *head=mylist;

	for(i=0; i<LIST_SIZE; i++)
	{
		pmylist->val=i;
		pmylist->next=pmylist+sizeof(struct node);
		pmylist = pmylist->next;
	}

	print_reverse(head);
	return 0;
}
