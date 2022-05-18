#include "shell.h"

/**
 * run_builtin - check arg_list for builtins and eecute found cmd
 * @arg_list: arg list
 * @env_p: environ list
 * @buf_size: buffer size
 * Return: 0 on success, 1 if no cmd found, 2 on builtin error
 */

int run_builtin(char **arg_list, env_t *env_p, int buf_size)
{
	int i, size, status;
	builtin table[] = {
		{"exit", hsh_exit}, {"env", hsh_env}, {"setenv", hsh_setenv},
		{"unsetenv", hsh_unsetenv}, {"cd", hsh_cd}, {"help", hsh_help},
		{"history", hsh_history}, {"alias", hsh_alias}
	};

	size = ARRAY_SIZE(table);
	for (i = 0; i < size; i++)
	{
		if (_str_match_strict(arg_list[0], table[i].name))
		{
			status = table[i].func(arg_list, env_p, buf_size);
			return (status);
		}
	}
	return (1);
}
