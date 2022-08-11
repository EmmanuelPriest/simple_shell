#include "toem.h"

/**
* _putchar - writes the character c to stdout
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
* _printenv - function that prints environment
*
* Return: 0 on success
*/
int _printenv(void)
{
	char **environ = *(getenviron());
	int n, m;

	n = 0;
	while (environ[n])
	{
		m = 0;
		while (environ[n][m] != 0)
		{
			_putchar(environ[n][m]);
			m++;
		}
		_putchar('\n');
		m++;
	}
	return (0);
}
