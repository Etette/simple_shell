#include "shell.h"

/**
 * trim_cmd - move pass flow ctrl point at given buffer position
 * @b: buffer struct
 * this helper functon for more_cmds advances the buffer
 * past command ctrl characters
 */

void trim_cmd(buffer *b)
{
	int flag;

	flag = 0;
	while (b->buf[b->bp] == ';')
		b->bp++, flag = 1;
	if (flag)
		return;
	while (b->buf[b->bp] == '|')
		b->bp++, flag = 1;
	if (flag)
		return;
	while (b->buf[b->bp] == '&')
		b->bp++;
}

/**
 * more_cmds - check the command line for the next command
 * @b: buffer structure
 * @retrn_value: Return value from last command
 * This function ctrls logic behind multi-part input
 * and Handles ; && and ||
 * Return: 1 if success, 0 on failure
 */

int more_cmds(buffer *b, int retrn_value)
{
	if (b->bp == 0)
		return (0);
	while (b->buf[b->bp] != '\0')
	{
		if (b->buf[b->bp] == ';')
		{
			trim_cmd(b);
			return (1);
		}
		if (b->buf[b->bp] == '|' && retrn_value == 0)
		{
			trim_cmd(b);
			return (1);
		}
		if (b->buf[b->bp] == '|' && retrn_value != 0)
		{
			trim_cmd(b);
			return (1);
		}
		b->bp++;
	}
	b->bp = 0;
	return (0);
}

/**
 * main - simple shell
 * @argc: argument count
 * @argv: argument vector i.e list of all args
 * @envp: environmental variable list frm the parent
 * Return: 0 on success
 */
int main(int argc, char **argv, char **envp)
{
	char **arg_list;
	env_t *env_p;
	int retrn_value;
	buffer b = {NULL, BUFSIZE, 0};
	(void)argc, (void)argv, (void)envp;

	b.buf = safe_malloc(sizeof(char) * b.size);
	arg_list = NULL;
	retrn_value = 0;

	env_p = create_envlist();
	history_wrapper("", env_p, 'c');
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, signal_handler);
	while (1)
	{
		if (!more_cmds(&b, retrn_value))
		{
			print_cmdline();
			_getline(&b, STDIN_FILENO, env_p);
			history_wrapper(b.buf, env_p, 'a');
		}
		while (alias_expansion(&b, env_p))
			;
		variable_expansion(&b, env_p, retrn_value);
		_getline_fileread(&b, env_p);
		tokenize_buf(&b, &arg_list);
		if (arg_list[0] == NULL)
			continue;
		retrn_value = run_builtin(arg_list, env_p, b.size);
	}
	retn (0);
}
