#include "shell.h"

/**
 * history_wrapper - determines history acts
 * @cmd: cmd for add history mode
 * @envp: env variable linked list
 * @mode: mode to determine next action
 * this function creates a mode to create list 'c',
 * 'a' adds history mode and 'w' writes to file mode
 */

void history_wrapper(char *cmd, env_t *envp, char mode)
{
	char **arg;

	arg = safe_malloc(sizeof(char *) * 2);
	if (mode == 'c')
		hsh_history(NULL, envp, 0);
	else if (mode == 'a')
	{
		arg[0] = safe_malloc(sizeof(char) * (_strlen(cmd) + 1));
		_memcpy(arg[0], cmd, _strlen(cmd) + 1);
		hsh_history(arg, envp, 1);
	}
	else if (mode == 'w')
		hsh_history(arg, envp, 2);
}
