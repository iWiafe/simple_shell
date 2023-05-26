#include "shell.h"

/**
 * _myexit - a function that exits the shell
 * @info: containing potential arguments. Used to maintain function prototype
 * Return: exits with a status (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - a function that changes the current directory
 * @info: containing potential arguments. Used to maintain function prototype
 * Return: 0 (Success)
 */
int _mycd(info_t *info)
{
	char *a, *direc, buffer[1024];
	int changedir_ret;

	a = getcwd(buffer, 1024);
	if (!a)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		direc = _getenv(info, "HOME=");
		if (!direc)
			changedir_ret =
				chdir((direc = _getenv(info, "PWD=")) ? direc : "/");
		else
			changedir_ret = chdir(direc);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(a);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		changedir_ret =
			chdir((direc = _getenv(info, "OLDPWD=")) ? direc : "/");
	}
	else
		changedir_ret = chdir(info->argv[1]);
	if (changedir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - a function that changes the current directory
 * @info: containing potential arguments. Used to maintain function prototype
 * Return: 0 (Success)
 */
int _myhelp(info_t *info)
{
	char **arg_array = info->argv;

	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);

	return (0);
}

