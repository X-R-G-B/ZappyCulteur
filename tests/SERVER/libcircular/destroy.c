#include <criterion/criterion.h>
#include <criterion/internal/test.h>

#include "circular_buffer.h"

Test(destroy, destroys_null)
{
    circular_buffer_destroy(NULL);
}

Test(destroy, destroys_a_circular_buffer)
{
    circular_buffer_t *buffer = circular_buffer_create(".");
    cr_assert_not_null(buffer);
    circular_buffer_destroy(buffer);
}
