#include <stdio.h>
#include <malloc.h>

static int k=0; //счетчик количества перестановок

int quickSort(int *arr,int low,int high,int size)
{
    if (low < high)
        {
            int left = low, right = high, middle = arr[(left + right) / 2];
            do
            {
                while (arr[left] < middle) left++;
                while (arr[right] > middle) right--;
                if (left <= right)
                {
                    int tmp = arr[left];
                    arr[left] = arr[right];
                    arr[right] = tmp;

                    left++;
                    right--;

                    k++;
                }
            } while (left <= right);
            quickSort(arr, low, right,size);
            quickSort(arr, left, high,size);
        }

    return k;
}


int main()
{

    int n;
    scanf("%d",&n);

    int *arr=(int*)malloc(n*sizeof (int));

    int i;
    for (i=0;i<n;i++) {
        scanf("%d",&arr[i]);
    }

    quickSort(arr,0,n-1,n); //сортировка

    for (i=0;i<n;i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    free(arr);

    return 0;
}

