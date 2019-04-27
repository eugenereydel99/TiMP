#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//быстрая сортировка
int quickSort(int *arr,int low,int high,int size)
{
    int k=0;
    if (low < high)
        {
            int left = low, right = high, middle = arr[(left + right) / 2];
            do
            {
                while (arr[left] < middle){
                    left++;
                }

                while (arr[right] > middle){
                    right--;
                }
                k++;
                if (left <= right)
                {
                    int tmp = arr[left];
                    arr[left] = arr[right];
                    arr[right] = tmp;

                    left++;
                    right--;

                    k++;
                }
                k++;

            } while (left <= right);

            k+=quickSort(arr, low, right,size);
            k+=quickSort(arr, left, high,size);
        }

    return k;
}

int main() {

    srand(time(NULL));
    int temp;

    double duration = 0;
    double time = 0;
    int operations = 0;

    double minTime = 1;
    double maxTime = 0;

    int minOperations=15000;
    int maxOperations=0;

    int *arr = (int*)malloc(sizeof(int));
    for (int j = 0; j < 1000; j++) {
        for (int i = 0; i < 100; i++) {
            arr[i] = rand()%1000;
        }
        clock_t start = clock();
        temp = quickSort(arr,0,99,100);
        clock_t stop = clock();
        duration = (double) (stop - start) / CLOCKS_PER_SEC;
        time += duration;
        operations+=temp;
        if (duration > maxTime) {
            maxTime = duration;
            maxOperations=temp;
        }
        if (duration < minTime) {
            minTime = duration;
            minOperations=temp;
        }
        if (temp>maxOperations) maxOperations=temp;
        if (temp<minOperations) minOperations=temp;
    }

    printf("Худшее время: %f\n", maxTime);
    printf("Максимальное число операций: %d\n",maxOperations);
    printf("\n");
    printf("Лучшее время: %f\n", minTime);
    printf("Минимальное число операций: %d\n",minOperations);

    return 0;
}
