#include "toem.h"

/**
* checkpath - function that checks the path
* @av: arguments
*
* Return: 1
*/
int checkpath(char *av[])
{
	char *path, *pathptr, *pathvar, *ptr, *pathenv = "PATH", *linect;
	int pathLength, cmdLength;

#ifdef DEBUGMODE
	printf("In checkpath\n");
#endif
	for (ptr = av[0], cmdLength = 0; *ptr != 0; ptr++)
		cmdLength++;
	pathvar = _getenv(pathenv);
	if (pathvar != pathenv)
	{
		pathenv = pathvar;
		while (*pathvar != 0)
		{
#ifdef DEBUGMODE
			printf("in loop pathvar:%s:*pathvar:%c\n", pathvar,
					*pathvar);
#endif
			for (pathLength = 0, ptr = pathvar; *ptr != 0 &&
					*ptr != ':'; ptr++)
				pathLength++;
			path = malloc(sizeof(char) * (cmdLength + pathLength
						+ 2));
			if (path == NULL)
			{
				free(pathenv);
				return (-1);
			}
			pathptr = path;
			while (*pathvar != ':' && *pathvar != 0)
				*pathptr++ = *pathvar++;
			if (pathptr != path)
				*pathptr++ = '/';
			ptr = av[0];
			while (*ptr != 0)
				*pathptr++ = *ptr++;
			*pathptr = 0;
			if (!access(path, F_OK))
			{
#ifdef DEBUGMODE
				printf("Found path:%s\n", path);
#endif
				pathLength = cmdcall(av, path);
				free(path);
				free(pathenv);
				return (pathLength);
			}
			free(path);
			if (*pathvar == ':')
				pathvar++;
		}
	}
	linect = itos(linecount(0));
	path = getsvar("0");
	fprintstrs(2, path, ": ", linect, ": ", av[0], ": not found\n", NULL);
	free(path);
	free(linect);
	if (pathenv != pathvar)
		free(pathenv);
	return (127);
}
/**
* cmdcall - function that calls commands
* @av: arguments
* @cmd: command
*
* Return: retval
*/
int cmdcall(char *av[], char *cmd)
{
	pid_t command;
	int stat;
	char *linect, *dolz;

#ifdef DEBUGMODE
	printf("In cmdcall av[0]:%s\n", av[0]);
#endif
	environ = getallenv();
	if (environ == NULL)
		return (-1);
#ifdef DEBUGMODE
	printf("Forking\n");
#endif
	command = fork();
#ifdef DEBUGMODE
	printf("command:%d\n", command);
	fflush(stdout);
#endif
	if (command == 0)
	{
#ifdef DEBUGMODE
		printf("Executing %s\n", av[0]);
#endif
		if (execve(cmd, av, *(getenviron())) == -1)
		{
			if (!access(cmd, F_OK))
			{
				printerr(NULL);
				exit(126);
			}
			else
			{
				linect = itos(linecount(0));
				dolz = getsvar("0");
				fprintstrs(2, dolz, ": ", linect, ": ",
						cmd, ": not found\n", NULL);
				free(dolz);
				free(linect);
				exit(127);
			}
			exit(1);
		}
#ifdef DEBUGMODE
		printf("Command done\n");
#endif
	}
	else
	{
		wait(&stat);
	}
#ifdef DEBUGMODE
	printf("Status %d\n", stat);
#endif
	free(environ);
	return (stat);
}
/**
* builtincall - function that calls builtin commands
* @av: arguments
*
* Return: ret
*/
int builtincall(char *av[])
{
	int ret = 0;
	char *retstr;

	if (av[0] == NULL)
		return (0);
#ifdef DEBUGMODE
	printf("In builtincall %p\n%s\n", av[0], av[0]);
	printf("av[1]:%s\n", av[1]);
#endif
	if (!_strcmp(av[0], "exit"))
	{
		if (av[1] != NULL)
			if (av[1][0] >= '0' && av[1][0] <= '9')
			{
				ret = _atoi(av[1]);
				exitcleanup(av);
				exit_hist();
				exit(ret);
			}
			else
			{
				printerr(": exit: Illegal number: ");
				fprintstrs(STDERR_FILENO, av[1], "\n", NULL);
				ret = 2;
			}
		else
		{
			retstr = getsvar("?");
			ret = _atoi(retstr);
			free(retstr);
			exitcleanup(av);
			exit_hist();
			exit(ret);
		}
	}
	else if (!_strcmp(av[0], "cd"))
		ret = _cd(av);
/*
 *
 * else if (!_strcmp(av[0], "getenv"))
 *	ret = !printf("%s\n", _getenv(av[1]));
*/
	else if (!_strcmp(av[0], "history"))
		ret = print_hist();
	else if (!_strcmp(av[0], "help"))
		ret = help(av[1]);
	else if (!_strcmp(av[0], "env"))
		ret = _printenv();
	else if (!_strcmp(av[0], "setenv"))
		ret = _setenv(av[1], av[2]);
	else if (!_strcmp(av[0], "unsetenv"))
		ret = _unsetenv(av[1]);
	else if (!_strcmp(av[0], "alias"))
		ret = aliascmd(av);
	else if (!_strcmp(av[0], "unset"))
		ret = unsetsvar(av[1]);
	else if (!_strcmp(av[0], "unalias"))
		ret = unsetalias(av[1]);
	else if (av[0][0] != '/' &&
		 !(av[0][0] == '.' && (av[0][1] == '/' ||
				       (av[0][1] == '.' && av[0][2] == '/'))))
		ret = checkpath(av);
	else
		ret = cmdcall(av, av[0]);
#ifdef DEBUGMODE
	printf("After call back in builtin retval:%d\n", ret);
#endif
	if (ret % 256 == 0)
		ret /= 256;
	retstr = itos(ret % 128);
#ifdef DEBUGMODE
	printf("Status string:%s\n", retstr);
#endif
	setsvar("?", retstr);
	free(retstr);
	return (ret);
}
