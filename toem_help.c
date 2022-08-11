#include "toem.h"

/**
* help - function for the help builtin command
* @cmd: the command line inserted
*
* Return: Always 0 (Success)
*/
int help(char *cmd)
{
	char *file;
	int fd, x;
	char *s;

	if (cmd == NULL)
	{
		s = "help: no builtin entered.\n";
		x = _strlen(s);
		x = write(1, s, x);
		return (0);
	}

	if (!_strcmp(cmd, "cd"))
	{
		file = "help_cd";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((x = read(fd, s, 256)) > 0)
		{
			x = write(1, s, x);
			if (x == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "history"))
	{
		file = "help_hist";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((x = read(fd, s, 256)) > 0)
		{
			x = write(1, s, x);
			if (x == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "help"))
	{
		file = "help_hel";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((x = read(fd, s, 256)) > 0)
		{
			x = write(1, s, x);
			if (x == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "alias"))
	{
		file = "help_al";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((x = read(fd, s, 256)) > 0)
		{
			x = write(1, s, x);
			if (x == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "unset"))
	{
		file = "help_unset";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((x = read(fd, s, 256)) > 0)
		{
			x = write(1, s, x);
			if (x == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "unalias"))
	{
		file = "help_unal";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((x = read(fd, s, 256)) > 0)
		{
			x = write(1, s, x);
			if (x == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "env"))
	{
		file = "help_env";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((x = read(fd, s, 256)) > 0)
		{
			x = write(1, s, x);
			if (x == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "setenv"))
	{
		file = "help_setenv";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((x = read(fd, s, 256)) > 0)
		{
			x = write(1, s, x);
			if (x == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else if (!_strcmp(cmd, "unsetenv"))
	{
		file = "help_unenv";
		fd = open(file, O_RDWR);
		s = malloc(256);
		if (s == NULL)
			return (-1);
		while ((x = read(fd, s, 256)) > 0)
		{
			x = write(1, s, x);
			if (x == -1)
			{
				return (-1);
			}
		}
		free(s);
		fd = close(fd);
		return (0);
	}
	else
	{
		s = "help: no help topics match.\n";
		x = _strlen(s);
		x = write(1, s, x);
		return (0);
	}
}
