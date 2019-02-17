#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <limits.h>

int main(void)
{
	setlocale(LC_ALL,"RUS");
	
	int a,b;
	
	printf("Введите число,которое будете возводить в степень:");
	scanf("%d",&a);
	
	printf("Введите степень:");
	scanf("%d",&b);
	
	pow(a,b)>INT_MAX ? printf("Результат возведения в степень больше допустимого!\n") : printf("Результат возведения числа %d в степень %d = %f\n",a,b,pow(a,b));
	
	return 0;
}
