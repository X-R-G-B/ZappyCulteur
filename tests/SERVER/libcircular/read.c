#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#include "circular_buffer.h"

Test(read, reads_from_empty_circular_buffer)
{
    circular_buffer_t *buffer = circular_buffer_create(".");

    cr_assert_eq(circular_buffer_read(buffer), NULL);
}

Test(read, reads_from_ok_buffer)
{
    circular_buffer_t *buffer = circular_buffer_create(".");
    char *abc;

    circular_buffer_write(buffer, "a.");
    abc = circular_buffer_read(buffer);
    cr_assert_str_eq(abc, "a.");
}

Test(read, reads_from_not_empty_buffer_but_not_ok)
{
    circular_buffer_t *buffer = circular_buffer_create(".");

    circular_buffer_write(buffer, "a");
    cr_assert_eq(circular_buffer_read(buffer), NULL);
}

Test(read_multiple, basic_1)
{
    circular_buffer_t *buffer = circular_buffer_create(".");

    circular_buffer_write(buffer, "a.b.");
    cr_assert_str_eq(circular_buffer_read_multiple(buffer), "a.b.");
    cr_assert_eq(circular_buffer_read(buffer), NULL);
}

Test(read_multiple, basic_2)
{
    circular_buffer_t *buffer = circular_buffer_create(".");

    circular_buffer_write(buffer, "a");
    circular_buffer_write(buffer, "b");
    circular_buffer_write(buffer, "c");
    circular_buffer_write(buffer, "d.");
    circular_buffer_write(buffer, "e.");
    cr_assert_str_eq(circular_buffer_read_multiple(buffer), "abcd.e.");
    cr_assert_eq(circular_buffer_read(buffer), NULL);
}

Test(read_multiple, basic_3)
{
    circular_buffer_t *buffer = circular_buffer_create(".");

    circular_buffer_write(buffer, "a");
    circular_buffer_write(buffer, "bbdede");
    circular_buffer_write(buffer, "c");
    circular_buffer_write(buffer, "dede.");
    circular_buffer_write(buffer, "edezf");
    circular_buffer_write(buffer, ".");
    cr_assert_str_eq(circular_buffer_read_multiple(buffer), "abbdedecdede.edezf.");
    cr_assert_eq(circular_buffer_read(buffer), NULL);
}
