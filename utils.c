#include "main.h"

/**
 * pf_is_digit - checks if c is digit
 * @c: char
 *
 * Return: 1 if digit, 0 otherwise
 */
int pf_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * pf_strlen - length of string
 * @s: string
 *
 * Return: length
 */
int pf_strlen(const char *s)
{
	int n;

	if (s == NULL)
		return (0);

	n = 0;
	while (s[n] != '\0')
		n++;
	return (n);
}

/**
 * pf_is_printable - printable ASCII check
 * @c: byte
 *
 * Return: 1 if printable, 0 otherwise
 */
int pf_is_printable(unsigned char c)
{
	if (c > 0 && c < 32)
		return (0);
	if (c >= 127)
		return (0);
	return (1);
}

/**
 * pf_hex_digit - hex digit for value 0..15
 * @v: value
 * @upper: 1 for uppercase, 0 for lowercase
 *
 * Return: hex digit
 */
char pf_hex_digit(unsigned int v, int upper)
{
	if (v < 10)
		return ((char)('0' + v));
	if (upper)
		return ((char)('A' + (v - 10)));
	return ((char)('a' + (v - 10)));
}

/**
 * pf_rot13_char - rot13 transform one character
 * @c: char
 *
 * Return: transformed char
 */
char pf_rot13_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return ((char)('a' + (c - 'a' + 13) % 26));
	if (c >= 'A' && c <= 'Z')
		return ((char)('A' + (c - 'A' + 13) % 26));
	return (c);
}
