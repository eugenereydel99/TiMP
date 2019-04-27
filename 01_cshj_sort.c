#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define swap(a,b) do {int tmp=a;a=b;b=tmp;} while(NULL) //перестановка элементов местами


//сортировка расческой
int combSort(int *arr,int size)
{

    int k=0;

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


//сортировка Шелла
int ShellSort(int *arr, int n)
{
    int k = 0;

    int step,tmp;

    int i,j;
    for (step = n / 2; step > 0; step /= 2){
        for (i = step; i < n; i++)
        {
            k++;
            tmp = arr[i];
            for (j = i; j >= step; j -= step)
            {
                k++;
                if (tmp < arr[j - step]){
                    arr[j] = arr[j - step];
                    k++;
                }
                else break;
            }
            arr[j] = tmp;
            k++;
        }
    }
    return k;

}


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


//-----------Сортировка кучей-----------//

//построение бинарного дерева
int heapify(int *arr,int size,int i)
{
    int k=0;
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
        k++;
        swap(arr[i],arr[max]);
        k+=heapify(arr,size,max);
    }
    return k;
}


//сборка убывающей кучи
int heapSort(int *arr,int size)
{
    int k=0;
    for (int i = size/2; i >= 0; i--) {
        k+=heapify(arr,size,i);
    }

    for (int j = size-1; j >= 0; j--) {
        k++;
        swap(arr[0],arr[j]);
        k+=heapify(arr,j,0);
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


//функция подсчета времени
double getTime(int(*pFunction)(int*,int),int *arr,int size)
{
    time_t start,end; //таймеры

    start=clock();
    pFunction(arr,size); //вызов функции сортировки
    end=clock();

    double time = difftime(end,start)/CLOCKS_PER_SEC;

    return time;
}

//функция для возвращения количества операций
double getOperations(int(*pFunction)(int*,int),int *arr,int size)
{
    return pFunction(arr,size);
}

//получение общего результата работы программы
void getResult1(int(*pFunction)(int*,int),int *arrayLength,double *arrayTime,int *arrayOperations, double *arrayMeanTime,int *arrayMeanOperations,double t,int k,double mean_t,int mean_k)
{
    unsigned int i,j;
    for (i=0;i<15;i++){
        k=0; //обновляем счетчики
        t=0; //
        for (j=0;j<1000;j++) {
            int *arr=(int*)malloc(sizeof(int));
            genArr(arr,arrayLength[i]);
            t+=getTime(pFunction,arr,arrayLength[i]);
            k+=getOperations(pFunction,arr,arrayLength[i]);
            free(arr);
        }
        arrayTime[i]=t;
        arrayOperations[i]=k;

        mean_t=t/1000; //получаем среднее количество времени и операций*
        mean_k=k/1000; //*
        arrayMeanTime[i]=mean_t; //записываем среднее время для каждой длины в отдельный массив
        arrayMeanOperations[i]=mean_k; //то же самое проделываем со средним количеством операций
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
}

//получение результата для массива конкретного размера
void getResult2(int(*pFunction)(int*,int),int size)
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
        temp = pFunction(arr,size);
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
    int k = 0; //кол-во операций
    double t = 0.0; //время

    int mean_k=0; //среднее кол-во операций
    double mean_t=0.0; //среднее время

    int arrayLength[15] = {1,2,3,4,5,10,15,20,25,30,50,75,100,250,500}; //размеры массивов

    double arrayTime[15]; // массив для хранения времени
    int arrayOperations[15]; //массив для хранения операций

    double arrayMeanTime[15];
    int arrayMeanOperations[15];



    //вывод результата
    printf("<------------------------- Сортировка расческой ------------------------->\n\n");
    getResult1(combSort,arrayLength,arrayTime,arrayOperations,arrayMeanTime,arrayMeanOperations,t,k,mean_t,mean_k);
    printf("Результаты для массива на 100 элементов:\n");
    getResult2(combSort,100);

    printf("<------------------------- Сортировка Шелла ------------------------->\n\n");
    getResult1(ShellSort,arrayLength,arrayTime,arrayOperations,arrayMeanTime,arrayMeanOperations,t,k,mean_t,mean_k);
    printf("Результаты для массива на 100 элементов:\n");
    getResult2(ShellSort,100);

    printf("<------------------------- Пирамидальная сортировка ------------------------->\n\n");
    getResult1(heapSort,arrayLength,arrayTime,arrayOperations,arrayMeanTime,arrayMeanOperations,t,k,mean_t,mean_k);
    printf("Результаты для массива на 100 элементов:\n");
    getResult2(heapSort,100);

    return 0;
}
