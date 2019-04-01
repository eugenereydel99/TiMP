#include <stdio.h>
#include <malloc.h>

int ShellSort(int *arr, int n)
{
    int k = 0; //счетчик количества сравнений
    int step,tmp;

    int i,j;
    for (step = n / 2; step > 0; step /= 2){
        for (i = step; i < n; i++)
        {
            tmp = arr[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < arr[j - step]){
                    arr[j] = arr[j - step];
                    k++;
                }
                else break;
            }
            arr[j] = tmp;
        }
    }
    return k;

}

int main()
{

    int n;
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    //заполняем массив
    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }

    ShellSort(arr, n); //сортировка

    //выводим отсортированный массив
    for (int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }

    free(arr);
    printf("\n");

    return 0;
}
