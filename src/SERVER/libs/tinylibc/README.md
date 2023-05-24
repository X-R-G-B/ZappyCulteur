# (my) TinyLibC

**just some basic functions (and why not, some non basic)**

## Source

[![Makefile Check](https://github.com/Saverio976/tinylibc/actions/workflows/makefile.yml/badge.svg?branch=main)](https://github.com/Saverio976/tinylibc/actions/workflows/makefile.yml)
[github repo](https://github.com/Saverio976/tinylibc)

## DOC

use doxygen:
- doc available at [doc](https://saverio976.github.io/tinylibc/)
- each function have doc with the (auto)completion of your IDE

## Example

- using **list**
`./examples/reamde.c`
```c
#include "tlcllists.h"
#include "tlcstrings.h"
#include "tlcutils.h"
#include "tlcstdios.h"

int main(int ac, const char *av[])
{
    list_t *list = list_create();

    x_puts("Hewwo fwiends!!", true);
    for (int i = 0; i < ac; i++) {
        list = list_append(list, x_strdup(av[i]), &free_ifnotnull, NULL);
    }
    // Now, you have a list of av
    for (L_EACH(x, list)) { // for each node named x in the list list
        // do something with x
        // more function and macro to
        // https://saverio976.github.io/tinylibc/d8/d07/tlcllists_8h.html
        x_printf("av[%d] = %s\n", list_find_ptrnode(list, x), L_DATA(x));
    }
    return (0);
}
```

```bash
gcc examples/readme.c -Iincludes/ -L. -ltinylibc
./a.out
```

## Install

```bash
git clone https://github.com/Saverio976/tinylibc.git
cd tinylibc
```

## Build

```bash
make
```
this will output the file  `libtinylibc.a`

*object are compiled to `obj` folder (and makefile dont relink !!!) (i'm proud of that xD)*

## Use it

compile your c code (change value of CC to your c compiler and PATHTINYLIBC to the right value):
```bash
export CC=gcc
export PATHTINYLIBC=path/where/libtinylibc.a/is/
$CC -L $PATHTINYLIBC -ltinylibc -I $PATHTINYLIBC/includes
```
