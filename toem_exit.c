#include "toem.h"
#include "alias.h"
#include "shellvars.h"

char ***getenviron();
ShellVar **getspecial();
ShellVar **getvars();
AliasData **getalist();

/**
* exitcleanup - function that cleans up various vars before exiting
* @av: argument list to free (if any)
*
* Return: nothing
*/
void exitcleanup(char **av)
{
	ShellVar *sptr = *(getspecial()), *snext;
	AliasData *aptr = *(getalist()), *anext;
	char **environ = *(getenviron());
	int n = 0;

	if (av != NULL)
		for (n = 0; av[n] != NULL; n++)
			free(av[n]);
	n = 0;
	while (environ[n] != NULL)
		free(environ[n++]);
	free(environ);
	while (sptr != NULL)
	{
		free(sptr->val);
		free(sptr->name);
		sptr = sptr->next;
	}
	free(*(getspecial()));
	sptr = *(getvars());
	while (sptr != NULL)
	{
		free(sptr->val);
		free(sptr->name);
		snext = sptr->next;
		free(sptr);
		sptr = snext;
	}
	while (aptr != NULL)
	{
		free(aptr->val);
		free(aptr->name);
		anext = aptr->next;
		free(aptr);
		aptr = anext;
	}
}
