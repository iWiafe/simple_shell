#include "shell.h"

/**
 * interactive - a function that returns true if shell is interactive mode
 * @info: address
 * Return: 1 if interactive mode, otherwise 0
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - a function that that checks the character of delimeter
 * @a: char to check
 * @delim: delimeter string
 * Return: 1 if true, false if 0
 */
int is_delim(char a, char *delim)
{
	while (*delim)
		if (*delim++ == a)
		{
			return (1);
		}
	return (0);
}

/**
 * _isalpha - a function thatchecks for alphabetic character
 * @a: character to input
 * Return: 1 if a is alphabet, otherwise 0
 */
int _isalpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * _atoi - a function that converts a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, otherwise converted number
 */
int _atoi(char *s)
{
	int a, sym = 1, digit = 0, display;
	unsigned int outcome = 0;

	for (a = 0; s[a] != '\0' && digit != 2; a++)
	{
		if (s[a] == '-')
			sym *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			digit = 1;
			outcome *= 10;
			outcome += (s[a] - '0');
		}
		else if (digit == 1)
			digit = 2;
	}

	if (sym == -1)
	{
		display = -outcome;
	}
	else
	{
		display = outcome;
	}
	return (display);
}

