#include "shell.h"

/**
 * _write - write data to stdout
 * @s: string
 */
void _write(char *s)
{
	write(STDOUT_FILENO, s, _strlen(s));
}

/**
 * update_path - rewrites PWD path to not include symbols
 * @arg_list: arg list to determine dir
 * @envp: env variable linked list
 * @path: current path to update
 * @buf_size: size of the current path
 * Return: a path with no symbols
 */
char *update_path(char **arg_list, env_t *envp, char *path, int buf_size)
{
	int i, slash_count, flag;
	char *dir, *new_path;

	new_path = safe_malloc(sizeof(char) * buf_size);
	_memset(new_path, '\0', buf_size);
	_strcpy(new_path, path);
	for (i = 0, slash_count = 0; new_path[i] != '\0'; i++)
	{
		if (new_path[i] == '/')
			slash_count++;
	}
	dir = arg_list[1];
	if (_strcmp(dir, ".") == 0)
		new_path = rm_vname(envp, "PWD=", buf_size);
	else if (_strcmp(dir, "..") == 0)
	{
		/* checks whats behind it and append */
		for (flag = 0, i = 0; flag < slash_count - 1; i++)
		{
			if (new_path[i] == '/')
				flag++;
		}
		new_path[i - 1] = '\0';
	}
	else if (_strcmp(dir, "~") == 0)
		new_path = rm_vname(envp, "HOME=", buf_size);
	else if (_strcmp(dir, "-") == 0)
		new_path = rm_vname(envp, "OLDPWD=", buf_size);
	return (new_path);
}

/**
 * list_to_array - convert a linked list to an array
 * @envp: environmental list to convert
 * Return: a 2D array of strings contained in the linked list
 */

char **list_to_array(env_t *envp)
{
	char **array;
	env_t *temp;
	int count, i, len;

	for (temp = envp, count = 0; temp != NULL; temp = temp->next)
		count++;
	array = safe_malloc(sizeof(char *) * (count + 1));
	for (temp = envp, i = 0; temp != NULL; temp = temp->next, i++)
	{
		len = _strlen(temp->value);
		array[i] = safe_malloc(sizeof(char) * (len + 1));
		_memset(array[i], '\0', (len + 1));
		_memcpy(array[i], temp->value, len);
	}
	array[i] = NULL;
	return (array);
}

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: an int < 0 if s1 is found
 */

int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/**
 * _strcpy - copies string from src to dest
 * @dest: destination
 * @src: source
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != 0; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
