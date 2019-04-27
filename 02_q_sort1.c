#include <malloc.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

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

//функция для генерации массива
void genArr(int *arr,int size)
{
    srand(time(0));
    for (int i=0;i<size;i++) {
        arr[i]=rand()%1000;
    }
}


////функция подсчета времени
double getTime(int(*pFunction)(int*,int,int,int),int *arr,int low,int high,int size)
{
    time_t start,end; //таймеры

    start=clock();
    pFunction(arr,low,high,size); //вызов функции сортировки
    end=clock();

    double time = difftime(end,start)/CLOCKS_PER_SEC;

    return time;
}

////функция для возвращения количества операций
int getOperations(int(*pFunction)(int*,int,int,int),int *arr,int low,int high,int size)
{
    return pFunction(arr,low,high,size);
}


void getResult(int(*pFunction)(int*,int,int,int),int low,int high,int size)
{
    int temp;

    double duration = 0;
    double time = 0;
    int operations = 0;

    double minTime = 1;
    double maxTime = 0;

    int minOperations=15000;
    int maxOperations=0;

    int *arr = (int*)malloc(sizeof(int));
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < size; j++) {
            arr[j] = rand()%1000;
        }
        clock_t start = clock();
        temp = pFunction(arr,low,high,size);
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

    printf("\n");

    printf("Худшее время: %f\n", maxTime);
    printf("Максимальное число операций: %d\n",maxOperations);
    printf("\n");
    printf("Лучшее время: %f\n", minTime);
    printf("Минимальное число операций: %d\n",minOperations);

    free(arr);
}

int main()
{
    int k = 0; //переменная для хранения кол-ва операций
    double t=0.0; //переменная для хранения времени

    int mean_k=0;
    double mean_t=0.0;

    int arrayLength[15] = {1,2,3,4,5,10,15,20,25,30,50,75,100,250,500}; //размеры массивов
    double arrayTime[15]; // массив для хранения среднего времени
    int arrayOperations[15]; //массив для хранения среднего количества операций

    double arrayMeanTime[15];
    int arrayMeanOperations[15];

    unsigned int i,j;
    for (i=0;i<15;i++){
        k=0; //обновляем счетчики
        t=0; //
        for (j=0;j<1000;j++) {
            int *arr=(int*)malloc(sizeof(int));
            genArr(arr,arrayLength[i]);
            t+=getTime(quickSort,arr,0,arrayLength[i]-1,arrayLength[i]);
            k+=getOperations(quickSort,arr,0,arrayLength[i]-1,arrayLength[i]);
            free(arr);
        }
        mean_t=t/1000;
        mean_k=k/1000;
        arrayTime[i]=t;
        arrayOperations[i]=k;

        arrayMeanTime[i]=mean_t;
        arrayMeanOperations[i]=mean_k;
    }

    for (j=0;j<15;j++) {
        printf("Время сортировки:");
        printf("%f\n",arrayTime[j]);
        printf("Количество операций:");
        printf("%d\n", arrayOperations[j]);
        printf("Среднее время сортировки:");
        printf("%f\n",arrayMeanTime[j]);
        printf("Среднее количество операций:");
        printf("%d\n", arrayMeanOperations[j]);
        printf("\n");
    }

    return 0;
}
