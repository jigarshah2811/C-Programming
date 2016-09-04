/*
 * BIT_duplicateNumber.c
 *
 *  Created on: Sep 3, 2016
 *      Author: jigasha2
 */
int getSingle(int a[], int n){
	int num = a[0];
	int result = 0;

	for(int i=1; i<n; i++){
		result = num ^ a[i];
		num = a[i];
	}
	return result;
}
int main()
{
    int arr[] = {3, 3, 2, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("The element with single occurrence is %d ",getSingle(arr, n));
    return 0;
}



