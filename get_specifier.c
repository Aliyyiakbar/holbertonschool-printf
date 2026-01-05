#include "main.h"

/**
 * get_specifier - returns the right function for a specifier
 * @c: specifier character
 *
 * Return: pointer to a function, or NULL if not found
 */
int (*get_specifier(char c))(va_list)
{
	if (c == 'c')
	{
		return (print_char);
	}
	if (c == 's')
	{
		return (print_string);
	}
	if (c == '%')
	{
		return (print_percent);
	}
	if (c == 'd' || c == 'i')
	{
		return (print_int);
	}
	return (NULL);
}
