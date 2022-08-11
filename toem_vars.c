#include "shellvars.h"
#include "toem.h"

/**
* getspecial - function that wraps getspecial static var
*
* Return: address of shellvar special
*/
ShellVar **getspecial()
{
	static ShellVar *special;

	return (&special);
}

/**
* getsvars - function that gets static vars wrapper
*
* Return: address of var
*/
ShellVar **getvars()
{
	static ShellVar *vars;

	return (&vars);
}
