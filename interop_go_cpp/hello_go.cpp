// hello_go.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <thread>
#include <chrono>
namespace cro = std::chrono;


int main()
{
    //std::cout << "Hello World!\n"; 
	HMODULE hLibDll = LoadLibrary(L"../go/src/cdll/cdll.dll");
	if (!hLibDll) {
		printf("fail\n");
		return -1;
	}
	void(__cdecl * HelloWorld)(void) = NULL;
	HelloWorld = (void (__cdecl*)(void))GetProcAddress(hLibDll, "HelloWorld");
	HelloWorld();

	void(__cdecl * GetTens)(int* tens, int size) = NULL;
	GetTens = (void(__cdecl*)(int*,int))GetProcAddress(hLibDll, "GetTens");
	int tens[5] = { 0,0,0,0,0 };
	GetTens(tens,5);
	for (int i = 0; i < 5; i++) {
		printf("%d\n", tens[i]);
	}

	void(__cdecl * OutputString)(char* str, int size) = NULL;
	OutputString = (void(__cdecl*)(char*, int))GetProcAddress(hLibDll, "OutputString");
	char msg[32];
	memset(msg, 0, 32);
	OutputString(msg, 32);
	printf("Secret message: \"%s\"\n", msg);

	typedef struct sDemo {
		int age;
		double height;
	} sDemo;

	void(__cdecl * Structy)(sDemo* str) = NULL;
	Structy = (void(__cdecl*)(sDemo*))GetProcAddress(hLibDll, "Structy");
	sDemo d[3];
	memset(d, 0, 3*sizeof(sDemo));
	Structy(d);
	for (int i = 0; i < 3; i++) {
		printf("age: %d, height: %0.2f\"\n", d[i].age, d[i].height);
	}
	
	typedef void(__cdecl * task)(void);
	task roar = []() {printf("roar\n"); };

	void(__cdecl * GiveMeTask)(task) = NULL;
	GiveMeTask = (void(__cdecl*)(task))GetProcAddress(hLibDll, "GiveMeTask");
	GiveMeTask(roar);

	void(__cdecl * DoGoroutine)(void) = NULL;
	DoGoroutine = (void(__cdecl*)(void))GetProcAddress(hLibDll, "DoGoroutine");
	DoGoroutine();
	std::this_thread::sleep_for(cro::seconds(12));
	

}
