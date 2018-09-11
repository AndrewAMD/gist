#pragma once
#ifdef LIB01_EXPORTS
#define DLLFUNC extern "C" __declspec(dllexport)
#else  
#define DLLFUNC extern "C" __declspec(dllimport)
#endif  

//// zorro functions
DLLFUNC void HelloWorld();
DLLFUNC int AddInt(int a, int b);

