#include <stdio.h>

int main(int argc, char const *argv[])
{
	float z;
	float x = 1230;
	float y = 1.00;
	int i = 0;

	z = y;
	for (i = 0; i < 9; ++i)
	{
		z += y;
	}
	z += x;
	printf("%8.e\n", z);
	return 0;
}
