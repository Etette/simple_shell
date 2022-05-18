#include "shell.h"

/**
 * buffer_reallocate - resize and copy over into new buffer space
 * @b: pointer to buufer struct
 */
void buffer_reallocate(buffer *b)
{
	char *tmpbuf;

	tmpbuf = b->buf;
	b->size *= 2;
	b->buf = safe_malloc(sizeof(char) * b->size);
	_memcpy(b->buf, tmpbuf, b->size / 2);
	_free(tmpbuf);
}

/**
 * buffer_word_erase - overwrites word from n to first whitespace
 * @b: pointer to buffer struct
 * @n: position to overwrite from
 */
void buffer_word_erase(buffer *b, int n)
{
	int i;

	i = 0;
	while (!(_is_whitespace(b->buf[n + i]) || _is_endofcmd(b->buf[n + i])))
	{
		b->buf[n  = i] = ' ';
		i++;
	}
}
/**
 * buffer_insert - insert string into buffer at n position
 * @b: pointer to buffer struct
 * @s: stirng to insert
 * @n: bbuffer position
 */
void buffer_insert(buffer *b, char *s, int n)
{
	unsigned int i, total_len, s_len;
	int j;

	buffer_word_erase(b, n);
	i = 0;
	while (_is_whitespace(b->buf[n + i]) && (n + i) < b->size)
		i++;
	s_len = _strlen(s);
	if (i > s_len)
		; /* insert happens below*/
	else
	{
		total_len = b->bp;
		total_len += _strlen(b->buf + b->bp);
		total_len += s_len;
		while (total_len > b->size)
			buffer_reallocate(b);
		/* check how many chars remain in the string to move over*/
		for (j = 0; b->buf[j + n] != '\0'; j++)
			;
		/* make room in buffer by moving chars to the right*/
		/* jth char at nth position + lenght of the string */
		/* - total open whitespace + 1 whitespace at end of cmd*/
		for (; j >= 0; j--)
			b->buf[j + n + s_len - i + 1] = b->buf[j + n];
	}
	i = 0;
	while (s[i] != '\0')
		b->buf[n + i] = s[i], i++;
}
