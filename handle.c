#include "main.h"

/**
 * pf_handle - dispatch specifier to printer
 * @b: buffer
 * @f: format
 * @ap: args
 *
 * Return: 0 on success, -1 on failure
 */
int pf_handle(pf_buffer_t *b, pf_format_t *f, va_list *ap)
{
	if (f->spec == 'c')
		return (pf_print_char(b, f, ap));
	if (f->spec == 's')
		return (pf_print_string(b, f, ap));
	if (f->spec == '%')
		return (pf_print_percent(b, f, ap));

	if (f->spec == 'd' || f->spec == 'i')
		return (pf_print_signed(b, f, ap));
	if (f->spec == 'u')
		return (pf_print_unsigned_base(b, f, ap, 10, 0));
	if (f->spec == 'o')
		return (pf_print_unsigned_base(b, f, ap, 8, 0));
	if (f->spec == 'x')
		return (pf_print_unsigned_base(b, f, ap, 16, 0));
	if (f->spec == 'X')
		return (pf_print_unsigned_base(b, f, ap, 16, 1));

	if (f->spec == 'b')
		return (pf_print_binary(b, f, ap));
	if (f->spec == 'S')
		return (pf_print_S(b, f, ap));
	if (f->spec == 'p')
		return (pf_print_pointer(b, f, ap));
	if (f->spec == 'r')
		return (pf_print_reverse(b, f, ap));
	if (f->spec == 'R')
		return (pf_print_rot13(b, f, ap));

	/* unknown spec: print '%' then spec */
	if (pf_buf_putc(b, '%') == -1)
		return (-1);
	if (pf_buf_putc(b, f->spec) == -1)
		return (-1);

	return (0);
}
