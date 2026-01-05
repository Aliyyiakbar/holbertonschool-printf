#include "main.h"

/**
 * pf_build_digits - build reversed digits of num in base
 * @num: number
 * @base: base
 * @upper: uppercase hex
 * @digits: output reversed digits
 *
 * Return: digit count
 */
static int pf_build_digits(unsigned long num, int base, int upper, char *digits)
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
		d = (unsigned int)(num % (unsigned long)base);
		digits[i++] = pf_hex_digit(d, upper);
		num /= (unsigned long)base;
	}
	return (i);
}

/**
 * pf_print_num_core - print number with flags/width/precision
 * @b: buffer
 * @f: format
 * @digits: reversed digits array
 * @dlen: digits length (reversed)
 * @sign: sign char or 0
 * @pref: prefix string
 * @plen: prefix length
 *
 * Return: 0 on success, -1 on failure
 */
static int pf_print_num_core(pf_buffer_t *b, pf_format_t *f, char *digits,
			    int dlen, char sign, const char *pref, int plen)
{
	int zeros, total, pad;
	char padc;

	zeros = 0;
	if (f->precision >= 0 && f->precision > dlen)
		zeros = f->precision - dlen;

	total = dlen + zeros + plen + (sign ? 1 : 0);

	pad = 0;
	if (f->width > total)
		pad = f->width - total;

	padc = ' ';
	if ((f->flags & PF_F_ZERO) && !(f->flags & PF_F_MINUS) && f->precision < 0)
		padc = '0';

	if (!(f->flags & PF_F_MINUS) && padc == ' ')
		if (pf_buf_pad(b, ' ', pad) == -1)
			return (-1);

	if (sign)
		if (pf_buf_putc(b, sign) == -1)
			return (-1);

	if (plen)
		if (pf_buf_putn(b, pref, plen) == -1)
			return (-1);

	if (!(f->flags & PF_F_MINUS) && padc == '0')
		if (pf_buf_pad(b, '0', pad) == -1)
			return (-1);

	if (pf_buf_pad(b, '0', zeros) == -1)
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

/**
 * pf_print_signed - handle %d/%i with l/h
 * @b: buffer
 * @f: format
 * @ap: args
 *
 * Return: 0 on success, -1 on failure
 */
int pf_print_signed(pf_buffer_t *b, pf_format_t *f, va_list *ap)
{
	long n;
	unsigned long num;
	char digits[65];
	int dlen;
	char sign;

	if (f->length == 'l')
		n = va_arg(*ap, long);
	else if (f->length == 'h')
		n = (short)va_arg(*ap, int);
	else
		n = va_arg(*ap, int);

	sign = 0;
	if (n < 0)
	{
		sign = '-';
		num = (unsigned long)(-(n + 1));
		num = num + 1;
	}
	else
	{
		if (f->flags & PF_F_PLUS)
			sign = '+';
		if (sign == 0 && (f->flags & PF_F_SPACE))
			sign = ' ';
		num = (unsigned long)n;
	}

	if (num == 0 && f->precision == 0)
		return (pf_print_num_core(b, f, digits, 0, sign, "", 0));

	dlen = pf_build_digits(num, 10, 0, digits);
	return (pf_print_num_core(b, f, digits, dlen, sign, "", 0));
}

/**
 * pf_print_unsigned_base - handle %u %o %x %X (with l/h)
 * @b: buffer
 * @f: format
 * @ap: args
 * @base: base
 * @upper: uppercase hex
 *
 * Return: 0 on success, -1 on failure
 */
int pf_print_unsigned_base(pf_buffer_t *b, pf_format_t *f, va_list *ap,
			   int base, int upper)
{
	unsigned long num;
	char digits[65];
	int dlen;
	const char *pref;
	int plen;

	if (f->length == 'l')
		num = va_arg(*ap, unsigned long);
	else if (f->length == 'h')
		num = (unsigned short)va_arg(*ap, unsigned int);
	else
		num = va_arg(*ap, unsigned int);

	pref = "";
	plen = 0;

	if ((f->flags & PF_F_HASH) && num != 0)
	{
		if (base == 8)
		{
			pref = "0";
			plen = 1;
		}
		if (base == 16 && !upper)
		{
			pref = "0x";
			plen = 2;
		}
		if (base == 16 && upper)
		{
			pref = "0X";
			plen = 2;
		}
	}

	if (num == 0 && f->precision == 0)
	{
		if ((f->flags & PF_F_HASH) && base == 8)
		{
			digits[0] = '0';
			return (pf_print_num_core(b, f, digits, 1, 0, "", 0));
		}
		return (pf_print_num_core(b, f, digits, 0, 0, "", 0));
	}

	dlen = pf_build_digits(num, base, upper, digits);
	return (pf_print_num_core(b, f, digits, dlen, 0, pref, plen));
}

/**
 * pf_print_binary - prints %b (unsigned int to binary)
 * @b: buffer
 * @f: format
 * @ap: args
 *
 * Return: 0 on success, -1 on failure
 */
int pf_print_binary(pf_buffer_t *b, pf_format_t *f, va_list *ap)
{
	unsigned long num;
	char digits[65];
	int dlen;

	num = (unsigned long)va_arg(*ap, unsigned int);

	if (num == 0 && f->precision == 0)
		return (pf_print_num_core(b, f, digits, 0, 0, "", 0));

	dlen = pf_build_digits(num, 2, 0, digits);
	return (pf_print_num_core(b, f, digits, dlen, 0, "", 0));
}
