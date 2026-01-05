#include "main.h"

/**
 * pf_build_digits_ptr - build reversed hex digits (lowercase)
 * @num: number
 * @digits: output reversed digits
 *
 * Return: count
 */
static int pf_build_digits_ptr(unsigned long long num, char *digits)
{
	int i;
	unsigned int d;

	i = 0;
	if (num == 0)
	{
		digits[i++] = '0';
		return (i);
	}

	while (num > 0)
	{
		d = (unsigned int)(num % 16ULL);
		digits[i++] = pf_hex_digit(d, 0);
		num /= 16ULL;
	}
	return (i);
}

/**
 * pf_print_pointer - prints %p
 * @b: buffer
 * @f: format
 * @ap: args
 *
 * Return: 0 on success, -1 on failure
 */
int pf_print_pointer(pf_buffer_t *b, pf_format_t *f, va_list *ap)
{
	unsigned long long num;
	char digits[65];
	int dlen, pad, total;
	const char *nil;

	nil = "(nil)";
	num = (unsigned long long)(unsigned long)va_arg(*ap, void *);

	if (num == 0)
	{
		total = 5;
		pad = (f->width > total) ? (f->width - total) : 0;

		if (!(f->flags & PF_F_MINUS))
		{
			if (pf_buf_pad(b, ' ', pad) == -1)
			{
				return (-1);
			}
		}

		if (pf_buf_putn(b, nil, 5) == -1)
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

	dlen = pf_build_digits_ptr(num, digits);

	/* prefix "0x" always, width applies, zero flag allowed unless '-' */
	total = 2 + dlen;
	pad = (f->width > total) ? (f->width - total) : 0;

	if (!(f->flags & PF_F_MINUS))
	{
		if (pf_buf_pad(b, ' ', pad) == -1)
		{
			return (-1);
		}
	}

	if (pf_buf_putn(b, "0x", 2) == -1)
	{
		return (-1);
	}

	while (dlen > 0)
	{
		if (pf_buf_putc(b, digits[--dlen]) == -1)
		{
			return (-1);
		}
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
