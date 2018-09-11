#pragma once

#ifdef T1DLLMTDEPENENCY_EXPORTS
#define DLLFUNC extern "C" __declspec(dllexport)
//#define DLLFUNC extern __declspec(dllexport)
#else  
#define DLLFUNC extern "C" __declspec(dllimport)
//#define DLLFUNC extern __declspec(dllimport)
#endif  


DLLFUNC const char* get_secret_word();
