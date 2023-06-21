#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include <stdbool.h>

#include "circular_buffer.h"

Test(empty, empty_a_circular_buffer)
{
    circular_buffer_t *buffer = circular_buffer_create(".");
    cr_assert_not_null(buffer);
    cr_assert_eq(circular_buffer_is_empty(buffer), true);
}

Test(empty, not_empty)
{
    circular_buffer_t *buffer = circular_buffer_create(".");
    cr_assert_not_null(buffer);
    cr_assert_eq(circular_buffer_is_empty(buffer), true);
    circular_buffer_write(buffer, "a");
    cr_assert_eq(circular_buffer_is_empty(buffer), false);
}

Test(empty, not_empty_and_to_empty)
{
    circular_buffer_t *buffer = circular_buffer_create(".");

    cr_assert_not_null(buffer);
    cr_assert_eq(circular_buffer_is_empty(buffer), true);
    circular_buffer_write(buffer, "a.");
    cr_assert_eq(circular_buffer_is_empty(buffer), false);
    cr_assert_not_null(circular_buffer_read(buffer));
    cr_assert_eq(circular_buffer_is_empty(buffer), true);
}

Test(is_read_ready, is_read_ready)
{
    circular_buffer_t *buffer = circular_buffer_create(".");

    cr_assert_not_null(buffer);
    cr_assert_eq(circular_buffer_is_read_ready(buffer), false);
    circular_buffer_write(buffer, "a.");
    cr_assert_eq(circular_buffer_is_read_ready(buffer), true);
    circular_buffer_read(buffer);
    cr_assert_eq(circular_buffer_is_read_ready(buffer), false);
}
