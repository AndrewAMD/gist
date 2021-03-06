// lib.cpp : Defines the exported functions for the DLL application.
//

#include "header.h"

#ifdef LIB_EXPORTS
#define DLLFUNC extern "C" __declspec(dllexport)
#else  
#define DLLFUNC extern "C" __declspec(dllimport)
#endif  
#include<stdio.h>
#include <stdarg.h>

DLLFUNC int say_hello(void)
{
	printf("Hello world!\n");
	return 0;
}
DLLFUNC int add(int numArgs, ...) {

	va_list valist;
	int sum = 0;
	int i;
	static int stat = 0;
	stat += 100000000;
	/* initialize valist for numArgs number of arguments */
	va_start(valist, numArgs);

	/* access all the arguments assigned to valist */
	for (i = 0; i < numArgs; i++) {
		sum += va_arg(valist, int);
	}

	/* clean memory reserved for valist */
	va_end(valist);

	return sum + stat;
}
DLLFUNC void print_num(int n)
{
	printf("%d\n", n);
}
//int main(void)
//{
//	print_num(add(7, 1, 20, 300, 4000, 50000, 600000, 7000000));
//	return 0;
//}
