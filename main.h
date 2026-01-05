#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

#define PF_BUF_SIZE 1024

#define PF_F_MINUS  (1 << 0)
#define PF_F_PLUS   (1 << 1)
#define PF_F_SPACE  (1 << 2)
#define PF_F_HASH   (1 << 3)
#define PF_F_ZERO   (1 << 4)

typedef struct pf_buffer_s
{
	char buf[PF_BUF_SIZE];
	int idx;
	int len;
	int err;
} pf_buffer_t;

typedef struct pf_format_s
{
	int flags;
	int width;
	int precision;
	char length;
	char spec;
} pf_format_t;

int _printf(const char *format, ...);

/* buffer */
void pf_buf_init(pf_buffer_t *b);
int pf_buf_flush(pf_buffer_t *b);
int pf_buf_putc(pf_buffer_t *b, char c);
int pf_buf_putn(pf_buffer_t *b, const char *s, int n);
int pf_buf_pad(pf_buffer_t *b, char c, int n);

/* utils */
int pf_is_digit(char c);
int pf_strlen(const char *s);
int pf_is_printable(unsigned char c);
char pf_hex_digit(unsigned int v, int upper);
char pf_rot13_char(char c);

/* parse + dispatch */
int pf_parse(const char **p, pf_format_t *f, va_list *ap);
int pf_handle(pf_buffer_t *b, pf_format_t *f, va_list *ap);

/* printers */
int pf_print_char(pf_buffer_t *b, pf_format_t *f, va_list *ap);
int pf_print_string(pf_buffer_t *b, pf_format_t *f, va_list *ap);
int pf_print_percent(pf_buffer_t *b, pf_format_t *f, va_list *ap);

int pf_print_signed(pf_buffer_t *b, pf_format_t *f, va_list *ap);
int pf_print_unsigned_base(pf_buffer_t *b, pf_format_t *f, va_list *ap,
			   int base, int upper);
int pf_print_binary(pf_buffer_t *b, pf_format_t *f, va_list *ap);
int pf_print_pointer(pf_buffer_t *b, pf_format_t *f, va_list *ap);

int pf_print_S(pf_buffer_t *b, pf_format_t *f, va_list *ap);
int pf_print_reverse(pf_buffer_t *b, pf_format_t *f, va_list *ap);
int pf_print_rot13(pf_buffer_t *b, pf_format_t *f, va_list *ap);

#endif
