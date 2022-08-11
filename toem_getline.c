#include "toem.h"
/**
* _getline - function that gets a line from fd or std input
* @lineptr: buffer to fill line with
* @fd: file descriptor
*
* Return: num of characters
*/
int _getline(char **lineptr, int fd)
{
	int size = 1025;
	int old_size = 0;
	int x = 1;
	int sum = 0;
	static char buffer[1025];
	static int begin;
	static int end;
	int y = 0;
	int z;

	if (fd == -2)
	{
		begin = 0;
		end = 0;
	}

	if (lineptr == NULL)
	{
		return (0);
	}
	if (*lineptr == NULL)
	{
		*lineptr = malloc(sizeof(char) * size + 1);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (begin == end)
		{
			while (sum < 1024 && x != 0)
			{
				x = read(fd, buffer + sum, 1024 - sum);
				begin = 0;
				sum += x;
				end = sum;
				/*printf("x : %d\n", x);*/
				for (z = 0; x != 0 && z < end; z++)
					if (buffer[z] == '\n')
						x = 0;
			}
			if (sum == 0)
			{
				buffer[0] = 0;
				return (sum);
			}
			buffer[sum] = 0;
			sum = 0;
		}
		for (; buffer[begin]; begin++)
		{
			if (begin == 1024)
			{
				/*free(buffer);*/
				/*(*lineptr)[y] = EOF;*/
				/*return (y);*/
				break;
			}
			/*printf("beginning for\n");//debug check*/
			if (buffer[begin] == '\n')
			{
				(*lineptr)[y] = '\n';
				begin++;
				y++;
				(*lineptr)[y] = '\0';
				return (y);
			}
			else
			{
				(*lineptr)[y] = buffer[begin];
			}
			y++;
		}
		if (y + begin >= 1024)
		{
			old_size = size;
			size = size + 1024;
			*lineptr = _realloc(*lineptr, old_size, size);
			if (*lineptr == NULL)
			{
				return (-1);
			}
		}
		else
		{
			(*lineptr)[old_size + begin] = 0;
			return (y);
		}
		/*printf("m: %d, n:%d, x:%d\n", m, n ,x);*/
	}
}
