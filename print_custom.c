#include "main.h"

/**
 * pf_print_S - prints %S with \\xHH for non-printables
 * @b: buffer
 * @f: format
 * @ap: args
 *
 * Return: 0 on success, -1 on failure
 */
int pf_print_S(pf_buffer_t *b, pf_format_t *f, va_list *ap)
{
	char *s;
	int i, out, pad, total;
	unsigned char c;

	s = va_arg(*ap, char *);
	if (s == NULL)
		s = "(null)";

	out = pf_strlen(s);
	if (f->precision >= 0 && f->precision < out)
		out = f->precision;

	total = 0;
	i = 0;
	while (i < out)
	{
		c = (unsigned char)s[i];
		if (pf_is_printable(c))
			total += 1;
		else
			total += 4;
		i++;
	}

	pad = 0;
	if (f->width > total)
		pad = f->width - total;

	if (!(f->flags & PF_F_MINUS))
		if (pf_buf_pad(b, ' ', pad) == -1)
			return (-1);

	i = 0;
	while (i < out)
	{
		c = (unsigned char)s[i];
		if (pf_is_printable(c))
		{
			if (pf_buf_putc(b, (char)c) == -1)
				return (-1);
		}
		else
		{
			if (pf_buf_putc(b, '\\') == -1)
				return (-1);
			if (pf_buf_putc(b, 'x') == -1)
				return (-1);
			if (pf_buf_putc(b, pf_hex_digit((c >> 4) & 0xF, 1)) == -1)
				return (-1);
			if (pf_buf_putc(b, pf_hex_digit(c & 0xF, 1)) == -1)
				return (-1);
		}
		i++;
	}

	if (f->flags & PF_F_MINUS)
		if (pf_buf_pad(b, ' ', pad) == -1)
			return (-1);

	return (0);
}

/**
 * pf_print_reverse - prints %r (reversed string)
 * @b: buffer
 * @f: format
 * @ap: args
 *
 * Return: 0 on success, -1 on failure
 */
int pf_print_reverse(pf_buffer_t *b, pf_format_t *f, va_list *ap)
{
	char *s;
	int len, out, pad, i;

	s = va_arg(*ap, char *);
	if (s == NULL)
		s = "(null)";

	len = pf_strlen(s);
	out = len;
	if (f->precision >= 0 && f->precision < out)
		out = f->precision;

	pad = 0;
	if (f->width > out)
		pad = f->width - out;

	if (!(f->flags & PF_F_MINUS))
		if (pf_buf_pad(b, ' ', pad) == -1)
			return (-1);

	i = out - 1;
	while (i >= 0)
	{
		if (pf_buf_putc(b, s[i]) == -1)
			return (-1);
		i--;
	}

	if (f->flags & PF_F_MINUS)
		if (pf_buf_pad(b, ' ', pad) == -1)
			return (-1);

	return (0);
}

/**
 * pf_print_rot13 - prints %R (rot13)
 * @b: buffer
 * @f: format
 * @ap: args
 *
 * Return: 0 on success, -1 on failure
 */
int pf_print_rot13(pf_buffer_t *b, pf_format_t *f, va_list *ap)
{
	char *s;
	int len, out, pad, i;
	char c;

	s = va_arg(*ap, char *);
	if (s == NULL)
		s = "(null)";

	len = pf_strlen(s);
	out = len;
	if (f->precision >= 0 && f->precision < out)
		out = f->precision;

	pad = 0;
	if (f->width > out)
		pad = f->width - out;

	if (!(f->flags & PF_F_MINUS))
		if (pf_buf_pad(b, ' ', pad) == -1)
			return (-1);

	i = 0;
	while (i < out)
	{
		c = pf_rot13_char(s[i]);
		if (pf_buf_putc(b, c) == -1)
			return (-1);
		i++;
	}

	if (f->flags & PF_F_MINUS)
		if (pf_buf_pad(b, ' ', pad) == -1)
			return (-1);

	return (0);
}
