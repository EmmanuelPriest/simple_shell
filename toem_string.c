#include "toem.h"
/**
* _strcmp - function that compares two strings
* @s1: char pointer
* @s2: char pointer
*
* Return: positive, negative, or 0 if they are the same
*/
int _strcmp(char *s1, char *s2)
{
	int n;

	n = 0;
	while (s1[n] != '\0' && s2[n] != '\0')
	{
		if (s1[n] != s2[n])
		{
			return (s1[n] - s2[n]);
		}
		n++;
	}
	return (s1[n] - s2[n]);
}

/**
* _strlen - function that counts the length of the string
* @str: string
*
* Return: length of the string
*/
size_t _strlen(char *str)
{
	size_t length = 0;

	while (*str++)
		length++;

	return (length);
}

/**
* _strcpy - function that copies string
* @dest: dest string
* @src: source string
*
* Return: string
*/
char *_strcpy(char *dest, char *src)
{
	char *ptr = dest;

	while (*src)
		*ptr++ = *src++;
	*ptr = *src;

	return (dest);
}

/**
* _strdup - function that duplicates string
* @str: string
*
* Return: string
*/
char *_strdup(char *str)
{
	char *new;

	if (str == NULL)
		return (NULL);
	new = malloc(sizeof(char) * (_strlen(str) + 1));
	if (new == NULL)
		return (NULL);
	_strcpy(new, str);
	return (new);
}

/**
* _strcat - function that concatinates strings
* @dest: destination
* @src: source
*
* Return: concatinated string
*/
char *_strcat(char *dest, char *src)
{
	char *ptrs = dest;

	while (*ptrs)
		ptrs++;
	while (*src)
		*ptrs++ = *src++;
	*ptrs = 0;
	return (dest);
}
