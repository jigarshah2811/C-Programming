#include <stdio.h>
#include <stdlib.h>

int value=10;
int *pvalue = &value;

// This is out_pointer for *pfoo but not foo
void foo(int **pfoo)
{
	pfoo = (int **)&pvalue;
}

int main()
{
	int *null_value;
	int **foo_value;

	// Pointer looses value between fun calls!
	foo(&null_value);
	foo_value = (int **)&pvalue;

	printf("null_value = %d\n", *null_value);
	printf("foo_value = %d\n", **foo_value);

	return 0;
}
