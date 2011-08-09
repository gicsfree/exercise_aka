#include "stdio.h"

#if 1
void quicksort(int arr[], int first, int end)
{
    int iloop = first;
    int jloop = end;
    int temp = arr[first];

    while (iloop < jloop)
    {
        while ((iloop < jloop) && (arr[jloop] >= temp))
        {
            jloop--;
        }
        arr[iloop] = arr[jloop];

        while ((iloop < jloop) && (arr[iloop] <= temp))
        {
            iloop++;	
        }	
        arr[jloop] = arr[iloop];
    }
    arr[iloop] = temp;

    if (first < iloop - 1) 
    {
        quicksort(arr, first, iloop - 1);
    }
    if (end > iloop + 1) 
    {		
        quicksort(arr, iloop + 1, end);
    }
}
#endif

void main(void)
{
    int arr[] = {49, 38, 65, 97, 76, 13, 27, 49};
    int len = 8;
    int iloop;

    printf("before sort\n");
    for(iloop = 0; iloop < len; iloop++)
    printf("%d  ", arr[iloop]);
    printf("\n");
	
    quicksort(arr, 0, len - 1);
	
    printf("after sorted\n");
    for(iloop = 0; iloop < len; iloop++)
    printf("%d  ", arr[iloop]);
    printf("\n");
}
