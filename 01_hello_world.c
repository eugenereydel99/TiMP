#include <stdio.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL,"RUS");
	
	printf("Hello world!\n");
	return 0;
}
