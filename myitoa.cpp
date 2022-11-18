#include "myitoa.h"

void myitoa (char *output, int input)
{
	int c = 0;
	bool leadingZeros = true;

	for (int i = 10000000; i >= 1; i /= 10)
	{
		output [c] = input / i;
		input -= output [c] * i;
		if (!leadingZeros || output [c] != 0)
		{
			output [c] += '0';
			c++;
			leadingZeros = false;
		}
	}

	if (leadingZeros)
	{
		output [c] = '0';
		c++;
	}
	output [c] = '\0';
}

void RightAlign (char *text, int len)
{
	char temp [9];
	signed int i;

	for (i = 0; i < len - strlen (text); i++)
		temp [i] = ' ';

	for (; i < len; i++)
		temp [i] = text [i - (len - strlen (text))];

	temp [i] = '\0';

	strcpy (text, temp);
}