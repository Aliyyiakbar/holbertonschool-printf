# Holberton School – printf

This repository contains our C implementation of a custom `_printf` function for the
Holberton School **C - printf** project. The goal is to understand how `printf` works
under the hood by handling format parsing, variadic arguments, and printing different
data types using `write()`.

## Requirements

- OS: Ubuntu 20.04 LTS
- Compiler: gcc
- Flags: -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format
- Style: Betty
- No global variables
- Max 5 functions per file
- No main.c files in the project root (keep tests in a separate folder)

## Authorized Functions / Macros

- `write`
- `malloc`, `free`
- `va_start`, `va_end`, `va_copy`, `va_arg`

## Files

- main.h — prototypes, structs, and macros
- _printf.c — main entry point (format parsing + dispatch)
- parse.c / handle.c — helpers for parsing and selecting handlers
- buffer.c — buffered writing helpers (if used)
- print_basic.c — printing for basic specifiers (c, s, %)
- print_int.c — printing for integers (d, i, u, o, x, X, etc.)
- print_pointer.c — printing for pointers (p)
- print_custom.c — custom/advanced specifiers (project advanced tasks)
- utils.c — shared helpers (length, conversions, etc.)
- man_3_printf — manual page for _printf

## Supported Format Specifiers

Minimum required:
- `%c` — character
- `%s` — string
- `%%` — percent sign

Project includes additional specifiers from later tasks (like d/i, u, o, x/X, b, p, r, R, S, + flags, etc.),
depending on the task level completed in the repository.

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c -o printf
```

## Usage

Example test file:

```cpp
#include <stdio.h>
#include "main.h"

int main(void)
{
    _printf("Hello %s!\n", "world");
    _printf("Number: %d\n", 42);
    _printf("Percent: %%\n");
    return (0);
}
```

Compile and run:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c main.c -o test
./test
```

## Authors

Aliyyiakbar Shirinli
Amal Shafiyev
