#include "main.h"

/**
 * pf_buf_init - initialize buffer
 * @b: buffer
 */
void pf_buf_init(pf_buffer_t *b)
{
	b->idx = 0;
	b->len = 0;
	b->err = 0;
}

/**
 * pf_buf_flush - flush buffer to stdout
 * @b: buffer
 *
 * Return: 0 on success, -1 on failure
 */
int pf_buf_flush(pf_buffer_t *b)
{
	ssize_t w;

	if (b->err)
		return (-1);

	if (b->idx == 0)
		return (0);

	w = write(1, b->buf, b->idx);
	if (w == -1 || w != (ssize_t)b->idx)
	{
		b->err = 1;
		return (-1);
	}

	b->idx = 0;
	return (0);
}

/**
 * pf_buf_putc - put a char into buffer
 * @b: buffer
 * @c: char
 *
 * Return: 0 on success, -1 on failure
 */
int pf_buf_putc(pf_buffer_t *b, char c)
{
	if (b->err)
		return (-1);

	if (b->idx >= PF_BUF_SIZE)
	{
		if (pf_buf_flush(b) == -1)
			return (-1);
	}

	b->buf[b->idx++] = c;
	b->len++;
	return (0);
}

/**
 * pf_buf_putn - write n bytes into buffer
 * @b: buffer
 * @s: string
 * @n: length
 *
 * Return: 0 on success, -1 on failure
 */
int pf_buf_putn(pf_buffer_t *b, const char *s, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		if (pf_buf_putc(b, s[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

/**
 * pf_buf_pad - pad n times with char c
 * @b: buffer
 * @c: padding char
 * @n: count
 *
 * Return: 0 on success, -1 on failure
 */
int pf_buf_pad(pf_buffer_t *b, char c, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		if (pf_buf_putc(b, c) == -1)
			return (-1);
		i++;
	}
	return (0);
}
