#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

int combSort(int *arr,unsigned int size)
{
    int k=0; //счетчик количества перестановок
    double fi = 1.247; //золотое сечение
    unsigned int step=size-1;

    int tmp; //временная переменная для обмена элементов местами

    unsigned int i;
    while (step>=1) {
        for (i=0;i+step<size;++i) {
	    k++;
            if (arr[i]>arr[i+step]){
                tmp=arr[i];
                arr[i]=arr[i+step];
                arr[i+step]=tmp;
                k++;
            }
        }
        step/=fi;
    }

    unsigned int j;
    for (i=0;i<size-1;i++) {
        bool flag = false;
        for (j=0;j<size-i-1;j++) {
	    ++k;
            if (arr[j]>arr[j+1]){
                tmp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=tmp;
                flag=true;
                ++k;
            }
        }
        if (!flag) break;
    }
    return k;
}

int main()
{
    unsigned int n;
    scanf("%d",&n);

    int *arr=(int*)malloc(n*sizeof (int));

    //заполняем массив
    unsigned int i;
    for (i=0;i<n;i++) {
        scanf("%d",&arr[i]);
    }

    combSort(arr,n); //сортировка

    //выводим отсортированный массив
    for (i=0;i<n;i++) {
        printf("%d ", arr[i]);
    }

    free(arr);
    printf("\n");


    return 0;
}
