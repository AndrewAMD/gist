#include "Inflator.h"
#include <iostream>
#include <string>
#include <algorithm>

int def(const v_char& input, v_char& output) // <----------- start with this
{
	int ret = 0;
	output.resize(input.size() * 2);

	z_stream strm;
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = (uInt)input.size();
	strm.next_in = (Bytef *)input.data();


	strm.avail_out = (uInt)output.size(); // size of output
	strm.next_out = (Bytef *)output.data(); // output char array

									 // the actual compression work.
	deflateInit(&strm, Z_BEST_COMPRESSION);
	ret = deflate(&strm, Z_FINISH);
	deflateEnd(&strm);

	output[strm.total_out + 1] = 0; // technically not necessary, but useful for printing junk
	output.resize(strm.total_out);

	// This is one way of getting the size of the output

	return ret;
}

void split(v_char in, vv_char& out, int size)
{
	int i, max;
	while (in.size())
	{
		v_char o;
		max = std::min((int)in.size(), size);
		o.reserve(max);
		for (i = 0; i < max; i++)
		{
			o.push_back(in[i]);
		}
		out.push_back(o);
		in.erase(in.begin(), in.begin() + max);
		//printf("size: %d\n", o.size());
	}

}






// adapted from: http://stackoverflow.com/questions/7540259/deflate-and-inflate-zlib-h-in-c
int main(int argc, char* argv[])
{

	v_char aa; aa.resize(37);
	strcpy_s(aa.data(), 37, "Hello Hello Hello Hello Hello Hello!");
	printf("Uncompressed size is: %lu\n", aa.size());
	printf("Uncompressed string is: %s\n", aa.data());


	printf("\n----------\n\n");


	v_char bb;
	//bb.resize(aa.size() * 2);
	def(aa, bb);

	printf("Compressed size is: %lu\n", bb.size());
	printf("Compressed string is: %s\n", bb.data());

	printf("\n----------\n\n");



	inflator i1, i2;
	i1.inf(bb);
	v_char cc1;
	i1.can_get_spliced_output(cc1);
	printf("cc1: %s\n", cc1.data());


	vv_char bb_split;
	split(bb, bb_split, 3);
	for (const auto& b : bb_split)
	{
		auto ret = i2.inf(b);
		std::cout << ret << ", ";
	}
	std::cout << std::endl;
	v_char cc2;
	i2.can_get_spliced_output(cc2);
	printf("cc2: %s\n", cc1.data());

	return 0;
}
