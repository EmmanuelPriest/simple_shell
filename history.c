#include "toem.h"
#include "history.h"

/**
 * gethistory - gets the history list
 * Return: 0 uposon success
 */

HistList **gethistory()
{
	static HistList *hlist;

	return (&hlist);
}

/**
 * sethist - set hist and value
 * @cmd: command
 * Return: 0 upon success
 */

int sethist(char *cmd)
{
	HistList **hlistroot = gethistory();
	HistList *hlist = *hlistroot;
	HistList *ptr = hlist, *new;

	if (hlist == NULL)
	{
		new = malloc(sizeof(HistList));
		if (new == NULL)
			return (-1);

		new->cmd = _strdup(cmd);
		new->next = NULL;
		*hlistroot = new;
		return (0);
	}
	while (ptr->next != NULL)
		ptr = ptr->next;

	new = malloc(sizeof(HistList));
	if (new == NULL)
		return (-1);
	new->cmd = _strdup(cmd);
	new->next = NULL;
	ptr->next = new;
	return (0);
}

/**
 * print_hist - prints all elements of listint
 *
 * Return: num of elements
 */

int print_hist(void)
{
	HistList **hlistroot = gethistory();
	HistList *h = *hlistroot;
	int n;
	int length, numLength;
	char *s, *num;

	n = 0;
	while (h != NULL)
	{
		length = _strlen(h->cmd);
		s = h->cmd;
		num = itos(n);
		numLength = _strlen(num);
		write(1, num, numLength);
		_putchar(' ');
		write(1, s, length);
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * exit_hist - exit history and copy to file
 * Return: integer
 */

int exit_hist(void)
{

	int fd;
	char *file = ".simple_shell_history";
	int length;
	char *s;

	HistList **hlistroot = gethistory();
	HistList *hlist = *hlistroot;
	HistList *ptr = hlist;

	fd = open(file, O_CREAT | O_RDWR, 0600);
	if (fd == -1)
		return (-1);

	while (hlist != NULL)
	{
		ptr = hlist->next;
		s = hlist->cmd;
		length = _strlen(s);
		write(fd, s, length);
		free(hlist->cmd);
		free(hlist);
		hlist = ptr;
	}

	close(fd);
	return (1);
}
