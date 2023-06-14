#include <criterion/criterion.h>

#include "circular_buffer.h"

Test(write, writes_to_empty_circular_buffer)
{
    circular_buffer_t *buffer = circular_buffer_create(".");
    char *abc;

    circular_buffer_write(buffer, "a.");
    circular_buffer_write(buffer, "b.");
    abc = circular_buffer_read(buffer);
    cr_assert_str_eq(abc, "a.");
    abc = circular_buffer_read(buffer);
    cr_assert_str_eq(abc, "b.");
    cr_assert_eq(circular_buffer_read(buffer), NULL);
}
