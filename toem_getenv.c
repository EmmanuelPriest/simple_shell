#include "toem.h"
/**
* getallenv - function that gets all environment
*
* Return: environment
*/
char **getallenv()
{
	char **environ = *(getenviron());
	char **envcopy;
	size_t length = 0;

	envcopy = environ;
	while (envcopy[len] != NULL)
		length++;
#ifdef DEBUGMODE
	printf("Got length of env lines %d\nNow copying\n", length);
#endif
	envcopy = malloc(sizeof(char **) * (length + 1));
	if (envcopy == NULL)
		return (NULL);
	while (length > 0)
	{
		envcopy[length] = environ[length];
		length--;
	}
	envcopy[length] = environ[length];
	return (envcopy);
}
/**
* setallenv - function that sets whole environment for new value
* @envin: environment
* @newval: new value to be added
*
* Return: 0 if success, -1 if failure
*/
/* add should be null for first init to not free passed array */
int setallenv(char **envin, char *newval)
{
	char ***environ = getenviron();
	size_t length = 0;

#ifdef DEBUGMODE
	printf("In setallenv, newval:%s\n", newval);
#endif
	while (envin[length] != NULL)
		length++;
	if (newval != NULL)
		length++;
	*environ = malloc(sizeof(char **) * (length + 1));
	if (*environ == NULL)
		return (-1);
	for (length = 0; envin[length] != NULL; length++)
		if (newval == NULL)
		{
			(*environ)[length] = _strdup(envin[length]);
		}
		else
			(*environ)[length] = envin[length];
	if (newval != NULL)
	{
#ifdef DEBUGMODE
		printf("Adding newval:%s\n", newval);
#endif
		(*environ)[length] = newval;
		length++;
	}
	(*environ)[length] = NULL;
#ifdef DEBUGMODE
	printf("At end. Free old environ if adding a string\n");
#endif
	if (newval != NULL)
		free(envin);
	return (0);
}
/**
* _getenv - function that gets local environment
* @name: environment variable
*
* Return: string of local environment
*/
char *_getenv(char *name)
{
	char **environ = *(getenviron());
	int n, m;
	char *s;

#ifdef DEBUGMODE
	printf("In getenv, name:%s\n", name);
#endif
	n = 0;
	while (environ[n] != NULL)
	{
		s = environ[n];
		m = 0;
#ifdef DEBUGSVARS
		printf("Checking against:%s\n", environ[n]);
#endif
		while (s[m] == name[m])
		{
			m++;
			if (name[m] == 0 && s[m] == '=')
				return (_strdup(s + m + 1));
		}
		n++;
	}
	return (name);
}
/**
* _setenv - function that sets environment for new value
* @name: name of variable
* @val: value of variable
*
* Return: 0 or setallenv if success, -1 if fail
*/
int _setenv(char *name, char *val)
{
	char ***environroot = getenviron();
	char **environ = *environroot;
	int n, m, namel, vall;
	char *s, *ptr;

#ifdef DEBUGMODE
	printf("In setenv, name:%s:val:%s\n", name, val);
#endif
	if (name == NULL || val == NULL)
		return (0);
	namel = _strlen(name);
	vall = _strlen(val);
	ptr = malloc(sizeof(char) * (namel + vall + 2));
	if (ptr == NULL)
		return (-1);
	s = ptr;
	_strcpy(s, name);
	s += namel;
	_strcpy(s++, "=");
	_strcpy(s, val);
	s += vall;
	*s = 0;
#ifdef DEBUGMODE
	printf("Ptr mallocd:%s\n", ptr);
#endif
	n = 0;
	while (environ[n] != NULL)
	{
		s = environ[n];
		m = 0;
		while (s[m] == name[m])
		{
			m++;
			if (name[m] == 0 && s[m] == '=')
			{
				free(environ[n]);
				environ[n] = ptr;
				return (0);
			}
		}
		n++;
	}
	return (setallenv(*environroot, ptr));
}

/**
* _unsetenv - function that unsets environment
* @name: name of variable to unset
*
* Return: 0 if success
* testing functionality  copy environ, if hits skip over, realloc
*/
int _unsetenv(char *name)
{
	char **environ = *getenviron();
	int n, m;
	int check = 0;
	char *s;
	char **env;

#ifdef DEBUGMODE
	printf("In unsetenv, name:%s\n", name);
#endif
	if (name == NULL)
		return (0);

	n = 0;
	while (environ[n] != NULL)
	{
		s = environ[n];
		m = 0;
		while (s[m] == name[m])
		{
			m++;
			if (s[m] == '=' && name[m] == '\0')
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
			break;
		n++;
	}
	free(environ[n]);
	while (environ[n] != NULL)
	{
		environ[n] = environ[n + 1];
		n++;
	}
	environ[n] = NULL;
	env = environ;
	setallenv(env, NULL);
	n = 0;
	while (env[n])
	{
		free(env[n]);
		n++;
	}
	free(env);
	return (0);
}
