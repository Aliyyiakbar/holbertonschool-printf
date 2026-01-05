#include "main.h"

/**
 * pf_build_ptr_digits - build reversed lowercase hex digits
 * @num: number
 * @digits: output reversed digits
 *
 * Return: digit count
 */
static int pf_build_ptr_digits(unsigned long num, char *digits)
{
	int i;
	unsigned int d;

	i = 0;
	while (num > 0)
	{
		d = (unsigned int)(num % 16UL);
		digits[i++] = pf_hex_digit(d, 0);
		num /= 16UL;
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
	unsigned long num;
	char digits[65];
	int dlen, pad, total;
	char padc;
	const char *nil;

	nil = "(nil)";
	num = (unsigned long)va_arg(*ap, void *);

	if (num == 0)
	{
		pad = 0;
		if (f->width > 5)
			pad = f->width - 5;

		if (!(f->flags & PF_F_MINUS))
			if (pf_buf_pad(b, ' ', pad) == -1)
				return (-1);

		if (pf_buf_putn(b, nil, 5) == -1)
			return (-1);

		if (f->flags & PF_F_MINUS)
			if (pf_buf_pad(b, ' ', pad) == -1)
				return (-1);

		return (0);
	}

	dlen = pf_build_ptr_digits(num, digits);

	total = 2 + dlen; /* "0x" + digits */
	pad = 0;
	if (f->width > total)
		pad = f->width - total;

	padc = ' ';
	if ((f->flags & PF_F_ZERO) && !(f->flags & PF_F_MINUS))
		padc = '0';

	if (!(f->flags & PF_F_MINUS) && padc == ' ')
		if (pf_buf_pad(b, ' ', pad) == -1)
			return (-1);

	if (pf_buf_putn(b, "0x", 2) == -1)
		return (-1);

	if (!(f->flags & PF_F_MINUS) && padc == '0')
		if (pf_buf_pad(b, '0', pad) == -1)
			return (-1);

	while (dlen > 0)
	{
		if (pf_buf_putc(b, digits[--dlen]) == -1)
			return (-1);
	}

	if (f->flags & PF_F_MINUS)
		if (pf_buf_pad(b, ' ', pad) == -1)
			return (-1);

	return (0);
}
