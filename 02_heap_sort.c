#include <stdio.h>
#include <malloc.h>
#define swap(a,b) do {int tmp=a;a=b;b=tmp;} while(NULL) //перестановка элементов местами

static int k=0; //счетчик количества перестановок

//построение бинарного дерева рекурсивно
void heapify(int *arr,int size,int i)
{
    int max=i; //инициализируем максимальный элемент значением корня
    int left=2*i+1; //левый потомок
    int right=2*i+2; //правый потомок

    if (left<size && arr[left]>arr[max]){
        max=left;
    }

    if (right<size && arr[right]>arr[max]){
        max=right;
    }

    //обмен узлов местами
    if (max != i){
        swap(arr[i],arr[max]);
        k++;
        heapify(arr,size,max);
    }
}

//сборка убывающей кучи
int heapSort(int *arr,int size)
{

    for (int i = size/2; i >= 0; i--) {
        heapify(arr,size,i);
    }

    for (int j = size-1; j >= 0; j--) {
        swap(arr[0],arr[j]);
        heapify(arr,j,0);
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

    heapSort(arr,n); //сортируем

    for (i=0;i<n;i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    free(arr);

    return 0;
}

