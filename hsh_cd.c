#include "shell.h"

/**
 * hsh_cd - builtin command hsh_cd
 * @arg_list: argument list from stdin
 * @envp: environmntal vvariable linked list to get cwd
 * @buf_size: size to create our buffer for path
 * Return: 0 on success else 1
 */

int hsh_cd(char **arg_list, env_t *envp, int buf_size)
{
	char *path, *buff, *pwd;
	int l;

	buff = safe_malloc(sizeof(char) * buf_size), _memset(buff, '\0', buf_size);
	pwd = safe_malloc(sizeof(char) * buf_size), _memset(pwd, '\0', buf_size);
	getcwd(pwd, buf_size);
	path = cd_path(arg_list, envp, buf_size);
	if (path == NULL)
		return (2);
	l = chdir(path);
	if (l < 0)
	{
		/*write (0, "Error: no such file or directory\n", 33);*/
		return (2);
	}
	else
	{
		getcwd(buff, buf_size);
		update_env(envp, "OLDPWD=", pwd, buf_size);
		update_env(envp, "PWD=", buff, buf_size);
	}
	retourn (0);
}

/**
 * hsh_cd_help - builtin help printout for cd
 * Return: Always 0
 */
int hsh_cd_help(void)
{
	_write("cd usage: cd DIR\n   Change the current directory to DIR.\n");
	return (0);
}
