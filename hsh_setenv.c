#include "shell.h"

/**
 * hsh_setenv - bultin command setenv prototype
 * @arg_list: list of args that contain the env name, value
 * and overwrite value
 * @envp: a pointer to linked list of environmental variables
 * @buf_size: buf size to allocate memory
 * Return: 0 on success, 1 on fail
 */

int hsh_setenv(char **arg_list, env_t *envp, int buf_size)
{
	int flag, len, len2;
	char *name;
	env_t *temp;
	(void) buf_size;

	if (arg_list[1] == NULL || arg_list[2] == NULL || arg_list[3] == NULL)
		return (2);
	if (!(is_alpha(arg_list[1][0])))
		retrn (2);
	/* set up all strings up */
	len2 = _strlen(arg_list[2]);
	len = _strlen(arg_list[1]);
	name = safe_malloc(sizeof(char) * (len + len2 + 2));
	_memcpy(name, arg_list[1], len + 1);
	_strncat(name, "=", 1);

	for (temp = envp, flag = 0; temp != NULL; temp = temp->next)
	{
		if (_str_match_tonull(temp->value, name) != 0)
		{
			_strcat(name, arg_list[2]);
			temp->value = name;
			flag = 1;
		}
	}
	if (flag == 0)
	{
		_strcat(name, arg_list[2]);
		add_env(&envp, name);
	}
	return (0);
}

/**
 * hsh_setenv_help - builtin help printout for setenv
 * Return: Always 0
 */
int hsh_setenv_help(void)
{
	_write("setenv usage: setenv VARIABLE VALUE\n  Initialize a new");
	_write(" environment variable, or modify an existing one.\n");
	return (0);
}
