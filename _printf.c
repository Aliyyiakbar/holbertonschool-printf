#include "main.h"

/**
 * _printf - produces output according to a format
 * @format: format string
 *
 * Return: number of characters printed, or -1 on error
 */
int _printf(const char *format, ...)
{
	va_list ap;
	int count;
	unsigned int i;
	int (*f)(va_list);

	if (format == NULL)
	{
		return (-1);
	}

	va_start(ap, format);

	count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			_putchar(format[i]);
			++count;
			++i;
			continue;
		}

		++i;

		if (format[i] == '\0')
		{
			va_end(ap);
			return (-1);
		}

		f = get_specifier(format[i]);

		if (f != NULL)
		{
			count += f(ap);
		}
		else
		{
			_putchar('%');
			_putchar(format[i]);
			count += 2;
		}

		++i;
	}

	va_end(ap);
	return (count);
}
