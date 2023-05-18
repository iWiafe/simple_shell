#include "shell.h"

/**
 * _strlen - function start
 * @s: input main
 * Return: Always 0
 */

int _strlen(char *s)
{
	int t = 0; /*initialization*/

	if (!s)
		return (0);

	while (*s++)
		t++;
	return (t);
}

/**
 * _strcmp - main program
 * @s1: strang one
 * @s2: strang two
 * Return: Always 0
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2) /*compares s1 with s2*/
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++; /*increamental*/
		s2++; /*increamental*/
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - start of function
 * @haystack: input one
 * @needle: input two
 * Return: Always 0
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++) /*conditional statement*/
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - program start
 * @dest: input one
 * @src: input two
 * Return: Always 0
 */

char *_strcat(char *dest, char *src)
{
	char *r = dest;  /*initialization*/

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (r);
}
