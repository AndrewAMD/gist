//#include <stdio.h>
//
//void say_hello(void);
//int main(void)
//{
//	say_hello();
//	return 0;
//}
//
//void say_hello(void)
//{
//	printf("Hello world!\n");
//}

// **************************

#include <Windows.h>
#include <stdio.h>

//----------------------------------------------------------------------------------
//
//But in our case that same function is in a dll.Ok let's see how we do it. 
//Your dll is located on the C : \ drive for example and is named "MyDLL.dll".It
//contains a function called "MyFunction".Create a function that calls the dll's function like so: 

int CallMyDLL(void)
{
	/* get handle to dll */
	HMODULE hLibDll = LoadLibrary(".\\lib.dll");
	if (!hLibDll) return -1;

	int(__cdecl * say_hello)(void) = NULL;
	int(__cdecl * add)(int numArgs, ...) = NULL;
	void(__cdecl * print_num)(int n) = NULL;

	//fpInVoidOutInt say_hello;
	say_hello = (void*)GetProcAddress(hLibDll, "say_hello");
	add = (void*)GetProcAddress(hLibDll, "add");
	print_num = (void*)GetProcAddress(hLibDll, "print_num");

	if (!say_hello) return -2;
	if (!add) return -3;
	if (!print_num) return -4;

	say_hello();
	print_num(add(7, 1, 20, 300, 4000, 50000, 600000, 7000000));
	print_num(add(7, 1, 20, 300, 4000, 50000, 600000, 7000000));


	/* Release the Dll */
	if(!FreeLibrary(hLibDll)) return -5;

	hLibDll = LoadLibrary(".\\lib.dll");
	say_hello = (void*)GetProcAddress(hLibDll, "say_hello");
	add = (void*)GetProcAddress(hLibDll, "add");
	print_num = (void*)GetProcAddress(hLibDll, "print_num");
	print_num(add(7, 1, 20, 300, 4000, 50000, 600000, 7000000));
	if (!FreeLibrary(hLibDll)) return -6;
	return 0;
}

int main(void)
{
	int out = CallMyDLL();
	printf("out: %d\n", out);
}