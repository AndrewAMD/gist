#pragma once


#ifdef T1DLLMTDEPENDS_EXPORTS
#define DLLFUNC1 extern "C" __declspec(dllexport)
//#define DLLFUNC1 extern __declspec(dllexport)
#else  
#define DLLFUNC1 extern "C" __declspec(dllimport)
//#define DLLFUNC1 extern __declspec(dllimport)
#endif  



DLLFUNC1 const char* get_three_words();
