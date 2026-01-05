#include "main.h"

/**
 * pf_init_format - init format structure
 * @f: format
 */
static void pf_init_format(pf_format_t *f)
{
	f->flags = 0;
	f->width = 0;
	f->precision = -1;
	f->length = 0;
	f->spec = 0;
}

/**
 * pf_parse_flags - parse flags
 * @p: pointer to format pointer
 * @f: format
 */
static void pf_parse_flags(const char **p, pf_format_t *f)
{
	while (**p == '-' || **p == '+' || **p == ' ' || **p == '#' || **p == '0')
	{
		if (**p == '-')
			f->flags |= PF_F_MINUS;
		if (**p == '+')
			f->flags |= PF_F_PLUS;
		if (**p == ' ')
			f->flags |= PF_F_SPACE;
		if (**p == '#')
			f->flags |= PF_F_HASH;
		if (**p == '0')
			f->flags |= PF_F_ZERO;

		(*p)++;
	}
}

/**
 * pf_parse_width - parse width
 * @p: pointer to format pointer
 * @f: format
 * @ap: args
 */
static void pf_parse_width(const char **p, pf_format_t *f, va_list *ap)
{
	int w;

	if (**p == '*')
	{
		w = va_arg(*ap, int);
		if (w < 0)
		{
			f->flags |= PF_F_MINUS;
			w = -w;
		}
		f->width = w;
		(*p)++;
		return;
	}

	while (pf_is_digit(**p))
	{
		f->width = f->width * 10 + (**p - '0');
		(*p)++;
	}
}

/**
 * pf_parse_precision - parse precision
 * @p: pointer to format pointer
 * @f: format
 * @ap: args
 */
static void pf_parse_precision(const char **p, pf_format_t *f, va_list *ap)
{
	int pr;

	if (**p != '.')
		return;

	(*p)++;
	f->precision = 0;

	if (**p == '*')
	{
		pr = va_arg(*ap, int);
		if (pr >= 0)
			f->precision = pr;
		else
			f->precision = -1;
		(*p)++;
		return;
	}

	while (pf_is_digit(**p))
	{
		f->precision = f->precision * 10 + (**p - '0');
		(*p)++;
	}
}

/**
 * pf_parse - parse after '%' and fill format
 * @p: pointer to format pointer (points after '%')
 * @f: format output
 * @ap: variadic args
 *
 * Return: 0 on success, -1 on error (missing spec)
 */
int pf_parse(const char **p, pf_format_t *f, va_list *ap)
{
	pf_init_format(f);
	pf_parse_flags(p, f);
	pf_parse_width(p, f, ap);
	pf_parse_precision(p, f, ap);

	if (**p == 'l' || **p == 'h')
	{
		f->length = **p;
		(*p)++;
	}

	if (**p == '\0')
		return (-1);

	f->spec = **p;
	(*p)++;
	return (0);
}
