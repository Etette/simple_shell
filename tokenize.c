#include "shell.h"

/**
 * tokenize_buf - tokenize buffer by inputting NULLs and filling **av
 * @b: the with command string
 * @argv: pointer to the command argv
 *
 * this function accepts a string e.g 'ls -l' and
 * changes it to 'ls\0-l. it puts pointers to 'ls'
 * and 'l' into *av
 *
 */

void tokenize_buf(buffer *b, char ***argv)
{
	int i, ap, flag, whitespace;

	_av_init(b->buf + b->bp, argv);

	for (i = b->bp, ap = 0, flag = 1; !_is_endofcmd(b->buf[i]); i++)
	{
		whitespace = _is_whitespace(b->buf[i]);
		if (flag && !whitespace)
		{
			(*argv)[ap++] = b->buf + 1;
			flag = 0;
		}
		if (whitespace)
		{
			b->buf[i] = '\0';
			flag = 1;
		}
	}
	(*argv)[ap] = NULL;

	if (b->buf[i] == '#')
		while (b->buf[i] != '\n' && b->buf[i] != '\0')
			i++;

	if (b->buf[i] == '\n' && b->buf[i + 1] != '\0')
		b->buf[i] = ';';
	else if (b->buf[i] == '\n')
		b->buf[i] = '\0';

	if (b->buf[i] == ';' || b->buf[i] == '|' || b->buf[i] == '&')
	{
		b->bp += i - b->bp;
		_add_null(b->buf + b->bp);
		b->bp++;
	}
	else
		b->bp = 0;
}

/**
 * _av_init - resize av if needed
 * @buf: buffer with the command string
 * @argv: command arg vector
 */

void _av_init(char *buf, char ***argv)
{
	int c, i, flag, whitespace;

	for (c = 0, flag = 1; !_is_endofcmd(*buf); buf++)
	{
		whitespace = _is_whitespace(*buf);
		if (flag && !whitespace)
			flag = 0, c++;
		else if (whitespace)
			flag = 1;
	}
	if (*argv != NULL)
	{
		for (i = 0; (*argv)[i] != NULL; i++)
			;
		if (c > 1)
		{
			_free(*argv);
			*argv = safe_malloc(sizeof(char *) * (c + 1));
		}
		return;
	}
	else
		*argv = safe_malloc(sizeof(char *) * (c + 1));
}

/**
 * _add_null - add a null before the multi-cmd operator
 * @buf: buffer struct to add null into
 */

void _add_null(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		;
	i++;
	for (; i > 0; i--)
		buf[i + 1] = buf[i];
	buf[i + 1] = buf[i];
	buf[i] = '\0';
}
/**
 * _is_whitespace - boolean true or false for whitespace
 * @c: character to evaluate
 * Return: 1 if true, 0 if fail
 */
int _is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

/**
 * _is_endofcmd - boolean to check if character signals end of command
 * @c: char to evaluate
 * Return: 1 if end of command, 0 if not
 */
int _is_endofcmd(char c)
{
	if (c == '\0' || c == '\n' || c == '|' || c == ';' || c == '#')
		return (1);
	return (0);
}
