#include "main.h"

/**
 * _printf - custom printf
 * @format: format string
 *
 * Return: number of chars printed, -1 on error
 */
int _printf(const char *format, ...)
{
	va_list ap;
	pf_buffer_t b;
	pf_format_t f;
	const char *p;

	if (format == NULL)
		return (-1);

	pf_buf_init(&b);
	va_start(ap, format);

	p = format;
	while (*p != '\0')
	{
		if (*p != '%')
		{
			if (pf_buf_putc(&b, *p) == -1)
				break;
			p++;
			continue;
		}

		p++;
		if (*p == '\0')
		{
			b.err = 1;
			break;
		}

		if (pf_parse(&p, &f, &ap) == -1)
		{
			b.err = 1;
			break;
		}

		if (pf_handle(&b, &f, &ap) == -1)
			break;
	}

	va_end(ap);

	if (pf_buf_flush(&b) == -1 || b.err)
		return (-1);

	return (b.len);
}
