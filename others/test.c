#include <stdio.h>
#include <stdlib.h>

void boo(int a, double b, double c)
{
	printf("\na=%d,b=%d,c=%f\n",a,b,c); 
}

int main()
{  
	int a;
	float b,c;  
	
	scanf("%2d%3f%4f",&a,&b,&c);  
	boo(a, b, c);
	return 0;
}
