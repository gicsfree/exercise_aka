void bubble_sort(int *array, int len)
{
	int i;
	int j;
	int tmp;

	for (i=1; i<len; i++){
		for (j=len-1; j>=i; j--){
			if (array[j] > array[j-1]){
				tmp = array[j];
				array[j] = array[j-1];
				array[j-1] = tmp;
			}
		}	
	}
}
