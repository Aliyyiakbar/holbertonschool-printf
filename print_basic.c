#include "main.h"

/**
 * pf_print_char - print %c with width
 * @b: buffer
 * @f: format
 * @ap: args
 *
 * Return: 0 on success, -1 on failure
 */
int pf_print_char(pf_buffer_t *b, pf_format_t *f, va_list *ap)
{
	char c;
	int pad;

	c = (char)va_arg(*ap, int);
	pad = (f->width > 1) ? (f->width - 1) : 0;

	if (!(f->flags & PF_F_MINUS))
	{
		if (pf_buf_pad(b, ' ', pad) == -1)
		{
			return (-1);
		}
	}

	if (pf_buf_putc(b, c) == -1)
	{
		return (-1);
	}

	if (f->flags & PF_F_MINUS)
	{
		if (pf_buf_pad(b, ' ', pad) == -1)
		{
			return (-1);
		}
	}

	return (0);
}

/**
 * pf_print_string - print %s with width/precision
 * @b: buffer
 * @f: format
 * @ap: args
 *
 * Return: 0 on success, -1 on failure
 */
int pf_print_string(pf_buffer_t *b, pf_format_t *f, va_list *ap)
{
	char *s;
	int len, out, pad;

	s = va_arg(*ap, char *);
	if (s == NULL)
	{
		s = "(null)";
	}

	len = pf_strlen(s);
	out = len;

	if (f->precision >= 0 && f->precision < out)
	{
		out = f->precision;
	}

	pad = (f->width > out) ? (f->width - out) : 0;

	if (!(f->flags & PF_F_MINUS))
	{
		if (pf_buf_pad(b, ' ', pad) == -1)
		{
			return (-1);
		}
	}

	if (pf_buf_putn(b, s, out) == -1)
	{
		return (-1);
	}

	if (f->flags & PF_F_MINUS)
	{
		if (pf_buf_pad(b, ' ', pad) == -1)
		{
			return (-1);
		}
	}

	return (0);
}

/**
 * pf_print_percent - print %%
 * @b: buffer
 * @f: format
 * @ap: args (unused)
 *
 * Return: 0 on success, -1 on failure
 */
int pf_print_percent(pf_buffer_t *b, pf_format_t *f, va_list *ap)
{
	int pad;

	(void)ap;
	pad = (f->width > 1) ? (f->width - 1) : 0;

	if (!(f->flags & PF_F_MINUS))
	{
		if (pf_buf_pad(b, (f->flags & PF_F_ZERO) ? '0' : ' ', pad) == -1)
		{
			return (-1);
		}
	}

	if (pf_buf_putc(b, '%') == -1)
	{
		return (-1);
	}

	if (f->flags & PF_F_MINUS)
	{
		if (pf_buf_pad(b, ' ', pad) == -1)
		{
			return (-1);
		}
	}

	return (0);
}
