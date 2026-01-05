#include "main.h"
#include <unistd.h>

/**
 * print_char - prints a char
 * @ap: va_list containing the argument
 *
 * Return: number of characters printed
 */
int print_char(va_list ap)
{
	char c;

	c = (char)va_arg(ap, int);
	_putchar(c);
	return (1);
}

/**
 * print_string - prints a string
 * @ap: va_list containing the argument
 *
 * Return: number of characters printed
 */
int print_string(va_list ap)
{
	char *s;
	int count;

	s = va_arg(ap, char *);
	if (s == NULL)
		s = "(null)";

	count = 0;
	while (s[count] != '\0')
	{
		_putchar(s[count]);
		count++;
	}
	return (count);
}

/**
 * print_percent - prints a percent sign
 * @ap: va_list (unused)
 *
 * Return: number of characters printed
 */
int print_percent(va_list ap)
{
	(void)ap;
	_putchar('%');
	return (1);
}
