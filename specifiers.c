#include "main.h"

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
	{
		s = "(null)";
	}
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

/**
 * print_int - prints an integer (%d, %i)
 * @ap: va_list containing the argument
 *
 * Return: number of characters printed
 */
int print_int(va_list ap)
{
	long n;
	unsigned long num;
	int count;
	char buf[21];
	int i;

	n = (long)va_arg(ap, int);
	count = 0;

	if (n < 0)
	{
		_putchar('-');
		count++;
		num = (unsigned long)(-n);
	}
	else
	{
		num = (unsigned long)n;
	}

	if (num == 0)
	{
		_putchar('0');
		return (count + 1);
	}

	i = 0;
	while (num > 0)
	{
		buf[i++] = (char)((num % 10) + '0');
		num /= 10;
	}

	while (i > 0)
	{
		_putchar(buf[--i]);
		count++;
	}

	return (count);
}
