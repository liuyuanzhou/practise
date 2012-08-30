#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GET_ARRAY_LEN(array,len){len = sizeof(array/sizeof(array[0]));}

void quicksort(int* a,int low,int high,int* totalCount)
{
	/*printf("begin sort,low:%d,high:%d\n",low,high);*/
	int key=*(a+low);
	int i = low;
	int j = high;
	int temp;
	int count = 0;
	/*printf("sort sequence:");*/
	while(i<j)
	{
		while((*(a+j) > key) && j > low)
		{
			(*totalCount)++;
			count++;
			/*printf("%d,",*(a+j));*/
			j--;
		}
		if(i < j)
		{
			/*printf("%d,",*(a+j));*/
			temp = *(a+j);
			*(a+j) = *(a+i);
			*(a+i) = temp;
			i++;
			(*totalCount)++;
			count++;
			if(i < j)
			{
				while(*(a+i)< key && i < j)
				{
					(*totalCount)++;
					count++;
					/*printf("%d,",*(a+i));*/
					i++;
				}
				if(i < j)
				{
					temp = *(a+j);
					/*printf("%d,",*(a+i));*/
					*(a+j) = *(a+i);
					*(a+i) = temp;
					j--;
					(*totalCount)++;
					count++;
				}
			}
		}
	}
	/*printf("\n");
	printf("sort count:%d :",count);
	for(temp = 0;temp < 10;temp++)
	{
		printf("%d,",*(a+temp));
	}
	printf("\n");*/
	if(i > low)
		quicksort(a,low,i-1,totalCount);
	if(j < high)
		quicksort(a,j+1,high,totalCount);
}

int main()
{
	int count;
	int totalCount = 0;
	printf("enter in array count:");
	scanf("%d",&count);
	int a[count],i;
	srand(time(NULL));
	printf("array before sort:\n");
	for(i=0;i<count;i++)
	{
		a[i]= rand()%100;
		printf("%d,",a[i]);
	}	
	printf("\n");
	quicksort(&a[0],0,count-1,&totalCount);
	printf("array after sort:\n");
	for(i=0;i<count;i++)
	{
		printf("%d,",a[i]);
	}	
	printf("\n");
	printf("totalCount:%d\n",totalCount);
	return 1;
}
