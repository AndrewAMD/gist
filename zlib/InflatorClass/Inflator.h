#pragma once
#ifndef INFLATOR_H
#define INFLATOR_H

#include "zlib.h"
#include <vector>
typedef std::vector<char> v_char;
typedef std::vector<v_char> vv_char;

class inflator
{
public:
	inflator();
	~inflator();
	void reset();
	int inf(const v_char& in);
	bool can_get_spliced_output(v_char& out);
private:
	vv_char _chunks_out;
	z_stream _strm;
	bool _ready;
};

#endif // INFLATOR_H