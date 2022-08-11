#include "toem.h"

/**
* _atoi - function that converts string to number
* @s : pointer int
* _atoi: converts string to number
*
* Return: The result (converted number)
*/
int _atoi(char *s)
{
	int n;
	int check_num;
	unsigned int sum;
	unsigned int m;
	int neg;

	neg = 0;
	check_num = 0;
	sum = 0;
	n = 0;

	/* run a while loop */
	while (s[n] != '\0')
	{
		if ((s[n] > '9' || s[n] < '0') && check_num > 0)
			break;
		if (s[n] == '-')
			neg++;
		if (s[n] >= '0' && s[n] <= '9')
			check_num++;
		n++;
	}
	n = n - 1;
	m = 1;
	while (check_num > 0)
	{
		sum = sum + ((s[n] - '0') * m);
		m = m * 10;
		n--;
		check_num--;
	}
	if (neg % 2 != 0)
		sum = sum * -1;
	return (sum);
}
