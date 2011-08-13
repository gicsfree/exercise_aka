#include <stdio.h>

#define LEN	5

int a[LEN] = {5,3,8,7,10};

int partition(int start,int end){

	int pivot = a[start];

	while( start < end){
		while(start < end && a[end] >= pivot)end--;
			a[start] = a[end];
		while(start < end && a[start] <= pivot)start++;
			a[end] = a[start];
	}
	a[start] = pivot;
	return start;
}
void qsort(int start,int end){

	int mid;
	if(start < end){
		
		int mid = partition(start,end);
		qsort(start,mid-1);
		qsort(mid+1,end);
	}
}

int main(){
	printf("%d, %d, %d, %d, %d\n",a[0],a[1],a[2],a[3],a[4]);
	qsort(0,LEN-1);

	printf("%d, %d, %d, %d, %d\n",a[0],a[1],a[2],a[3],a[4]);
}
