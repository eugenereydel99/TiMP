#include <stdio.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL,"RUS");
	
	int a,b;
	printf("Введите два числа через пробел:");
	scanf("%d %d",&a,&b);
	
	printf("Сумма чисел %d и %d = %d\n",a,b,a+b);
	return 0;
}
