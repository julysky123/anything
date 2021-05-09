#include <cstdio>
#include <cstdlib>
#include <Pdh.h>
int cycle;
unsigned long long a = 123145;
int parse_int(char* str)
{
	int pos = 0;
	int ret = 0;
	int sign = 1;
	if (str[pos] == '-')
	{
		sign = -1;
		pos++;
	}
	for (int i = pos; str[i]; i++)
	{
		ret = ret * 10 + str[i] - '0';
	}
	ret *= sign;
	return ret;
}

int main(int argc, char* argv[])
{
	printf("%s\n", argv[0]);
	if (argc != 2) return 0;
	cycle = parse_int(argv[1]);
	printf("cycle : %d\n", cycle);
	for (;;) 
	{
		Sleep(1);
		for (int i = 0; i < cycle; i++)
		{
			a = a * 123145156;
		}
	}
}
