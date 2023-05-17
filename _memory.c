#include "shell.h"

/**
 * bfree - main function begins here
 *
 * @ptr: input address of the function
 *
 * Return: Always 0
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr); /*freeing memory*/
		*ptr = NULL; /*setting the pointer to null*/
		return (1); /*return value*/
	}
	return (0);
}
