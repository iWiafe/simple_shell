#include "shell.h"

/**
 * _erratoi - a function that converts a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, -1 on error otherwise
 */
int _erratoi(char *s)
{
	int a = 0;
	unsigned long int outcome = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			outcome *= 10;
			outcome += (s[a] - '0');
			if (outcome > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}
	return (outcome);
}

/**
 * print_error - a function that prints an error message
 * @info: parameter & return information struct
 * @estr: string with specified error type
 * Return: 0 if no numbers in string, -1 on error otherwise
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - a function that prints a decimal (integer) number (base 10)
 * @input: input
 * @fd: filedescriptor written
 * Return: number printed character
 */
int print_d(int input, int fd)
{
	int a, num = 0;
	int (*__putchar)(char) = _putchar;
	unsigned int _mno_, present;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_mno_ = -input;
		__putchar('-');
		num++;
	}
	else
		_mno_ = input;
	present = _mno_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_mno_ / a)
		{
			__putchar('0' + present / a);
			num++;
		}
		present %= a;
	}
	__putchar('0' + present);
	num++;

	return (num);
}

/**
 * convert_number - a function that converts, a clone of itoa
 * @num: number
 * @base: base
 * @flags: flags
 * Return: a string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *group;
	char sym = 0;
	static char buffer[50];
	char *abc;
	unsigned long a = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		a = -num;
		sym = '-';

	}
	group = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	abc = &buffer[49];
	*abc = '\0';

	do	{
		*--abc = group[a % base];
		a /= base;
	} while (a != 0);

	if (sym)
		*--abc = sym;
	return (abc);
}

/**
 * remove_comments - a function that replaces first instance of '#' with '\0'
 * @buf: address of the string
 * Return: 0 (Success)
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}

