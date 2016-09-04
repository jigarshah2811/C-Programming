int binarySearch(int arr[], int low, int high, int val){
	if(low <= high){
		int mid = (low + high) >> 1;
		if(arr[mid] == val) return mid;
		if(arr[mid] > val) binarySearch(arr, 0, mid-1, val);
		else binarySearch(arr, mid+1, high, val);
	}

	return -1;
}

int main(void)
{
   int arr[] = {2, 3, 4, 10, 40};
   int n = sizeof(arr)/ sizeof(arr[0]);
   int x = 10;
   int result = binarySearch(arr, 0, n-1, x);
   (result == -1)? printf("Element is not present in array")
                 : printf("Element is present at index %d", result);
   return 0;
}
