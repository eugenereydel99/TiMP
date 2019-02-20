#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL,"RUS");
	
	int a;
	scanf("%d",&a);
	
	int b;
	scanf("%d",&b);
	
	(pow(a,b)>INT_MAX || pow(a,b)<INT_MIN)?printf("Недопустимый результат!\n"):printf("%f\n",pow(a,b));

	return 0;
}
