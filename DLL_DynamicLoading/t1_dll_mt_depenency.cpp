// t1_dll_mt_depenency.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "t1_dll_mt_depenency.h"
#include <string>


DLLFUNC const char* get_secret_word()
{
	static int i = 0;
	++i;
	static std::string word;
	word = "fantabulous" + std::to_string(i);
	return word.c_str();
}
